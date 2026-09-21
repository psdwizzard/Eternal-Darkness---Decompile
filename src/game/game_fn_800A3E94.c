typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object800A3E94 {
    u32* callbacks;
    u8 pad04[0x60];
    u32 field64;
    u8 pad68[0x1c];
    u16 field84;
    u16 field86;
    u8 pad88[0x106];
    u16 field18E;
    int field190;
    u16 field194;
    u8 pad196[0xb6];
    u32 fields24C[4];
    u8 field25C;
    u8 pad25D;
    u8 field25E;
    u8 field25F;
    u16 field260;
    u8 pad262[0x10];
    u16 field272;
    u8 pad274[0xe];
    u8 field282;
    u8 field283;
    u8 pad284[3];
    u8 field287;
    u8 pad288[4];
    int field28C;
    int field290;
    u8 pad294[8];
    u16 field29C;
    u8 pad29E[4];
    u8 flag80 : 1;
    u8 flag40 : 1;
    u8 flag20 : 1;
    u8 flag10 : 1;
    u8 flag08 : 1;
    u8 flag04 : 1;
    u8 flag02 : 1;
    u8 flag01 : 1;
} Object800A3E94;

extern int lbl_8064C940;
extern u32 lbl_8031D6C8[19];
extern void* memset(void*, int, unsigned int);

extern void fn_800A1E94(Object800A3E94*);
extern void fn_800A2DBC(Object800A3E94*);
extern void fn_800A2ED8(Object800A3E94*, int);
extern void fn_800A30F4(Object800A3E94*, int);
extern void fn_800A1D18(void);
extern void fn_800A1D1C(void);
extern void fn_800A2308(void);
extern void fn_800A2200(void);
extern void fn_800A2220(void);
extern void fn_800A22D8(void);
extern void fn_800A1D20(void);
extern void fn_800A1D24(void);
extern void fn_800CFCD4(Object800A3E94*);
extern void fn_800D3B68(Object800A3E94*);
extern void fn_800D67A4(Object800A3E94*);

/*
 * Game-state object initializer and callback-table setup.
 */
void fn_800A3E94(Object800A3E94* object, int kind)
{
    int i;

    lbl_8064C940 = 0;
    object->fields24C[0] = 0;
    object->fields24C[1] = 0;
    object->fields24C[2] = 0;
    object->fields24C[3] = 0;
    object->field64 = 0;
    object->field84 = 0;
    object->field18E = 0xb4;
    object->field190 = -1;
    object->field194 = 0;
    object->field260 = 0xf0;
    object->field25E = 0;
    object->field25F = 0;
    object->field272 = 3;
    object->field86 = 0;
    object->field25C = 0;
    object->field282 = 0;
    object->field283 = 0;
    object->flag80 = 0;
    object->flag40 = 0;
    object->field287 = 0;
    object->field29C = 0;
    object->flag04 = 0;
    object->flag02 = 0;

    fn_800A1E94(object);
    fn_800A2DBC(object);
    object->field28C = -1;
    object->flag20 = 0;
    object->flag08 = 0;
    fn_800A2ED8(object, 0);
    fn_800A30F4(object, 0);
    object->field290 = 1;

    memset(lbl_8031D6C8, 0, 0x4c);
    object->callbacks = lbl_8031D6C8;
    object->callbacks[0] = (u32)fn_800A1D18;
    object->callbacks[3] = 0;
    object->callbacks[4] = (u32)fn_800A1D1C;
    object->callbacks[5] = (u32)fn_800A2308;
    object->callbacks[6] = (u32)fn_800A2308;
    object->callbacks[7] = (u32)fn_800A2308;
    object->callbacks[8] = (u32)fn_800A2200;
    object->callbacks[9] = (u32)fn_800A2220;
    object->callbacks[10] = (u32)fn_800A22D8;
    object->callbacks[12] = (u32)fn_800A1D20;
    object->callbacks[18] = (u32)fn_800A1D24;

    switch (kind) {
    case 1:
        fn_800CFCD4(object);
        break;
    case 2:
        fn_800D3B68(object);
        break;
    case 3:
        fn_800D67A4(object);
        break;
    }

    /* The empty 19-iteration loop is intentional: GC/1.3 removes the
     * unrolled iterations but retains a CTR remainder loop starting at 18.
     * Starting the C loop at 18 instead removes it entirely.
     */
    for (i = 0; i < 19;) {
        i++;
    }
}
