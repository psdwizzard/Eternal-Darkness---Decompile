typedef unsigned char u8;

extern void* fn_8011F9E4(void*, int);
extern int fn_8011FA40(void*);
extern void* fn_8011FA4C(void*, int);
extern int fn_8011FA60(void*);

void* fn_801FB318(void* object, int index, int alternate)
{
    u8* records;
    int count;

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
    if (index < count) {
        return records + index * 120;
    }
    return 0;
}
