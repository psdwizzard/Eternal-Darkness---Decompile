typedef unsigned short u16;

extern float lbl_80650F48;

int sndPitchUpOne(u16 value)
{
    return (int)(lbl_80650F48 * value);
}
