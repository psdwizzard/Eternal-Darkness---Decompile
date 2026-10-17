typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct DefinitionData {
    u8 pad00[0x70];
    float values[5];
} DefinitionData;

typedef struct ObjectData {
    u8 pad00[0x8C];
    DefinitionData *definition;
    u8 pad90[0x0E];
    u8 category;
} ObjectData;

typedef struct Entry80201814 Entry80201814;

extern int fn_80201A84(void *);
extern Entry80201814 *fn_80201814(int);
extern void *fn_80201B8C(unsigned char *);
extern void fn_800C1B50(int, int, int, float, float);

extern u32 lbl_8023EB80[5];
extern float lbl_8064E350;
extern float lbl_8064E354;
extern float lbl_8064E358;

void fn_80045CE0(register void *source)
{
    register ObjectData *object;
    register s32 i;
    register int objectId;
    register float invalid1;
    register float invalid2;
    register float value;
    register Entry80201814 *entry;

    objectId = fn_80201A84(source);
    entry = fn_80201814(objectId);
    if (entry != 0) {
        object = fn_80201B8C((unsigned char *)entry);
        if (object != 0 &&
            (object->category == 2 || object->category == 1 || object->category == 4)) {
            invalid2 = lbl_8064E350;
            invalid1 = lbl_8064E354;
            i = 0;
            do {
                value = object->definition->values[i];
                if (invalid2 != value && invalid1 != value) {
                    fn_800C1B50(objectId, lbl_8023EB80[i], 0,
                                lbl_8064E358, value);
                }
                i++;
            } while (i < 5);
        }
    }
}
