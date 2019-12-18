
#include <stdio.h>
#include <stdlib.h>
#include <ogg/ogg.h>
#include "ogg_test.h"
ogg_stream_state * stream_state=NULL;
int main(int argc, char *argv[])
{
    FILE * file=NULL;
    int rc=0;
    ogg_packet packet;
    int packet_count=0;
    if(argc!=2){
        printf("invalid usage\n");
        exit(1);
    }
    
    file= fopen(argv[1], "rb+");
    while((rc=read_next_packet(file,&packet))==1){
        packet_count++;
        printf("packet NO %I64d, length is %d\n",packet.packetno,packet.bytes);
    }
    if(rc==0){  //normal end of file and eof page.
        packet_count++;
        printf("packet NO %I64d, length is %d\n",packet.packetno,packet.bytes);
    }
    printf("total packet count is %d\n",packet_count);
    fclose(file);	
}
int read_ogg_page(FILE * file,ogg_sync_state * sync_state,ogg_page * page){
    int rc=0;
    long cache_size = 8 * 1024;
    char* buffer=NULL;
	size_t bytes=0;    
    while ((ogg_sync_pageout(sync_state, page))!=1) {
        buffer = ogg_sync_buffer(sync_state, cache_size);
        bytes = fread(buffer, 1, cache_size, file);
        ogg_sync_wrote(sync_state, bytes);
        if(bytes!=cache_size)  {   //end of file
            //printf("End of file, exiting.\n");
            rc=ogg_sync_pageout(sync_state, page);
            if(rc==1){
                return 0;  //end of file and the last page is returned.
            }else
                return -2; //end of file and skipped some bytes.
        }
    }
    return 1;
}
int write_page_to_stream(FILE * file){
    ogg_sync_state sync_state;
	ogg_page page;
    int rc=0;
	ogg_sync_init(&sync_state);
    rc=read_ogg_page(file,&sync_state,&page);
    if(rc==1){ //page is available normally.
        if(!stream_state){
            stream_state=malloc(sizeof(ogg_stream_state));
            ogg_stream_init(stream_state,ogg_page_serialno(&page));
        }
        ogg_stream_pagein(stream_state,&page);
    }else if(rc==0){ //end of file and the last page is returned.
        //write last page to stream;
        ogg_stream_pagein(stream_state,&page);
    }else{  //rc==-2 end of file and skipped some bytes.
    }
    return rc;
}
int  read_next_packet(FILE * file,ogg_packet  *  packet){
    // -1 if end of file.
      //  1 if a packet was assembled normally. op contains the next packet from the stream.
      int rc=0,rc1=0;
     do{
         rc1=write_page_to_stream(file);
         if(rc1==0){
            ogg_stream_packetout(stream_state, packet);
            break;
         }else if(rc1==-2){
             break;
         }else{
             rc=ogg_stream_packetout(stream_state,packet);
        }
     }while(rc!=1);
     return rc1;   
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
