typedef unsigned int u32;

extern void* lbl_805B4A20[6];
extern void* lbl_805B4A38[6];
extern float lbl_806504A8;

typedef struct QueryResult8014B7B0 {
    u32 words[6];
} QueryResult8014B7B0;

extern void* fn_8011F130(void*);
extern float fn_8011F6F8(void*);
extern u32 fn_80143C28(void*, void*, float, QueryResult8014B7B0*, void**,
                       void**);

int fn_8014B7B0(void* object)
{
    int i;
    void* owner;
    float radius;

    owner = fn_8011F130(object);
    radius = lbl_806504A8 + fn_8011F6F8(object);

    for (i = 0; i < 6; i++) {
        if (lbl_805B4A20[i] != 0 && lbl_805B4A38[i] != 0) {
            QueryResult8014B7B0 result;
            void* firstHit;
            void* secondHit;
            if (fn_80143C28(owner, lbl_805B4A38[i], radius,
                            &result, &firstHit, &secondHit) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
