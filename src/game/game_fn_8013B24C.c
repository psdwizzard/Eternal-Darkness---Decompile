typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct FaceRef {
    unsigned short index;
    unsigned short pad;
    const void* data;
} FaceRef;

typedef struct TriggerShape {
    FaceRef face0;          /* 0x00 */
    FaceRef face1;          /* 0x08 */
    Vec3 normal0;           /* 0x10 */
    Vec3 normal1;           /* 0x1C */
    signed char context0;   /* 0x28 */
    signed char context1;   /* 0x29 */
    char pad2A[2];
    float offset0;          /* 0x2C */
    float offset1;          /* 0x30 */
    short value0;           /* 0x34 */
    short value1;           /* 0x36 */
} TriggerShape;

typedef struct TriggerObject {
    char pad00[0x2C];
    void* target;           /* 0x2C */
    TriggerShape shape;     /* 0x30 */
    int flags;              /* 0x68 */
    short type;             /* 0x6C */
} TriggerObject;

typedef struct Mover {
    Vec3 prev;              /* 0x00 */
    Vec3 pos;               /* 0x0C */
    Vec3 delta;             /* 0x18 */
    float limit;            /* 0x24 */
} Mover;

extern int fn_801A7E04(Vec3*, void*);
extern int fn_801A7EA8(void*, void*);
extern int fn_8013D88C(const Vec3*, const Vec3*, const FaceRef*, float, float,
                       const Vec3*, int, Vec3*);
extern int fn_8013B178(void*, void*, int, int, int);
extern void fn_8011DFE8(void*);
extern void fn_80047674(void*, void*);
extern void fn_800475E8(void*, void*);
extern float lbl_80650300;
extern float lbl_80650304;

void fn_8013B24C(TriggerObject* obj, Mover* mover, int mode, void* actor, int skip,
                 short* outValue, int* outKind, int update, int exact)
{
    TriggerShape* shape = &obj->shape;
    int hit = 0;
    short val0 = 0;
    short val1 = 0;
    short val2 = 0;
    Vec3 pos;
    Vec3 start;
    Vec3 hitPos;

    obj->flags &= ~4;
    if (skip == 0) {
        short type = obj->type;
        if (type == 0 || type == 1) {
            pos = mover->pos;
            pos.z += lbl_80650300;
            if (exact != 0) {
                hit = fn_801A7EA8(mover, obj);
            } else {
                hit = fn_801A7E04(&pos, obj);
            }
        } else if (type == 2) {
            if (mode != 1 && lbl_80650304 != mover->limit) {
                start = mover->prev;
                start.z += lbl_80650300;
                hit = fn_8013D88C(&start, &mover->delta, &shape->face0, mover->limit,
                                  shape->offset0, &shape->normal0, shape->context0, &hitPos);
                if (hit != 0) {
                    *outValue = shape->value0;
                    obj->flags |= 4;
                } else {
                    hit = fn_8013D88C(&start, &mover->delta, &shape->face1, mover->limit,
                                      shape->offset1, &shape->normal1, shape->context1, &hitPos);
                    if (hit != 0) {
                        *outValue = shape->value1;
                        obj->flags |= 8;
                    }
                }
            }
        }
    }

    if (mode == 0) {
        switch (obj->type) {
        case 0:
            val0 = ((short*)shape)[5];
            val1 = ((short*)shape)[6];
            val2 = ((short*)shape)[7];
            break;
        case 1:
            val0 = ((short*)shape)[6];
            val1 = ((short*)shape)[7];
            val2 = ((short*)shape)[8];
            break;
        }
    } else if (mode == 1) {
        switch (obj->type) {
        case 0:
            val0 = ((short*)shape)[8];
            val1 = ((short*)shape)[9];
            val2 = ((short*)shape)[10];
            break;
        case 1:
            val0 = ((short*)shape)[9];
            val1 = ((short*)shape)[10];
            val2 = ((short*)shape)[11];
            break;
        }
    }

    switch (fn_8013B178(actor, obj, hit, mode, update)) {
    case 0:
        break;
    case 2:
        if (mode == 0 && update != 0) {
            fn_8011DFE8(obj);
        }
        if (val1 > 0) {
            *outValue = val1;
            *outKind = 1;
        }
        if (update != 0) {
            fn_80047674(actor, obj->target);
        }
        break;
    case 1:
        if (val0 > 0) {
            *outValue = val0;
            *outKind = 2;
        }
        if (update != 0) {
            fn_800475E8(actor, obj->target);
        }
        break;
    case 3:
        if (val2 > 0) {
            *outValue = val2;
            *outKind = 3;
        }
        break;
    }
}
