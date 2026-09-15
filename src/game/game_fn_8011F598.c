typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SearchRecord {
    volatile int second;
    int first;
    u8 pad08[0x0C];
    float value;
    u8 pad18[4];
} SearchRecord;

typedef struct SearchResult {
    int second;
    int first;
    u8 pad08[0x18];
    float value;
} SearchResult;

extern void fn_8011F220(void* object, int index, SearchResult* result);
extern void fn_8011F244(void* object, int index, SearchResult* result, int mode);
extern void fn_8011F574(void* object, int index, SearchResult* result);

int fn_8011F598(void* object, int first, int second, int previous,
                SearchResult* result, u8 options)
{
    u8* owner = *(u8**)((u8*)object + 0x3C);
    int index;
    int found = -1;

    if (owner != 0) {
        int count = *(u16*)(owner + 0xB8);
        SearchRecord* record;

        if (previous + 1 >= 0) {
            index = previous + 1;
            if (index < count) {
                int current = index;
                record = (SearchRecord*)(*(u8**)(owner + 0xBC) + index * 0x1C);
                for (; current < count; record++, current++) {
                    if ((record->first == first || first == -1) &&
                        (record->second == second || second == -1)) {
                        result->second = record->second;
                        result->first = record->first;
                        result->value = record->value;
                        if (options & 1) {
                            fn_8011F220(object, current, result);
                        } else if (options & 2) {
                            fn_8011F244(object, current, result, 2);
                        } else if (options & 4) {
                            fn_8011F574(object, current, result);
                        }
                        found = current;
                        break;
                    }
                }
            }
        }
    }
    return found;
}
