#include "ogg_encoder_test.h"
#include "ogg_encoder.h"
#include "hex_dump.h"
#include <stdio.h>
#include <stdlib.h>
#include <ogg/ogg.h>
#include "ogg_test.h"
#include "ogg_encoder.h"
#include <string.h>
#include "ogg_decoder.h"
/*
int mainx(int argc, char *argv[]);
ogg_stream_state * stream_state=NULL;
int main1(int argc, char *argv[])
{
    FILE * file=NULL;
    int rc=0;
    ogg_page * page_list[10]={NULL};
    for(int i=0;i<10;i++){
        page_list[i]=malloc(sizeof(ogg_page));
        memset(page_list[i],0,sizeof(ogg_page));
    }
    ogg_packet packet;
    ogg_encoding_context * encoding_context=init_encoding_context();
    int packet_count=0;
    if(argc!=2){
        printf("invalid usage\n");
        exit(1);
    }

    file= fopen(argv[1], "rb+");
    while((rc=read_next_packet(file,&packet))==1){
        packet_count++;
        get_next_page(encoding_context,&packet,page_list,10);
        printf("packet NO %I64d, length is %I32d\n",packet.packetno,packet.bytes);
    }
    if(rc==0){  //normal end of file and eof page.
        packet_count++;
        printf("packet NO %I64d, length is %I32d\n",packet.packetno,packet.bytes);
    }
    destroy_encoding_context(encoding_context);
    free_obj(page_list,10);
    //get_next_page(NULL,page_list,10);
    printf("total packet count is %d\n",packet_count);
    fclose(file);
    return 0;
}
void free_obj(ogg_page * page_list[],int size){
    if(page_list!=NULL){
        for(int i=0;i<size;i++)
            free(page_list[i]);
    }
}

int mainx(int argc, char *argv[]){
    ogg_packet packet=init_bos_packet();
    ogg_page * page_list[10]={NULL};
    //get_next_page(&packet,page_list,10);
    //hexDump("header",page_list[0]->header,page_list[0]->header_len);
    return 0;
}
ogg_packet init_bos_packet(){
    ogg_packet packet;
    packet.packet=NULL;
    packet.bytes=0;
    packet.b_o_s=1;
    packet.e_o_s=0;
    packet.granulepos=-1;
    packet.packetno=1;
    return packet;
}
*/
