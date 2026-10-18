typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectDescriptor {
    u32 word;
    u16 half;
} EffectDescriptor;

typedef struct EffectParams {
    u8 bytes[0x90];
} EffectParams;

typedef struct Payload {
    short position[3];
    short pad06[5];
    void* effects[9];
    void* particles[3];
    u8 pad40[0x7C];
} Payload;

typedef struct Object {
    u8 pad00[4];
    u32 type;
    int owner;
    u8 pad0C[0x2C];
    Vec3 position;
    u32 linked;
    u8 pad48[0x74];
    Payload payload;
    u8 pad178[0xE7C];
    u16 state;
} Object;

extern int lbl_8064D18C;
extern int fn_801CEB2C(u32);
extern void fn_80190500(void*, void*);
extern void fn_801FE22C(u32);
extern void fn_801A9E40(int);
extern void fn_801D0E78(Object*);
extern void fn_8017E804(Payload*, short*, int);
extern void fn_8017DC88(Payload*, short*, short);
extern void* fn_8017FDA8(void*, int);
extern void fn_801FDEB4(u32, const Vec3*);
extern void fn_801FDF74(u32, int);
extern short fn_801D3A34(int, int);
extern int fn_801D38E8(int);
extern void* fn_801D3974(int);
extern void* fn_8014E9B0(void*, Vec3*, u8, short, void*, int, int, int);
extern void* fn_80156938(void*);
extern void fn_801858E0(void*);
extern void fn_801D38BC(int, void*, void*);
extern void* fn_80185AE8(short*, void*, u8*);
extern int fn_801E8328(u32, u32);
extern void fn_80180CE4(void*, int);
extern void fn_80180CC8(void*, void*);
extern void fn_8018358C(u8*);
extern void fn_80183D94(u8*);
extern void* fn_801D3944(int);
extern void* fn_80148008(Vec3, EffectDescriptor*, EffectParams*, void*);
extern u8* fn_80183454(void*, void*, void*);
extern u8* fn_80183E44(void*, void*, void*);
extern void* memcpy(void*, const void*, u32);
extern u8 lbl_802FC5BC[];
extern u32 lbl_80651EF4;
extern u16 lbl_80651EF8;
extern u32 lbl_80651EFC;
extern u16 lbl_80651F00;

void fn_801DC778(void* arg)
{
    u32 type;
    Payload* payload;
    Object* object = arg;
    int count;
    int i;

    payload = &object->payload;
    type = object->type;
    count = fn_801CEB2C(type);

    if (object->owner != lbl_8064D18C) {
        if (object->state <= 0x99) {
            Payload* cursor = payload;
            for (i = 0; i < (short)count;
                 cursor = (Payload*)((u8*)cursor + sizeof(void*)), i++) {
                if (cursor->effects[0] != 0) {
                    fn_80190500(cursor->effects[0], 0);
                }
            }
        }
        if (object->linked != 0) {
            fn_801FE22C(object->linked);
        }
        fn_801A9E40(-1);
        fn_801D0E78(object);
        return;
    }

    if (object->state >= 40 && object->state <= 120) {
        Vec3 position;
        fn_8017E804(payload, &payload->pad06[0], 5 - ((object->state - 40) >> 4));
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        if (object->linked != 0) {
            fn_801FDEB4(object->linked, &position);
        }
        for (i = 0; i < (short)count; i++) {
            if (payload->effects[i] != 0) {
                short* effect = fn_8017FDA8(payload->effects[i], 0);
                effect[2] = payload->position[2];
            }
        }
    } else if (object->state > 140 && object->state < 154) {
        short next[3];
        next[2] = payload->pad06[3];
        fn_8017DC88(payload, next, 2);
        payload->pad06[3] = next[2];
        {
            Vec3 position;
            position.x = payload->position[0];
            position.y = payload->position[1];
            position.z = payload->position[2];
            if (object->linked != 0) {
                fn_801FDEB4(object->linked, &position);
            }
        }
        for (i = 0; i < (short)count; i++) {
            if (payload->effects[i] != 0) {
                short* effect = fn_8017FDA8(payload->effects[i], 0);
                effect[2] = payload->position[2];
            }
        }
    }

    switch (object->state) {
    case 10:
    {
        Vec3 position;
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        fn_8014E9B0(&payload->pad40[0], &position, (u8)count,
                    fn_801D3A34(type, 57), lbl_802FC5BC + 12,
                    16, 4, 0);
        break;
    }
    case 25:
    {
        Vec3 position;
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        fn_8014E9B0(&payload->pad40[0], &position, (u8)count,
                    fn_801D3A34(type, 61), lbl_802FC5BC + 12,
                    16, 4, 1);
        break;
    }
    case 40:
    {
        Vec3 position;
        void* config;
        void* particle;
        config = fn_801D3974(fn_801D38E8(type));
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        particle = fn_8014E9B0(&payload->pad40[0], &position, (u8)count,
                               65, &config, 16, 4, 1);
        if (particle != 0) {
            payload->particles[0] = fn_80156938(particle);
        } else {
            payload->particles[0] = 0;
        }
        break;
    }
    case 55:
    {
        Vec3 position;
        void* particle;
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        particle = fn_8014E9B0(&payload->pad40[0], &position, (u8)count,
                               fn_801D3A34(type, 57),
                               lbl_802FC5BC + 12, 16, 4, 0);
        if (particle != 0) {
            payload->particles[1] = fn_80156938(particle);
        } else {
            payload->particles[1] = 0;
        }
        break;
    }
    case 70:
    {
        Vec3 position;
        void* particle;
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        particle = fn_8014E9B0(&payload->pad40[0], &position, (u8)count,
                               fn_801D3A34(type, 57),
                               lbl_802FC5BC + 12, 16, 4, 0);
        if (particle != 0) {
            payload->particles[2] = fn_80156938(particle);
        } else {
            payload->particles[2] = 0;
        }
        break;
    }
    case 121:
        payload->pad06[2] -= 200;
        break;
    case 152:
        break;
    case 151:
    {
        u8* descriptor = (u8*)payload + 0xF0;
        struct {
            u32 word;
            u16 half;
        } init;

        init.word = lbl_80651EF4;
        init.half = lbl_80651EF8;
        fn_801858E0(descriptor);
        type = fn_801D38E8(type);
        descriptor[1] = 100;
        *(u16*)(descriptor + 8) = 60;
        *(u16*)(descriptor + 6) = 84;
        ((signed char*)descriptor)[3] = -10;
        fn_801D38BC(type, descriptor + 0x78, descriptor + 4);
        descriptor[0x14] = 50;
        *(u16*)(descriptor + 0x1C) = 250;
        descriptor[0x18] |= 2;
        descriptor[0x19] = 4;
        *(void**)(descriptor + 0x90) = fn_80185AE8;
        *(Vec3*)(descriptor + 0x98) = object->position;
        memcpy(descriptor + 0xA4, &init, 6);
        *(u32*)(descriptor + 0x94) = 0;
        descriptor[0xAA] = 4;
        fn_801E8328(16, (u32)descriptor);
        {
            int index;
            for (index = 0; index < 3; index++) {
                if (payload->particles[index] != 0) {
                    fn_80180CE4(payload->particles[index], 1);
                    fn_80180CC8(payload->particles[index], &object->position);
                }
            }
        }
        break;
    }
    case 153:
    {
        int j;
        EffectDescriptor descriptor;
        EffectParams first_params;
        EffectParams second_params;

        descriptor.word = lbl_80651EFC;
        descriptor.half = lbl_80651F00;
        fn_8018358C(first_params.bytes);
        *(void**)(first_params.bytes + 0x1C) = fn_801D3944(type);
        fn_80183D94(second_params.bytes);
        *(void**)(second_params.bytes + 0x1C) = fn_801D3944(type);

        for (j = 0; j < (short)count; j++) {
            if (payload->effects[j] != 0) {
                short* effect = fn_8017FDA8(payload->effects[j], 0);
                Vec3 position;

                position.x = effect[0];
                position.y = effect[1];
                position.z = effect[2];
                fn_80148008(position, &descriptor, &first_params,
                            fn_80183454);

                position.z = effect[2] + 40;
                fn_80148008(position, &descriptor, &second_params,
                            fn_80183E44);
                fn_80190500(payload->effects[j], 0);
            }
        }
        if (object->linked != 0) {
            fn_801FDF74(object->linked, 0xC3500);
        }
        break;
    }
    case 173:
        if (object->linked != 0) {
            fn_801FDF74(object->linked, 0x493E0);
        }
        break;
    case 193:
        fn_801A9E40(-1);
        fn_801D0E78(object);
        break;
    }
}
