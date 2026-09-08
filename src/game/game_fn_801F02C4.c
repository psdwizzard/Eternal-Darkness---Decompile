typedef struct FloatTriple {
    float x;
    float y;
    float z;
} FloatTriple;

extern int lbl_8064D6C0;
extern float lbl_8064D6C8;
extern float lbl_8064D6CC;
extern int lbl_8064D6D0;
extern float lbl_8064D6D4;
extern int lbl_8064D6D8;
extern const float lbl_80651348;
extern volatile const float lbl_8065135C;

extern FloatTriple* fn_8015AB00(int);

void fn_801F02C4(void)
{
    FloatTriple* value;
    float angle;
    float limit;

    if (lbl_8064D6D8 == 0 && lbl_8064D6C0 == 0) {
        value = fn_8015AB00(2);
        if (value != 0) {
            if (lbl_8064D6D0 != 0) {
                lbl_8064D6D0--;
                if (lbl_8064D6D0 == 0) {
                    value->x = lbl_8064D6D4;
                    lbl_8064D6D0 = 0;
                    lbl_8064D6D4 = lbl_80651348;
                } else {
                    value->x += (lbl_8064D6D4 - value->x) / (float)lbl_8064D6D0;
                }
            }

            angle = lbl_8064D6C8 + value->y;
            limit = lbl_8065135C;
            lbl_8064D6C8 = angle;
            if (angle > limit) {
                lbl_8064D6C8 = angle - limit;
            }

            angle = lbl_8064D6CC + value->z;
            limit = lbl_8065135C;
            lbl_8064D6CC = angle;
            if (angle > limit) {
                lbl_8064D6CC = angle - limit;
            }
        }
    }
}
