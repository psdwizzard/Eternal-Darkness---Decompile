extern int GetTRKConnected(void);
extern int SetTRKConnected(int);
extern void OSReport(const char *);

int usr_puts_serial(const char *text)
{
    int result = 0;
    signed char ch;

    while (result == 0 && (ch = *text++) != 0) {
        int state = GetTRKConnected();
        char string[2];

        string[0] = ch;
        string[1] = 0;
        SetTRKConnected(0);
        OSReport(string);
        SetTRKConnected(state);
        result = 0;
    }
    return result;
}
