typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern u32 lbl_8064D7C8;
extern u32 lbl_8064D7CC;
extern void* lbl_8064D7D0;
extern const float lbl_80651540;
extern const float lbl_80651544;
extern void* memset(void*, int, unsigned int);

static u8* pointers[12] = {0};
static u8 entries[12][124] = {0};
static Vec3 tail = {0};

void fn_801FD318(void)
{
    u32 i;

    memset(entries, 0, sizeof(entries));
    for (i = 0; i < 12; i++) {
        pointers[i] = entries[i];
    }
    lbl_8064D7D0 = entries;
    lbl_8064D7CC = 0;
    lbl_8064D7C8 = 0x10000;
    tail.x = lbl_80651540;
    tail.y = lbl_80651540;
    tail.z = lbl_80651544;
}
