typedef signed int s32;
extern int fn_80201B54();
extern void* fn_80158598(int object_id, int index);
extern s32 fn_80157E1C(void* object);
extern s32 fn_80157FE0(void* object, s32 index, s32 value);
extern void* fn_80158514(void* object, s32 value);
extern unsigned int rand(void);
#define rand() ((int)rand())

s32 fn_80049220(void* object, s32 mode)
{
    s32 result = 0;
    void* entry = fn_80158598(fn_80201B54(object), 0);

    if (entry != 0) {
        s32 count = fn_80157E1C(entry);

        if (count > 0) {
            switch (mode) {
            case 0:
                result = 0;
                break;
            case 1:
                result = 0;
                if (count > 1) {
                    s32 value = fn_80157FE0(entry, 1, 0);
                    if (value != -1) {
                        result = (s32)fn_80158514(entry, value);
                    }
                }
                break;
            case 2:
            {
                s32 random = rand();
                result = count - 1;
                random &= 1;
                if (random < result) {
                    result = random;
                }
                break;
            }
            }
        }
    }
    return result;
}
