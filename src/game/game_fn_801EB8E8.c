typedef unsigned int u32;
typedef struct Entry { u32 value; void* object; } Entry;
extern int lbl_8064D650;
extern int lbl_8064D654;
extern Entry lbl_80639260[];
extern u32 fn_801EB30C(void);
void fn_801EB8E8(void* object)
{
    int count;
    if (lbl_8064D650 != 0) {
        lbl_80639260[lbl_8064D654].object = object;
        object = (void*)fn_801EB30C();
        count = lbl_8064D654;
        lbl_80639260[count].value = (u32)object;
        lbl_8064D654 = count + 1;
    }
}
