typedef struct State801B19BC {
    unsigned char pad[0x18];
    unsigned char data;
} State801B19BC;

extern State801B19BC* __DTKCurrentTrack;

void* DTKGetCurrentTrackFileInfo(void)
{
    if (__DTKCurrentTrack != 0) {
        return &__DTKCurrentTrack->data;
    }
    return 0;
}
