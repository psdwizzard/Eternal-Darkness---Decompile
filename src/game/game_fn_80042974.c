typedef unsigned int u32;

typedef struct Table Table;

extern Table* lbl_8064C520;
extern int lbl_8064C7E0;

extern void* fn_801E86A0(Table*, u32);
extern u32 fn_801E88E4(Table*);
extern void fn_8012B9C8(void*, void*);

void fn_80042974(void)
{
    u32 i;

    if (lbl_8064C7E0 != 0) {
        lbl_8064C7E0 = 0;
        for (i = 0; i < fn_801E88E4(lbl_8064C520); i++) {
            void* object = fn_801E86A0(lbl_8064C520, i);

            if (object != 0) {
                if (object != 0) {
                    fn_8012B9C8(object, (void*)1);
                }
            }
        }
    }
}
