/* Extract or peek at the next packet in an Ogg logical stream. */
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
} OggStreamState;

typedef struct OggPacket {
    unsigned char *packet;
    int bytes;
    int b_o_s;
    int e_o_s;
    int granulepos;
    int packetno;
} OggPacket;

int _packetout(OggStreamState *os, OggPacket *op, int advance) {
    int ptr = os->lacing_returned;
    int *lacing;
    int val;
    long bytes = 0;
    int size = 0;
    int eos = 0;
    int bos = 0;

    if (os->lacing_packet <= ptr)
        return 0;
    lacing = os->lacing_vals;
    val = lacing[ptr];
    if (val & 0x400) {
        os->lacing_returned++;
        os->packetno++;
        return -1;
    }
    if (!op && !advance)
        return 1;

    size = val & 0xff;
    eos = val & 0x200;
    bos = val & 0x100;
    bytes += size;
    while (size == 255) {
        int val = lacing[ptr += 1];
        size = val & 0xff;
        if (val & 0x200)
            eos = 0x200;
        bytes += size;
    }


    if (op) {
        op->e_o_s = eos;
        op->b_o_s = bos;
        op->packet = os->body_data + os->body_returned;
        op->packetno = os->packetno;
        op->granulepos = os->granule_vals[ptr];
        op->bytes = bytes;
    }
    if (advance) {
        os->body_returned += bytes;
        os->lacing_returned = ptr + 1;
        os->packetno++;
    }
    return 1;
}
