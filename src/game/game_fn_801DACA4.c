typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int fn_80201AE4(void);
extern int fn_80201B9C(void);
extern u8* fn_80201B8C(int);
extern int fn_80201BC0(int);
extern int fn_800360B0(int, u16*);
extern void fn_80036060(int, u16);

void fn_801DACA4(int object, int set)
{
    int current = object;
    int setting = set;
    u16 flags;

    if (current == fn_80201AE4()) {
        current = fn_80201B9C();
        while ((u32)current != 0) {
            u8* instance = fn_80201B8C(current);
            if (instance != 0 && instance[0x9F] == 3 &&
                fn_800360B0(current, &flags) != 0) {
                if (setting != 0)
                    fn_80036060(current, flags | 0x80);
                else
                    fn_80036060(current, flags & ~0x80);
            }
            current = fn_80201BC0(current);
        }
    }
}
