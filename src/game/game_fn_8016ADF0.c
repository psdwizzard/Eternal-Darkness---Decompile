typedef signed short s16;
typedef unsigned short u16;

typedef struct Entry {
    s16 id;
    u16 value2;
    u16 value4;
    u16 value6;
} Entry;

extern Entry lbl_805FAA60[10];

void fn_8016ADF0(s16 id, s16 value2, s16 value4)
{
    int i;
    int selected = -1;

    for (i = 0; i < 10; i++) {
        if (lbl_805FAA60[i].id == id) {
            selected = i;
            break;
        }
        if (selected == -1 && lbl_805FAA60[i].id == 0) {
            selected = i;
        }
    }

    lbl_805FAA60[selected].id = id;
    if (value2 >= 0) {
        lbl_805FAA60[selected].value2 = value2;
    }
    if (value4 >= 0) {
        lbl_805FAA60[selected].value4 = value4;
    }
}
