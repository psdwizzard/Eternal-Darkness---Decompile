typedef unsigned short u16;
typedef unsigned long u32;

typedef struct Descriptor801A852C {
    u32 words[8];
} Descriptor801A852C;

extern const volatile Descriptor801A852C lbl_8023B2B0;

extern void fn_801EDA7C(Descriptor801A852C*, u32, u32, u32);

void fn_801A852C(u32* value, int index, u16 replacement, u32 word6)
{
    Descriptor801A852C descriptor = lbl_8023B2B0;

    if (index != -1) {
        ((u16*)&descriptor)[index] = replacement;
    }
    {
        u32 last = *value;
        volatile u32* descriptor_word6 = &descriptor.words[6];
        *descriptor_word6 = word6;
        descriptor.words[7] = last;
    }
    fn_801EDA7C(&descriptor, 0, 0x2BF, 0);
}
