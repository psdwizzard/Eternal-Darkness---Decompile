typedef unsigned int u32;

extern volatile int lbl_8064D808[2];
extern volatile u32 lbl_8064D810[2];
extern volatile u32 lbl_8064D818[2];
extern volatile u32 lbl_8064D820[2];
extern volatile u32 lbl_8064D828[2];
extern volatile u32 lbl_8064D830[2];
extern volatile u32 lbl_8064D838[2];
extern volatile u32 lbl_8064D840[2];
extern volatile u32 lbl_8064D848[2];
extern volatile u32 lbl_8064D850[2];
extern volatile u32 lbl_8064D858[2];
extern char lbl_802FC880[];
extern char lbl_802FC8AC[];

extern void fn_800F8BAC(const char*, const char*, int);

void fn_801FEB54(int frame, int effects, int particles, int trails,
                 int textures, int anims)
{
#define SLOT(name) (name[frame])
    u32 base = SLOT(lbl_8064D858) + 0x86470;
    u32 address;

    address = (base - effects * 6) & ~31;
    SLOT(lbl_8064D850) = address;
    address = (address - particles * 4) & ~31;
    SLOT(lbl_8064D848) = address;
    address = (address - ((particles >> 3) + ((particles & 7) != 0))) & ~31;
    SLOT(lbl_8064D840) = address;
    address = (address - particles) & ~31;
    SLOT(lbl_8064D838) = address;
    address = (address - trails * 8) & ~31;
    SLOT(lbl_8064D830) = address;
    address = (address - anims * 4) & ~31;
    SLOT(lbl_8064D828) = address;
    address = (address - textures * 0x74) & ~31;
    SLOT(lbl_8064D820) = address;
    address = (address - 0x7A120) & ~31;
    SLOT(lbl_8064D810) = address;
    SLOT(lbl_8064D818) = (address - 0x20) & ~31;
    SLOT(lbl_8064D808) = base - address;

    if (SLOT(lbl_8064D808) >= 0x86470) {
        fn_800F8BAC(lbl_802FC880, lbl_802FC8AC, 0x81);
    }
}
