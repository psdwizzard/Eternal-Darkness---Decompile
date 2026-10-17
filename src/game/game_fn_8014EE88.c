typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectDescriptor {
    u8 data[0x94];
    void* instance;
    Vec3 position;
    u16 rotation[3];
    u8 variant;
    u8 padding[5];
} EffectDescriptor;

typedef struct Ring {
    u8 count;
    u8 pad1[3];
    int active;
    int spawned;
    u8 pad2[0x1C];
    u16 radius;
    s16 kind;
    s16 first_kind;
    s16 second_kind;
    u8 pad3[4];
    Vec3 origin;
    u8 pad4[0xC];
    EffectDescriptor glow[7];
    EffectDescriptor first[7];
    EffectDescriptor second[7];
} Ring;

typedef struct RingEvent {
    void* links[2];
    Ring ring;
    u8 pad[0x1324 - 8 - sizeof(Ring)];
    int owner;
    u8 variant;
    u8 pad2[3];
    u16 state;
} RingEvent;

extern int lbl_8064D18C;
extern const float lbl_80650550;
extern const float lbl_80650554;

extern int fn_80180C4C(void);
extern void fn_80153A24(Vec3* origin, int count, u16 radius, s16 first_kind,
                        s16 second_kind, EffectDescriptor* first,
                        EffectDescriptor* second, u8 variant);
extern void fn_80182380(EffectDescriptor*);
extern void fn_80182448(void);
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern int fn_801E8328(u32, u32);
extern void fn_80182430(u8*, u8);
extern void fn_80182440(u8*, u8);
extern void fn_8014ECD8(u8* object, int index, u8 variant);
extern void fn_8014EB38(u8* object, int index);
typedef struct ListNode ListNode;
extern void fn_80149E28(ListNode* node);

void fn_8014EE88(RingEvent* event)
{
    Ring* ring = &event->ring;
    EffectDescriptor* effect;
    EffectDescriptor template;
    Vec3 position;
    void* instance;
    float angle;
    int i;
    int count;

    switch (event->state) {
    case 0x0:
        if (event->owner == lbl_8064D18C && fn_80180C4C() < 0x30) {
            fn_80153A24(&ring->origin, ring->count, ring->radius,
                        ring->first_kind, ring->second_kind, ring->first,
                        ring->second, event->variant);
            ring->spawned = 1;
        }
        break;
    case 0x10:
        if (event->owner == lbl_8064D18C) {
            fn_80182380(&template);
            template.data[0] = 8;
            template.data[1] = 2;
            *(s16*)(template.data + 4) = ring->kind;
            *(u16*)(template.data + 6) = 60;
            *(u16*)(template.data + 8) = 6;
            template.data[2] = 250;
            *(signed char*)(template.data + 3) = -25;
            *(u16*)(template.data + 0x1A) = 3;
            *(u16*)(template.data + 0x18) = 0;
            template.data[0x1F] = 2;
            template.data[0x20] = 1;
            *(float*)(template.data + 0x28) = lbl_80650550;
            template.data[0x21] = 125;
            template.data[0x22] = 250;
            *(void (**)(void))(template.data + 0x90) = fn_80182448;
            template.rotation[0] = 0;
            template.rotation[1] = 0;
            template.rotation[2] = 1;
            template.variant = event->variant;

            count = ring->count;
            for (i = 0; i < count; i++) {
                angle = lbl_80650554 * (float)i / (float)count;
                position.x = ring->origin.x + (float)ring->radius * fn_80048C2C(angle);
                position.y = ring->origin.y + (float)ring->radius * fn_80048C50(angle);
                position.z = ring->origin.z;
                effect = &ring->glow[i];
                *effect = template;
                effect->position = position;
                fn_801E8328(16, (u32)effect);
                if (ring->spawned != 0 && ring->first[i].instance != 0) {
                    fn_80182430(ring->first[i].instance, 2);
                }
            }
        }
        break;
    case 0x20:
        if (event->owner == lbl_8064D18C) {
            if (ring->spawned != 0) {
                count = ring->count;
                for (i = 0; i < count; i++) {
                    instance = ring->first[i].instance;
                    if (instance != 0) {
                        fn_80182430(instance, 3);
                        fn_80182440(instance, 7);
                    }
                    if (ring->second[i].instance != 0) {
                        fn_80182430(ring->second[i].instance, 2);
                    }
                }
            }
            fn_8014ECD8((u8*)ring, 0, event->variant);
        }
        break;
    case 0x30:
        if (event->owner == lbl_8064D18C) {
            count = ring->count;
            for (i = 0; i < count; i++) {
                if (ring->glow[i].instance != 0) {
                    fn_80182430(ring->glow[i].instance, 3);
                }
            }
        }
        break;
    case 0x3C:
        if (event->owner == lbl_8064D18C) {
            fn_8014ECD8((u8*)ring, 1, event->variant);
        }
        break;
    case 0x48:
        if (event->owner == lbl_8064D18C && ring->active != 0) {
            fn_8014EB38((u8*)ring, 0);
        }
        break;
    case 0x58:
        if (event->owner == lbl_8064D18C) {
            fn_8014ECD8((u8*)ring, 2, event->variant);
        }
        break;
    case 0x64:
        if (event->owner == lbl_8064D18C && ring->active != 0) {
            fn_8014EB38((u8*)ring, 1);
        }
        break;
    case 0x80:
        if (event->owner == lbl_8064D18C && ring->active != 0) {
            fn_8014EB38((u8*)ring, 2);
        }
        break;
    case 0x14C:
        fn_80149E28((ListNode*)event);
        break;
    }
}
