## lib_LTLIBRARIES = libogg-encoder.la
##AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include -I$(top_builddir)/ogg_test
##libogg_encoder_la_SOURCES = ogg_encoder.c hex_dump.c ogg_encoder_test.c ogg_test.c ogg_encoder.h ogg_test.h ogg_encoder_test.h
##libogg_encoder_la_LIBADD = ../src/libogg.la
##libogg_encoder_la_LDFLAGS = -module
bin_PROGRAMS=ogg-codecs
ogg_codecs_SOURCES=ogg_encoder.c ogg_decoder.c hex_dump.c ogg_encoder_test.c ogg_test.c ogg_encoder.h ogg_test.h ogg_encoder_test.h ogg_decoder.h
ogg_codecs_LDADD=../src/libogg.la
AM_CPPFLAGS=-I$(top_srcdir)/include
