extern char lbl_8024F738[];
extern char lbl_8064BB4C;
extern char lbl_8064BB50;

extern int strlen(const char*);
extern unsigned long strcspn(const char*, const char*);
extern char* strncpy(char*, const char*, unsigned long);
extern char* fn_800FD40C(char*, const char*);
extern int sprintf(char*, const char*, ...);

void luaO_chunkid(char* output, signed char* source, int size)
{
    char* strings = lbl_8024F738;
    int length;

    if (*source == '=') {
        strncpy(output, (char*)source + 1, size);
        output[size - 1] = 0;
    } else if (*source == '@') {
        source++;
        length = strlen((char*)source);
        if (length > size - 13) {
            source += length - (size - 13);
            sprintf(output, strings + 0x24, source);
        } else {
            sprintf(output, strings + 0x34, source);
        }
    } else {
        length = strcspn((char*)source, &lbl_8064BB4C);
        if ((unsigned long)length > (unsigned long)(size - 17)) {
            length = size - 17;
        }
        if (source[length] != 0) {
            fn_800FD40C(output, strings + 0x44);
            output += strlen(output);
            strncpy(output, (char*)source, length);
            fn_800FD40C(output + length, &lbl_8064BB50);
        } else {
            sprintf(output, strings + 0x50, source);
        }
    }
}
