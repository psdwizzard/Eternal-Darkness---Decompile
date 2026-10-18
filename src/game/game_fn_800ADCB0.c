typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PadStatus {
    u16 button;
    signed char stickX, stickY;
    signed char substickX, substickY;
    u8 triggerL, triggerR;
    u8 analogA, analogB;
    signed char err;
} PadStatus;

typedef struct EffectNode EffectNode;

typedef struct DiscMessages {
    u8 cover_open[0x2B8];
    u8 fatal_error[0x3EC];
    u8 retry[0x394];
    u8 no_disc[0x1D0];
    u8 wrong_disc[0x7B0];
    u8 loading[0x118];
    char resumed[20];
} DiscMessages;
extern DiscMessages lbl_802458F0;
extern PadStatus lbl_8031E3D8[4];
extern u8 lbl_80302460[];
extern int lbl_8064B678, lbl_8064B67C;
extern int lbl_8064B680, lbl_8064B684;
extern int lbl_8064B688, lbl_8064B68C;
extern int lbl_8064B690, lbl_8064B694;
extern int lbl_8064B698, lbl_8064B69C;
extern int lbl_8064B6A0, lbl_8064B6A4;
extern int lbl_8064C64C, lbl_8064C6D8;
extern int lbl_8064C998, lbl_8064C99C, lbl_8064C9A0;
extern int lbl_8064C9A4, lbl_8064C9A8, lbl_8064C9B0;
extern void* lbl_8064C9B4;
extern int lbl_8064C9B8, lbl_8064C9BC, lbl_8064C9C0;
extern int lbl_8064CA64;

extern int DVDGetDriveStatus(void);
extern int OSGetResetButtonState(void);
extern int DVDCheckDisk(void);
extern void fn_800ADC2C(int);
extern void fn_80025AA4(void);
extern void OSResetSystem(int, u32, int);
extern void fn_80237D84(void);
extern void VIWaitForRetrace(void);
extern void PADControlMotor(int, u32);
extern void fn_80025AA0(void);
extern void fn_80025D28(void);
extern int fn_80144F48(void);
extern int fn_80144F5C(void);
extern int PADRead(PadStatus*);
extern int PADReset(u32);
extern int PADRecalibrate(u32);
extern u32 DTKGetState(void);
extern int fn_801AD72C(void);
extern void DTKSetState(int);
extern void fn_801ACFB0(void);
extern void sndMasterVolume(u8, u16, u8, u8);
extern void* fn_801EFE84(void*);
extern void fn_80236914(void);
extern void fn_801AD95C(int);
extern void fn_80006954(u32);
extern void fn_800AD540(void*, int, int, int);
extern void VIFlush(void);
extern int fn_801ACDD4(void);
extern void fn_801ACD8C(void);
extern EffectNode* fn_801AD4B4(int, int, int, u16);
extern void fn_80008B6C(void);
extern u8 fn_801A9B30(void);
extern u8 fn_801A9B28(void);
extern void fn_802368A8(void);
extern void OSReport(const char*, ...);
extern void OSStopStopwatch(void*);
extern void OSResetStopwatch(void*);
extern void OSStartStopwatch(void*);
extern int fn_800ADB44(int*, int*, int*);
extern int fn_8023657C(void);
extern int fn_80156F10(void);
extern int OSCheckActiveThreads(void);

/* Drive-error monitor: suspend resources while displaying an error,
 * process reset requests, and restore resources when the drive recovers. */
void fn_800ADCB0(void)
{
    int kind1_count, kind2_count, kind4_count;
    int drive_status;
    int reset;
    int special;
    int saved_object;
    int pad_reset;
    register DiscMessages* data;
    u8* last_message;
    register u8* message;
    int height, width, stride;
    u32 saved_state;
    register int message_frames;

    data = &lbl_802458F0;
    pad_reset = 0;
    message_frames = 0;
    last_message = 0;
    lbl_8064C9B0 = 0;
    lbl_8064C9C0 = 0;
    lbl_8064C9BC = 0;
    for (;;) {
        drive_status = DVDGetDriveStatus();
        reset = OSGetResetButtonState();
        if (lbl_8064C9A0 != 0) {
            lbl_8064C9B0 = 1;
            reset = 0;
        }
        if (reset != 0) {
            lbl_8064C9B0 = 1;
            lbl_8064C99C = 0;
        } else if (lbl_8064C9B0 != 0 && lbl_8064CA64 == 0 && lbl_8064C998 > 120) {
            if (lbl_8064C9B8 != 0 || DVDCheckDisk() == 0) {
                fn_800ADC2C(1);
                fn_80025AA4();
                OSResetSystem(1, 0, 0);
            }
            fn_80237D84();
            VIWaitForRetrace();
            VIWaitForRetrace();
            PADControlMotor(0, 2);
            lbl_8064C6D8 = 13;
            fn_800ADC2C(1);
            fn_80025AA0();
            fn_80025D28();
            lbl_8064C9B0 = 0;
        } else if (lbl_8064C9B0 != 0) {
            lbl_8064C9A0 = 1;
        }

        if (pad_reset == 0) {
            pad_reset = fn_80144F48();
        }
        fn_80144F5C();
        if (pad_reset != 0) {
            VIWaitForRetrace();
            PADRead(lbl_8031E3D8);
            if (lbl_8031E3D8[0].err != 0) {
                VIWaitForRetrace();
                PADReset(0x80000000);
                VIWaitForRetrace();
            } else {
                VIWaitForRetrace();
                PADRecalibrate(0x80000000);
                do {
                    VIWaitForRetrace();
                } while (PADReset(0x80000000) != 1);
                VIWaitForRetrace();
                pad_reset = 0;
            }
        }

        switch (drive_status) {
        case 5:
            height = lbl_8064B67C;
            /* ASM: addi computes message = data->cover_open at offset zero.
             * MWCC folds that C expression into mr instead of retail's addi. */
            asm { addi message, data, 0 }
            width = lbl_8064B678;
            stride = 0x2B6;
            message_frames = 5;
            break;
        case 4:
            height = lbl_8064B694;
            message = data->no_disc;
            width = lbl_8064B690;
            stride = 0x1CD;
            message_frames = 5;
            break;
        case 6:
            height = lbl_8064B69C;
            message = data->wrong_disc;
            width = lbl_8064B698;
            stride = 0x338;
            message_frames = 5;
            break;
        case 11:
            height = lbl_8064B68C;
            message = data->retry;
            width = lbl_8064B688;
            stride = 0x391;
            message_frames = 5;
            break;
        case -1:
            height = lbl_8064B684;
            message = data->fatal_error;
            width = lbl_8064B680;
            stride = 0x3EA;
            message_frames = 5;
            break;
        default:
            if (message_frames > 0) {
                message_frames--;
            }
            break;
        }

        if (message_frames != 0) {
            if (lbl_8064C9B8 == 0) {
                fn_800ADC2C(1);
                saved_state = DTKGetState();
                if (saved_state != 0 && saved_state != 3) {
                    saved_object = fn_801AD72C();
                    DTKSetState(0);
                    fn_801ACFB0();
                }
                sndMasterVolume(0, 5, 1, 1);
                lbl_8064C9B4 = fn_801EFE84(0);
                PADControlMotor(0, 2);
                fn_80236914();
                fn_801AD95C(1);
                lbl_8064C9B8 = 1;
                fn_80006954(1);
            } else {
                PADRead(lbl_8031E3D8);
                if (lbl_8031E3D8[0].err == 0) {
                    if ((lbl_8031E3D8[0].button & 0x1600) == 0x1600) {
                        if (++lbl_8064C9A4 >= 30 && lbl_8064CA64 == 0) {
                            lbl_8064C9B0 = 1;
                        }
                    } else {
                        lbl_8064C9A4 = 0;
                    }
                }
            }
            if (last_message != message) {
                fn_800AD540(message, width, height, stride);
                last_message = message;
            }
            VIFlush();
        } else if (lbl_8064C9B8 != 0) {
            if (DVDCheckDisk() == 1) {
                if (fn_801ACDD4() == 1) {
                    fn_801ACD8C();
                    saved_state = 0;
                }
                if (saved_state != 0) {
                    fn_801ACD8C();
                    fn_801AD4B4(saved_object, 0, 0, 0);
                    fn_80008B6C();
                }
                sndMasterVolume(fn_801A9B30(), 5, 0, 1);
                sndMasterVolume(fn_801A9B28(), 5, 1, 0);
                DTKSetState(saved_state);
                fn_800ADC2C(0);
                fn_801EFE84(lbl_8064C9B4);
                fn_802368A8();
                lbl_8064C9B8 = 0;
                OSReport(data->resumed);
                OSStopStopwatch(lbl_80302460);
                OSResetStopwatch(lbl_80302460);
                OSStartStopwatch(lbl_80302460);
                saved_state = 0;
                fn_80006954(60);
            }
            if (last_message != message) {
                height = lbl_8064B6A4;
                message = data->loading;
                width = lbl_8064B6A0;
                stride = 0x8B;
                fn_800AD540(message, width, height, stride);
                last_message = message;
            }
        } else {
            special = fn_800ADB44(&kind1_count, &kind2_count, &kind4_count);
            if (fn_8023657C() != 0) {
                height = lbl_8064B6A4;
                message = data->loading;
                width = lbl_8064B6A0;
                stride = 0x8B;
                fn_800AD540(message, width, height, stride);
                last_message = message;
            } else {
                last_message = 0;
            }
            if (kind2_count + kind1_count < 2 || special != 0) {
                lbl_8064C99C++;
                if (special != 0) {
                    PADRead(lbl_8031E3D8);
                    if (lbl_8031E3D8[0].err == 0) {
                        if ((lbl_8031E3D8[0].button & 0x1600) == 0x1600) {
                            if (++lbl_8064C9A8 >= 30 && lbl_8064CA64 == 0) {
                                lbl_8064C9B0 = 1;
                            }
                        } else {
                            lbl_8064C9A8 = 0;
                        }
                    }
                }
            } else {
                if (lbl_8064C64C == lbl_8064C9C0) {
                    lbl_8064C9BC++;
                } else {
                    lbl_8064C9C0 = lbl_8064C64C;
                    lbl_8064C9BC = 0;
                }
                if (lbl_8064C9BC == 1000) {
                    fn_80156F10();
                }
                lbl_8064C99C = 0;
            }
        }
        lbl_8064C998++;
        OSCheckActiveThreads();
        VIWaitForRetrace();
    }
}
