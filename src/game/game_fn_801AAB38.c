typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct State {
    unsigned char pad[0x90];
    Vec3 first;
    Vec3 second;
    Vec3 third;
    Vec3 fourth;
} State;

extern volatile State lbl_80608020;

extern void fn_801F68B0(Vec3*);
extern void fn_801F68F8(Vec3*);
extern void fn_801F6974(Vec3*);
extern void fn_801F68D4(Vec3*);
extern void fn_801C9510(volatile State*, volatile Vec3*, volatile Vec3*,
                        volatile Vec3*, volatile Vec3*, int, int);

void fn_801AAB38(void)
{
    Vec3 first;
    Vec3 fourth;
    Vec3 third;
    Vec3 source_first;
    Vec3 unused;
    Vec3 source_fourth;
    volatile Vec3* first_ptr;
    volatile Vec3* third_ptr;
    volatile Vec3* fourth_ptr;

    fn_801F68B0(&source_first);
    first = source_first;
    fn_801F68F8(&unused);
    fn_801F6974(&source_fourth);
    fourth = source_fourth;
    fn_801F68D4(&third);

    (first_ptr = &lbl_80608020.first)->x = first.x;
    lbl_80608020.first.y = first.y;
    lbl_80608020.first.z = first.z;
    (third_ptr = &lbl_80608020.third)->x = third.x;
    lbl_80608020.third.y = third.y;
    lbl_80608020.third.z = third.z;
    (fourth_ptr = &lbl_80608020.fourth)->x = fourth.x;
    lbl_80608020.fourth.y = fourth.y;
    lbl_80608020.fourth.z = fourth.z;
    fn_801C9510(&lbl_80608020, first_ptr, &lbl_80608020.second,
                third_ptr, fourth_ptr, 127, 0);
}
