typedef struct DebugEntry {
    void* object;
    void* owner;
    unsigned char active;
    unsigned char pad9;
    unsigned short timer;
} DebugEntry;

extern unsigned char lbl_805B1268[];

#pragma opt_common_subs off
void fn_801409C0(unsigned char index)
{
    unsigned char* base = lbl_805B1268;
    unsigned int offset = index * sizeof(DebugEntry);
    ((DebugEntry*)(base + offset))->timer = 0;
    *(void**)(base + offset) = 0;
    ((DebugEntry*)(base + offset))->owner = 0;
    ((DebugEntry*)(base + offset))->active = 0;
}
#pragma opt_common_subs reset
