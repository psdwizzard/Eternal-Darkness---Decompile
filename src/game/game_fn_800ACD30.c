typedef struct Vec3s {
    short x, y, z;
} Vec3s;

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct SpawnRequest {
    Vec3f position;
    float facing;
    unsigned int kind;
    unsigned int subtype;
    unsigned int param18;
    unsigned int param1C;
    unsigned int param20;
    unsigned int param24;
    unsigned int count;
    void *owner;
    unsigned int enabled;
    unsigned short flags;
    unsigned char active;
    unsigned char pad37;
} SpawnRequest;

typedef struct ObjectData {
    unsigned char pad0[0x94];
    int state;
} ObjectData;

extern unsigned int fn_801E741C(const char *);
extern int fn_8015C4A4(void *, int);
extern void *fn_80158ABC(int, int, float *);
extern ObjectData *fn_80201B8C(void *);
extern void fn_80043F44(SpawnRequest *);
extern int fn_80034708(void *);
extern void fn_800355F0(void *, int);
extern void fn_80201D54(void *, void *);
extern void fn_802015A4(void *);
extern int fn_800CCA44(void *);
extern int fn_801E8328(unsigned int, unsigned int);
extern const char lbl_802458C4[];
extern unsigned int lbl_8064C980;
extern const float lbl_8064EF18;

void fn_800ACD30(void *object)
{
    SpawnRequest request;
    Vec3f position;
    unsigned int resource;
    Vec3s *source;
    ObjectData *data;
    void *spawned;

    resource = fn_801E741C(lbl_802458C4);
    source = fn_80158ABC(fn_8015C4A4((void *)resource, 2), 2, 0);
    data = fn_80201B8C(object);
    if (source != 0) {
        position.x = source->x;
        position.y = source->y;
        position.z = source->z;
        lbl_8064C980 = resource;
        fn_80043F44(&request);
        switch (data->state) {
        case 1:
            request.kind = 0x56;
            request.subtype = 0x60;
            break;
        case 2:
            request.kind = 0x57;
            request.subtype = 0x61;
            break;
        case 3:
        default:
            request.kind = 0x58;
            request.subtype = 0x62;
            break;
        }
        request.facing = lbl_8064EF18;
        request.count = 0x3A;
        request.position = position;
        request.param24 = 0x2FD;
        spawned = (void *)fn_80034708(&request);
        fn_800355F0(spawned, data->state);
        fn_80201D54(spawned, request.owner);
        fn_802015A4(spawned);
        fn_800CCA44(spawned);
        fn_801E8328(1, (unsigned int)spawned);
    }
}
