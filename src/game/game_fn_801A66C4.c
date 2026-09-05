typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

extern void fn_801A68C4(void*);
extern void* fn_801A7780(void*);
extern void fn_801A6ADC(void*);
extern u32 fn_80157C80(void*);

void fn_801A66C4(void* state, int magnitude)
{
    unsigned char* data = state;
    int first;
    int second;
    int absolute;
    u32 flags;

    magnitude = 0;
    *(u16*)(data + 0xAC) = 1;
    first = *(s16*)(data + 0xB0);
    if (first < -7) {
        if ((s16)first < 0) {
            first = -first;
        }
        magnitude = first;
        *(u16*)(data + 0xAC) = 8;
    } else if (first > 7) {
        if ((s16)first < 0) {
            first = -first;
        }
        magnitude = first;
        *(u16*)(data + 0xAC) = 16;
    }

    second = *(s16*)(data + 0xB2);
    absolute = second;
    if ((s16)second < 0) {
        absolute = -second;
    }
    if (absolute > magnitude) {
        if (second < -7) {
            *(u16*)(data + 0xAC) = 4;
        } else if (second > 7) {
            *(u16*)(data + 0xAC) = 2;
        }
    }

    fn_801A68C4(state);
    fn_801A7780(state);
    fn_801A6ADC(state);
    flags = fn_80157C80(*(void**)(data + 0x68));
    if (flags & 0x80) {
        *(u16*)(data + 0xAC) = 0x80;
    } else if (flags & 0x20) {
        *(u16*)(data + 0xAC) = 0x40;
    }
}
