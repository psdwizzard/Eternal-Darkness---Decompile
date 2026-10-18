typedef unsigned char u8;

extern int __DTKTrackEnded;
extern int __DTKPosition;

void __DTKCallbackForStreamStatus(int value)
{
    if ((value & 0xFF) == 0) {
        __DTKTrackEnded = 1;
        __DTKPosition = 0;
    }
}
