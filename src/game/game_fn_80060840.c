typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef enum Result {
    ResultFour = 4,
    ResultFive = 5,
    ResultSix = 6
} Result;
extern int fn_80200C38();
extern u16 fn_801A7434(void *);
extern unsigned int rand(void);
#define rand() ((int)rand())

Result fn_80060840(void *owner, s32 *special)
{
    void *context = (void *)fn_80200C38(owner);
    Result result = (Result)-1;

    switch (fn_801A7434(context)) {
    case 16:
        result = 4;
        break;
    case 8:
        result = 5;
        break;
    case 1:
        result = 6;
        break;
    case 2:
        *special = 1;
        break;
    default:
        result = (u32)rand() % 2 ? ResultFour :
                 ((u32)rand() % 2 ? ResultFive : ResultSix);
        break;
    }

    return result;
}
