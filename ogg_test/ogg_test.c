#include <stdio.h>
#include <stdlib.h>
#include <ogg/ogg.h>
#include "ogg_test.h"
#include "ogg_encoder.h"
#include <string.h>
#include "ogg_decoder.h"

int main(int argc, char *argv[])
{
    FILE * file=NULL;
    int rc=0, pi=0;
    ogg_packet * packet[MAX_PACKET_NUM]={NULL};
    for(int i=0;i<MAX_PACKET_NUM;i++){
        packet[i]=malloc(sizeof(ogg_packet));
        memset(packet[i],0,sizeof(ogg_packet));
    }
    ogg_decoding_context * decoding_context=init_decoding_context();
    int packet_count=0;
    if(argc!=2){
        printf("invalid usage\n");
        exit(1);
    }

    file= fopen(argv[1], "rb+");
    while((rc=read_next_packets(file,decoding_context, packet))!=-1){
        if(rc>0){
            for(int i=0;i<rc;i++){
                packet_count++;
                printf("packet NO %I64d, length is %I32d\n",packet[i]->packetno,packet[i]->bytes);
            }
        }
    }
    if(rc==-1){  //normal end of file and eof page.
        while(packet[pi++]){
            packet_count++;
            printf("packet NO %I64d, length is %I32d\n",packet[pi]->packetno,packet[pi]->bytes);
        }
    }
    destroy_decoding_context(decoding_context);
    free_packet_list(packet,MAX_PACKET_NUM);
    printf("total packet count is %d\n",packet_count);
    fclose(file);
    return 0;
}
void free_packet_list(ogg_packet * packets[],int packet_num){
    for(int i=0;i<packet_num;i++){
        free(packets[i]);
    }
}
/*
void free_obj(ogg_page * page_list[],int size){
    if(page_list!=NULL){
        for(int i=0;i<size;i++)
            free(page_list[i]);
    }
}*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
