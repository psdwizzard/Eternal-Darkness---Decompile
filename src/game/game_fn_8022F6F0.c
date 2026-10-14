/* Return the Ogg page's end-of-stream flag. */
typedef struct AudioPage {
    unsigned char *header;
    int headerSize;
    unsigned char *body;
    int bodySize;
} AudioPage;

int fn_8022F6F0(AudioPage *page) {
    return page->header[5] & 4;
}
