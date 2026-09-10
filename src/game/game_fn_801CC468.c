typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DSPvoice {
    u8 pad00[0x24];
    u32 changed[5];
    u8 pad38[0xBC];
} DSPvoice;

extern u8 lbl_8064D3A0;
extern DSPvoice* volatile lbl_8064D4AC;
extern u8 lbl_8064D4E5;
extern u8 lbl_8064D4E6;
extern u8 lbl_8064D4E7;

extern void fn_801B9C94(void);
extern void fn_801CE2F0(void);
extern void fn_801CE070(void);
extern void fn_801CE190(void);
extern void fn_801CE310(void);
extern void fn_801C7868(void);
extern void fn_801CC6CC(u32);
extern void fn_801B5228(u32);
extern void fn_801B7A7C(u32);
extern void fn_801C9E74(void);
extern void fn_801B941C(void);
extern void fn_801C36FC(void);

void fn_801CC468(void)
{
    u32 timeOffset;
    u8 voiceIndex;
    u8 i;

    if (lbl_8064D3A0 == 0) {
        return;
    }

    fn_801B9C94();
    fn_801CE2F0();
    fn_801CE070();
    fn_801CE190();
    fn_801CE310();
    fn_801CE2F0();
    fn_801C7868();
    fn_801CE310();
    fn_801CE2F0();

    lbl_8064D4E7 ^= 1;
    lbl_8064D4E6 = (lbl_8064D4E6 + 1) % 3;

    for (voiceIndex = 0; voiceIndex < lbl_8064D4E5; voiceIndex++) {
        for (i = 0; i < 5; i++) {
            lbl_8064D4AC[voiceIndex].changed[i] = 0;
        }
    }

    fn_801CE310();

    for (timeOffset = 0; (u8)timeOffset < 5; timeOffset++) {
        fn_801CE2F0();
        fn_801CC6CC(timeOffset);
        fn_801B5228(0x100);
        fn_801B7A7C(0x100);
        fn_801CE310();
    }

    fn_801CE2F0();
    fn_801CC6CC(0);
    fn_801C9E74();
    fn_801CE310();
    fn_801CE2F0();
    fn_801B941C();
    fn_801CE310();
    fn_801CE2F0();
    fn_801C36FC();
    fn_801CE310();
}
