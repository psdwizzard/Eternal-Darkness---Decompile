typedef unsigned char u8;
typedef unsigned short u16;

extern const float lbl_806501D8;
extern void fn_8017A630(float*);
extern void fn_8012BE78(const float*, void*);

typedef struct Pair { unsigned int a; unsigned int b; } Pair;

void fn_8012C3B8(u8* state)
{
    float vector[3];

    *(u16*)(state + 0xA) &= ~9;
    fn_8017A630(vector);
    fn_8012BE78(vector, state + 0x6C);
    *(Pair*)(state + 0x74) = *(Pair*)(state + 0x6C);
    *(Pair*)(state + 0x7C) = *(Pair*)(state + 0x6C);
    *(float*)(state + 0x84) = lbl_806501D8;
    *(float*)(state + 0x88) = lbl_806501D8;
    *(unsigned int*)(state + 0x8C) = 0;
}
