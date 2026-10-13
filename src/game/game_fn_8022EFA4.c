/* fn_8022EFA4: libogg ogg_sync_pageseek. Finds the next complete, checksum-
 * verified Ogg page in the sync buffer. */

extern int fn_800F98EC(const void *a, const void *b, unsigned long n); /* memcmp */
extern void *memcpy(void *dst, const void *src, unsigned long n);
extern void *memset(void *dst, int c, unsigned long n);
extern void *memchr(const void *ptr, int value, unsigned long count);

extern const char lbl_80651790[8]; /* "OggS" */

typedef struct ogg_page {
    unsigned char *header;
    long header_len;
    unsigned char *body;
    long body_len;
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

extern void fn_8022F2F8(ogg_page *og); /* ogg_page_checksum_set */

long fn_8022EFA4(ogg_sync_state *oy, ogg_page *og) {
    unsigned char *page = oy->data + oy->returned;
    unsigned char *next;
    long bytes = oy->fill - oy->returned;

    if (oy->headerbytes == 0) {
        int headerbytes, i;
        if (bytes < 27) return 0;

        if (fn_800F98EC(page, lbl_80651790, 4)) goto sync_fail;

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

        memcpy(chksum, page + 22, 4);
        memset(page + 22, 0, 4);

        log.header = page;
        log.header_len = oy->headerbytes;
        log.body = page + oy->headerbytes;
        log.body_len = oy->bodybytes;
        fn_8022F2F8(&log);

        if (fn_800F98EC(chksum, page + 22, 4)) {
            memcpy(page + 22, chksum, 4);
            goto sync_fail;
        }
    }

    {
        unsigned char *page = oy->data + oy->returned;
        long bytes;

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
    oy->headerbytes = 0;
    oy->bodybytes = 0;

    next = memchr(page + 1, 'O', bytes - 1);
    if (!next)
        next = oy->data + oy->fill;

    oy->returned = next - oy->data;
    return -(next - page);
}
