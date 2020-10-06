#include "ogg_decoder.h"
#include <stdio.h>
#include <stdlib.h>
int read_ogg_page(FILE * file,ogg_sync_state * sync_state,ogg_page * page){
    /**read a ogg page from a file. */
    int rc=0;
    long cache_size = 4 * 1024;
    char* buffer=NULL;
	size_t bytes=0;
    do {
        buffer = ogg_sync_buffer(sync_state, cache_size);
        if(!buffer){
            printf("Failed to allocate new buffer for decoding.\n");
            continue;
        }
        bytes = fread(buffer, 1, cache_size, file);
        ogg_sync_wrote(sync_state, bytes);
        if(bytes!=cache_size)  {   //end of file
            //printf("End of file, exiting.\n");
            rc=ogg_sync_pageout(sync_state, page);
            if(rc==1){
                return 0;  //end of file and the last page is returned.
            }else{
                printf("End of file is reached, but some error occurred when reading the last page.");
                return -2; //end of file and skipped some bytes.
            }
        }
    }while(ogg_sync_pageout(sync_state, page)!=1);
    return 1;
}
ogg_decoding_context * init_decoding_context(){
    ogg_decoding_context * decoding_context=malloc(sizeof(ogg_decoding_context));
    decoding_context->sync_state=malloc(sizeof(ogg_sync_state));
    decoding_context->stream_state=NULL;

    //memset(decoding_context,0,sizeof(ogg_decoding_context));
    memset(decoding_context->sync_state,0,sizeof(ogg_sync_state));
    //memset(decoding_context->stream_state,0,sizeof(ogg_stream_state));

    ogg_sync_init(decoding_context->sync_state);
    //ogg_stream_init(decoding_context->stream_state,0);
    return decoding_context;
}
void destroy_decoding_context(ogg_decoding_context * decoding_context){
    if(decoding_context->sync_state)
        ogg_sync_destroy(decoding_context->sync_state);
    if(decoding_context->stream_state)
        ogg_stream_destroy(decoding_context->stream_state);
    free(decoding_context);
}
int write_page_to_stream(FILE * file,ogg_decoding_context * decoding_context){
    int temp_rc=0;
    ogg_sync_state * sync_state=decoding_context->sync_state;
    ogg_stream_state * stream_state=decoding_context->stream_state;
	ogg_page * page=malloc(sizeof(ogg_page));
	memset(page,0,sizeof(ogg_page));
    int rc=0;
    rc=read_ogg_page(file,sync_state, page);
    if(!stream_state){
        stream_state=malloc(sizeof(ogg_stream_state));
        decoding_context->stream_state=stream_state;
        ogg_stream_init(stream_state,ogg_page_serialno(page));
    }
    if(rc==1){ //page is available normally.
        temp_rc=ogg_stream_pagein(stream_state, page);
    }else if(rc==0){ //end of file and the last page is returned.
        //write last page to stream;
        temp_rc=ogg_stream_pagein(stream_state, page);
    }else{  //rc==-2 end of file and skipped some bytes.
    }
    return rc;
}
int  read_next_packets(FILE * file,ogg_decoding_context * decoding_context,ogg_packet *  packets[])
{
    /*this method get an array of packets from the given file and it will allocate the memory for available packets,
    which should be freed manually after the packets are processed. packets in the array is valid only if the value of the pointer is not NULL

    Return number of packets*/
    int rc1=0;
    do
    {
        rc1=write_page_to_stream(file,decoding_context);
        if(rc1==0)   //last page is available.
        {
            read_packets_in_current_page(decoding_context->stream_state,packets);
            return -1; //indicates last page.
        }
        else if(rc1==-2)
        {
            break;
        }
        else   // normal page is available.
        {
            return read_packets_in_current_page(decoding_context->stream_state,packets);
        }
    }
    while(rc1==1);
    return -2;
}

int read_packets_in_current_page(ogg_stream_state * stream_state, ogg_packet * packets []){
    /**read all packets in the current page and return the number of packets.*/
    int rc=0, pi=0;
    ogg_packet * temp_packet=NULL;
    for(int i=0;i<MAX_PACKET_NUM;i++)
        packets[i]=NULL;
    do{
            temp_packet=malloc(sizeof(ogg_packet));
            rc=ogg_stream_packetout(stream_state, temp_packet);
            if(rc==1){ // a packet is available.
                packets[pi]=temp_packet;
                pi++;
            }else{
                free(temp_packet);
            }
            if(pi>=MAX_PACKET_NUM){
                printf("[error] Array used to arrange packets is full..\n");
                exit(10);
            }
    }while(rc!=0);//no sufficient data is available to construct a packet.
    return pi;
}
