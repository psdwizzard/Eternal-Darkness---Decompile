typedef unsigned int u32;

typedef struct State801B192C {
    unsigned char pad[0x48];
    u32 value;
} State801B192C;

extern State801B192C* __DTKCurrentTrack;
extern u32 DTKGetPosition(void);

u32 DTKGetTrackPosition(void)
{
    if (__DTKCurrentTrack != 0) {
        return DTKGetPosition() - __DTKCurrentTrack->value;
    }
    return 0;
}
