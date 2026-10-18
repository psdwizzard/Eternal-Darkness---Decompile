typedef unsigned int u32;

typedef struct Status {
    unsigned char pad0[0x34];
    u32 size;
} Status;

extern int DVDOpen(void*, Status*);

u32 fn_8015D630(void* object)
{
    Status status;
    u32 result = 0;

    if (DVDOpen(object, &status)) {
        result = status.size;
    }
    return result;
}
