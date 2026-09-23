typedef int s32;
typedef unsigned int u32;
typedef u32* Color;
typedef unsigned char u8;
typedef float f32;

#pragma use_lmw_stmw on

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef f32 Mtx[3][4];

typedef struct BatchEntry {
    u8 data[0x1B8];
} BatchEntry;

typedef struct Quad {
    Vec3f points[4];
} Quad;

extern const Quad lbl_80238BF8;
extern char lbl_802515D0[];
extern s32 lbl_8064CBA4;
extern const f32 lbl_8064DF58;
extern const f32 lbl_8064DF64;
extern const f32 lbl_8064DF74;
extern const f32 lbl_8064DF78;

extern void fn_80225F4C(s32, void*, s32);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_80211268(Mtx, u8, f32);
extern void fn_80211710(Mtx, Vec3f*, Vec3f*);
extern void fn_801ECF50(s32);
extern void fn_80226AB4(s32, s32, s32);
extern void fn_80026754(s32, s32, s32);
extern void fn_80026744(f32, f32);
extern void fn_80026740(void);

/* NonMatching: the eight signed corner assignments and conversion stack
 * slots agree with retail. Remaining differences are GPR allocation, quad
 * addressing, cursor setup order, and the compiler-generated bias symbol. */
void fn_80026320(BatchEntry* batch)
{
    s32 i;
    u8* entry;
    const Quad* initial = &lbl_80238BF8;

    fn_80225F4C(13, lbl_802515D0, 4);

    for (i = 0; i < 11; i++) {
        entry = batch->data + i * 0x24;
        if (entry[0x4B] != 0) {
            s32 extent = *(s32*)(entry + 0x34);
            u32 value;
            Quad points;
            Vec3f source0;
            Vec3f source1;
            Vec3f source2;
            Vec3f source3;
            Mtx matrix;
            f32 center_x;
            f32 center_y;

            source0 = initial->points[0];
            source1 = initial->points[1];
            source2 = initial->points[2];
            source3 = initial->points[3];

            center_x = *(f32*)(entry + 0x2C);
            center_y = *(f32*)(entry + 0x30);

            source0.x = -extent;
            source0.y = -extent;
            source1.x = extent;
            source1.y = -extent;
            source2.x = extent;
            source2.y = extent;
            points.points[0] = source0;
            points.points[1] = source1;
            points.points[2] = source2;
            source3.x = -extent;
            source3.y = extent;
            points.points[3] = source3;

            value = *(u32*)(entry + 0x48);
            fn_801A852C(&value, 0, *(u32*)(entry + 0x38), 0x80000000);
            fn_80211268(matrix, 'z', *(f32*)(entry + 0x40));
            fn_80211710(matrix, &points.points[0], &points.points[0]);
            fn_80211710(matrix, &points.points[1], &points.points[1]);
            fn_80211710(matrix, &points.points[2], &points.points[2]);
            fn_80211710(matrix, &points.points[3], &points.points[3]);

            if (lbl_8064CBA4 == 1) {
                points.points[0].x /= lbl_8064DF74;
                points.points[1].x /= lbl_8064DF74;
                points.points[2].x /= lbl_8064DF74;
                points.points[3].x /= lbl_8064DF74;
            }

            points.points[0].x = lbl_8064DF78 * (points.points[0].x + center_x);
            points.points[1].x = lbl_8064DF78 * (points.points[1].x + center_x);
            points.points[2].x = lbl_8064DF78 * (points.points[2].x + center_x);
            points.points[3].x = lbl_8064DF78 * (points.points[3].x + center_x);
            points.points[0].y = lbl_8064DF78 * (points.points[0].y + center_y);
            points.points[1].y = lbl_8064DF78 * (points.points[1].y + center_y);
            points.points[2].y = lbl_8064DF78 * (points.points[2].y + center_y);
            points.points[3].y = lbl_8064DF78 * (points.points[3].y + center_y);

            fn_801ECF50(8);
            fn_80226AB4(0x80, 2, 4);
            fn_80026754((s32)points.points[0].x, (s32)points.points[0].y, -0x20);
            fn_80026744(lbl_8064DF58, lbl_8064DF58);
            fn_80026754((s32)points.points[1].x, (s32)points.points[1].y, -0x20);
            fn_80026744(lbl_8064DF64, lbl_8064DF58);
            fn_80026754((s32)points.points[2].x, (s32)points.points[2].y, -0x20);
            fn_80026744(lbl_8064DF64, lbl_8064DF64);
            fn_80026754((s32)points.points[3].x, (s32)points.points[3].y, -0x20);
            fn_80026744(lbl_8064DF58, lbl_8064DF64);
            fn_80026740();
        }
    }
}
