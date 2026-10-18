typedef struct Vec3i {
    int x;
    int y;
    int z;
} Vec3i;

extern unsigned int rand(void);
#define rand() ((int)rand())
extern int fn_8011F598(int, int, int, int, void*, int);
extern void fn_80179DB0(Vec3i*, void*);
extern void* lbl_8064C5A8;
extern float lbl_8064EF7C;
extern void fn_801D6B44(int, int, int, int, Vec3i*, int, int, int, int, int,
                       int, int, int, int, int, int, int, int, int, int,
                       int, int);
extern void fn_8020104C(int, void*, void*, int, float);
#define fn_8020104C(a,b,c,d,e) fn_8020104C((a),(void*)(c),(void*)(d),(int)(e),(b))

void fn_800AAB90(int owner, int search, int option, int value, int resource,
                 void** positions, int position_count)
{
    Vec3i result;
    unsigned char search_result[0x30];
    int selector = 17;
    int position_index;

    goto check_selector;
choose_selector:
    selector = rand() & 0xF;
check_selector:
    if (selector >= 17) {
        goto choose_selector;
    }
    if (fn_8011F598(search, 9, 15, selector - 1, search_result, 1) == -1) {
        goto choose_selector;
    }

    position_index = position_count;
    while (position_index >= position_count) {
        position_index = rand() & 7;
    }
    fn_80179DB0(&result, (unsigned char*)positions[position_index] + 0x2C);

    position_count = 0x40040;
    if ((unsigned short)option == 0) {
        position_count |= 0x10;
    }
    if ((rand() & 1) != 0) {
        position_count |= 0x10000;
    }
    if ((rand() & 1) != 0) {
        position_count |= 0x20000;
    }
    if ((rand() & 1) != 0) {
        position_count |= 0x2000;
    }

    fn_801D6B44(owner, 9, 15, selector, &result, *(int*)lbl_8064C5A8, 0, 0,
                value, 8, 3, 5, 2, 0, 1, 17, 4, 4, 0, resource, option,
                position_count);
    fn_8020104C(0xF1, lbl_8064EF7C, owner, owner, position_index);
}
