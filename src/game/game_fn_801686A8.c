#pragma use_lmw_stmw on

extern const char lbl_8024FAD0[];
extern const char lbl_8064BBCC;
extern const char lbl_8064BBD4;
extern volatile const double lbl_80650668;
extern void LoadSignature(void*, void*);
extern int ezgetc(void*, void*);
extern int ZNAME(void*);
extern int luaU_endianess(void);
extern void TestSize(void*, int, const char*, void*);
extern double LoadNumber(void*, void*, int);
extern void luaO_verror(void*, const char*, ...);

int LoadHeader(void* object, void* input)
{
    const char* strings = lbl_8024FAD0;
    int byte;
    int native;
    int reverse;
    double value;

    LoadSignature(object, input);
    byte = ezgetc(object, input);
    if (byte > 0x40) {
        luaO_verror(object, strings + 0xA0, ZNAME(input),
                    byte / 16, byte % 16, 4, 0);
    }
    if (byte < 0x40) {
        luaO_verror(object, strings + 0xE0, ZNAME(input),
                    byte / 16, byte % 16, 4, 0);
    }

    byte = ezgetc(object, input);
    native = luaU_endianess();
    reverse = (unsigned int)((byte - native) | (native - byte)) >> 31;
    TestSize(object, 4, strings + 0x120, input);
    TestSize(object, 4, strings + 0x12C, input);
    TestSize(object, 4, strings + 0x13C, input);
    TestSize(object, 0x20, strings + 0x150, input);
    TestSize(object, 6, &lbl_8064BBCC, input);
    TestSize(object, 9, &lbl_8064BBD4, input);
    TestSize(object, 8, strings + 0x164, input);

    value = LoadNumber(object, input, reverse);
    if ((int)value != (int)lbl_80650668) {
        luaO_verror(object, strings + 0x174, ZNAME(input),
                    value, lbl_80650668);
    }
    return reverse;
}
