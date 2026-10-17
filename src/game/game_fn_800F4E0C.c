typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
typedef int DSError;

extern const volatile int lbl_80239C00[4];

/* MetroTRK: validate an address interval against the memory map. */
DSError fn_800F4E0C(u32 address, u32 length, BOOL readOnly)
{
    u32 last = length + address;
    DSError error = 0x700;
    u32 i;
    u32 boundary;

    if (--last < address) {
        return 0x700;
    }
    for (i = 0; i < 1; ++i) {
        if (address <= (u32)lbl_80239C00[i * 4 + 1] &&
            last >= (u32)lbl_80239C00[i * 4]) {
            if (((u8)readOnly == 0 && lbl_80239C00[i * 4 + 2] == 0) ||
                ((u8)readOnly == 1 && lbl_80239C00[i * 4 + 3] == 0)) {
                error = 0x700;
            } else {
                error = 0;
                boundary = (u32)lbl_80239C00[i * 4];
                if (address < boundary) {
                    error = fn_800F4E0C(address,
                        boundary - address, readOnly);
                }
                if (error == 0) {
                    boundary = (u32)lbl_80239C00[i * 4 + 1];
                    if (last > boundary) {
                        error = fn_800F4E0C(boundary, last - boundary, readOnly);
                    }
                }
            }
            break;
        }
    }
    return error;
}
