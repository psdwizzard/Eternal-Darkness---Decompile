extern int fn_8015784C(void*);
extern int fn_80157858(void*);
extern double lbl_8064FE78;
extern const float lbl_8064FE90;

int fn_8010D36C(void* object)
{
    float lower = (float)fn_80157858(object);
    int upper = fn_8015784C(object);

    return (int)(lower + lbl_8064FE90 * (float)(upper - fn_80157858(object)));
}
