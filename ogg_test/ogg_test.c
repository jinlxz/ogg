
#include <stdio.h>
#include <stdlib.h>
#include <ogg/ogg.h>
#include "ogg_test.h"
#include "ogg_encoder.h"
#include <string.h>
#include "ogg_decoder.h"
ogg_stream_state * stream_state=NULL;
int main(int argc, char *argv[])
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


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
