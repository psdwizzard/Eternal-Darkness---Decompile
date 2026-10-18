typedef struct OggStreamState OggStreamState;
typedef struct OggPacket OggPacket;

extern int _packetout(OggStreamState *os, OggPacket *op, int advance);

/* Extract the next packet and advance the Ogg logical stream. */
int ogg_stream_packetout(OggStreamState *os, OggPacket *op) {
    return _packetout(os, op, 1);
}
