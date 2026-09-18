typedef unsigned int size_t;

typedef struct String {
    char pad00[8];
    unsigned int length;
    char pad0C[8];
    char data[1];
} String;

typedef struct Value {
    int type;
    int pad04;
    String* string;
    int pad0C;
} Value;

extern int fn_80168A70(void*, Value*);
extern int fn_801691AC(void*, Value*, int);
extern void fn_8016044C(void*, Value*, int, void*);
extern void fn_80160FAC(void*, const char*);
extern void* fn_80163A9C(void*, unsigned int);
extern String* fn_80166E3C(void*, void*, unsigned int);
extern void* memcpy(void*, const void*, size_t);
extern int lbl_8064BBF0;
extern char lbl_8024FCD0[];

void fn_801694A8(void* context, int count, Value* end)
{
    do {
        int grouped = 2;

        if ((end[-2].type != 3 && fn_80168A70(context, end - 2) != 0) ||
            (end[-1].type != 3 && fn_80168A70(context, end - 1) != 0)) {
            if (fn_801691AC(context, end, 12) == 0) {
                fn_8016044C(context, end - 2, 3, &lbl_8064BBF0);
            }
        } else if (end[-1].string->length != 0) {
            int scanOffset = 32;
            Value* scan;
            unsigned int total = end[-1].string->length + end[-2].string->length;
            goto scanTest;
scanAdd:
            total += scan[-1].string->length;
            scanOffset += 16;
            ++grouped;
scanTest:
            if (grouped < count) {
                Value* value;
                scan = (Value*)((char*)end - scanOffset);
                value = scan - 1;
                if (value->type == 3 ||
                    fn_80168A70(context, value) == 0) {
                    goto scanAdd;
                }
            }
            if (total > 0xFFFFFFFDU) {
                fn_80160FAC(context, lbl_8024FCD0);
            }
            {
                char* joined = fn_80163A9C(context, total);
                unsigned int copied = 0;
                int offset = grouped << 4;
                int remaining = grouped;
                while (remaining > 0) {
                    String* string = *(String**)((char*)end - offset + 8);
                    unsigned int length = string->length;
                    memcpy(joined + copied, string->data, length);
                    copied += length;
                    offset -= 16;
                    --remaining;
                }
                (end - grouped)->string =
                    fn_80166E3C(context, joined, copied);
            }
        }
        count -= grouped - 1;
        end = (Value*)((char*)end - ((grouped - 1) << 4));
    } while (count > 1);
}
