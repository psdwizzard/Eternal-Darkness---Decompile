extern void* memset(void*, int, unsigned long);
extern int fn_800FD1E8(const char*, const char*, unsigned long);
extern char* fn_800FD350(char*, const char*, unsigned long);
extern char* fn_800FD3C8(char*, const char*, unsigned long);

extern char lbl_8024A268[];

void fn_801EF910(void)
{
    char months[36] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char date[12];
    int month = 0;

    do {
        if (fn_800FD1E8(months + month * 3, lbl_8024A268, 3) == 0) {
            break;
        }
        month++;
    } while (month < 12);

    if (month < 12) {
        memset(date, 0, sizeof(date));
        fn_800FD350(date, lbl_8024A268 + 7, 4);
        date[4] = ' ';
        if (month + 1 >= 10) {
            date[5] = '1';
            date[6] = month + 0x27;
        } else {
            date[5] = '0';
            date[6] = month + 0x31;
        }
        date[7] = ' ';
        fn_800FD350(date, lbl_8024A268 + 4, 2);
        fn_800FD3C8(lbl_8024A268, date, 11);
    }
}
