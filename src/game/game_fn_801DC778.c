typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct EffectDescriptor {
    u32 word;
    u16 half;
} EffectDescriptor;

typedef struct EffectParams {
    u8 pad00[0x1C];
    void* value1C;
    u8 pad20[0x70];
} EffectParams;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Effect {
    u8 pad00;
    u8 value01;
    u8 pad02;
    s8 value03;
    u16 value04;
    u16 value06;
    u16 value08;
    u8 pad0A[0xA];
    u8 value14;
    u8 pad15[3];
    u8 value18;
    u8 value19;
    u8 pad1A[2];
    u16 value1C;
    u8 pad1E[0x5A];
    u32 value78;
    u8 pad7C[0x14];
    void (*callback90)(void);
    void* object94;
    Vec3 position98;
    u8 descriptorA4[6];
    u8 valueAA;
} Effect;

typedef struct Payload {
    short position[3];
    short target[3];
    short velocity_z;
    short pad0E;
    void* effects[3];
    u8 pad1C[0x18];
    void* particles[3];
    u8 emitter[0xB0];
    Effect effect;
} Payload;

typedef struct GameObject {
    u8 pad00[4];
    u32 owner;
    int type;
    u8 pad0C[0x2C];
    Vec3 position;
    void* resource;
    u8 pad48[0x74];
    Payload payload;
    u8 pad258[0xD9C];
    u16 state;
} GameObject;

extern int lbl_8064D18C;
extern s16 fn_801CEB2C(u32);
extern void fn_80190500(void*, int);
extern void fn_801FE22C(void*);
extern void fn_801A9E40(int);
extern void fn_801D0E78(GameObject*);
extern void fn_8017E804(Payload*, short*, int);
extern void fn_8017DC88(Payload*, short*, int);
extern void* fn_8017FDA8(void*, int);
extern void fn_801FDEB4(void*, Vec3*);
extern void fn_801FDF74(void*, u32);
extern int fn_801D3A34(u32, int);
extern int fn_801D38E8(u32);
extern void* fn_801D3974(void);
extern void* fn_8014E9B0(void*, Vec3*, u8, int, void*, int, int, int);
extern void* fn_80156938(void*);
extern void fn_801858E0(Effect*);
extern void fn_801D38BC(u32, u32*, u16*);
extern void fn_80185AE8(void);
extern void fn_801E8328(int, Effect*);
extern void fn_80180CE4(void*, int);
extern void fn_80180CC8(void*, void*);
extern void fn_8018358C(EffectParams*);
extern void fn_80183D94(EffectParams*);
extern void* fn_801D3944(u32);
extern void* fn_80148008(Vec3, EffectDescriptor*, EffectParams*, void*);
extern void fn_80183454(void);
extern void fn_80183E44(void);
extern void* memcpy(void*, const void*, u32);
extern Color lbl_802FC5BC[];
extern u32 lbl_80651EF4;
extern u16 lbl_80651EF8;
extern u32 lbl_80651EFC;
extern u16 lbl_80651F00;

void fn_801DC778(void* arg)
{
    u32 owner;
    Payload* payload;
    GameObject* object;
    s16 count;
    int i;

    object = arg;
    payload = &object->payload;
    owner = object->owner;
    count = fn_801CEB2C(owner);

    if (object->type != lbl_8064D18C) {
        if (object->state <= 0x99) {
            for (i = 0; i < count; i++) {
                if (payload->effects[i] != 0) {
                    fn_80190500(payload->effects[i], 0);
                }
            }
        }
        if (object->resource != 0) {
            fn_801FE22C(object->resource);
        }
        fn_801A9E40(-1);
        fn_801D0E78(object);
        return;
    }

    if (object->state >= 40 && object->state <= 120) {
        Vec3 position;
        fn_8017E804(payload, payload->target, 5 - ((object->state - 40) >> 4));
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        if (object->resource != 0) {
            fn_801FDEB4(object->resource, &position);
        }
        for (i = 0; i < count; i++) {
            if (payload->effects[i] != 0) {
                short* effect = fn_8017FDA8(payload->effects[i], 0);
                effect[2] = payload->position[2];
            }
        }
    } else if (object->state > 140 && object->state < 154) {
        short next[3];
        next[2] = payload->velocity_z;
        fn_8017DC88(payload, next, 2);
        payload->velocity_z = next[2];
        {
            Vec3 position;
            position.x = payload->position[0];
            position.y = payload->position[1];
            position.z = payload->position[2];
            if (object->resource != 0) {
                fn_801FDEB4(object->resource, &position);
            }
        }
        for (i = 0; i < count; i++) {
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
        fn_8014E9B0(payload->emitter, &position, (u8)count,
                    fn_801D3A34(owner, 57), &lbl_802FC5BC[3],
                    16, 4, 0);
        break;
    }
    case 25:
    {
        Vec3 position;
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        fn_8014E9B0(payload->emitter, &position, (u8)count,
                    fn_801D3A34(owner, 61), &lbl_802FC5BC[3],
                    16, 4, 1);
        break;
    }
    case 40:
    {
        Vec3 position;
        void* config;
        void* particle;
        fn_801D38E8(owner);
        config = fn_801D3974();
        position.x = payload->position[0];
        position.y = payload->position[1];
        position.z = payload->position[2];
        particle = fn_8014E9B0(payload->emitter, &position, (u8)count,
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
        particle = fn_8014E9B0(payload->emitter, &position, (u8)count,
                               fn_801D3A34(owner, 57),
                               &lbl_802FC5BC[3], 16, 4, 0);
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
        particle = fn_8014E9B0(payload->emitter, &position, (u8)count,
                               fn_801D3A34(owner, 57),
                               &lbl_802FC5BC[3], 16, 4, 0);
        if (particle != 0) {
            payload->particles[2] = fn_80156938(particle);
        } else {
            payload->particles[2] = 0;
        }
        break;
    }
    case 121:
        payload->target[2] -= 200;
        break;
    case 152:
        break;
    case 151:
    {
        Effect* effect = &payload->effect;
        EffectDescriptor init;

        init.word = lbl_80651EF4;
        init.half = lbl_80651EF8;
        fn_801858E0(effect);
        owner = fn_801D38E8(owner);
        effect->value01 = 100;
        effect->value08 = 60;
        effect->value06 = 84;
        effect->value03 = -10;
        fn_801D38BC(owner, &effect->value78, &effect->value04);
        effect->value14 = 50;
        effect->value1C = 250;
        effect->value18 |= 2;
        effect->value19 = 4;
        effect->callback90 = fn_80185AE8;
        effect->position98 = object->position;
        memcpy(effect->descriptorA4, &init, 6);
        effect->object94 = 0;
        effect->valueAA = 4;
        fn_801E8328(16, effect);
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
        fn_8018358C(&first_params);
        first_params.value1C = fn_801D3944(owner);
        fn_80183D94(&second_params);
        second_params.value1C = fn_801D3944(owner);

        for (j = 0; j < count; j++) {
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
        if (object->resource != 0) {
            fn_801FDF74(object->resource, 0xC3500);
        }
        break;
    }
    case 173:
        if (object->resource != 0) {
            fn_801FDF74(object->resource, 0x493E0);
        }
        break;
    case 193:
        fn_801A9E40(-1);
        fn_801D0E78(object);
        break;
    }
}
