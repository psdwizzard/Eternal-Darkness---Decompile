typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;
typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct DescriptorKey {
    u32 word;
    u16 half;
} DescriptorKey;

typedef struct EffectDescriptor {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    s8 field_03;
    u16 field_04;
    u16 field_06;
    u8 pad_08[0xE];
    u8 field_16;
    u8 field_17;
    u8 pad_18[4];
    u32 field_1C;
    u32 field_20;
    u8 pad_24[4];
    u32 field_28;
    u8 pad_2C[8];
    float scale;
    u32 field_38;
    u8 pad_3C[0x58];
} EffectDescriptor;

typedef struct Command {
    u8 pad_00[4];
    u16 field_04;
    u16 field_06;
    u8 pad_08[0xC];
    void *object;
    u32 field_18;
    u8 pad_1C[4];
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u8 pad_26[6];
    u32 field_2C;
    u8 pad_30[0x60];
    void (*callback)(void);
    u32 field_94;
    Vec3f position;
    u8 key[6];
    u8 kind;
} Command;

typedef struct Work {
    s32 active;
    s32 initialized;
    u8 pad_08[2];
    u16 field_0A;
    s16 field_0C;
    s16 field_0E;
    s16 field_10;
    u16 start_frame;
    u16 field_14;
    u16 field_16;
    u16 end_frame;
    u16 effect_frame;
    u16 field_1C;
    u16 stop_frame;
    void *field_20;
    u32 field_24;
    s32 amount;
    Vec3f position;
    Vec3f target;
    u8 command_storage[0x1F4];
    void *tracked_effect;
    u8 pad_23C[0x18];
    void *object;
    u32 effect_key;
} Work;

typedef struct Instance {
    u8 pad_0000[8];
    Work work;
    u8 pad_0264[0x10C0];
    s32 owner;
    u8 pad_1328[4];
    u16 frame;
} Instance;

extern u32 lbl_80651C20;
extern u16 lbl_80651C24;
extern u32 lbl_80651C28;
extern u16 lbl_80651C2C;
extern u32 lbl_80651C30;
extern u16 lbl_80651C34;
extern float lbl_80650584;
extern s32 lbl_8064D18C;
extern void fn_80199128(void*, s32);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_8019B134(void*, s32);
extern void fn_8019B13C(void*);
extern void* fn_80148008(Vec3f*, void*, void*, void (*)(void));
extern void fn_8019ADE4(void);
extern void* fn_80156938(void);
extern void fn_8017FF1C(void*, s32);
extern void fn_8017FE1C(void*, void (*)(void));
extern void fn_8018B058(void);
extern void fn_801809B8(void*, u8);
extern void fn_80150950(s32, Vec3f*, u16, u16, s32, u32, u32, void*);
extern void fn_8019A3A4(void*);
extern void fn_8019A300(void);
extern Vec3s* fn_8017FDA8(void*, s32);
extern void* memcpy(void*, const void*, u32);
extern int fn_801E8328(u32, u32);
extern void fn_80199EBC(void*);
extern void fn_80199E18(void);
extern void fn_8014F700(Vec3f*, s16, void*);
extern void fn_80149E28(void*);

void fn_80150400(void* argument) {
    Instance* instance = argument;
    Work* work;
    s32 amount;
    Vec3f position0;
    EffectDescriptor descriptor;

    work = &instance->work;
    if ((instance->work.active != 0) && (work->initialized == 0)) {
        work->end_frame = instance->frame + work->field_16;
        if (work->tracked_effect != 0) {
            fn_80199128(work->tracked_effect, 0);
        }
        work->stop_frame = work->end_frame - 50;
        amount = work->amount;
        if (amount > 0) {
            fn_8020123C(0xE2, amount, amount, 0);
        }
        work->initialized = 1;
    }
    if ((work->object != 0) && (instance->frame == work->stop_frame)) {
        fn_8019B134(work->object, 0);
    }
    if (instance->frame == work->start_frame - 60) {
        DescriptorKey key;
        Vec3f position;
        key.word = lbl_80651C20;
        key.half = lbl_80651C24;
        fn_8019B13C(&descriptor);
        descriptor.field_01 = 1;
        descriptor.field_06 = work->end_frame - work->start_frame + 20;
        descriptor.field_04 = work->field_0E;
        descriptor.field_02 = 0xF5;
        descriptor.field_03 = -7;
        descriptor.field_1C = 0;
        descriptor.field_20 = 0;
        descriptor.field_16 = 7;
        descriptor.field_17 = 0xF5;
        descriptor.scale = lbl_80650584;
        descriptor.field_38 = work->field_24;
        descriptor.field_28 = 1;
        position = work->position;
        if (fn_80148008(&position, &key, &descriptor, fn_8019ADE4) != 0) {
            void* object = fn_80156938();
            fn_8017FF1C(object, 2);
            fn_8017FE1C(object, fn_8018B058);
            work->object = object;
        }
    } else if ((instance->frame >= work->start_frame - 58) &&
               (instance->frame <= work->start_frame - 10) &&
               (work->object != 0)) {
        fn_801809B8(work->object, instance->frame - (work->start_frame - 56));
    }
    if (instance->frame >= work->end_frame - 50) {
        s32 delta = work->end_frame - instance->frame - 1;
        u8 value = (0 > delta) ? 0 : delta;
        if ((work->object != 0) && (value != 0)) {
            fn_801809B8(work->object, value);
        }
    }
    if (instance->frame == work->start_frame) {
        s32 amount = work->amount;
        void* optional = 0;
        if (amount > 0) {
            optional = work;
        }
        fn_80150950(instance->owner, &work->target, work->field_1C,
                    work->field_14, (s32)work->object, work->field_24,
                    amount, optional);
    } else if ((instance->frame == work->start_frame + 10) &&
               (work->active == 0)) {
        Command* command;
        Vec3s* object_position;
        DescriptorKey key;
        key.word = lbl_80651C28;
        key.half = lbl_80651C2C;
        command = (Command*)(work->command_storage + 0x160);
        fn_8019A3A4(command);
        command->field_04 = work->field_10;
        command->field_06 = work->field_14 - 20;
        command->object = work->object;
        command->field_18 = work->field_24;
        command->callback = fn_8019A300;
        object_position = fn_8017FDA8(work->object, 0);
        command->position.x = object_position->x;
        command->position.y = object_position->y;
        command->position.z = object_position->z;
        memcpy(command->key, &key, 6);
        command->field_94 = 0;
        command->kind = 2;
        fn_801E8328(0x10, (u32)command);
    }
    if (instance->owner == lbl_8064D18C) {
        if (instance->frame == 0) {
            Command* command;
            DescriptorKey key;
            key.word = lbl_80651C30;
            key.half = lbl_80651C34;
            command = (Command*)work->command_storage;
            fn_80199EBC(command);
            command->field_06 = work->start_frame - 10;
            command->field_04 = work->field_0E;
            command->field_20 = work->position.x;
            command->field_22 = work->position.y;
            command->field_24 = work->position.z;
            command->field_2C = work->field_24;
            command->callback = fn_80199E18;
            memcpy(command->key, &key, 6);
            command->field_94 = 0;
            command->kind = 4;
            fn_801E8328(0x10, (u32)command);
        }
        if ((instance->frame == work->effect_frame) ||
            (instance->frame == work->effect_frame + 10) ||
            (instance->frame == work->effect_frame + 20)) {
            u32 effect_key;
            Vec3s* object_position = fn_8017FDA8(work->object, 0);
            position0.x = object_position->x;
            position0.y = object_position->y;
            position0.z = object_position->z;
            effect_key = work->effect_key;
            fn_8014F700(&position0, work->field_0C, &effect_key);
        }
    }
    if (instance->frame == work->effect_frame + 20) {
        work->effect_frame += 0x8D;
    }
    if (work->amount > 0) {
        if ((work->active != 0) && (instance->frame == work->end_frame)) {
            fn_80149E28(instance);
        }
    } else if (instance->frame == work->end_frame) {
        fn_80149E28(instance);
    }
}
