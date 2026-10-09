extern int fn_80157858(void*);
extern int fn_8010D36C(void*);
extern double lbl_8064FE78;
extern const float lbl_8064FE94;

int fn_8010D414(void* object)
{
    float lower = (float)fn_80157858(object);
    short upper = fn_8010D36C(object);

    return (int)(lower + lbl_8064FE94 * (float)(upper - fn_80157858(object)));
}
