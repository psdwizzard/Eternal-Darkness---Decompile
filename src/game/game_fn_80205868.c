typedef unsigned int u32;

extern void *lbl_8064D18C;

extern void fn_80200F3C(int value, void *object);
extern u32 fn_8011FAEC(void *object);
extern u32 fn_8012B89C(void *object);
extern int fn_80128228(u32 type);
extern int fn_80128130(u32 type);
extern int fn_801207F0(void *object);
extern void *fn_80205730(void *object, int value, void *data, u32 flags);

void *fn_80205868(void *object, int value, void *data, u32 flags)
{
    void *result = 0;
    u32 object_flags;
    u32 type;
    int allowed;

    fn_80200F3C(-1, lbl_8064D18C);
    object_flags = fn_8011FAEC(object);
    type = fn_8012B89C(object);
    if (type <= 3) {
        allowed = fn_80128228(type);
    } else {
        allowed = fn_80128130(type);
    }

    if (allowed != 0 && fn_801207F0(object) != 0) {
        result = fn_80205730(object, value, data,
                             flags | (object_flags & 0xDFFFFF3F));
    }
    return result;
}
