typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Runtime {
    unsigned char pad0[0x68];
    int* data;
    unsigned char pad1[0x32];
    unsigned char type;
    unsigned char subtype;
} Runtime;

typedef struct SpawnConfig {
    Vec3 position;
    float scale;
    int kind;
    int value0;
    int pad0;
    int value1;
    int pad1;
    int value2;
    int mode;
    int pad2[4];
} SpawnConfig;

extern float lbl_8064EC10;

extern void *fn_80201B9C();
extern int fn_80201B44();
extern void fn_800DE8FC(void*, Vec3*);
extern void *fn_80201B8C();
extern int fn_80201EB8();
extern int fn_80201B54();
extern unsigned long long fn_8020123C();
extern void* fn_80201BC0(void*);
extern void fn_80043F44(SpawnConfig*);
extern int fn_800FBFB0(void);
extern void* fn_80034708(SpawnConfig*);
extern void *fn_80201BC8();
extern void fn_80201D54(void*, void*);
extern void fn_802015A4(void*);
extern void fn_800CCA44(void*);
extern void* fn_80201B94();
extern int fn_80201CD4(void);
extern void fn_80201DD8(void*, void*);
extern void fn_80201E60(void*, int);
extern int fn_801E8328();
extern int fn_80038464(void*, int, short*);
extern int fn_800389E0(void*, int, short, int);
extern void fn_800386FC(void*, int, short*);
extern void fn_80038544(void*, int, short);
extern void fn_8011F0E8(void*, Vec3*);
extern void fn_80048708(void*);

void* fn_8008F224(int object_id, int create, int transfer)
{
    void* found;
    void* current;
    void* owner;
    Vec3 position;
    short value;
    void* source_owner;

    current = fn_80201B9C((void*)object_id);
    found = 0;
    owner = 0;
    source_owner = ((void*)fn_80201B44());
    fn_800DE8FC((void*)object_id, &position);
    while (current != 0 && found == 0) {
        Runtime* runtime = ((Runtime*)fn_80201B8C(current));
        if (runtime != 0) {
            int candidate = fn_80201EB8(current);
            void* candidate_owner = ((void*)fn_80201B54(current));
            if (candidate == object_id && runtime->type == 2 &&
                runtime->subtype == 10 &&
                (int)(fn_8020123C(59, 0, candidate_owner, 0) & 0xFFFFFFFF) != 0) {
                found = current;
            }
        }
        current = fn_80201BC0(current);
    }

    if (found == 0) {
        if (create != 0) {
            SpawnConfig config;
            void* state;
            void* spawned;
            Runtime* runtime;
            int flags;
            unsigned int index;
            int* data;

            fn_80043F44(&config);
            index = (unsigned int)object_id - 0xF1;
            config.kind = 68;
            config.scale = lbl_8064EC10;
            config.mode = 44;
            config.position = position;
            switch (index) {
            case 6:
                config.value0 = 106;
                config.value1 = 0x817;
                config.value2 = 0x2A9;
                break;
            case 5:
                config.value0 = 106;
                config.value1 = 0x8BA;
                config.value2 = 0x2D6;
                break;
            case 1:
                config.value0 = 105;
                config.value1 = 0x819;
                config.value2 = 0x2D9;
                break;
            case 4: {
                int alternate;
                config.value0 = (fn_800FBFB0() & 1) + 105;
                alternate = config.value0 == 106;
                alternate = alternate != 0;
                config.value1 = alternate + 0x7FB;
                config.value2 = alternate + 0x2D7;
                break;
            }
            case 0:
                config.value0 = 106;
                config.value1 = 0x816;
                config.value2 = 0x2D4;
                break;
            case 3:
                config.value0 = 106;
                config.value1 = 0x818;
                config.value2 = 0x2D5;
                break;
            default:
                config.value0 = 106;
                config.value1 = 0x818;
                break;
            }
            spawned = fn_80034708(&config);
            fn_80201BC8();
            owner = ((void*)fn_80201B54(spawned));
            fn_80201D54(spawned, (void*)object_id);
            fn_802015A4(spawned);
            fn_800CCA44(spawned);
            state = fn_80201B94(spawned);
            flags = fn_80201CD4();
            fn_80201DD8(state, source_owner);
            fn_80201E60(state, flags | 1);
            runtime = ((Runtime*)fn_80201B8C(spawned));
            data = runtime->data;
            data[1] = 0xAD7;
            fn_801E8328(1, spawned, data);
        }
    } else {
        owner = ((void*)fn_80201B54(found));
        if (transfer != 0) {
            void* actor = fn_80201BC8(found);
            fn_80038464(found, 0, &value);
            fn_800389E0(found, 0, value, 0);
            fn_800386FC(owner, 0, &value);
            fn_80038544(owner, 0, value);
            fn_800386FC(owner, 2, &value);
            fn_80038544(owner, 2, value);
            fn_800386FC(owner, 3, &value);
            fn_80038544(owner, 3, value);
            fn_800386FC(owner, 1, &value);
            fn_80038544(owner, 1, value);
            fn_8011F0E8(actor, &position);
            fn_80048708(actor);
        }
    }
    return owner;
}
