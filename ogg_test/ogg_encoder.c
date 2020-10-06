#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ogg/ogg.h>
#include "ogg_encoder.h"
//ogg_stream_state * stream_state_encoder=NULL;
unsigned char eos_page[]={0x4f,0x67,0x67,0x53, //magic number
0x00, //version
0x04, //header_type_flag
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,//granule_position
0x01,0x00,0x00,0x00,//bitstream_serial_number
0xff,0xff,0xff,0xff,//page_sequence_number
//0x69,0x89,0x7A,0x4E,//CRC_checksum
0x4e,0x7a,0x89,0x69,//CRC_checksum
0x00//number_page_segments
};
int get_next_page(ogg_encoding_context * encoding_context,ogg_packet * packet, ogg_page * pages[], int page_size){
    int page_index=0;
    int rc=0,rc0=0,rc1=0;
    ogg_page * temp_page=NULL;
    ogg_stream_state * stream_state_encoder=encoding_context->stream_state;
    /*
    if(!stream_state_encoder){
        stream_state_encoder=malloc(sizeof(ogg_stream_state));
        ogg_stream_init(stream_state_encoder,1);
    }*/
    for(int i=0;i<page_size;i++){
        pages[i]->header=NULL;
        pages[i]->header_len=0;
        pages[i]->body=NULL;
        pages[i]->body_len=0;
    }
    rc0=ogg_stream_packetin(stream_state_encoder,packet);
    encoding_context->opus_packets_in_page++;
    if(rc0==0){
        do{
            temp_page=malloc(sizeof(ogg_page));
            memset(temp_page,0,sizeof(ogg_page));
            rc=ogg_stream_pageout(stream_state_encoder,temp_page);
            if(rc>0){
                pages[page_index++]=temp_page;
                encoding_context->opus_packets_in_page=0;
            }
            else if(rc==0 && encoding_context->opus_packets_in_page>=1) { // insufficient data has accumulated to fill a page
                rc1=ogg_stream_flush(stream_state_encoder,temp_page); // generate a page forcely.
                pages[page_index++]=temp_page;
                encoding_context->opus_packets_in_page=0;
                break;
            }else{ //rc == 0 , not enough data.
                break;
            }
        }while(rc>0); // a page is generated, more page may be generated.
    }else{
        rc=-1;// failed to do ogg_stream_packetin
    }
    return rc;
}
ogg_encoding_context * init_encoding_context(){
    ogg_stream_state * stream_state=malloc(sizeof(ogg_stream_state));
    ogg_stream_init(stream_state,1);
    ogg_encoding_context * encoding_context=malloc(sizeof(ogg_encoding_context));
    encoding_context->stream_state=stream_state;
    encoding_context->opus_packets_in_page=0;
    return encoding_context;
}
int destroy_encoding_context(ogg_encoding_context * encoding_context){
        int rc=0;
        if(encoding_context->stream_state!=NULL){
            //ogg_stream_state * stream_state=encoding_context->stream_state;
            rc=ogg_stream_destroy(encoding_context->stream_state);
            free(encoding_context);
        }
        return rc;
}
int reset_encoding_context(ogg_encoding_context * encoding_context){
        //int rc=-1;
        if(encoding_context->stream_state!=NULL){
            //ogg_stream_reset(encoding_context->stream_stat;
            ogg_stream_clear(encoding_context->stream_state);
            ogg_stream_init(encoding_context->stream_state,1);
        }
        return 0;
}
