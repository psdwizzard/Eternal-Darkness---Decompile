/* ogg_sync_pageseek: libogg ogg_sync_pageseek. Finds the next complete, checksum-
 * verified Ogg page in the sync buffer. */

extern int fn_800F98EC(const void *a, const void *b, unsigned long n); /* memcmp */
extern void *memcpy(void *dst, const void *src, unsigned long n);
extern void *memset(void *dst, int c, unsigned long n);
extern void *memchr(const void *ptr, int value, unsigned long count);

extern const char lbl_80651790[8]; /* "OggS" */

typedef struct ogg_page {
    unsigned char *header;
    int header_len;
    unsigned char *body;
    int body_len;
} ogg_page;

typedef struct ogg_sync_state {
    unsigned char *data;
    int storage;
    int fill;
    int returned;
    int unsynced;
    int headerbytes;
    int bodybytes;
} ogg_sync_state;

extern void ogg_page_checksum_set(ogg_page *og); /* ogg_page_checksum_set */

int ogg_sync_pageseek(register ogg_sync_state *oy, ogg_page *og) {
    register unsigned char *page = oy->data + oy->returned;
    unsigned char *next;
    register int bytes = oy->fill - oy->returned;

    if (oy->headerbytes == 0) {
        int headerbytes, i;
        if (bytes < 27) return 0;

        {
            register unsigned char *capture;
            /* ASM: or (mr) preserves the retail copy encoding, which MWCC
             * otherwise replaces with an addi with a zero offset. */
            asm { or capture, page, page }
            if (fn_800F98EC(capture, lbl_80651790, 4)) goto sync_fail;
        }

        headerbytes = page[26] + 27;
        if (bytes < headerbytes) return 0;

        for (i = 0; i < page[26]; i++)
            oy->bodybytes += page[27 + i];
        oy->headerbytes = headerbytes;
    }

    if (oy->bodybytes + oy->headerbytes > bytes) return 0;

    {
        ogg_page log;
        char chksum[4];
        int headerbytes;

        memcpy(chksum, page + 22, 4);
        memset(page + 22, 0, 4);

        log.header = page;
        headerbytes = oy->headerbytes;
        log.body = page + headerbytes;
        log.header_len = headerbytes;
        log.body_len = oy->bodybytes;
        ogg_page_checksum_set(&log);

        if (fn_800F98EC(chksum, page + 22, 4)) {
            memcpy(page + 22, chksum, 4);
            goto sync_fail;
        }
    }

    {
        unsigned char *page = oy->data + oy->returned;
        int bytes;

        if (og) {
            og->header = page;
            og->header_len = oy->headerbytes;
            og->body = page + oy->headerbytes;
            og->body_len = oy->bodybytes;
        }

        oy->unsynced = 0;
        oy->returned += (bytes = oy->headerbytes + oy->bodybytes);
        oy->headerbytes = 0;
        oy->bodybytes = 0;
        return bytes;
    }

sync_fail:
    {
        register int zero;
        register unsigned char *search;
        register unsigned long count;
        register int marker;
        /* ASM: li, addi and stw retain the retail ordering of state resets
         * and memchr arguments; MWCC schedules these C assignments differently. */
        asm {
            li zero, 0
            addi search, page, 1
            stw zero, 20(oy)
            addi count, bytes, -1
            li marker, 79
            stw zero, 24(oy)
        }
        next = memchr(search, marker, count);
    }
    if (!next)
        next = oy->data + oy->fill;

    oy->returned = next - oy->data;
    return -(next - page);
}
