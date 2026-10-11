typedef struct Entry80201814 Entry80201814;

extern int fn_80200C10(int *event);
extern int fn_80200C20(int *event);
extern void *fn_80200C38(void **event);
extern Entry80201814 *fn_80201814(int id);
extern int fn_80036E50(void *object);
extern int lbl_8064D18C;

int fn_800CCAD0(void *unused, int *event)
{
    int kind = fn_80200C10(event);
    void *payload = fn_80200C38((void **)event);

    switch (kind) {
    case 8:
    case 11:
    case 39:
    case 59:
        if (lbl_8064D18C == 0xD0) {
            int id = fn_80200C20(event);
            Entry80201814 *object = fn_80201814(id);
            if (object != 0 && fn_80036E50(object) == 0x28) {
                return 0;
            }
        } else if (lbl_8064D18C == 0x40 && kind == 59 && (int)payload == 1) {
            return 0;
        }
        goto accepted;

    case 10:
    case 24:
    case 25:
    case 30:
    case 32:
    case 50:
    case 53:
    case 55:
    case 57:
    case 60:
    case 63:
    case 67:
    case 101:
    case 103:
    case 107:
    case 125:
    case 133:
    case 202:
accepted:
        return 1;
    default:
        return 0;
    }
}
