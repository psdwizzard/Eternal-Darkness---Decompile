typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct DebugMesh DebugMesh;
typedef struct DebugOwner {
    u8 pad0[0xC];
    const s16* points;
} DebugOwner;

typedef struct DebugEntry {
    DebugMesh* mesh;
    DebugOwner* owner;
    u8 active;
    u8 pad9;
    u16 timer;
} DebugEntry;

extern DebugEntry lbl_805B1268[6];
extern u8 lbl_8064D018;
extern s16 lbl_802FC53C[];
extern Color lbl_802FC5BC[];
extern const float lbl_806503F0;
extern const float lbl_806503F4;

extern void fn_801ED468(int);
extern void fn_80226D28(int);
extern void fn_801ED118(void);
extern int fn_801EDA7C(s16*, int, int, void*);
extern void fn_801ECF50(u32);
extern void fn_80226C18(int, int);
extern void fn_80140E70(const s16*, DebugMesh*, u8, int, u8);
extern void fn_801ECD74(Color*);

/* NonMatching: MWCC pools the unsigned-to-float conversion bias under
 * a private symbol instead of referencing lbl_806503F8. */
void fn_80140D38(void)
{
    u8 i;
    Color color;

    if ((signed char)lbl_8064D018 != 0) {
        fn_801ED468(0x1B);
        fn_80226D28(0);
        fn_801ED118();
        fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
        fn_801ECF50(4);
        fn_80226C18(0x12, 0);
        for (i = 0; i < 6; i++) {
            DebugEntry* entry = &lbl_805B1268[i];
            if ((int)entry->active == 1) {
                fn_80140E70(entry->owner->points, entry->mesh, 6, 12,
                    (u8)(lbl_806503F0 * ((float)entry->timer / lbl_806503F4)));
            }
        }
        fn_80226D28(1);
        color = lbl_802FC5BC[3];
        fn_801ECD74(&color);
    }
}
