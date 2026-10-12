typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct SpawnRequest {
    Vec3 position;
    float scale;
    int kind;
    int subtype;
    int param18;
    int param1C;
    int param20;
    int param24;
    int count;
    int owner;
    int enabled;
    u16 flags;
    u8 active;
    u8 pad37;
} SpawnRequest;

extern void *fn_80201BC8(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_80201B54(int *);
extern int fn_80035628(void *);
extern int fn_800CAC5C(int, int, int *, int *, int *);
extern void fn_80043F44(SpawnRequest *);
extern float fn_8012B750(void *);
extern int fn_800CA554(void *, u32);
extern void *fn_801DD200(int, SpawnRequest *, int, int, int, u16, int);
extern void fn_801DE5D4(void *, int);

void *fn_800CA3A0(void *object, int type, Vec3 *position, register int argOption)
{
    SpawnRequest request;
    Vec3 sourcePosition;
    int kind;
    int subtype;
    int value;
    int mode;
    register int usePosition;
    register int option;
    int id;
    void *result;
    Vec3 *source;

    /* ASM: mr preserves the option copy in a separate register. MWCC
     * coalesces the C assignment with the parameter, changing allocation. */
    asm { mr option, argOption }
    result = 0;
    usePosition = 0;
    source = fn_80201BC8(object);
    fn_8011F114(&sourcePosition, source);
    id = fn_80201B54(object);
    mode = fn_80035628(object);
    if (fn_800CAC5C(type, mode, &kind, &subtype, &value)) {
        fn_80043F44(&request);
        request.kind = kind;
        request.subtype = subtype;
        request.scale = fn_8012B750(source);
        request.count = 40;
        if (position != 0) {
            usePosition = 1;
            request.position = *position;
        }
        result = fn_801DD200(id, &request, (int)fn_800CA554,
                            ((u32)id << 8) | 0x78, usePosition, 200, option);
        fn_801DE5D4(result, value);
    }
    return result;
}
