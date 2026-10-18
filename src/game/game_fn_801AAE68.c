typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Record {
    unsigned char pad00[0x50];
    Vec3 position;
    Vec3 velocity;
    unsigned char pad68[0x0C];
    int handle;
    float magnitude;
    unsigned char pad7C[4];
    int sequence;
    unsigned short kind;
    unsigned short id;
    unsigned char result;
    unsigned char arg4;
    unsigned char arg5;
    unsigned char pad8B[2];
    unsigned char clear8D;
    unsigned char flags;
    signed char active;
    unsigned char pad90;
    unsigned char arg8;
    unsigned char async;
    unsigned char clear93;
    unsigned char arg9;
    unsigned char pad95[3];
} Record;

extern int lbl_8064D2F4;
extern float lbl_80650E60;
extern float lbl_80650E74;
extern float lbl_80650E78;
extern Record* fn_801AAC10(void);
extern int fn_801AAD58(unsigned short, unsigned short, const Vec3*);
extern int fn_80236D30(void);
extern unsigned char fn_801ABF34(Vec3*, float, unsigned char, unsigned char,
                                 unsigned char);
extern int sndAddEmitter(Record*, Vec3*, Vec3*, float, float, int,
                       unsigned short, unsigned char, unsigned char, int);
extern void sndFXCtrl14(int, int, int);

int fn_801AAE68(unsigned short id, unsigned char arg4, unsigned char arg5,
                float magnitude, Vec3* position, signed char active,
                unsigned char arg8, unsigned char arg9, unsigned short kind,
                unsigned int flags)
{
    Record* record;
    unsigned int async;
    int result = 0;
    float zero;
    Record* owner;
    int mode;
    int call_result;

    async = flags & 0x10;

    if (async && fn_80236D30() != 0)
        goto done;
    record = fn_801AAC10();
    if (record == 0)
        goto done;
    if (active != 2 && fn_801AAD58(id, kind, position) != 0)
        goto done;

    record->position.x = position->x;
    record->position.y = position->y;
    record->position.z = position->z;
    zero = lbl_80650E60;
    record->velocity.x = zero;
    record->velocity.y = zero;
    record->velocity.z = zero;
    record->handle = -1;
    record->active = active;
    record->id = id;
    record->clear8D = 0;
    record->clear93 = 0;
    record->arg4 = arg4;
    record->arg5 = arg5;
    record->magnitude = magnitude;
    record->kind = kind;
    record->sequence = lbl_8064D2F4++;
    record->arg9 = arg9;
    record->arg8 = arg8;
    record->flags = flags & 3;
    record->flags |= (unsigned char)(flags & 0x20);
    record->result = fn_801ABF34(&record->position, record->magnitude,
                                 record->arg5, record->arg4, record->arg8);
    result = record->sequence;
    if (async) {
        record->async = 1;
        goto done;
    }
    record->async = 0;
    if (active == 2) {
        mode = 0;
        owner = 0;
    } else {
        mode = 31;
        owner = record;
    }
    call_result = sndAddEmitter(owner, &record->position, &record->velocity,
                              lbl_80650E74, lbl_80650E78, mode, record->id,
                              record->result, record->arg5, 0);
    if (flags & 0x40)
        sndFXCtrl14(call_result, 0x80, 0x3FFF);
    if (active == 2)
        record->active = 0;
done:
    return result;
}
