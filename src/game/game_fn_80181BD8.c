typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct FloatCoord3 {
    float x;
    float y;
    float z;
} FloatCoord3;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

extern const double lbl_806509A0;
extern const float lbl_80650990;
extern const double lbl_806509A8;
extern const float lbl_80650994;
extern const float lbl_80650998;
extern ShortCoord3 lbl_80651CE0;

extern void fn_8018163C(void*, ShortCoord3*, u8, u16);
extern void PSMTXRotAxisRad(void*, void*, float);
extern void PSMTXMultVec(void*, FloatCoord3*, FloatCoord3*);

void fn_80181BD8(u8* object, u8* config)
{
    u16* state_half;
    int i;
    u8* state;
    u8* entry;
    u8 count;
    ShortCoord3 coord;
    FloatCoord3 vector;

    count = object[1];
    state = object + 0x8C;
    entry = *(u8**)(object + 0x4C);
    *(s16*)(object + 0x98) = *(s16*)(config + 0xC);
    *(u16*)(object + 0x96) = *(u16*)(config + 6);
    *(u16*)(object + 0x92) = *(u16*)(config + 8);
    object[0x8D] = config[0];
    object[0x8C] = 0;
    object[0x8E] = 2;
    *(FloatCoord3*)(object + 0xF8) = *(FloatCoord3*)(config + 0x34);
    *(FloatCoord3*)(object + 0xEC) = *(FloatCoord3*)(config + 0x34);
    *(float*)(object + 0xBC) = lbl_80650990 / (float)count;
    object[0x8F] = count;

    state_half = (u16*)state;
    for (i = 0; i < count; state_half++, i++, entry += 0x38) {
        coord = lbl_80651CE0;
        state_half[7] = *(u16*)(state + 6);
        fn_8018163C(entry, &coord,
                    (u8)((int)((float)i * *(float*)(state + 0x30)) & 0x3F),
                    state_half[7]);
        vector.x = (float)*(s16*)(entry + 0xA);
        vector.y = (float)*(s16*)(entry + 0xC);
        vector.z = (float)*(s16*)(entry + 0xE);
        PSMTXRotAxisRad(state + 0x78, state + 0x60,
                    lbl_80650998 * (*(float*)(state + 0x68) < lbl_80650994
                                            ? -*(float*)(state + 0x68)
                                            : *(float*)(state + 0x68)));
        PSMTXMultVec(state + 0x78, &vector, &vector);
        *(s16*)(entry + 0xA) = (s16)(vector.x + (float)*(s16*)(object + 0x10));
        *(s16*)(entry + 0xC) = (s16)(vector.y + (float)*(s16*)(object + 0x12));
        *(s16*)(entry + 0xE) = *(s16*)(object + 0x14);
    }
}
