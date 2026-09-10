extern void *fn_80200C40(void);
extern void *fn_80200C4C(void *);
extern int fn_80200C54(void *);
extern void *fn_80200C60(void *);
extern int fn_80200C10(void *);
extern int fn_80200C28(void *);
extern float fn_80200C30(void *);
extern void fn_80200C08(void *, float);
extern float lbl_80651580;

void fn_802003C0(int object_id, int event_id)
{
    void *node = fn_80200C40();

    while (node != 0) {
        if (fn_80200C54(node) == 0) {
            void *object = fn_80200C60(node);
            int kind = fn_80200C10(object);

            if (fn_80200C28(object) == object_id && event_id == kind) {
                fn_80200C08(object, lbl_80651580 + fn_80200C30(object));
            }
        }
        node = fn_80200C4C(node);
    }
}
