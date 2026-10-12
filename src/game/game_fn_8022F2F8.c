/* fn_8022F2F8: compute the CRC-32 of a save block (header + body) and
 * store it byte-reversed into the header's checksum bytes. */

extern unsigned int lbl_802FF8C8[256]; /* CRC-32 table */

typedef struct CrcBlock {
    unsigned char *header;
    int headerSize;
    unsigned char *body;
    int bodySize;
} CrcBlock;

void fn_8022F2F8(CrcBlock *block) {
    int i;
    int size;
    unsigned int crc;

    if (block != 0) {
        crc = 0;
        block->header[0x16] = 0;
        block->header[0x17] = 0;
        block->header[0x18] = 0;
        block->header[0x19] = 0;

        size = block->headerSize;
        for (i = 0; i < size; i++) {
            crc = (crc << 8) ^ lbl_802FF8C8[(crc >> 24) ^ block->header[i]];
        }
        size = block->bodySize;
        for (i = 0; i < size; i++) {
            crc = (crc << 8) ^ lbl_802FF8C8[(crc >> 24) ^ block->body[i]];
        }

        block->header[0x16] = crc;
        block->header[0x17] = crc >> 8;
        block->header[0x18] = crc >> 16;
        block->header[0x19] = crc >> 24;
    }
}
