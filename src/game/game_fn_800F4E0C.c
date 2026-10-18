typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
typedef int DSError;

extern const volatile int gTRKMemMap[4];

/* MetroTRK: validate an address interval against the memory map. */
DSError TRKValidMemory32(u32 address, u32 length, BOOL readOnly)
{
    u32 last = length + address;
    DSError error = 0x700;
    u32 i;
    u32 boundary;

    if (--last < address) {
        return 0x700;
    }
    for (i = 0; i < 1; ++i) {
        if (address <= (u32)gTRKMemMap[i * 4 + 1] &&
            last >= (u32)gTRKMemMap[i * 4]) {
            if (((u8)readOnly == 0 && gTRKMemMap[i * 4 + 2] == 0) ||
                ((u8)readOnly == 1 && gTRKMemMap[i * 4 + 3] == 0)) {
                error = 0x700;
            } else {
                error = 0;
                boundary = (u32)gTRKMemMap[i * 4];
                if (address < boundary) {
                    error = TRKValidMemory32(address,
                        boundary - address, readOnly);
                }
                if (error == 0) {
                    boundary = (u32)gTRKMemMap[i * 4 + 1];
                    if (last > boundary) {
                        error = TRKValidMemory32(boundary, last - boundary, readOnly);
                    }
                }
            }
            break;
        }
    }
    return error;
}
