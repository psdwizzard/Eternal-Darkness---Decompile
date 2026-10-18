extern unsigned int vidGetInternalId(void);

int sndFXCheck(int arg0)
{
    if (vidGetInternalId() != (unsigned int)-1) {
        return arg0;
    }
    return -1;
}
