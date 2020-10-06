#ifndef OGG_ENCODER_H
#define OGG_ENCODER_H
#include "ogg/ogg.h"
typedef struct {
    ogg_stream_state * stream_state;
    int opus_packets_in_page;
    }ogg_encoding_context;
int get_next_page(ogg_encoding_context * encoding_context, ogg_packet * packet, ogg_page *pages [], int page_size);
ogg_encoding_context * init_encoding_context();
int destroy_encoding_context(ogg_encoding_context * encoding_context);
int reset_encoding_context(ogg_encoding_context * encoding_context);
#endif
