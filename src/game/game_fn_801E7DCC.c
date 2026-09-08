typedef unsigned int u32;

typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

extern int lbl_8064CB6C;
extern int lbl_8064D5A0;
extern int lbl_8064C350;
extern int lbl_8064C354;
extern char lbl_80264AB0[16][255];

extern void* memset(void*, int, u32);
extern int fn_800F9E2C(char*, const char*, void*);
extern int fn_800FD228(const char*, const char*);
extern char* fn_800FD40C(char*, const char*);

void fn_801E7DCC(const char* format, ...)
{
    va_list args;
    char buffer[256];
    int i;

    if (lbl_8064CB6C != 0) {
        memset(buffer, 0, sizeof(buffer));
        va_start(args, format);
        fn_800F9E2C(buffer, format, args);
        buffer[255] = 0;

        for (i = 0; i < 16; i++) {
            if (fn_800FD228(buffer, lbl_80264AB0[i]) == 0) {
                return;
            }
        }

        fn_800FD40C(lbl_80264AB0[lbl_8064D5A0], buffer);
        lbl_8064C350 = lbl_8064D5A0;
        lbl_8064C354 = lbl_8064D5A0;
        lbl_8064D5A0++;
        if (lbl_8064D5A0 >= 16) {
            lbl_8064D5A0 = 0;
        }
    }
}
