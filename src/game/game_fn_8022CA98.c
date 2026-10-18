typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Entry {
    u8 state;
    u8 pad01[0x0B];
    u32 resource2;
    u32 resource0;
    u32 status;
    u8 pad18[0x04];
    u32 resource2b;
    u32 resource3b;
    u32 resource3;
    u8 pad28[0x08];
    u32 flagsb;
    u32 flags;
    u8 pad38[0x08];
    u32 memoryCounters[10][2];
    u32 graphicsCounters[4][2];
} Entry;

extern volatile u16 *__memReg;
extern void GXReadXfRasMetric(u32 *, u32 *, u32 *, u32 *);

void PERFGetAllMemMetrics(Entry *entry, s32 sample)
{

    GXReadXfRasMetric(&entry->graphicsCounters[0][sample],
                &entry->graphicsCounters[1][sample],
                &entry->graphicsCounters[2][sample],
                &entry->graphicsCounters[3][sample]);
    {
        u32 high = __memReg[25];
        u32 low = __memReg[26];
        entry->memoryCounters[0][sample] = (high << 16) | low;
    }
    {
        u32 high = __memReg[27];
        u32 low = __memReg[28];
        entry->memoryCounters[1][sample] = (high << 16) | low;
    }
    {
        u32 high = __memReg[29];
        u32 low = __memReg[30];
        entry->memoryCounters[2][sample] = (high << 16) | low;
    }
    {
        u32 high = __memReg[31];
        u32 low = __memReg[32];
        entry->memoryCounters[3][sample] = (high << 16) | low;
    }
    {
        u32 high = __memReg[33];
        u32 low = __memReg[34];
        entry->memoryCounters[4][sample] = (high << 16) | low;
    }
    {
        u32 high = __memReg[35];
        u32 low = __memReg[36];
        entry->memoryCounters[5][sample] = (high << 16) | low;
    }
    {
        u32 high = __memReg[37];
        u32 low = __memReg[38];
        entry->memoryCounters[6][sample] = (high << 16) | low;
    }
    {
        u32 high = __memReg[39];
        u32 low = __memReg[40];
        entry->memoryCounters[7][sample] = (high << 16) | low;
        high = __memReg[41];
        low = __memReg[42];
        entry->memoryCounters[8][sample] = (high << 16) | low;
    }
    entry->memoryCounters[9][sample] = ((u32)__memReg[43] << 16) | __memReg[44];
}
