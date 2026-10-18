typedef unsigned char u8;

typedef struct Envelope {
    u8 mode;
    u8 state;
} Envelope;

extern int salChangeADSRState(Envelope* envelope);

int adsrSetup(Envelope* envelope)
{
    envelope->state = 0;
    return salChangeADSRState(envelope);
}
