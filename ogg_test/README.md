Example of using libogg
---
An example of decoding ogg container using libogg, the program decodes the ogg container and iterates on each packet, prints the ID and length of each packet,
it also counts the total number of packets in the file and prints it out, the program assumes that there is only 1 logical stream in the physical stream,
you can easily modify it to support multiple logical streams.
