/* ogg_sync_pageout: extract a page, reporting each loss of sync once. */

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

extern long ogg_sync_pageseek(ogg_sync_state *oy, ogg_page *og);

int ogg_sync_pageout(ogg_sync_state *oy, ogg_page *og) {
    for (;;) {
        long result = ogg_sync_pageseek(oy, og);

        if (result > 0)
            return 1;
        if (result == 0)
            return 0;
        if (!oy->unsynced) {
            oy->unsynced = 1;
            return -1;
        }
    }
}
