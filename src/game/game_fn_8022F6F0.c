/* Return the Ogg page's end-of-stream flag. */
typedef struct AudioPage {
    unsigned char *header;
    int headerSize;
    unsigned char *body;
    int bodySize;
} AudioPage;

int ogg_page_eos(AudioPage *page) {
    return page->header[5] & 4;
}
