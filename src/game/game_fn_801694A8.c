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

extern int luaV_tostring(void*, Value*);
extern int call_binTM(void*, Value*, int);
extern void luaG_binerror(void*, Value*, int, void*);
extern void lua_error(void*, const char*);
extern void* luaO_openspace(void*, unsigned int);
extern String* luaS_newlstr(void*, void*, unsigned int);
extern void* memcpy(void*, const void*, size_t);
extern int lbl_8064BBF0;
extern char lbl_8024FCD0[];

void luaV_strconc(void* context, int count, Value* end)
{
    do {
        int grouped = 2;

        if ((end[-2].type != 3 && luaV_tostring(context, end - 2) != 0) ||
            (end[-1].type != 3 && luaV_tostring(context, end - 1) != 0)) {
            if (call_binTM(context, end, 12) == 0) {
                luaG_binerror(context, end - 2, 3, &lbl_8064BBF0);
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
                    luaV_tostring(context, value) == 0) {
                    goto scanAdd;
                }
            }
            if (total > 0xFFFFFFFDU) {
                lua_error(context, lbl_8024FCD0);
            }
            {
                char* joined = luaO_openspace(context, total);
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
                    luaS_newlstr(context, joined, copied);
            }
        }
        count -= grouped - 1;
        end = (Value*)((char*)end - ((grouped - 1) << 4));
    } while (count > 1);
}
