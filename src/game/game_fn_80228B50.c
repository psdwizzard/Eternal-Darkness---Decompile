/* GXInitTlutObj: initialise a texture lookup table object. */
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXTlutObjInt {
    u32 format;
    u32 load;
    u16 entries;
    u16 padding;
} GXTlutObjInt;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

void fn_80228B50(void *obj, void *table, u32 format, u16 entries)
{
    u32 tableBase;
    GXTlutObjInt *t = (GXTlutObjInt *)obj;

    t->format = 0;
    SET_REG_FIELD(t->format, 2, 10, format);
    tableBase = ((u32)table & 0x3FFFFFFF) >> 5;
    SET_REG_FIELD(t->load, 21, 0, tableBase);
    SET_REG_FIELD(t->load, 8, 24, 0x64);
    t->entries = entries;
}
