typedef struct Entry { void* resource; unsigned char index; unsigned char pad[3]; } Entry;
typedef struct Group {
    unsigned char pad0[0x3C]; unsigned short count; unsigned short pad3E;
    Entry* entries; unsigned char* records; unsigned char pad48[4]; const void* context;
} Group;
typedef struct Result { unsigned int word[6]; } Result;

extern void* lbl_8064C4E0;
extern float lbl_8065037C;
extern int fn_801E79FC(void*, int);
extern int fn_8013E284(const void*, const void*, const void*, Result*);
extern float PSVECSquareDistance(const Result*, const void*);

Entry* fn_8013E188(const void* point, const Group* group, Result* result)
{
    unsigned short i;
    Entry* entry = group->entries;
    const void* context = group->context;
    float best = lbl_8065037C;
    Entry* found = 0;
    Result candidate;
    i = 0;
    while (i < group->count) {
        if (fn_801E79FC(lbl_8064C4E0, (int)entry->resource) &&
            fn_8013E284(point, group->records + entry->index * 56,
                        context, &candidate)) {
            float distance = PSVECSquareDistance(&candidate, point);
            if (distance < best) {
                best = distance;
                found = entry;
                *result = candidate;
            }
        }
        i++;
        entry++;
    }
    return found;
}
