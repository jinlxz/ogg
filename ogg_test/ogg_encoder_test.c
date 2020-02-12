#include "ogg_encoder_test.h"
#include "ogg_encoder.h"
#include "hex_dump.h"
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