typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef f32 Matrix34[3][4];

typedef struct GXColor {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} GXColor;

typedef struct QueryResult {
    s32 words[2];
    Vec3 position;
    s32 tail[5];
} QueryResult;

typedef struct BoxFace {
    s32 unk0;
    Vec3 normal;
    u16 vertex[4];
    s32 unk18;
} BoxFace;

typedef struct CollisionBox {
    s16 vertex[8][3];
    BoxFace face[6];
} CollisionBox;

typedef struct CollisionModel {
    u8 pad[0xF0];
    s32 boxCount;
    CollisionBox *boxes;
} CollisionModel;

typedef struct CollisionObject {
    u8 pad[0x3C];
    CollisionModel *model;
} CollisionObject;

extern GXColor lbl_802FC5BC[];
extern f32 lbl_806502B0;

extern void fn_800EB750(Vec3 *quad, Vec3 *normal, GXColor *color, s32 alpha);
extern void fn_800EBA80(s32 mode, Vec3 *position, GXColor *color, s32 alpha, f32 size);
extern s32 fn_8011EB1C(void *);
extern Vec3 *fn_8011F130(void *);
extern s32 fn_8011F6A4(void *, s32, s32, s32, QueryResult *, s32);
extern f32 fn_8011F6F0(void *);
extern f32 fn_8011F6F8(void *);
extern Vec3 *fn_8011F770(void *);
extern u32 fn_8011FAEC(void *);
extern void *fn_8011FE34(void *);
extern void fn_80179B08(void *, Vec3 *);
extern void fn_802114E0(Matrix34, void *);
extern void fn_80211710(Matrix34, Vec3 *, Vec3 *);
extern void fn_80211A48(Vec3 *, Vec3 *, Vec3 *);

void fn_80137AF0(CollisionObject *object) {
    QueryResult query;
    Matrix34 mtx;
    Vec3 quad[4];
    Vec3 position;
    Vec3 normal;
    GXColor pointColor;
    GXColor altColor;
    GXColor originColor;
    GXColor modelColor;
    GXColor faceColor;
    s32 count;
    s32 i;
    CollisionBox *box;
    Vec3 *origin;
    s32 j;
    f32 size;
    Vec3 *offset;
    Vec3 *base;

    if (fn_8011FAEC(object) & 0x100000) {
        base = fn_8011F130(object);
        fn_8011F6F8(object);
        size = fn_8011F6F0(object);
        offset = fn_8011F770(object);
        fn_80211A48(base, offset, &position);
        if (fn_8011EB1C(object) == 2) {
            pointColor = lbl_802FC5BC[11];
            fn_800EBA80(0, &position, &pointColor, 0xB4, size);
        } else {
            altColor = lbl_802FC5BC[8];
            fn_800EBA80(0, &position, &altColor, 0xB4, size);
        }
        return;
    }

    count = object->model->boxCount;
    box = object->model->boxes;
    if (fn_8011F6A4(object, 0x1B, 0xF, -1, &query, 1) == -1) {
        origin = fn_8011F130(object);
    } else {
        origin = &query.position;
    }
    originColor = lbl_802FC5BC[3];
    fn_800EBA80(0, origin, &originColor, 0xB4, lbl_806502B0);
    modelColor = lbl_802FC5BC[13];
    fn_800EBA80(0, fn_8011F130(object), &modelColor, 0xB4, lbl_806502B0);

    fn_802114E0(mtx, fn_8011FE34(object));
    for (i = 0; i < count; i++, box++) {
        for (j = 0; j < 6; j++) {
            fn_80179B08(box->vertex[box->face[j].vertex[0]], &quad[0]);
            fn_80211710(mtx, &quad[0], &quad[0]);
            fn_80211A48(&quad[0], origin, &quad[0]);
            fn_80179B08(box->vertex[box->face[j].vertex[1]], &quad[1]);
            fn_80211710(mtx, &quad[1], &quad[1]);
            fn_80211A48(&quad[1], origin, &quad[1]);
            fn_80179B08(box->vertex[box->face[j].vertex[2]], &quad[2]);
            fn_80211710(mtx, &quad[2], &quad[2]);
            fn_80211A48(&quad[2], origin, &quad[2]);
            fn_80179B08(box->vertex[box->face[j].vertex[3]], &quad[3]);
            fn_80211710(mtx, &quad[3], &quad[3]);
            fn_80211A48(&quad[3], origin, &quad[3]);
            faceColor = lbl_802FC5BC[6];
            normal = box->face[j].normal;
            fn_800EB750(quad, &normal, &faceColor, 0x28);
        }
    }
}
