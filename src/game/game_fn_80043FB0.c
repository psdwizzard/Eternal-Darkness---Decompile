typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;

typedef struct PrimaryRecord {
    s16 x, y, z, group;
    u8 padding08[0x34];
    Vec3 axis;
    float angle;
    u16 zone, type, actor;
    s16 stageA, stageB;
    u8 padding56[0xC];
    u16 model, flag;
} PrimaryRecord;

typedef struct SecondaryRecord {
    s16 x, y, z, group;
    Vec3 axis;
    float angle;
    u16 type, zone;
    s16 stageA, stageB;
    u16 actor, model;
    u16 padding24, flag;
} SecondaryRecord;

typedef struct TertiaryRecord {
    s16 x, y, z, group;
    Vec3 axis;
    float angle;
    u16 type1, zone1, actor1;
    u16 type2, zone2, actor2;
    u16 type3, zone3, actor3;
    s16 stageA, stageB;
    u16 model, padding30, flag;
} TertiaryRecord;

typedef struct RecordList {
    int padding00;
    int secondaryCount;
    SecondaryRecord *secondary;
    int primaryCount;
    PrimaryRecord *primary;
    int padding14[2];
    int tertiaryCount;
    TertiaryRecord *tertiary;
} RecordList;

typedef struct ObjectInfo {
    u8 padding00[0x8C];
    void *actor;
    u8 padding90[8];
    s16 zone;
} ObjectInfo;

extern RecordList *lbl_8064D0BC;
extern int *lbl_8064C5A8;
extern const float lbl_8064E330;

extern void *fn_80201BC8(void *);
extern void *fn_8011F130(void *);
extern void *fn_8011FE34(void *);
extern void *fn_80201B94(u8 *);
extern void *fn_80201B8C(u8 *);
extern void fn_8017A244(const Vec3 *, Vec4 *, float);
extern void *fn_8011FB4C(void *);
extern int fn_8011EB04(void *);
extern int fn_80201B5C(int *);
extern void *fn_80201C50(void *);
extern unsigned int fn_80201CDC(void *);

int fn_80043FB0(void *object, int *category, int *index)
{
    void *runtime;
    Vec3 *position;
    Vec4 *rotation;
    void *model;
    ObjectInfo *info;
    Vec3 axis;
    Vec4 transformedPrimary;
    Vec4 transformedSecondary;
    Vec4 transformedTertiary;
    int i;
    int offset;
    PrimaryRecord *primary;
    SecondaryRecord *secondary;
    TertiaryRecord *tertiary;
    u16 zone, type;
    unsigned int actor;

    runtime = fn_80201BC8(object);
    position = (Vec3 *)fn_8011F130(runtime);
    rotation = (Vec4 *)fn_8011FE34(runtime);
    model = fn_80201B94((u8 *)object);
    info = (ObjectInfo *)fn_80201B8C((u8 *)object);

    offset = 0;
    for (i = 0; i < lbl_8064D0BC->primaryCount; i++) {
        primary = (PrimaryRecord *)((u8 *)lbl_8064D0BC->primary + offset);
        axis.x = -primary->axis.x;
        axis.y = -primary->axis.y;
        axis.z = -primary->axis.z;
        fn_8017A244(&axis, &transformedPrimary, primary->angle);
        if (!((float)primary->x >= position->x - 0.1f)) goto nextPrimary;
        if (!((float)primary->x <= 0.1f + position->x)) goto nextPrimary;
        if (!((float)primary->y >= position->y - 0.1f)) goto nextPrimary;
        if (!((float)primary->y <= 0.1f + position->y)) goto nextPrimary;
        if (!((float)primary->z >= position->z - 0.1f)) goto nextPrimary;
        if (!((float)primary->z <= 0.1f + position->z)) goto nextPrimary;
        if (primary->group != (int)fn_8011FB4C(runtime)) goto nextPrimary;
        if (!(transformedPrimary.x >= rotation->x - lbl_8064E330)) goto nextPrimary;
        {
            float upper = lbl_8064E330;
            upper += rotation->x;
            if (!(transformedPrimary.x <= upper)) goto nextPrimary;
        }
        if (!(transformedPrimary.y >= rotation->y - lbl_8064E330)) goto nextPrimary;
        {
            float upper = lbl_8064E330;
            upper += rotation->y;
            if (!(transformedPrimary.y <= upper)) goto nextPrimary;
        }
        if (!(transformedPrimary.z >= rotation->z - lbl_8064E330)) goto nextPrimary;
        {
            float upper = lbl_8064E330;
            upper += rotation->z;
            if (!(transformedPrimary.z <= upper)) goto nextPrimary;
        }
        if (!(transformedPrimary.w >= rotation->w - lbl_8064E330)) goto nextPrimary;
        {
            float upper = lbl_8064E330;
            upper += rotation->w;
            if (!(transformedPrimary.w <= upper)) goto nextPrimary;
        }
        if (primary->zone != info->zone) goto nextPrimary;
        if (primary->type != fn_8011EB04(runtime)) goto nextPrimary;
        if (primary->actor != fn_80201B5C((int *)object)) goto nextPrimary;
        if (primary->stageA != *(s16 *)((u8 *)info->actor + 0x146)) goto nextPrimary;
        if (primary->stageB != *(s16 *)((u8 *)info->actor + 0x148)) goto nextPrimary;
        if (primary->model != (int)fn_80201C50(model)) goto nextPrimary;
        if ((int)primary->flag != (int)((fn_80201CDC(object) >> 2) & 1)) goto nextPrimary;
        *category = 0;
        *index = i;
        return 0;
    nextPrimary:
        offset += 0x68;
    }

    i = 0;
    offset = 0;
    for (; i < lbl_8064D0BC->secondaryCount; i++) {
        secondary = (SecondaryRecord *)((u8 *)lbl_8064D0BC->secondary + offset);
        axis.x = -secondary->axis.x;
        axis.y = -secondary->axis.y;
        axis.z = -secondary->axis.z;
        fn_8017A244(&axis, &transformedSecondary, secondary->angle);
        if (!((float)secondary->x >= position->x - 0.1f)) goto nextSecondary;
        if (!((float)secondary->x <= 0.1f + position->x)) goto nextSecondary;
        if (!((float)secondary->y >= position->y - 0.1f)) goto nextSecondary;
        if (!((float)secondary->y <= 0.1f + position->y)) goto nextSecondary;
        if (!((float)secondary->z >= position->z - 0.1f)) goto nextSecondary;
        if (!((float)secondary->z <= 0.1f + position->z)) goto nextSecondary;
        if (secondary->group != (int)fn_8011FB4C(runtime)) goto nextSecondary;
        if (!(transformedSecondary.x >= rotation->x - lbl_8064E330)) goto nextSecondary;
        {
            float upper = lbl_8064E330;
            upper += rotation->x;
            if (!(transformedSecondary.x <= upper)) goto nextSecondary;
        }
        if (!(transformedSecondary.y >= rotation->y - lbl_8064E330)) goto nextSecondary;
        {
            float upper = lbl_8064E330;
            upper += rotation->y;
            if (!(transformedSecondary.y <= upper)) goto nextSecondary;
        }
        if (!(transformedSecondary.z >= rotation->z - lbl_8064E330)) goto nextSecondary;
        {
            float upper = lbl_8064E330;
            upper += rotation->z;
            if (!(transformedSecondary.z <= upper)) goto nextSecondary;
        }
        if (!(transformedSecondary.w >= rotation->w - lbl_8064E330)) goto nextSecondary;
        {
            float upper = lbl_8064E330;
            upper += rotation->w;
            if (!(transformedSecondary.w <= upper)) goto nextSecondary;
        }
        if (secondary->zone != info->zone) goto nextSecondary;
        if (secondary->type != fn_8011EB04(runtime)) goto nextSecondary;
        if (secondary->actor != fn_80201B5C((int *)object)) goto nextSecondary;
        if (secondary->stageA != *(s16 *)((u8 *)info->actor + 0x146)) goto nextSecondary;
        if (secondary->stageB != *(s16 *)((u8 *)info->actor + 0x148)) goto nextSecondary;
        if (secondary->model != (int)fn_80201C50(model)) goto nextSecondary;
        if ((int)secondary->flag != (int)((fn_80201CDC(object) >> 2) & 1)) goto nextSecondary;
        *category = 1;
        *index = i;
        return 0;
    nextSecondary:
        offset += 0x28;
    }

    i = 0;
    offset = 0;
    for (; i < lbl_8064D0BC->tertiaryCount; i++) {
        tertiary = (TertiaryRecord *)((u8 *)lbl_8064D0BC->tertiary + offset);
        axis.x = -tertiary->axis.x;
        axis.y = -tertiary->axis.y;
        axis.z = -tertiary->axis.z;
        fn_8017A244(&axis, &transformedTertiary, tertiary->angle);
        switch (*lbl_8064C5A8) {
        case 1:
            zone = tertiary->zone1;
            type = tertiary->type1;
            actor = tertiary->actor1;
            break;
        case 2:
            zone = tertiary->zone2;
            type = tertiary->type2;
            actor = tertiary->actor2;
            break;
        case 3:
            zone = tertiary->zone3;
            type = tertiary->type3;
            actor = tertiary->actor3;
            break;
        }
        if (!((float)tertiary->x >= position->x - 0.1f)) goto nextTertiary;
        if (!((float)tertiary->x <= 0.1f + position->x)) goto nextTertiary;
        if (!((float)tertiary->y >= position->y - 0.1f)) goto nextTertiary;
        if (!((float)tertiary->y <= 0.1f + position->y)) goto nextTertiary;
        if (!((float)tertiary->z >= position->z - 0.1f)) goto nextTertiary;
        if (!((float)tertiary->z <= 0.1f + position->z)) goto nextTertiary;
        if (tertiary->group != (int)fn_8011FB4C(runtime)) goto nextTertiary;
        if (!(transformedTertiary.x >= rotation->x - lbl_8064E330)) goto nextTertiary;
        {
            float upper = lbl_8064E330;
            upper += rotation->x;
            if (!(transformedTertiary.x <= upper)) goto nextTertiary;
        }
        if (!(transformedTertiary.y >= rotation->y - lbl_8064E330)) goto nextTertiary;
        {
            float upper = lbl_8064E330;
            upper += rotation->y;
            if (!(transformedTertiary.y <= upper)) goto nextTertiary;
        }
        if (!(transformedTertiary.z >= rotation->z - lbl_8064E330)) goto nextTertiary;
        {
            float upper = lbl_8064E330;
            upper += rotation->z;
            if (!(transformedTertiary.z <= upper)) goto nextTertiary;
        }
        if (!(transformedTertiary.w >= rotation->w - lbl_8064E330)) goto nextTertiary;
        {
            float upper = lbl_8064E330;
            upper += rotation->w;
            if (!(transformedTertiary.w <= upper)) goto nextTertiary;
        }
        if (zone != info->zone) goto nextTertiary;
        if (type != fn_8011EB04(runtime)) goto nextTertiary;
        if ((int)actor != fn_80201B5C((int *)object)) goto nextTertiary;
        if (tertiary->stageA != *(s16 *)((u8 *)info->actor + 0x146)) goto nextTertiary;
        if (tertiary->stageB != *(s16 *)((u8 *)info->actor + 0x148)) goto nextTertiary;
        if (tertiary->model != (int)fn_80201C50(model)) goto nextTertiary;
        if ((int)tertiary->flag != (int)((fn_80201CDC(object) >> 2) & 1)) goto nextTertiary;
        *category = 2;
        *index = i;
        return 0;
    nextTertiary:
        offset += 0x34;
    }
    return 1;
}
