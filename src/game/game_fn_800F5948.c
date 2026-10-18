extern int GetTRKConnected(void);
extern unsigned char TRKCloseFile(int, void *);

int __close_console(void *arg)
{
    unsigned char result;
    if (GetTRKConnected() == 0) {
        return 1;
    }
    result = TRKCloseFile(0xD3, arg);
    switch (result) {
    case 0:
        return 0;
    case 2:
        return 2;
    default:
        return 1;
    }
}
