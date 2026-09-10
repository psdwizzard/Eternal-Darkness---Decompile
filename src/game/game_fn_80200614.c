extern void *fn_80200C40(void);
extern void *fn_80200C4C(void *);
extern int fn_80200C54(void *);
extern void *fn_80200C60(void *);
extern int fn_80200C10(void *);
extern int fn_80200C18(void *);
extern int fn_80200C28(void *);

int fn_80200614(int object_id, int subtype, int kind)
{
    void *node = fn_80200C40();
    int found = 0;

    while (node != 0) {
        if (fn_80200C54(node) == 0) {
            void *object = fn_80200C60(node);
            int found_id = fn_80200C28(object);
            int found_kind = fn_80200C10(object);
            int found_subtype = fn_80200C18(object);

            if (object_id == found_id &&
                (found_kind == -1 || found_kind == kind) &&
                (subtype == -1 || found_subtype == subtype)) {
                found = 1;
                break;
            }
        }
        node = fn_80200C4C(node);
    }
    return found;
}
