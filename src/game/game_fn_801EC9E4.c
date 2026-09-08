typedef unsigned int u32;

typedef struct TransformData {
    u32 words[13];
} TransformData;

extern void fn_801ED118(void);
extern void fn_80228D9C(void);
extern void fn_801F02C4(void);
extern void fn_801F683C(TransformData* value);
extern void fn_801F03F0(TransformData* value, int index);
extern void fn_80120688(void);

void fn_801EC9E4(void)
{
    TransformData target;
    TransformData source;

    fn_801ED118();
    fn_80228D9C();
    fn_801F02C4();
    fn_801F683C(&source);
    target = source;
    fn_801F03F0(&target, 0);
    fn_80120688();
}
