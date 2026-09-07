typedef unsigned char u8;
typedef unsigned short u16;

typedef int (*Callback)(void *);

typedef struct Owner {
    unsigned char pad_00[4];
    void *resource;
    unsigned char pad_08[0x38];
    Callback callbacks[4];
    void *arguments[4];
    u16 ids[4];
    u8 index;
    u8 last_index;
} Owner;

typedef struct DebugRecord {
    unsigned char pad_00[0x14];
    int value;
} DebugRecord;

extern void fn_8006C9C0(void *resource);
extern void fn_8006C9E4(void *resource, int value);
extern void fn_800EBA80(int type, void *text, int *value, int size, float scale);
extern int lbl_8064C8B0;
extern int lbl_8064C8B4;
extern unsigned char lbl_80312888[];
extern DebugRecord lbl_802FC5BC[];
extern const float lbl_8064E820;

int fn_8006EA4C(Owner *owner)
{
    int id;
    int result;
    u8 index;
    void *resource;
    int i;
    int value;
    Callback callback;
    void *argument;

    result = 0;
    resource = owner->resource;
    index = owner->index;
    id = *(unsigned int *)((unsigned char *)resource + 0x14) >> 16;
    fn_8006C9C0(resource);
    callback = owner->callbacks[index];
    argument = owner->arguments[index];
    if (id == owner->ids[index]) {
        if (index < 4 && callback != 0 && argument != 0) {
            callback(argument);
            fn_8006C9E4(resource, 0);
            owner->last_index = index;
            index++;
            if (index >= 4) {
                result = 1;
            }
        } else {
            result = 1;
        }
    }
    owner->index = index;

    if (lbl_8064C8B0 != 0) {
        for (i = 0; i < lbl_8064C8B4; i++) {
            value = lbl_802FC5BC->value;
            fn_800EBA80(2, lbl_80312888 + i * 0xC, &value, 0x40, lbl_8064E820);
        }
    }
    return result;
}
