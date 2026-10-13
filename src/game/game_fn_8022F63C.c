/* Initialize an Ogg logical stream and its body and packet buffers. */
typedef struct OggStreamState {
    unsigned char *body_data;
    int body_storage;
    int body_fill;
    int body_returned;
    int *lacing_vals;
    int *granule_vals;
    int lacing_storage;
    int lacing_fill;
    int lacing_packet;
    int lacing_returned;
    int e_o_s;
    int b_o_s;
    int serialno;
    int pageno;
    int packetno;
    int granulepos;
} OggStreamState;

extern void *memset(void *dest, int value, unsigned long size);
extern void *fn_8022F780(int size);

int fn_8022F63C(OggStreamState *stream, int serialno) {
    if (stream != 0) {
        memset(stream, 0, sizeof(*stream));
        stream->body_storage = 0x2000;
        stream->body_data = fn_8022F780(stream->body_storage);
        stream->lacing_storage = 0x200;
        stream->lacing_vals = fn_8022F780(stream->lacing_storage * sizeof(*stream->lacing_vals));
        stream->granule_vals = fn_8022F780(stream->lacing_storage * sizeof(*stream->granule_vals));
        stream->serialno = serialno;
        return 0;
    }
    return -1;
}
