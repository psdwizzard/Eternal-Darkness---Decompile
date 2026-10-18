typedef int s32;

typedef struct AlignmentRecord {
    s32 value;
    s32 unknown_04;
    s32 alternate;
} AlignmentRecord;

extern AlignmentRecord lbl_8023E118[];
extern s32 lbl_8064D564;
extern s32 lbl_803003C8[];
extern s32 lbl_8064C538;
extern s32 lbl_8064CD34;

extern char lbl_8064B37C;
extern char lbl_8064B380;
extern char lbl_8064B384;
extern char lbl_8064B38C;
extern char lbl_8064B390;
extern char lbl_8064B398;
extern char lbl_8064B39C;
extern char lbl_8064B374;
extern char lbl_8023E154, lbl_8023E160, lbl_8064B2F8, lbl_8023E16C;
extern char lbl_8023E178, lbl_8064B300, lbl_8064B304, lbl_8023E184;
extern char lbl_8064B308, lbl_8064B310, lbl_8064B318, lbl_8064B320;
extern char lbl_8064B328, lbl_8064B330, lbl_8064B334, lbl_8064B33C;
extern char lbl_8064B344, lbl_8064B34C, lbl_8064B354, lbl_8064B35C;
extern char lbl_8023E194, lbl_8023E1A0, lbl_8023E1AC, lbl_8023E1B8;
extern char lbl_8023E1FC, lbl_8064B364, lbl_8023E20C, lbl_8023E220;
extern char lbl_8023E230, lbl_8023E240, lbl_8064B36C, lbl_8023E250;
extern char lbl_8023E260, lbl_8023E270;
extern char lbl_8023E280;
extern char* lbl_8023E28C[];

extern s32 fn_80045240(s32);
extern void strcat(char*, const char*);
extern char* fn_800FD40C(char*, const char*);
extern s32 fn_80036E50(void);
extern void* fn_80201B3C();
extern s32 fn_801E394C(const char*);

const char* fn_80028E88(const signed char* command, s32* result)
{
    const char* text = 0;

    switch (*command) {
    case 'c':
        text = lbl_8023E28C[1];
        break;
    case 'u':
        text = lbl_8023E28C[2];
        break;
    case 'x':
        text = lbl_8023E28C[3];
        break;
    case 'm':
        text = lbl_8023E28C[4];
        break;
    case 'a':
        text = lbl_8023E28C[lbl_8064D564];
        break;
    case 's':
        text = lbl_8023E28C[lbl_8023E118[lbl_8064D564].value];
        break;
    case 'd':
        text = lbl_8023E28C[lbl_8023E118[lbl_8064D564].alternate];
        break;
    case 'g':
    {
        char buffer[0x70];

        fn_800FD40C(buffer, &lbl_8064B37C);
        if (fn_80045240(1) != 0) {
            strcat(buffer, &lbl_8064B380);
            strcat(buffer, lbl_8023E28C[1]);
            strcat(buffer, &lbl_8064B384);
        }
        if (fn_80045240(2) != 0) {
            strcat(buffer, &lbl_8064B38C);
            strcat(buffer, lbl_8023E28C[2]);
            strcat(buffer, &lbl_8064B390);
        }
        if (fn_80045240(3) != 0) {
            strcat(buffer, &lbl_8064B398);
            strcat(buffer, lbl_8023E28C[3]);
            strcat(buffer, &lbl_8064B39C);
        }
        {
            char** strings = lbl_8023E28C;
            fn_800FD40C((char*)strings[23], buffer);
            text = strings[23];
        }
        break;
    }
    case 'p':
        if (fn_80201B3C() != 0) {
            switch (fn_80036E50()) {
            case 6:
                text = lbl_8023E28C[20];
                break;
            case 3:
                text = lbl_8023E28C[21];
                break;
            case 4:
                text = lbl_8023E28C[22];
                break;
            case 1:
                text = lbl_8023E28C[8 + lbl_803003C8[0]];
                break;
            }
        } else {
            text = lbl_8023E28C[8 + lbl_803003C8[0]];
        }
        break;
    case 'r': {
        s32 value = lbl_8064C538;
        s32 positive = value > 0 ? value : 0;
        value = positive > 1 ? 1 : (value > 0 ? value : 0);
        lbl_8064C538 = value;
        text = lbl_8023E28C[5 + value];
        break;
    }
    case 'z':
        text = lbl_8023E28C[24 + lbl_8064CD34];
        break;
    default:
        text = lbl_8023E28C[7];
        break;
    }

    *result = fn_801E394C(text);
    return text;
}
