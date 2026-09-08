typedef unsigned int u32;

typedef struct DrawParams {
    float value[28];
} DrawParams;

typedef struct DrawPacket {
    float value[16];
} DrawPacket;

extern DrawParams lbl_8023B6C8;
extern u32 lbl_806512C8;
extern u32 lbl_806512CC;
extern u32 lbl_806512D0;
extern u32 lbl_806512D4;
extern float lbl_806512D8;
extern float lbl_806512DC;
extern float lbl_806512E0;
extern float lbl_806512E4;
extern float lbl_806512E8;
extern float lbl_806512EC;
extern float lbl_806512F0;
extern float lbl_806512F4;
extern float lbl_806512F8;
extern float lbl_806512FC;
extern float lbl_80651300;
extern float lbl_8064D5D8;
extern float lbl_8064D5DC;
extern u32 lbl_8064D5E4;
extern char lbl_80265D60[];

extern void fn_8022B58C(float*);
extern void fn_801E3AA4(int);
extern void fn_801E5430(int, int);
extern void fn_801E56AC(char*, u32, ...);
extern void fn_8022B4B8(DrawPacket*, int);
extern void fn_80228020(int);
extern void fn_8022806C(int, int, int, int, int, int, int);
extern void fn_8022A118(int, int, int, int);
extern void fn_80229964(int, int);
extern void fn_802262B8(int);
extern void fn_8022A2F4(int);
extern void fn_801ECEC8(int, int, int);
extern void fn_802254D0(void);
extern void fn_80224A60(int, int);
extern void fn_8022551C(int, int, int, int, int);
extern void fn_80210FB0(void*);
extern void fn_8022B690(void*, int);
extern void fn_80227EB8(int, u32*);
extern void fn_80226C18(int, int);
extern void fn_80226AB4(int, int, int);
extern void fn_801EB068(float, float, float);
extern void fn_801EB064(void);

void fn_801EAA04(float width, float height)
{
    DrawParams p = lbl_8023B6C8;
    DrawPacket packet;
    u32 color;
    float sx = height / lbl_806512D8;
    float sy = width / lbl_806512D8;
    int i;

    if (sx > lbl_806512DC) sx = lbl_806512DC;
    if (sy > lbl_806512DC) sy = lbl_806512DC;
    p.value[10] *= sx;
    p.value[12] *= sy;
    p.value[13] += lbl_806512E0;
    p.value[15] += lbl_806512E0;
    p.value[9] += lbl_806512E4;
    p.value[11] += lbl_806512E4;
    for (i = 1; i < 28; i += 2) p.value[i] += lbl_806512E8;
    fn_8022B58C(&p.value[0]);
    fn_801E3AA4(0);
    fn_801E5430(10, 380);
    fn_801E56AC(lbl_80265D60, lbl_8064D5E4, lbl_806512DC,
                lbl_8064D5DC, lbl_8064D5D8);

    for (i = 0; i < 16; i++) packet.value[i] = lbl_806512EC;
    packet.value[0] = lbl_806512F0;
    packet.value[5] = lbl_806512F4;
    packet.value[10] = lbl_806512DC;
    packet.value[15] = lbl_806512DC;
    packet.value[3] = lbl_806512F8;
    packet.value[7] = lbl_806512FC;
    fn_8022B4B8(&packet, 1);
    fn_80228020(1);
    fn_8022806C(4, 0, 0, 0, 0, 0, 2);
    fn_8022A118(0, 255, 255, 4);
    fn_80229964(0, 4);
    fn_802262B8(0);
    fn_8022A2F4(1);
    fn_801ECEC8(0, 7, 0);
    fn_802254D0();
    fn_80224A60(9, 1);
    fn_8022551C(0, 9, 1, 4, 0);

    color = lbl_806512CC;
    fn_80227EB8(0, &color);
    fn_80226C18(96, 0);
    fn_80226AB4(168, 0, 2);
    fn_801EB068(p.value[18], p.value[19], lbl_80651300);
    fn_801EB068(p.value[20], p.value[21], lbl_80651300);
    fn_801EB064();
    color = lbl_806512D0;
    fn_80227EB8(0, &color);
    fn_80226C18(24, 0);
    fn_80226AB4(168, 0, 2);
    fn_801EB068(p.value[14], p.value[15], lbl_80651300);
    fn_801EB068(p.value[16], p.value[17], lbl_80651300);
    fn_801EB064();
    color = lbl_806512D4;
    fn_80227EB8(0, &color);
    fn_80226C18(24, 0);
    fn_80226AB4(168, 0, 2);
    fn_801EB068(p.value[10], p.value[11], lbl_80651300);
    fn_801EB068(p.value[12], p.value[13], lbl_80651300);
    fn_801EB064();
    color = lbl_806512C8;
    fn_80227EB8(0, &color);
    fn_80226C18(12, 0);
    fn_80226AB4(168, 0, 14);
    for (i = 0; i < 14; i++)
        fn_801EB068(p.value[i * 2], p.value[i * 2 + 1], lbl_80651300);
    fn_801EB064();
    fn_801ECEC8(1, 3, 1);
    for (i = 0; i < 16; i++) packet.value[i] = lbl_806512EC;
    packet.value[0] = p.value[1];
    packet.value[2] = p.value[3];
    packet.value[5] = p.value[5];
    packet.value[6] = p.value[6];
    packet.value[10] = p.value[7];
    packet.value[11] = p.value[8];
    packet.value[14] = lbl_80651300;
    fn_8022B4B8(&packet, 0);
}
