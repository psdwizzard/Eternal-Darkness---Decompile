#include "src/game/types.h"

/* Memory card style checksum: sum and inverted sum of 16-bit words. */
void __CARDCheckSum(u16* data, s32 length, u16* checksum, u16* checksumInv) {
    *checksum = *checksumInv = 0;
    for (length /= sizeof(u16); 0 < length; length--) {
        *checksum += *data;
        *checksumInv += ~*data;
        data++;
    }
    if (*checksum == 0xFFFF) {
        *checksum = 0;
    }
    if (*checksumInv == 0xFFFF) {
        *checksumInv = 0;
    }
}
