#ifndef OGG_DECODER_H
#define OGG_DECODER_H
#include <stdio.h>
#include "ogg/ogg.h"
int read_ogg_page(FILE * file,ogg_sync_state * state,ogg_page * page);
int read_packets_in_current_page(ogg_packet * packets []);

typedef struct {
    ogg_sync_state * sync_state;
    ogg_stream_state * stream_state;
} ogg_decoding_context;
int write_page_to_stream(FILE * file,ogg_decoding_context * decoding_context);
int  read_next_packets(FILE * file,ogg_decoding_context * decoding_context,ogg_packet *  packets[]);
ogg_decoding_context * init_decoding_context();
void destroy_decoding_context(ogg_decoding_context * decoding_context);
#endif // OGG_DECODER_H
