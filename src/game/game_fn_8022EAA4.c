typedef struct OggStreamState OggStreamState;
typedef struct OggPacket OggPacket;

extern int fn_8022EAC8(OggStreamState *os, OggPacket *op, int advance);

/* Extract the next packet and advance the Ogg logical stream. */
int fn_8022EAA4(OggStreamState *os, OggPacket *op) {
    return fn_8022EAC8(os, op, 1);
}
