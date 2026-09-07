extern float lbl_8064E938;
extern int fn_80200C38();
extern int fn_80201B54();
extern void *fn_801A7498(void *object);
extern void *fn_80201814();
extern int fn_80128EAC(void *object);
extern int fn_80201B5C(void *object);
extern unsigned char fn_80204508(void *object, void *other);
extern void fn_80064B38(void *object, int value, void *work);
extern int fn_80079008(void *object, void *resource);
extern int fn_80128F40(void *object);
extern int fn_801A74F8(void *object);
extern float fn_8010181C(float value);
extern void fn_801A7518(void *object, int value);

void fn_80079AA4(void *object, void *resource, int value, void *work)
{
    void *wrapper = (void *)fn_80200C38(value);
    void *candidate;
    int type;

    fn_80201B54(object);
    candidate = fn_80201814(fn_801A7498(wrapper));
    type = fn_80128EAC(resource);

    if ((candidate != 0 ? fn_80201B5C(candidate) : 0) != 0x19) {
        if (candidate == 0 || !fn_80204508(object, candidate)) {
            fn_80064B38(object, value, work);
        } else {
            int state = fn_80079008(object, resource);
            int field = fn_80128F40(resource) >> 17;

            if (state == 0 || type == 0x7C || type == 0x81) {
                int allowed;

                if (type == 0x7C) {
                    allowed = field > 10;
                } else if (type == 0x81) {
                    allowed = field < 10;
                } else {
                    allowed = 1;
                }
                if (allowed) {
                    int original = fn_801A74F8(wrapper);
                    int randomized = (int)fn_8010181C((float)(short)original * lbl_8064E938);

                    fn_801A7518(wrapper, randomized);
                    fn_80064B38(object, value, work);
                    fn_801A7518(wrapper, original);
                }
            }
        }
    }
}
