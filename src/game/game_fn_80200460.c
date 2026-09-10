extern void *fn_80200C40(void);
extern void *fn_80200C4C(void *);
extern int fn_80200C54(void *);
extern void *fn_80200C60(void *);
extern int fn_80200C10(void *);
extern int fn_80200C20(void *);
extern int fn_80200C28(void *);
extern float fn_80200C30(void *);
extern void fn_80200C08(void *, float);

void fn_80200460(int first, int second, int third, int force, float value)
{
    void *node = fn_80200C40();

    while (node != 0) {
        if (fn_80200C54(node) == 0) {
            void *object = fn_80200C60(node);
            int kind = fn_80200C10(object);
            int object_id = fn_80200C28(object);

            if (first == fn_80200C20(object) && second == object_id && third == kind) {
                if (value > fn_80200C30(object) || force != 0) {
                    fn_80200C08(object, value);
                }
            }
        }
        node = fn_80200C4C(node);
    }
}
