typedef struct StringReadState {
    const char* cursor;
    int null_seen;
} StringReadState;

int __StringRead(StringReadState* state, int ch, int mode)
{
    const char* cursor;
    int result;

    switch (mode) {
    case 0:
        cursor = state->cursor;
        result = *(const unsigned char*)cursor;
        if ((signed char)result == 0) {
            state->null_seen = 1;
            return -1;
        }
        state->cursor = cursor + 1;
        return result;
    case 1:
        if (!state->null_seen) {
            --state->cursor;
        } else {
            state->null_seen = 0;
        }
        return ch;
    case 2:
        return state->null_seen;
    default:
        return 0;
    }
}
