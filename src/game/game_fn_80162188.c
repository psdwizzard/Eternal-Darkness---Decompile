extern char* token2string[];
extern char* fn_800FD40C(char*, char*);

void luaX_token2str(int value, char* output)
{
    if (value < 0x100) {
        output[0] = value;
        output[1] = 0;
    } else {
        fn_800FD40C(output, token2string[value - 0x101]);
    }
}
