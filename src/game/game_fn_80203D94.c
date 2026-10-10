typedef struct Entry80201814 Entry80201814;
typedef struct Object80201D14 Object80201D14;
typedef struct Object80201D2C Object80201D2C;

extern int lbl_8064D18C;
extern int lbl_8064D180;
extern unsigned char *lbl_8064C4E0;
extern int lbl_8064D8AC;

extern int fn_80035628(void *object);
extern int fn_800459E0(void *object);
extern void fn_8004892C(int value);
extern void fn_801E7974(unsigned char *bits, unsigned int index);
extern int fn_80200C10(int *data);
extern int fn_80200C20(int *data);
extern unsigned long long fn_8020123C(int type, int first, int second, int value);
extern Entry80201814 *fn_80201814(int id);
extern int fn_802019EC(int id, int group);
extern int fn_80201B54(int *object);
extern void fn_80201D14(Object80201D14 *object, unsigned char value);
extern void fn_80201D2C(Object80201D2C *object, int value);

int fn_80203D94(int *object, int action, int *data, int *result)
{
    int type = fn_80200C10(data);
    int id = fn_80200C20(data);
    Entry80201814 *resolved = fn_80201814(id);
    int other = fn_80201B54(object);
    int event = fn_800459E0(resolved);

    if (action != 0) {
        if (action == 0xE) {
            if (type == 0x3B) {
                int value = 0;
                if (event == 6) {
                    switch (lbl_8064D18C) {
                    case 7:
                    case 0x20:
                        value = 1;
                        break;
                    }
                }
                if (result != 0)
                    *result = value;
                return 1;
            }

            if (type == 0x85) {
                int state = lbl_8064D18C;
                int target = -1;
                int value;

                switch (state) {
                case 7:
                    target = fn_802019EC(0x331, state);
                    value = 0x179;
                    break;
                case 0x20:
                    target = fn_802019EC(0x17A, state);
                    value = 0x17A;
                    fn_8004892C(0x965);
                    break;
                }

                if (other == target) {
                    fn_801E7974(lbl_8064C4E0, value);
                    lbl_8064D8AC = fn_80035628(resolved);
                    fn_80201D2C((Object80201D2C *)object, 0x30);
                    fn_80201D14((Object80201D14 *)object, 1);
                }
                return 1;
            }
        } else if (action == 0x30) {
            if (type == 0x3D) {
                int state = lbl_8064D180;
                int target = -1;
                switch (state) {
                case 7:
                    target = fn_802019EC(0x331, state);
                    break;
                case 0x20:
                    target = fn_802019EC(0x17A, state);
                    break;
                }

                if (other == target)
                    fn_8020123C(0x39, other, other, 0);
                return 1;
            }
        } else {
            return 0;
        }
    }

    return 0;
}
