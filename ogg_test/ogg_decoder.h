#ifndef OGG_DECODER_H
#define OGG_DECODER_H
int  read_next_packets(FILE * file,ogg_decoding_context * decoding_context,ogg_packet *  packets[])
int read_ogg_page(FILE * file,ogg_sync_state * state,ogg_page * page);
int write_page_to_stream(FILE * file);
typedef struct {
    ogg_sync_state * sync_state;
    ogg_stream_state * stream_state;
} ogg_decoding_context;

ogg_decoding_context * init_decoding_context();
#endif // OGG_DECODER_H
