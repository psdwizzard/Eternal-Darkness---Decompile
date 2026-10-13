/* fn_8021D1E8: CARDInit. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef signed long long OSTime;

typedef struct OSContext OSContext;
typedef struct OSAlarm OSAlarm;
typedef struct OSThread OSThread;
typedef struct DVDDiskID DVDDiskID;
typedef struct OSResetFunctionInfo OSResetFunctionInfo;
typedef void (*OSAlarmHandler)(OSAlarm *alarm, OSContext *context);

struct OSAlarm {
    OSAlarmHandler handler;
    u32 tag;
    OSTime fire;
    OSAlarm *prev;
    OSAlarm *next;
    OSTime period;
    OSTime start;
};

typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef struct CardControl {
    s32 attached;
    s32 result;
    u8 reserved08[0x8C - 0x08];
    OSThreadQueue threadQueue;
    u8 reserved94[0xE0 - 0x94];
    OSAlarm alarm;
    u8 reserved108[4];
    const DVDDiskID *diskID;
} CardControl;

extern CardControl lbl_80641C60[2];
extern OSResetFunctionInfo lbl_802FEB60;
extern void fn_8021B8E0(void);
extern void OSInitAlarm(void);
extern void OSInitThreadQueue(OSThreadQueue *queue);
extern void OSCreateAlarm(OSAlarm *alarm);
extern void fn_8021D284(const DVDDiskID *diskID);
extern void OSRegisterResetFunction(OSResetFunctionInfo *info);

void fn_8021D1E8(void)
{
    CardControl *card = lbl_80641C60;
    s32 channel;

    if (card[0].diskID == 0 || card[1].diskID == 0) {
        fn_8021B8E0();
        OSInitAlarm();
        for (channel = 0; channel < 2; ++channel, ++card) {
            card->result = -3;
            OSInitThreadQueue(&card->threadQueue);
            OSCreateAlarm(&card->alarm);
        }
        fn_8021D284((const DVDDiskID *)0x80000000);
        OSRegisterResetFunction(&lbl_802FEB60);
    }
}
