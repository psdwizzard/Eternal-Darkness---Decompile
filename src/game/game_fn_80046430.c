typedef unsigned short u16;
typedef int s32;
typedef unsigned long long u64;
#define NULL ((void *)0)

extern void *lbl_8064C4E0;
extern void *lbl_8064C4E4;
extern int lbl_8064D18C;

extern int fn_8015AB68(int);
extern u16 *fn_8015AB8C(int);
extern void *fn_80201B9C(void);
extern void *fn_80204844(void *, int);
extern void *fn_8006D444(void *);
extern s32 fn_8006BCB4(void *);
extern int fn_8006B804(void *, int);
extern int fn_8006B96C(int, int);
extern int fn_801E79FC(void *, int);
extern int fn_801207F0(void *);
extern int fn_80128328(void);
extern int fn_800467F0(int, int);
extern void *fn_8015C5E4(int, u16 *);
extern int fn_800A1580(int);
extern int fn_80070CD8(int);
extern void fn_8006EFA4(void *, int, int, int);
extern int fn_80201B54(void *);
extern u64 fn_8020123C(int, int, int, int);

int fn_80046430(int id, int arg1, int arg2, int arg3) {
    int result = 0;
    if (id > 0) {
        int clear = 0;
        int allowed = 0;
        int count = fn_8015AB68(2);
        u16 *list = fn_8015AB8C(2);
        void *res = fn_80204844(fn_80201B9C(), 0x20);
        void *obj = fn_8006D444(res);
        u16 *entry;
        int i;

        s32 current = fn_8006BCB4(obj);

        if (current == id) {
            if ((u16)count != 0) {
                allowed = 1;
                clear = 1;
            }

            switch (id) {
            case 12:
                if (fn_8006B804(obj, arg1) != 0 || (u16)count != 0) {
                    if (fn_801E79FC(lbl_8064C4E0, 0x3bf) == 0) {
                        allowed = 1;
                    }
                }
                clear = 0;
                break;
            case 22: {
                int r = fn_8006B96C(arg1, 1);
                allowed = 0;
                if (r >= 0 && r < 10) {
                    allowed = 1;
                }
                clear = 0;
                break;
            }
            case 13: {
                int r = fn_8006B96C(arg1, 2);
                allowed = 0;
                if (r >= 0 && r < 5) {
                    allowed = 1;
                }
                break;
            }
            case 10:
            case 18:
                entry = list;
                allowed = 0;
                for (i = 0; i < (u16)count; i++) {
                    if (entry != NULL && *entry == id) {
                        allowed = 1;
                        break;
                    }
                    entry++;
                }
                break;
            case 15:
            case 20:
            case 25:
            case 26:
            case 28:
            case 34:
            case 36:
                allowed = 0;
                break;
            case 21:
                if (fn_8006B96C(lbl_8064D18C, 7) != -1) {
                    allowed = 0;
                }
                break;
            case 33:
                if (fn_8006B96C(lbl_8064D18C, 8) != -1) {
                    allowed = 0;
                }
                break;
            case 11:
            case 17:
                if (lbl_8064C4E4 != NULL) {
                    if (fn_801207F0(lbl_8064C4E4) == 0 || fn_80128328() == 0) {
                        allowed = 0;
                    }
                }
                break;
            case 23:
                if (fn_800467F0(lbl_8064D18C, 0) > 0) {
                    allowed = 0;
                }
                break;
            }

            switch (id) {
            case 16:
            case 18:
            case 19:
            case 21:
            case 29:
                if (fn_8015C5E4(2, 0) != NULL) {
                    allowed = 0;
                }
                if (fn_8006B96C(lbl_8064D18C, 9) != -1) {
                    allowed = 0;
                }
                break;
            }

            if (clear != 0 && (u16)count != 0) {
                if (fn_8006B96C(lbl_8064D18C, 4) != -1) {
                    allowed = 0;
                }
                if (id != 13) {
                    if (fn_8006B96C(lbl_8064D18C, 6) != -1) {
                        allowed = 0;
                    }
                }
                if (fn_8006B96C(lbl_8064D18C, 5) != -1) {
                    allowed = 0;
                }
                if (fn_8006B96C(lbl_8064D18C, 10) != -1) {
                    allowed = 0;
                }
                if (lbl_8064D18C == 0x1b && id == 0x13) {
                    allowed = 0;
                }
            }

            if (obj != NULL && allowed != 0) {
                int flags = fn_800A1580(id);
                if (fn_80070CD8(flags) != 0) {
                    fn_8006EFA4(obj, arg1, arg2, arg3);
                    fn_8020123C(0x54, 0, fn_80201B54(res), 0);
                    result = 1;
                }
            }
        }
    }
    return result;
}
