typedef unsigned int u32;

typedef struct Table Table;

extern Table* lbl_8064C528;

extern void* fn_801E86A0(Table*, u32);
extern void fn_801E87A4(Table*, Table*);
extern u32 fn_801E88E4(Table*);
extern void fn_8012B9C8(void*, int);

void fn_80042C38(Table* table)
{
    u32 i;
    void* entry;

    for (i = 0; i < fn_801E88E4(table); i++) {
        entry = fn_801E86A0(table, i);
        if (entry != 0) {
            fn_8012B9C8(entry, 1);
        }
    }
    fn_801E87A4(lbl_8064C528, table);
}
