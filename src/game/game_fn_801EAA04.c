typedef unsigned int u32;

typedef struct DrawColor {
    unsigned char r, g, b, a;
} DrawColor;

typedef struct DrawParams {
    float value[28];
} DrawParams;

typedef struct DrawPointPair {
    float value[4];
} DrawPointPair;

typedef struct DrawData {
    DrawParams params;
    DrawPointPair pair0;
    DrawPointPair pair1;
    DrawPointPair pair2;
} DrawData;

typedef struct DrawPacket {
    float value[16];
} DrawPacket;

extern DrawData lbl_8023B6C8;
extern DrawColor lbl_806512C8;
extern DrawColor lbl_806512CC;
extern DrawColor lbl_806512D0;
extern DrawColor lbl_806512D4;
extern float lbl_806512D8;
extern float lbl_806512DC;
extern float lbl_806512E0;
extern float lbl_806512E4;
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

extern void GXGetProjectionv(float*);
extern void fn_801E3AA4(int);
extern void fn_801E5430(int, int);
extern void fn_801E56AC(float, const char*, ...);
extern void GXSetProjection(DrawPacket*, int);
extern void GXSetNumChans(int);
extern void GXSetChanCtrl(int, int, int, int, int, int, int);
extern void GXSetTevOrder(int, int, int, int);
extern void GXSetTevOp(int, int);
extern void GXSetNumTexGens(int);
extern void GXSetNumTevStages(int);
extern void fn_801ECEC8(int, int, int);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int, int);
extern void GXSetVtxAttrFmt(int, int, int, int, int);
extern void PSMTXIdentity(void*);
extern void GXLoadPosMtxImm(void*, int);
extern void GXSetChanMatColor(int, DrawColor);
extern void GXSetLineWidth(int, int);
extern void GXBegin(int, int, int);
extern void fn_801EB068(float, float, float);
extern void fn_801EB064(void);

void fn_801EAA04(float width, float height)
{
    /* The template contains the outline followed by three line segments. */
    float* data = (float*)&lbl_8023B6C8;
    DrawColor color3 = lbl_806512C8;
    DrawParams p = *(DrawParams*)data;
    DrawPacket packet;
    float matrix[12];
    float transformed[7];
    float offset;
    DrawColor color0 = lbl_806512CC;
    DrawPointPair pair0 = *(DrawPointPair*)((char*)data + 112);
    DrawColor color1 = lbl_806512D0;
    DrawPointPair pair1 = *(DrawPointPair*)((char*)data + 128);
    DrawColor color2 = lbl_806512D4;
    DrawPointPair pair2 = *(DrawPointPair*)((char*)data + 144);
    float sy;
    float sx = height / lbl_806512D8;

    if (sx > lbl_806512DC) sx = lbl_806512DC;
    ((float*)&pair2)[2] *= sx;
    sy = width / lbl_806512D8;
    if (sy > 1.0f) sy = 1.0f;
    ((float*)&pair1)[2] *= sy;
    ((float*)&pair1)[1] += lbl_806512E0;
    ((float*)&pair1)[3] += lbl_806512E0;
    ((float*)&pair2)[1] += lbl_806512E4;
    ((float*)&pair2)[3] += lbl_806512E4;
    /* The vertical offset uses the compiler's pooled float constant. */
    offset = -8.0f;
    p.value[1] += offset;
    p.value[3] += offset;
    p.value[5] += offset;
    p.value[7] += offset;
    p.value[9] += offset;
    p.value[11] += offset;
    p.value[13] += offset;
    p.value[15] += offset;
    p.value[17] += offset;
    p.value[19] += offset;
    p.value[21] += offset;
    p.value[23] += offset;
    p.value[25] += offset;
    p.value[27] += offset;
    GXGetProjectionv(transformed);
    fn_801E3AA4(0);
    fn_801E5430(10, 380);
    fn_801E56AC(lbl_806512DC, lbl_80265D60,
                lbl_8064D5DC, lbl_8064D5D8, lbl_8064D5E4);

    packet.value[0] = lbl_806512EC;
    packet.value[1] = lbl_806512EC;
    packet.value[2] = lbl_806512EC;
    packet.value[3] = lbl_806512EC;
    packet.value[4] = lbl_806512EC;
    packet.value[5] = lbl_806512EC;
    packet.value[6] = lbl_806512EC;
    packet.value[7] = lbl_806512EC;
    packet.value[8] = lbl_806512EC;
    packet.value[9] = lbl_806512EC;
    packet.value[10] = lbl_806512EC;
    packet.value[11] = lbl_806512EC;
    packet.value[12] = lbl_806512EC;
    packet.value[13] = lbl_806512EC;
    packet.value[14] = lbl_806512EC;
    packet.value[15] = lbl_806512EC;
    packet.value[0] = lbl_806512F0;
    packet.value[5] = lbl_806512F4;
    packet.value[15] = packet.value[10] = lbl_806512DC;
    packet.value[3] = lbl_806512F8;
    packet.value[7] = lbl_806512FC;
    GXSetProjection(&packet, 1);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetTevOrder(0, 255, 255, 4);
    GXSetTevOp(0, 4);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    fn_801ECEC8(0, 7, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    PSMTXIdentity(matrix);
    GXLoadPosMtxImm(matrix, 0);

    GXSetChanMatColor(0, color0);
    GXSetLineWidth(96, 0);
    GXBegin(168, 0, 2);
    fn_801EB068(((float*)&pair0)[0], ((float*)&pair0)[1], lbl_80651300);
    fn_801EB068(((float*)&pair0)[2], ((float*)&pair0)[3], lbl_80651300);
    fn_801EB064();
    GXSetChanMatColor(0, color1);
    GXSetLineWidth(24, 0);
    GXBegin(168, 0, 2);
    fn_801EB068(((float*)&pair1)[0], ((float*)&pair1)[1], lbl_80651300);
    fn_801EB068(((float*)&pair1)[2], ((float*)&pair1)[3], lbl_80651300);
    fn_801EB064();
    GXSetChanMatColor(0, color2);
    GXSetLineWidth(24, 0);
    GXBegin(168, 0, 2);
    fn_801EB068(((float*)&pair2)[0], ((float*)&pair2)[1], lbl_80651300);
    fn_801EB068(((float*)&pair2)[2], ((float*)&pair2)[3], lbl_80651300);
    fn_801EB064();
    GXSetChanMatColor(0, color3);
    GXSetLineWidth(12, 0);
    GXBegin(168, 0, 14);
    fn_801EB068(p.value[0], p.value[1], lbl_80651300);
    fn_801EB068(p.value[2], p.value[3], lbl_80651300);
    fn_801EB068(p.value[4], p.value[5], lbl_80651300);
    fn_801EB068(p.value[6], p.value[7], lbl_80651300);
    fn_801EB068(p.value[8], p.value[9], lbl_80651300);
    fn_801EB068(p.value[10], p.value[11], lbl_80651300);
    fn_801EB068(p.value[12], p.value[13], lbl_80651300);
    fn_801EB068(p.value[14], p.value[15], lbl_80651300);
    fn_801EB068(p.value[16], p.value[17], lbl_80651300);
    fn_801EB068(p.value[18], p.value[19], lbl_80651300);
    fn_801EB068(p.value[20], p.value[21], lbl_80651300);
    fn_801EB068(p.value[22], p.value[23], lbl_80651300);
    fn_801EB068(p.value[24], p.value[25], lbl_80651300);
    fn_801EB068(p.value[26], p.value[27], lbl_80651300);
    fn_801EB064();
    fn_801ECEC8(1, 3, 1);
    packet.value[0] = lbl_806512EC;
    packet.value[1] = lbl_806512EC;
    packet.value[2] = lbl_806512EC;
    packet.value[3] = lbl_806512EC;
    packet.value[4] = lbl_806512EC;
    packet.value[5] = lbl_806512EC;
    packet.value[6] = lbl_806512EC;
    packet.value[7] = lbl_806512EC;
    packet.value[8] = lbl_806512EC;
    packet.value[9] = lbl_806512EC;
    packet.value[10] = lbl_806512EC;
    packet.value[11] = lbl_806512EC;
    packet.value[12] = lbl_806512EC;
    packet.value[13] = lbl_806512EC;
    packet.value[14] = lbl_806512EC;
    packet.value[15] = lbl_806512EC;
    packet.value[0] = transformed[1];
    packet.value[2] = transformed[2];
    packet.value[5] = transformed[3];
    packet.value[6] = transformed[4];
    packet.value[10] = transformed[5];
    packet.value[11] = transformed[6];
    packet.value[14] = lbl_80651300;
    GXSetProjection(&packet, 0);
}
