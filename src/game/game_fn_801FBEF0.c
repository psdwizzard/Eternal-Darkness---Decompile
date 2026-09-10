typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Query {
    unsigned char data[0x48];
} Query;

typedef struct EntryTable {
    unsigned char pad[0xA4];
    unsigned int first;
    unsigned char padA8[4];
    unsigned int second;
} EntryTable;

extern Vec3 lbl_8063D378;

extern int fn_801FA250(int, int, int);
extern EntryTable* fn_8015C28C(int);
extern void fn_80179DB0(Vec3*, Vec3*);
extern void fn_80140E58(void);
extern void fn_8013F3C0(Query*, Vec3*, Vec3*);
extern void* fn_8011F130(void*);
extern float fn_8011F6F0(void*);
extern int fn_8011F760(void*);
extern int fn_8013EA5C(Query*, void*, int, float);

int fn_801FBEF0(void* object, int value, int alternate)
{
    Vec3 first;
    Vec3 second;
    Query query;
    int property;
    float scale;
    void* shape;

    {
        EntryTable* table;
        int index;

        index = fn_801FA250(value, 2, 0);
        table = fn_8015C28C(2);
        property = table->second + index * 0x78;
        fn_80179DB0(&first, (Vec3*)(table->first + index * 0x78));
        fn_80179DB0(&second, (Vec3*)property);
    }
    fn_80140E58();
    fn_8013F3C0(&query, &first, &second);
    property = fn_8011F760(object);
    scale = fn_8011F6F0(object);
    shape = fn_8011F130(object);
    if (fn_8013EA5C(&query, shape, property, scale)) {
        return 1;
    }
    if (alternate) {
        fn_80140E58();
        fn_8013F3C0(&query, &lbl_8063D378, &first);
        property = fn_8011F760(object);
        scale = fn_8011F6F0(object);
        shape = fn_8011F130(object);
        return fn_8013EA5C(&query, shape, property, scale);
    }
    return 0;
}
