#ifndef OGG_TEST_H
#define OGG_TEST_H
int  read_next_packet(FILE * file, ogg_packet  *  packet);
int read_ogg_page(FILE * file,ogg_sync_state * state,ogg_page * page);
int write_page_to_stream(FILE * file);
void free_obj(ogg_page * page_list[],int size);
#endif