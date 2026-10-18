/* ogg_stream_pagein: ogg_stream_pagein -- submit a page of Ogg bitstream data
 * into a logical stream (early libogg, without the buffer expand calls). */

typedef unsigned int u32;

typedef struct OggPage {
    unsigned char *header;
    long header_len;
    unsigned char *body;
    long body_len;
} OggPage;

typedef struct OggStreamState {
    unsigned char *body_data;
    long body_storage;
    long body_fill;
    long body_returned;
    int *lacing_vals;
    long *granule_vals;
    long lacing_storage;
    long lacing_fill;
    long lacing_packet;
    long lacing_returned;
    int e_o_s;
    int b_o_s;
    long serialno;
    long pageno;
} OggStreamState;

extern void *memmove(void *dest, const void *src, u32 size);
extern void *memcpy(void *, const void *, u32);

static inline long ogg_page_granulepos(OggPage *og) {
    long granulepos = og->header[13] & 0xff;
    granulepos = (granulepos << 8) | (og->header[12] & 0xff);
    granulepos = (granulepos << 8) | (og->header[11] & 0xff);
    granulepos = (granulepos << 8) | (og->header[10] & 0xff);
    granulepos = (granulepos << 8) | (og->header[9] & 0xff);
    granulepos = (granulepos << 8) | (og->header[8] & 0xff);
    granulepos = (granulepos << 8) | (og->header[7] & 0xff);
    granulepos = (granulepos << 8) | (og->header[6] & 0xff);
    return granulepos;
}

static inline int ogg_page_serialno(OggPage *og) {
    return og->header[14] | (og->header[15] << 8) | (og->header[16] << 16) |
           (og->header[17] << 24);
}

static inline long ogg_page_pageno(OggPage *og) {
    return og->header[18] | (og->header[19] << 8) | (og->header[20] << 16) |
           (og->header[21] << 24);
}

int ogg_stream_pagein(OggStreamState *os, OggPage *og) {
    int segptr = 0;
    unsigned char *header = og->header;
    unsigned char *body = og->body;
    long bodysize = og->body_len;

    int version = header[4];
    int continued = header[5] & 0x01;
    int bos = header[5] & 0x02;
    int eos = header[5] & 0x04;
    long granulepos = ogg_page_granulepos(og);
    int serialno = ogg_page_serialno(og);
    long pageno = ogg_page_pageno(og);
    int segments = header[26];
    long lr;
    long br;

    /* clean up 'returned data' */
    {
        lr = os->lacing_returned;
        br = os->body_returned;

        /* body data */
        if (br) {
            os->body_fill -= br;
            if (os->body_fill)
                memmove(os->body_data, os->body_data + br, os->body_fill);
            os->body_returned = 0;
        }

        if (lr) {
            /* segment table */
            if (os->lacing_fill - lr) {
                memmove(os->lacing_vals, os->lacing_vals + lr,
                            (os->lacing_fill - lr) * sizeof(*os->lacing_vals));
                memmove(os->granule_vals, os->granule_vals + lr,
                            (os->lacing_fill - lr) * sizeof(*os->granule_vals));
            }
            os->lacing_fill -= lr;
            os->lacing_packet -= lr;
            os->lacing_returned = 0;
        }
    }

    /* check the serial number */
    if (serialno != os->serialno) return -1;
    if (version > 0) return -1;

    /* are we in sequence? */
    if (pageno != os->pageno) {
        int i;

        /* unroll previous partial packet (if any) */
        for (i = os->lacing_packet; i < os->lacing_fill; i++)
            os->body_fill -= os->lacing_vals[i] & 0xff;
        os->lacing_fill = os->lacing_packet;

        /* make a note of dropped data in segment table */
        if (os->pageno != -1) {
            os->lacing_vals[os->lacing_fill++] = 0x400;
            os->lacing_packet++;
        }

        /* are we a 'continued packet' page?  If so, we'll need to skip
           some segments */
        if (continued) {
            bos = 0;
            for (; segptr < segments; segptr++) {
                int val = header[27 + segptr];
                body += val;
                bodysize -= val;
                if (val < 255) {
                    segptr++;
                    break;
                }
            }
        }
    }

    if (bodysize) {
        memcpy(os->body_data + os->body_fill, body, bodysize);
        os->body_fill += bodysize;
    }

    {
        int saved = -1;
        while (segptr < segments) {
            int val = header[27 + segptr];
            os->lacing_vals[os->lacing_fill] = val;
            os->granule_vals[os->lacing_fill] = -1;

            if (bos) {
                os->lacing_vals[os->lacing_fill] |= 0x100;
                bos = 0;
            }

            if (val < 255) saved = os->lacing_fill;

            os->lacing_fill++;
            segptr++;

            if (val < 255) os->lacing_packet = os->lacing_fill;
        }

        /* set the granulepos on the last pageno */
        if (saved != -1) {
            os->granule_vals[saved] = granulepos;
        }
    }

    if (eos) {
        os->e_o_s = 1;
        if (os->lacing_fill > 0)
            os->lacing_vals[os->lacing_fill - 1] |= 0x200;
    }

    os->pageno = pageno + 1;

    return 0;
}
