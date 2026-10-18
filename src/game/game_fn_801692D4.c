typedef unsigned int size_t;

typedef struct Text {
    char pad00[8];
    unsigned int length;
    char pad0C[8];
    char text[1];
} Text;

extern int strcoll(const char*, const char*);
extern size_t strlen(const char*);

int luaV_strcomp(Text* left, Text* right)
{
    char* left_text = left->text;
    unsigned int left_length = left->length;
    char* right_text = right->text;
    unsigned int right_length = right->length;

    for (;;) {
        int result = strcoll(left_text, right_text);
        unsigned int length;

        if (result != 0) {
            return result;
        }
        length = strlen(left_text);
        if (length == left_length) {
            return length == right_length ? 0 : -1;
        }
        if (length == right_length) {
            return 1;
        }
        ++length;
        left_text += length;
        right_text += length;
        left_length -= length;
        right_length -= length;
    }
}
