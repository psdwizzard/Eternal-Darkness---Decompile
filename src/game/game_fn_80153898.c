extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_801534D8(void*, float, short*);

void fn_80153898(void* object, short* rotation)
{
    float fraction = (float)(rand() & 15) / 15.0f;
    fn_801534D8(object, fraction, rotation);
}
