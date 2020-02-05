#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ogg/ogg.h>
#include "ogg_encoder.h"
ogg_stream_state * stream_state_encoder=NULL;
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
int get_next_page(ogg_packet * packet, ogg_page * pages[10]){
    int page_index=0;
    int rc=0,rc0=0;
    static int packets_in_page=0;
    ogg_page * temp_page=NULL;
    if(!stream_state_encoder){
        stream_state_encoder=malloc(sizeof(ogg_stream_state));
        ogg_stream_init(stream_state_encoder,1);
    }
    for(int i=0;i<10;i++)
        pages[i++]=NULL;
    if(packet==NULL){ //end of page
        temp_page=malloc(sizeof(ogg_page));
        memset(temp_page,0,sizeof(ogg_page));
        temp_page->header=eos_page;
        temp_page->header_len=sizeof(eos_page);
        rc=ogg_stream_pageout(stream_state_encoder,temp_page);
    }
    rc0=ogg_stream_packetin(stream_state_encoder,packet);
    packets_in_page++;
    if(rc0==0){
        do{
            temp_page=malloc(sizeof(ogg_page));
            memset(temp_page,0,sizeof(ogg_page));
            rc=ogg_stream_pageout(stream_state_encoder,temp_page);
            if(rc>0)
                pages[page_index++]=temp_page;
            else if(rc==0 && packets_in_page>=4) { // insufficient data has accumulated to fill a page
                ogg_stream_flush(stream_state_encoder,temp_page); // generate a page forcely.
                pages[page_index++]=temp_page;
                packets_in_page=0;
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