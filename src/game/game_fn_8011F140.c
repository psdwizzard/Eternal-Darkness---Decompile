typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct TransformData {
    float unused[2];
    float position[3];
    float direction[3];
} TransformData;

extern const float lbl_80650080;
extern const float lbl_80650084;
extern const float lbl_80650068;
extern const float lbl_8065006C;

void fn_8011F140(void* object, int index, TransformData* output)
{
    u8* owner = *(u8**)((u8*)object + 60);
    u8* record = *(u8**)(owner + 188) + index * 28;
    register float* direction = output->direction;
    register u8* source = record + 14;
    float scaled;

    scaled = lbl_80650080 * (float)*(s16*)(record + 8);
    output->position[0] = scaled * lbl_80650084;
    scaled = lbl_80650080 * (float)*(s16*)(record + 10);
    output->position[1] = scaled * lbl_80650084;
    scaled = lbl_80650080 * (float)*(s16*)(record + 12);
    output->position[2] = scaled * lbl_80650084;
    /* Convert the packed u16 direction through the configured GQRs. */
    asm {
        psq_l f0, 0(source), 0, 7
        psq_lu f1, 4(source), 1, 7
        psq_st f0, 0(direction), 0, 0
        psq_stu f1, 8(direction), 1, 0
    }
    if (lbl_80650068 == output->direction[0] && lbl_80650068 == output->direction[1] &&
        lbl_80650068 == output->direction[2]) {
        output->direction[1] = lbl_8065006C;
    }
}
