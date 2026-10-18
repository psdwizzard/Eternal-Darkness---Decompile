typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
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

extern volatile u32* GXRedirectWriteGatherPipe(volatile u32*);
extern void GXRestoreWriteGatherPipe(void);
extern u16 lbl_805AAE40[];

u32 fn_80130EAC(StripMesh* mesh, StripGroup* groups, int groupCount, s8* enabled,
                DisplayListEntry* entries, int* entryCount, volatile u32* buffer)
{
    u16* table;
    u32 size;
    StripGroup* end;
    int prevKey;
    int count;
    StripVertex* src;
    volatile u32* fifo;
    int n;
    u8 key;
    u32 a;
    u32 b;
    u16 ua;
    u16 ub;

    table = lbl_805AAE40;
    end = groups + groupCount;
    size = 0;
    prevKey = -1;
    count = *entryCount;
    fifo = GXRedirectWriteGatherPipe(buffer);

    for (; groups != end; groups++, enabled++) {
        if (*enabled == 0) {
            continue;
        }
        key = groups->key;
        n = groups->count;
        src = &mesh->vertices[groups->index];
        if (key != prevKey) {
            entries[count].key = key;
            if (count != 0) {
                u32 pad;
                u32 i;

                pad = 32 - (size & 31);
                if (pad != 32) {
                    size += pad;
                    for (i = 0; i < (pad & 3); i++) {
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
        *(volatile u8*)fifo = 0x9F;
        *(volatile u16*)fifo = n;
        size += 3;
        size += n * 6;
        if (n & 1) {
            a = table[src[0].position];
            ua = src[0].texcoord;
            src++;
            *fifo = (a << 16) | (a & 0xFFFF);
            *(volatile u16*)fifo = ua;
        }
        if (n & 2) {
            a = table[src[0].position];
            ua = src[0].texcoord;
            b = table[src[1].position];
            ub = src[1].texcoord;
            src += 2;
            *fifo = (a << 16) | (a & 0xFFFF);
            *fifo = (ua << 16) | b;
            *fifo = (b << 16) | ub;
        }
        n >>= 2;
        if (n != 0) do {
            a = table[src[0].position];
            ua = src[0].texcoord;
            b = table[src[1].position];
            ub = src[1].texcoord;
            *fifo = (a << 16) | (a & 0xFFFF);
            *fifo = (ua << 16) | b;
            *fifo = (b << 16) | ub;
            a = table[src[2].position];
            ua = src[2].texcoord;
            b = table[src[3].position];
            ub = src[3].texcoord;
            src += 4;
            *fifo = (a << 16) | (a & 0xFFFF);
            *fifo = (ua << 16) | b;
            *fifo = (b << 16) | ub;
        } while (--n != 0);
    }

    if (size != 0) {
        u32 rest;
        u32 j;

        rest = 32 - (size & 31);
        if (rest != 32) {
            size += rest;
            for (j = 0; j < (rest & 3); j++) {
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
    GXRestoreWriteGatherPipe();
    return size;
}
