rm -rf *.o *.so
gcc -c -Wall -fpic -I./include -I./src -I./ogg_test src/framing.c src/bitwise.c ogg_test/ogg_encoder.c ogg_test/hex_dump.c ogg_test/hex_dump.c ogg_test/ogg_encoder_test.c \
ogg_test/ogg_test.c ogg_test/ogg_decoder.c
gcc -o ogg-codecs.exe *.o
gcc -shared -o libogg.so *.o

