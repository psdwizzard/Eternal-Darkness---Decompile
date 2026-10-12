extern int fn_800B1944(void);
extern int fn_800B6908(void);
extern void fn_800B7D20(void);
extern void fn_800B8DBC(void);
extern void fn_800B9260(void);
extern void fn_800B933C(void);
extern void fn_801E5FB0(void *);
extern void *lbl_8064CA20;
extern signed char lbl_8064CA31;
extern int lbl_8064CDC8;

void fn_800B23FC(int value)
{
    int active = fn_800B6908();

    switch (value) {
    case 0:
    case 3:
    case 7:
    case 90:
    case 94:
        break;
    case 1:
    case 2:
        switch (fn_800B1944()) {
        case 1:
            if (active == 0) {
                if (lbl_8064CA20 != 0) {
                    fn_801E5FB0(lbl_8064CA20);
                }
                fn_800B7D20();
            }
            break;
        case 0:
            if (fn_800B6908() == 1 && lbl_8064CDC8 != 3) {
                fn_800B7D20();
            }
            break;
        case 3:
            if (lbl_8064CA20 != 0) {
                fn_801E5FB0(lbl_8064CA20);
            }
            fn_800B7D20();
            break;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
        fn_800B8DBC();
        break;
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
    case 89:
    case 91:
    case 92:
    case 93:
    case 95:
    case 96:
    case 97:
        fn_800B9260();
        break;
    case 98:
        if (lbl_8064CA31 == 0) {
            fn_800B933C();
        }
        break;
    }
}
