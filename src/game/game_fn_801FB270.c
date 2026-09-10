typedef unsigned char u8;

extern void* fn_8011F9E4(void*, int);
extern int fn_8011FA40(void*);
extern void* fn_8011FA4C(void*, int);
extern int fn_8011FA60(void*);

int fn_801FB270(void* object, void* record, int alternate)
{
    u8* records;
    int count;
    int index;

    if (alternate) {
        records = (u8*)fn_8011FA4C(object, 0);
    } else {
        records = (u8*)fn_8011F9E4(object, 0);
    }
    if (alternate) {
        count = fn_8011FA60(object);
    } else {
        count = fn_8011FA40(object);
    }
    for (index = 0; index < count; index++) {
        if (records == record) {
            return index;
        }
        records += 120;
    }
    return -1;
}
