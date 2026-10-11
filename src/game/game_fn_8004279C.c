typedef struct Object Object;
typedef struct Table Table;
typedef struct Header Header;

extern int fn_8011EB04(Object *object);
extern void *fn_801E86A0(Table *table, unsigned int index);
extern void *fn_8013898C(Header *header);
extern Table *lbl_8064C530;

void *fn_8004279C(Object *object)
{
    int index = fn_8011EB04(object);
    Header *header = fn_801E86A0(lbl_8064C530, index);

    if (header != 0) {
        return fn_8013898C(header);
    }
    return 0;
}
