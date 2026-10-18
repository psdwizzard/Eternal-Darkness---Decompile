typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad000[0x10];
    u32 state;
} Entry;

extern volatile u32 __DTKState;
extern Entry* __DTKCurrentTrack;
extern u32 __DTKTrackEnded;
extern unsigned char __block_for_set_state[];

extern void __DTKStartAi(void);
extern void __DTKCheckUserCallback(Entry*, u32);
extern void __DTKPrepareCurrentTrack(void);
extern void __DTKPrepareCurrentTrackPaused(void);
extern void __DTKCallbackForStop(void);
extern void DVDCancelStreamAsync(void*, void (*)(void));
extern void AISetStreamPlayState(int);
extern void AISetStreamVolLeft(int);
extern void AISetStreamVolRight(int);

void DTKSetState(int state)
{
    if (__DTKState == state || __DTKState == 3) {
        return;
    }

    switch (state) {
    case 0:
        if (__DTKCurrentTrack != 0) {
            __DTKCurrentTrack->state = 0;
            __DTKState = 3;
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            AISetStreamPlayState(0);
            DVDCancelStreamAsync(__block_for_set_state, __DTKCallbackForStop);
        }
        break;
    case 1:
        if (__DTKState == 2) {
            __DTKStartAi();
            __DTKState = 1;
            if (__DTKCurrentTrack != 0) {
                __DTKCheckUserCallback(__DTKCurrentTrack, 1);
            }
        } else if (__DTKCurrentTrack != 0) {
            __DTKState = 3;
            __DTKPrepareCurrentTrack();
        } else {
            __DTKState = 1;
        }
        __DTKTrackEnded = 0;
        break;
    case 4:
        if (__DTKState == 0) {
            if (__DTKCurrentTrack != 0) {
                __DTKState = 3;
                __DTKPrepareCurrentTrackPaused();
            }
            __DTKTrackEnded = 0;
        }
        break;
    case 2:
        AISetStreamPlayState(0);
        if (__DTKState == 1) {
            __DTKState = 2;
        }
        if (__DTKCurrentTrack != 0) {
            __DTKCheckUserCallback(__DTKCurrentTrack, 4);
        }
        break;
    }
}
