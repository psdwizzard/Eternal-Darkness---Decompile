typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;

typedef struct StripGroup {
    u8 key;
    u8 count;
    u16 index;
} StripGroup;

typedef struct StripVertex {
    u16 position;
    u16 texcoord;
} StripVertex;

typedef struct StripMesh {
    u8 pad0[0x44];
    StripVertex* vertices;
} StripMesh;

typedef struct DisplayListEntry {
    u32 size;
    u32 offset;
    u32 key;
    u32 unkC;
} DisplayListEntry;

extern volatile u32* fn_80224650(volatile u32*);
extern void fn_80224754(void);
extern u16 lbl_805AAE40[];

u32 fn_80130A14(StripMesh* mesh, StripGroup* groups, int groupCount, s8* enabled,
                DisplayListEntry* entries, int* entryCount, volatile u32* buffer,
                int width)
{
    u16* table;
    u32 size;
    StripGroup* end;
    int prevKey;
    int count;
    u32 firstDelta;
    u32 secondDelta;
    volatile u32* fifo;
    int n;
    u8 key;
    u32 positionWord;
    u32 pairPosition;
    u32 packedWord;
    u16 texcoordA;
    u16 texcoordB;
    int stride;
    int doubleStride;

    /* Pack the alternating offsets into two 16-bit index fields. */
    stride = width - 1;
    doubleStride = stride + stride;
    table = lbl_805AAE40;
    end = groups + groupCount;
    firstDelta = (stride << 16) | doubleStride;
    secondDelta = (doubleStride << 16) | stride;
    size = 0;
    prevKey = -1;
    count = *entryCount;
    fifo = fn_80224650(buffer);

    for (; groups != end; groups++, enabled++) {
        if (*enabled == 0) {
            continue;
        }
        {
            StripVertex* src;
            key = groups->key;
            n = groups->count;
            src = &mesh->vertices[groups->index];
            /* Start a new display list when the group key changes. */
            if (key != prevKey) {
                entries[count].key = key;
                if (count != 0) {
                    u32 pad;
                    u32 padBytes;
                    u32 i;

                    pad = 32 - (size & 31);
                    if (pad != 32) {
                        padBytes = pad & 3;
                        size += pad;
                        for (i = 0; i < padBytes; i++) {
                            *(volatile u8*)fifo = 0;
                        }
                        for (i = 0; i < (pad >> 2); i++) {
                            *fifo = 0;
                        }
                    }
                    entries[count - 1].size = size - entries[count - 1].offset;
                }
                entries[count].offset = size;
                count++;
                prevKey = groups->key;
            }
            *(volatile u8*)fifo = 0x99;
            *(volatile u16*)fifo = n;
            size += 3;
            size += n * 10;
            if (n & 1) {
                positionWord = table[src[0].position];
                texcoordA = src[0].texcoord;
                src++;
                positionWord = (positionWord << 16) | (positionWord & 0xFFFF);
                *fifo = positionWord;
                *fifo = positionWord + firstDelta;
                *(volatile u16*)fifo = texcoordA;
            }
            /* Emit a two-vertex remainder before the four-vertex loop. */
            if (n & 2) {
                u32 pairWord;
                positionWord = table[src[0].position];
                texcoordA = src[0].texcoord;
                pairPosition = table[src[1].position];
                texcoordB = src[1].texcoord;
                src += 2;
                pairWord = (pairPosition << 16) | (pairPosition & 0xFFFF);
                packedWord = pairWord + secondDelta;
                positionWord = (positionWord << 16) | (positionWord & 0xFFFF);
                *fifo = positionWord;
                *fifo = positionWord + firstDelta;
                *fifo = (texcoordA << 16) | pairPosition;
                *fifo = (pairPosition << 16) | (packedWord & 0xFFFF);
                *fifo = (packedWord & 0xFFFF0000) | texcoordB;
            }
            n >>= 2;
            /* Four vertices are packed into ten 32-bit FIFO writes. */
            if (n != 0) do {
                u32 mixed;
                u32 secondPosition;
                u32 secondOffsetWord;
                u32 firstOffsetWord;
                positionWord = table[src[0].position];
                texcoordA = src[0].texcoord;
                secondPosition = table[src[1].position];
                texcoordB = src[1].texcoord;
                positionWord = (positionWord << 16) | (positionWord & 0xFFFF);
                firstOffsetWord = positionWord + firstDelta;
                mixed = (texcoordA << 16) | secondPosition;
                *fifo = positionWord;
                *fifo = firstOffsetWord;
                secondOffsetWord = (secondPosition << 16) | (secondPosition & 0xFFFF);
                secondOffsetWord += secondDelta;
                *fifo = mixed;
                *fifo = (secondPosition << 16) | (secondOffsetWord & 0xFFFF);
                *fifo = (secondOffsetWord & 0xFFFF0000) | texcoordB;
                {
                    u16 thirdPosition;
                    u16 fourthPosition;
                    u32 thirdOffsetWord;
                    u32 fourthOffsetWord;
                    u16 thirdTexcoord;
                    u32 fourthTexcoordWord;
                    thirdPosition = table[src[2].position];
                    thirdTexcoord = src[2].texcoord;
                    fourthPosition = table[src[3].position];
                    fourthTexcoordWord = src[3].texcoord;
                    packedWord = (thirdPosition << 16) | (thirdPosition & 0xFFFF);
                    thirdOffsetWord = packedWord + firstDelta;
                    *fifo = packedWord;
                    /* Keep the halfword joins as rotate-and-insert operations. */
                    packedWord = __rlwimi(fourthPosition, fourthPosition, 16, 0, 15);
                    packedWord += secondDelta;
                    src += 4;
                    *fifo = thirdOffsetWord;
                    fourthTexcoordWord = (packedWord & 0xFFFF0000) | fourthTexcoordWord;
                    *fifo = __rlwimi(fourthPosition, thirdTexcoord, 16, 0, 15);
                    fourthOffsetWord = __rlwimi(fourthPosition << 16, packedWord, 0, 16, 31);
                    *fifo = fourthOffsetWord;
                    *fifo = fourthTexcoordWord;
                }
            } while (--n != 0);
        }
    }

    if (size != 0) {
        u32 rest;
        u32 restBytes;
        u32 j;

        rest = 32 - (size & 31);
        if (rest != 32) {
            restBytes = rest & 3;
            size += rest;
            for (j = 0; j < restBytes; j++) {
                *(volatile u8*)fifo = 0;
            }
            rest >>= 2;
            for (j = 0; j < rest; j++) {
                *fifo = 0;
            }
        }
        *entryCount = count;
        entries[count - 1].size = size - entries[count - 1].offset;
    }
    fn_80224754();
    return size;
}
