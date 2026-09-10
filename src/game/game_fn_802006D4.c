typedef void (*ObjectCallback)(int);

extern void *fn_80200C40(void);
extern void *fn_80200C4C(void *);
extern int fn_80200C54(void *);
extern void *fn_80200C60(void *);
extern void fn_80200C64(void *);
extern int fn_80200C10(void *);
extern int fn_80200C18(void *);
extern int fn_80200C20(void *);
extern int fn_80200C28(void *);
extern int fn_80200C38(void *);

int fn_802006D4(int first, int object_id, int subtype, int kind,
                ObjectCallback callback)
{
    void *node = fn_80200C40();
    int count = 0;

    while (node != 0) {
        if (fn_80200C54(node) == 0) {
            void *object = fn_80200C60(node);
            int found_kind = fn_80200C10(object);
            int found_subtype = fn_80200C18(object);
            int callback_value = fn_80200C38(object);
            int found_id = fn_80200C28(object);

            if (first == fn_80200C20(object) && object_id == found_id &&
                (found_kind == -1 || found_kind == kind) &&
                (subtype == -1 || found_subtype == subtype)) {
                if (callback != 0) {
                    callback(callback_value);
                }
                fn_80200C64(node);
                count++;
            }
        }
        node = fn_80200C4C(node);
    }
    return count;
}
