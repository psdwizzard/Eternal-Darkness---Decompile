extern void* memcpy(void*, const void*, unsigned int);
extern void *fn_80201BC8();
extern unsigned int lbl_80651BD8;
extern unsigned short lbl_80651BDC;
extern unsigned int lbl_80651BE0;
extern unsigned short lbl_80651BE4;

typedef struct QueryResult {
    unsigned char pad[8];
    float x;
    float y;
    float z;
    unsigned char pad2[20];
} QueryResult;

extern int fn_8011F6A4(void*, void*, int, int, QueryResult*, int);

void fn_801493D4(void* object, short* firstOut, void* firstQuery,
                 void* secondQuery, unsigned char* secondOut)
{
    unsigned short first[3];
    unsigned short second[3];
    QueryResult result;
    void* base;

    *(unsigned int*)&first[0] = lbl_80651BD8;
    first[2] = lbl_80651BDC;
    *(unsigned int*)&second[0] = lbl_80651BE0;
    second[2] = lbl_80651BE4;

    base = fn_80201BC8(object);
    if (fn_8011F6A4(base, firstQuery, 15, -1, &result, 1) != -1) {
        first[0] = (short)result.x;
        first[1] = (short)result.y;
        first[2] = (short)result.z;
    }
    if (fn_8011F6A4(base, secondQuery, 15, -1, &result, 1) != -1) {
        second[0] = (short)result.x;
        second[1] = (short)result.y;
        second[2] = (short)result.z;
    }
    memcpy(firstOut, first, 6);
    memcpy(secondOut + 0x20, second, 6);
}
