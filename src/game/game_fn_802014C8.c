typedef struct Fn802014C8Data {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    int unk18;
    int flags;
    unsigned char unk20;
} Fn802014C8Data;

void fn_802014C8(Fn802014C8Data *data, int value)
{
    data->unk10 = value;
    data->unk14 = 0;
    data->unk18 = 0;
    data->unk8 = 0;
    data->unk20 = 0;
    data->flags |= 2;
}
