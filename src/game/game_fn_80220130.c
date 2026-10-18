typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

/* __CARDVendorID */
extern u16 __CARDVendorID;
/* SectorSizeTable */
extern s32 SectorSizeTable[];

/* IsCard */
BOOL IsCard(u32 id)
{
    u32 size;
    s32 sectorSize;

    if ((id & 0xFFFF0000) && (id != 0x80000004 || __CARDVendorID == 0xFFFF)) {
        return FALSE;
    }

    if ((id & 0x00000003) != 0) {
        return FALSE;
    }

    size = id & 0xFC;
    switch (size) {
    case 4:
    case 8:
    case 16:
    case 32:
    case 64:
    case 128:
        break;
    default:
        return FALSE;
    }

    sectorSize = SectorSizeTable[(id & 0x00003800) >> 11];
    if (sectorSize == 0) {
        return FALSE;
    }

    /* card capacity in bytes (size is in megabits) divided into sectors */
    if ((size * 1024 * 1024 / 8) / sectorSize < 8) {
        return FALSE;
    }

    return TRUE;
}
