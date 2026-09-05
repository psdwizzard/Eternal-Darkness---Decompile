typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EffectDescriptor {
    u8 data[0xB0];
} EffectDescriptor;

extern void fn_80182380(EffectDescriptor*);
extern void fn_80182448(void);
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern int fn_801E8328();

extern const float lbl_806505B8;
extern const float lbl_806505BC;
extern const float lbl_806505C0;

void fn_80153A24(Vec3* origin, int count, u16 radius, u16 first_kind,
                 u16 second_kind, EffectDescriptor* first,
                 EffectDescriptor* second, u8 variant)
{
    EffectDescriptor first_template;
    EffectDescriptor second_template;
    Vec3 position;
    int i;
    float angle;
    EffectDescriptor* targets[2];

    fn_80182380(&first_template);
    first_template.data[0] = 4;
    first_template.data[1] = 2;
    *(u16*)(first_template.data + 4) = first_kind;
    *(u16*)(first_template.data + 6) = 60;
    *(u16*)(first_template.data + 8) = 8;
    first_template.data[2] = 100;
    *(signed char*)(first_template.data + 3) = -10;
    *(u16*)(first_template.data + 0x1A) = 2;
    *(u16*)(first_template.data + 0x18) = 0;
    first_template.data[0x1F] = 1;
    first_template.data[0x20] = 1;
    *(float*)(first_template.data + 0x28) = lbl_806505B8;
    first_template.data[0x21] = 50;
    first_template.data[0x22] = 100;
    first_template.data[0x23] = 96;
    first_template.data[0x24] = 2;
    *(void (**)(void))(first_template.data + 0x90) = fn_80182448;
    *(u16*)(first_template.data + 0xA4) = 0;
    *(u16*)(first_template.data + 0xA6) = 0;
    *(u16*)(first_template.data + 0xA8) = 1;
    first_template.data[0xAA] = variant;

    fn_80182380(&second_template);
    second_template.data[0] = 6;
    second_template.data[1] = 8;
    *(u16*)(second_template.data + 4) = second_kind;
    *(u16*)(second_template.data + 6) = 50;
    *(u16*)(second_template.data + 8) = 7;
    second_template.data[2] = 250;
    *(signed char*)(second_template.data + 3) = -25;
    *(u16*)(second_template.data + 0x1A) = 3;
    *(u16*)(second_template.data + 0x18) = 0;
    second_template.data[0x1F] = 1;
    second_template.data[0x20] = 1;
    *(float*)(second_template.data + 0x28) = lbl_806505BC;
    second_template.data[0x21] = 50;
    second_template.data[0x22] = 250;
    *(void (**)(void))(second_template.data + 0x90) = fn_80182448;
    *(u16*)(second_template.data + 0xA4) = 0;
    *(u16*)(second_template.data + 0xA6) = 0;
    *(u16*)(second_template.data + 0xA8) = 1;
    second_template.data[0xAA] = variant;

    targets[0] = first;
    targets[1] = second;
    for (i = 0; i < count; i++) {
        angle = lbl_806505C0 * (float)i / (float)count;
        position.x = origin->x + (float)radius * fn_80048C2C(angle);
        position.y = origin->y + (float)radius * fn_80048C50(angle);
        position.z = origin->z;
        *targets[0] = first_template;
        *(Vec3*)(targets[0]->data + 0x98) = position;
        fn_801E8328(16, targets[0]);
        *targets[1] = second_template;
        *(Vec3*)(targets[1]->data + 0x98) = position;
        fn_801E8328(16, targets[1]);
        targets[0]++;
        targets[1]++;
    }
}
