typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad[8];
    u16 flags;
} Entry;

typedef struct Object {
    u8 pad[0x240];
    Entry **entries;
} Object;

extern int fn_8012FA54(Object *object, int index);
extern u16 fn_8012DBE8(u8 *owner, u32 index, u8 *color);
extern int fn_8012DCBC(Object *object, int index, int mode, void *value,
                     int *direction, int flags);
extern float lbl_806500A4;
extern float lbl_806500C0;

int fn_80120558(Object *object, int index)
{
    int direction;
    u8 color[4];
    float first;
    float second;
    int visible = 1;

    if (fn_8012FA54(object, index) == 0) {
        visible = 0;
    }
    if (visible != 0) {
        fn_8012DBE8((u8 *)object, index, color);
        if (color[3] <= 5U) {
            visible = 0;
        }
    }
    if (visible != 0 && fn_8012DCBC(object, index, 1, &first, 0, 0) != 0) {
        if (first <= lbl_806500C0) {
            visible = 0;
        } else {
            visible = 1;
        }
    }
    if (visible != 0 && fn_8012DCBC(object, index, 0, &second, &direction, 4) != 0) {
        if (direction == 0) {
            second = lbl_806500A4 - second;
        }
        if (second <= lbl_806500C0) {
            visible = 0;
        } else {
            visible = 1;
        }
    }
    return visible;
}
