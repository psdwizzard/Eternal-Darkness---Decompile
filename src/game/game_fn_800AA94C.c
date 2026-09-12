extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern int fn_8011F598(int, int, int, int, void*, int);
extern void* lbl_8064C5A8;
extern void fn_801D6724(int, int, int, int, int, int, int, int, int, int,
                       int, int, int, int, int, int, int, int, int, int,
                       int, int, int, int, int);

void fn_800AA94C(int owner_arg, int search_arg, int option_arg, int value_arg,
                 int resource_arg)
{
    unsigned char result[0x30];
    int first;
    int second;
    int search = search_arg;
    int flags;
    int value = value_arg;
    int owner = owner_arg;
    int option = option_arg;
    int resource = resource_arg;

    first = 17;
    while (first >= 17) {
first_random:
        first = fn_800FBFB0() & 0xF;
    }
    if (fn_8011F598(search, 9, 15, first - 1, result, 1) == -1) {
        goto first_random;
    }

    second = 17;
    while (second >= 17 || first == second) {
second_random:
        second = fn_800FBFB0() & 0xF;
    }
    if (fn_8011F598(search, 9, 15, second - 1, result, 1) == -1) {
        goto second_random;
    }

    flags = 0x42040;
    if ((unsigned short)option == 0) {
        flags |= 0x10;
    }
    if ((fn_800FBFB0() & 1) != 0) {
        flags |= 0x10000;
    } else {
        flags |= 0x20000;
    }

    fn_801D6724(owner, 9, 15, first, second, *(int*)lbl_8064C5A8, 0, 0,
                value, 6, 2, 3, 1, 0, 1, 17, 4, 2, 16, 0, resource,
                option, flags, 0, 4);
}
