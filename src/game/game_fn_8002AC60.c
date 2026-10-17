typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct QueryResult {
    u8 pad[8];
    Vec3 position;
    Vec3 direction;
    u8 pad2[8];
} QueryResult;

typedef struct TargetInfo {
    u8 pad[4];
    Vec3 position;
} TargetInfo;

typedef struct DebugPath {
    Vec3 start[10];
    Vec3 end[10];
    u32 active[10];
} DebugPath;

typedef struct PaletteEntry {
    u8 pad[4];
    int disabled;
} PaletteEntry;

typedef struct Palette {
    u8 pad[0x70];
    PaletteEntry **entries;
} Palette;

typedef struct Actor {
    u8 pad[0x9F];
    u8 kind;
} Actor;

extern void *fn_80156938(void *callback);
extern void *fn_80201BC8(void *object);
extern int fn_80201ADC(void);
extern void fn_801EC9A8(void);
extern Palette *fn_8015C28C(int id);
extern u32 fn_8011FAEC(void *model);
extern void fn_80120A30(void *model, void *entry, void *tag);
extern void *fn_80201B8C(void *object);
extern void fn_80201E78(Vec3 *out, void *object);
extern int fn_8011F6A4(void *model, int a, int b, int c, void *out, int d);
extern void fn_801E7CBC(Vec3 *a, Vec3 *b, Vec3 *c, Vec3 *d, u32 *color);

/* Keep separate copies for each face submitted to the renderer. */
#define DRAW_FACE(a, b, c, d, color) do { \
    Vec3 faceA, faceB, faceC, faceD; \
    Color faceColor; \
    faceColor = (color); \
    faceD = (d); \
    faceC = (c); \
    faceB = (b); \
    faceA = (a); \
    fn_801E7CBC(&faceA, &faceB, &faceC, &faceD, (u32 *)&faceColor); \
} while (0)
extern void *fn_80205288(void *object);
extern u32 fn_80178E94(const f32 *a, const f32 *b);
extern void fn_80211A90(const Vec3 *in, Vec3 *out, f32 scale);
extern void fn_80211A48(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void fn_80211C78(Vec3 *a, Vec3 *b, Vec3 *out);
extern void fn_80211AAC(Vec3 *in, Vec3 *out);
extern void fn_800EBA80(int a, Vec3 *pos, Color *color, u8 b, f32 c);

extern DebugPath lbl_80303A18;
extern const Vec3 lbl_80238CC4;
extern Color lbl_802FC5BC[19];
extern void *lbl_8064C4E4;
extern int lbl_8064C5C4;
extern int lbl_8064C5C8;
extern int lbl_8064C710;
extern u8 *lbl_8064C718;
extern int lbl_8064CB5C;
extern int lbl_8064CB60;
extern u8 lbl_8064D5F8;
extern const Color lbl_8064E004;
extern const Color lbl_8064E008;
extern const Color lbl_8064E00C;
extern const Color lbl_8064E010;
extern const f32 lbl_8064E014;
extern const f32 lbl_8064E018;
extern const f32 lbl_8064E01C;
extern const f32 lbl_8064E020;
extern const f32 lbl_8064E024;

void fn_8002AC60(void *callback) {
    QueryResult result;
    QueryResult hit;
    Vec3 position;
    Vec3 positionLow;
    Vec3 otherLow;
    Vec3 start;
    Vec3 startHigh;
    Vec3 target;
    Vec3 endHigh;
    Vec3 offset;
    Vec3 end;
    Vec3 side;
    Vec3 tip;
    Vec3 tipHigh;
    Vec3 lineEnd;
    Vec3 lineStart;
    Vec3 lineTip;
    Color offColor;
    Color onColor;
    Color color;
    Vec3 *starts;
    Vec3 *ends;
    u32 *active;
    void *object;
    register void *model;
    register void *current;
    Palette *palette;
    PaletteEntry **entries;
    void **info;
    void *partner;
    void *partnerModel;
    Actor *actor;
    int kind;
    int i;
    DebugPath *path;

    path = &lbl_80303A18;
    object = fn_80156938(callback);
    model = fn_80201BC8(object);
    current = fn_80201BC8((void *)fn_80201ADC());
    fn_801EC9A8();
    if (lbl_8064C5C4 == 0 && model == lbl_8064C4E4) {
        return;
    }
    if (lbl_8064C5C8 == 0) {
        /* ASM: cmplw, bne and b preserve the original early-exit branch
         * shape; MWCC merges the equivalent C test into a single beq. */
        asm {
            cmplw current, model
            bne render
            b done
        }
    }
render:
    if (model != 0) {
        palette = fn_8015C28C(2);
        fn_8011FAEC(model);
        entries = palette->entries;
        if (entries != 0) {
            if (entries[lbl_8064D5F8]->disabled != 0) {
                fn_80120A30(model, entries[lbl_8064D5F8], (void *)0xBB8);
            } else {
                fn_80120A30(model, entries[0], (void *)0xBB8);
            }
        } else {
            fn_80120A30(model, 0, (void *)0xBB8);
        }

        if (lbl_8064CB5C != 0) {
            info = fn_80201B8C(object);
            if (info != 0 && info[1] != 0) {
                Vec3 fetched;
                Vec3 other;

                fn_80201E78(&fetched, object);
                position = fetched;
                other = lbl_80238CC4;
                color = lbl_8064E004;
                if (fn_8011F6A4(model, 0x13, 0, -1, &result, 1) != -1) {
                    position = result.position;
                } else {
                    position.z += lbl_8064E014;
                }
                positionLow = position;
                positionLow.z -= lbl_8064E018;
                otherLow = other;
                otherLow.z -= lbl_8064E018;
                DRAW_FACE(position, positionLow, other, otherLow, color);
                DRAW_FACE(otherLow, other, positionLow, position, color);
            }
        }

        if (lbl_8064CB60 != 0) {
            info = fn_80201B8C(object);
            if (info != 0 && *info != 0) {
                partner = fn_80205288(object);
                if (partner != 0) {
                    partnerModel = fn_80201BC8(partner);
                } else {
                    partnerModel = 0;
                }
                if (partner != 0) {
                    actor = fn_80201B8C(partner);
                } else {
                    actor = 0;
                }
                kind = actor != 0 ? actor->kind : 0x13;
                if (kind == 0x12 && partnerModel != 0) {
                    Vec3 fetched;
                    Color lineColor;
                    u32 length;
                    Vec3 *direction;

                    fn_80201E78(&fetched, object);
                    start = fetched;
                    lineColor = lbl_8064E008;
                    target = ((TargetInfo *)*info)->position;
                    offColor = lbl_8064E00C;
                    onColor = lbl_8064E010;
                    if (fn_8011F6A4(partnerModel, 4, -1, -1, &hit, 1) != -1) {
                        start = hit.position;
                    }
                    length = fn_80178E94(&start.x, &target.x);
                    direction = &hit.direction;
                    fn_80211A90(direction, &offset, (f32)length);
                    fn_80211A48(&hit.position, &offset, &end);
                    startHigh = start;
                    startHigh.z += lbl_8064E01C;
                    endHigh = end;
                    endHigh.z += lbl_8064E01C;
                    lineStart = start;
                    lineEnd = end;
                    DRAW_FACE(start, startHigh, end, endHigh, lineColor);
                    DRAW_FACE(endHigh, end, startHigh, start, lineColor);

                    {
                        Color markerColor = lbl_802FC5BC[5];
                        fn_800EBA80(0, &target, &markerColor, 100, lbl_8064E020);
                    }

                    if (lbl_8064C718 != 0) {
                        fn_80211C78(direction, (Vec3 *)(lbl_8064C718 + 0x14), &side);
                        fn_80211AAC(&side, &side);
                        fn_80211A90(&side, &side, lbl_8064E024);
                        fn_80211A48(&end, &side, &tip);
                        tipHigh = tip;
                        tipHigh.z += lbl_8064E01C;
                        lineTip = tip;
                        DRAW_FACE(end, endHigh, tip, tipHigh, lineColor);
                        DRAW_FACE(tipHigh, tip, endHigh, end, lineColor);
                    }

                    starts = path->start;
                    ends = path->end;
                    active = path->active;
                    for (i = 0; i <= lbl_8064C710; i++) {
                        u32 enabled = active[i];
                        start = *starts;
                        startHigh = start;
                        startHigh.z += lbl_8064E01C;
                        end = *ends;
                        endHigh = end;
                        endHigh.z += lbl_8064E01C;
                        if (enabled != 0) {
                            DRAW_FACE(start, startHigh, end, endHigh, onColor);
                            DRAW_FACE(endHigh, end, startHigh, start, onColor);
                        } else {
                            DRAW_FACE(start, startHigh, end, endHigh, offColor);
                            DRAW_FACE(endHigh, end, startHigh, start, offColor);
                        }
                        starts++;
                        ends++;
                    }
                }
            }
        }
    }
done:
    return;
}
