typedef unsigned char u8;
typedef signed char s8;
typedef struct Color { u8 r, g, b, a; } Color;

extern int fn_801261F4(void *object);
extern void *fn_8011FCEC(void *object);
extern void fn_8011EBFC(void *object);
extern void *fn_8012C62C(u8 *object, int index, void *start, s8 *rate,
                        void *end, int flags);
extern int lbl_8064D18C;
extern const Color lbl_8064F5D8;
extern const Color lbl_8064F5DC;
extern const Color lbl_8064F5E0;
extern const Color lbl_8064F5E4;
extern const Color lbl_80651B10;
extern const Color lbl_8064F5E8;
extern const Color lbl_8064F5EC;
extern const Color lbl_80651B14;
extern const Color lbl_8064F5F0;
extern const Color lbl_8064F5F4;
extern const Color lbl_80651B18;
extern const Color lbl_8064F5F8;
extern const Color lbl_8064F5FC;
extern const Color lbl_80651B1C;
extern const Color lbl_8064F600;
extern const Color lbl_8064F604;
extern const Color lbl_80651B20;
extern const Color lbl_8064F608;
extern const Color lbl_8064F60C;
extern const Color lbl_80651B24;
extern const Color lbl_8064F610;

void fn_800E13EC(u8 *object, int extra_slots, int level, int special)
{
    Color special_start, special_rate, special_end;
    Color normal_start, normal_rate, normal_end;
    Color second_start, second_rate, second_end;
    Color third_start, third_rate, third_end;
    Color base_start, base_rate, base_end;
    Color eighth_start, eighth_rate, eighth_end;
    Color ninth_start, ninth_rate, ninth_end;

    if (level == lbl_8064D18C) {
        if (fn_801261F4(object) != 0 && (int)fn_8011FCEC(object) != -1) {
            fn_8011EBFC(object);
        }
        if (special != 0) {
            special_end = lbl_8064F5E0;
            special_rate = lbl_8064F5DC;
            special_start = lbl_8064F5D8;
            fn_8012C62C(object, 1, &special_start, (s8 *)&special_rate,
                        &special_end, 0x816);
        } else {
            normal_end = lbl_8064F5E8;
            normal_rate = lbl_80651B10;
            normal_start = lbl_8064F5E4;
            fn_8012C62C(object, 1, &normal_start, (s8 *)&normal_rate,
                        &normal_end, 0x54);
        }
        second_end = lbl_8064F5F0;
        second_rate = lbl_80651B14;
        second_start = lbl_8064F5EC;
        fn_8012C62C(object, 2, &second_start, (s8 *)&second_rate,
                    &second_end, 4);
        third_end = lbl_8064F5F8;
        third_rate = lbl_80651B18;
        third_start = lbl_8064F5F4;
        fn_8012C62C(object, 3, &third_start, (s8 *)&third_rate,
                    &third_end, 4);
        base_end = lbl_8064F600;
        base_rate = lbl_80651B1C;
        base_start = lbl_8064F5FC;
        fn_8012C62C(object, 0, &base_start, (s8 *)&base_rate,
                    &base_end, 4);
        if (extra_slots != 0) {
            eighth_end = lbl_8064F608;
            eighth_rate = lbl_80651B20;
            eighth_start = lbl_8064F604;
            fn_8012C62C(object, 8, &eighth_start, (s8 *)&eighth_rate,
                        &eighth_end, 4);
            ninth_end = lbl_8064F610;
            ninth_rate = lbl_80651B24;
            ninth_start = lbl_8064F60C;
            fn_8012C62C(object, 9, &ninth_start, (s8 *)&ninth_rate,
                        &ninth_end, 4);
        }
    }
}
