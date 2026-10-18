extern void sndFXCtrl(void *, int, int);

void fn_801A9984(void *object, int value)
{
    if (object != 0) {
        sndFXCtrl(object, 7, value);
    }
}
