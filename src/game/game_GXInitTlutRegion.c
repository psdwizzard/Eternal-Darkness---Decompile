/* Initialize the TLUT region's TMEM allocation register. */
typedef unsigned long u32;

typedef struct GXTlutRegion {
    u32 loadTlut1;
    u32 tlutBase;
    u32 tlutAddress;
    u32 tlutEntries;
} GXTlutRegion;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void GXInitTlutRegion(GXTlutRegion *region, u32 tmem_addr, u32 tlut_size) {
    region->loadTlut1 = 0;
    SET_REG_FIELD(region->loadTlut1, 10, 0, (tmem_addr - 0x80000) >> 9);
    SET_REG_FIELD(region->loadTlut1, 11, 10, tlut_size);
    SET_REG_FIELD(region->loadTlut1, 8, 24, 0x65);
}
