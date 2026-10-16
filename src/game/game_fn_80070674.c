typedef unsigned char u8;
typedef unsigned int u32;

/* Opaque views used by the corresponding callee definitions. */
typedef struct Owner Owner;
typedef struct Object80201D14 Object80201D14;
typedef struct Object80201D1C Object80201D1C;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D34 Object80201D34;
typedef struct Object80201EB8 Object80201EB8;

typedef struct ObjectState {
    u8 padding[0x14E];
    short counter;
} ObjectState;

typedef struct ObjectInfo {
    u8 padding[0x8C];
    ObjectState *state;
    u8 padding90[0xA];
    short id;
} ObjectInfo;

extern int fn_80200C10(int *);
extern void *fn_80201B8C(u8 *);
extern void *fn_80201BC8(void *);
extern int fn_80201B54(int *);
extern int fn_80072070(int);
extern void fn_80201D2C(Object80201D2C *, int);
extern void fn_80201D14(Object80201D14 *, unsigned char);
extern void fn_80201D34(Object80201D34 *, int);
extern void fn_80201D1C(Object80201D1C *, unsigned char);
extern int fn_801E8328(u32, u32);
extern int fn_80201EB8(Object80201EB8 *);
extern int fn_801261F4(Owner *);
extern int fn_8006BE44(void);
extern void *fn_8012C62C(u8 *, int, void *, signed char *, void *, int);
extern int lbl_8064D18C;
extern const u32 lbl_8064E838, lbl_8064E83C;
extern const u32 lbl_8064E840, lbl_8064E844;
extern const u32 lbl_8064E848, lbl_8064E84C;
extern const u32 lbl_80651988, lbl_8065198C, lbl_80651990;

int fn_80070674(u8 *object, int mode, int *event)
{
    int eventType;
    ObjectInfo *info;
    u8 *runtime;

    eventType = fn_80200C10(event);
    info = fn_80201B8C(object);
    runtime = fn_80201BC8(object);
    fn_80201B54((int *)object);
    if (mode == 0) {
        if (eventType == 1) {
            info->state->counter = fn_80072070(info->id);
            fn_80201D2C((Object80201D2C *)object, 1);
            fn_80201D14((Object80201D14 *)object, 1);
            return 1;
        } else if (eventType == 0x39) {
            fn_80201D34((Object80201D34 *)object, 0);
            fn_80201D1C((Object80201D1C *)object, 1);
            fn_801E8328(2, (u32)object);
            return 1;
        } else if (eventType == 0x3E) {
            if (lbl_8064D18C == fn_80201EB8((Object80201EB8 *)object)) {
                fn_801261F4((Owner *)runtime);
                if (fn_8006BE44() >= 2) {
                    info->state->counter++;
                    if (info->state->counter > 3) {
                        u32 start;
                        u32 end;
                        u32 color;
                        color = lbl_8064E83C;
                        end = lbl_8064E838;
                        start = lbl_80651988;
                        fn_8012C62C(runtime, 15, &start, (signed char *)&end, &color, 4);
                        info->state->counter = fn_80072070(info->id);
                    } else {
                        u32 start;
                        u32 end;
                        u32 color;
                        color = lbl_8065198C;
                        end = lbl_8064E844;
                        start = lbl_8064E840;
                        fn_8012C62C(runtime, 15, &start, (signed char *)&end, &color, 4);
                    }
                } else {
                    u32 start;
                    u32 end;
                    u32 color;
                    color = lbl_80651990;
                    end = lbl_8064E84C;
                    start = lbl_8064E848;
                    fn_8012C62C(runtime, 15, &start, (signed char *)&end, &color, 4);
                }
            }
            return 1;
        }
    } else if (mode == 1) {
        if (eventType == 1)
            return 1;
        if (eventType == 3)
            return 1;
    } else {
        return 0;
    }
    return 0;
}
