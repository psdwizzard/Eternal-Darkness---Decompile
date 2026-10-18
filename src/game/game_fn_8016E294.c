typedef unsigned char u8;

typedef struct DVDFileInfo {
    u8 data[0x3C];
} DVDFileInfo;

extern void* fn_8015E4A4(void);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int sprintf(char*, const char*, ...);
extern int DVDChangeDir(const char*);
extern int DVDOpen(const char*, DVDFileInfo*);
extern void DVDClose(DVDFileInfo*);
extern void fn_8015977C(int, int, int, int, int);
extern const char lbl_8024FF00[];
extern const char lbl_8024FFEC[];
extern const char lbl_8064DC80[];
extern char lbl_8064BC10;
extern char lbl_8064BC18;

int fn_8016E294(void* state)
{
    signed char path[16];
    DVDFileInfo file;
    int first;
    int second;
    int third;
    int i;
    int opened;

    fn_8015E4A4();
    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    third = (int)lua_tonumber(state, 3);
    sprintf((char*)path, lbl_8024FFEC, lbl_8064DC80, first);
    for (i = 0; i < 13; i++) {
        if (path[i] == ' ') {
            path[i] = '0';
        }
    }
    DVDChangeDir(&lbl_8064BC10);
    opened = DVDOpen((char*)path, &file);
    DVDChangeDir(&lbl_8064BC18);
    if (opened != 0) {
        DVDClose(&file);
        fn_8015977C(first, second, third, 0, 0);
    }
    return 0;
}
