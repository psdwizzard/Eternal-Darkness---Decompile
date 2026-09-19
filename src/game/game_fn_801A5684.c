typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern u8 lbl_80607130[];
extern int lbl_8064D738;

extern void fn_801A5620(u8*, u8*);
extern void DCFlushRange(void*, u32);
extern u32 fn_801ED57C(u32);
extern void fn_80226D28(u32);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_801ED468(u32);
extern void fn_801ECEC8(u32, u32, u32);
extern int fn_8017FFB8(void);
extern int fn_8017FFB0(void);
extern int fn_8017FF98(void);
extern void fn_80225F4C(u32, void*, u8);
extern void fn_80226AB4(u32, u32, u16);
extern void fn_801A5838(void);
extern void fn_801A583C(u16);
extern void fn_801A5848(u16);
extern void fn_801A5854(u16);

void fn_801A5684(u8* object)
{
    u16 count;
    u16 size0;
    u16 size1;
    u16 size2;
    u8* destination;
    u8 object_count;
    u8* source;
    u16 i;
    u8* output;
    int j;
    u32 token;

    destination = object + 0x8c;
    object_count = object[1];
    count = *(u16*)(lbl_80607130 + 2);
    size0 = *(u16*)(lbl_80607130 + 0xa);
    size1 = *(u16*)(lbl_80607130 + 0xe);
    size2 = *(u16*)(lbl_80607130 + 0xc);
    source = *(u8**)(object + 0x4c);
    {
        u8* buffer0 = *(u8**)(object + 0x50);
        u8* buffer1 = *(u8**)(object + 0x54);
        u8* buffer2 = *(u8**)(object + 0x58);

        if (lbl_8064D738 != 0) {
            buffer1 += count * 4;
            buffer0 += count * 6;
            buffer2 += count * 4;
        }
        output = buffer2;

        for (i = 0; i < object_count; i++) {
            for (j = 0; j < source[0x20]; j++) {
                output[3] = source[0x2b];
                output += 4;
            }
            source += 0x38;
        }

        fn_801A5620(buffer0, destination);
        DCFlushRange(buffer0, size0);
        DCFlushRange(buffer1, size1);
        DCFlushRange(buffer2, size2);
        token = fn_801ED57C(0);
        fn_80226D28(0);
        fn_8018D0D0(object, object + 0x5c, *(s16*)(object + 0xe));
        fn_801ED468(0x1b);
        fn_801ECEC8(1, 3, 0);
        fn_80225F4C(9, buffer0, fn_8017FFB8());
        fn_80225F4C(0xd, buffer1, fn_8017FFB0());
        fn_80225F4C(0xb, buffer2, fn_8017FF98());
        fn_80226AB4(0x80, 5, count);

        for (buffer0 = 0; (u16)buffer0 < count; buffer0++) {
            object = (u8*)(u16)buffer0;
            fn_801A5854((u16)object);
            fn_801A5848((u16)object);
            fn_801A583C((u16)object);
        }
        fn_801A5838();
        fn_801ED57C(token);
    }
}
