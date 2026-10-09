typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SaveHeader {
    u8 pad0;
    u8 value1;
    u16 value2;
    int value4;
    int value8;
    int valueC;
    int value10;
    u8 value14;
    u8 value15;
    u16 value16;
    u8 pad18[0x28];
    u16 value40;
    u8 pad42[0x56];
} SaveHeader;

typedef struct Player {
    u8 pad0[0x8142];
    signed char value8142;
    signed char value8143;
} Player;

typedef struct GameState {
    u8 pad0[0x14];
    u8 data[0x1900];
    u8 value1914;
    u8 pad1915;
    u16 value1916;
    u8 pad1918[2];
    u8 value191A;
} GameState;

extern void* memcpy(void*, const void*, u32);
extern void fn_801E8DE4(int, int);
extern void fn_800427E0(int);
extern void fn_801E81C0(int);
extern int fn_801E7508(const void*, const u32*);
extern void fn_801E79A0(void*, int);
extern int fn_801E79FC(void*, int);
extern int fn_800877FC(u8*);
extern int fn_800E507C(u8*);
extern int fn_801F4E94(u8*);
extern void fn_80159440(int, int);
extern int fn_800B0704(u8*, int);
extern Player* fn_8015C28C(int);
extern void fn_80046B0C(Player*);
extern void fn_8015AC3C(int);
extern int fn_8007D834(void);
extern void fn_8007D94C(void);
extern int fn_80028E0C(u8*);
extern int fn_80071324(u8*);
extern int fn_8016B21C(u8*);
extern void fn_8015AC94(int, int);
extern int fn_801FAD4C(u8*);
extern int fn_801F6794(u8*);
extern int fn_801E9068(u8*);
extern int fn_801A8268(u8*);
extern int fn_8011E98C(u8*);
extern int fn_801A9A20(u8*);
extern int fn_80117AAC(u8*);
extern int fn_80111750(u8*);
extern void fn_80201B44(void);
extern void* fn_80201814(void);
extern void fn_80201F80(void*, int, int);
extern void fn_80200EAC(int, int, int, float, int);

extern GameState lbl_803003C8;
extern u32* lbl_8024E388[3];
extern void* lbl_8064C4E0;
extern int lbl_8064C578;
extern u32* lbl_8064D158;
extern int lbl_8064D184;
extern int lbl_8064D18C;
extern float lbl_8064F010;

int fn_800B0F54(u8* data)
{
    SaveHeader header;
    int offset;
    u32 i;
    Player* player;
    void* card;

    memcpy(&header, data, sizeof(SaveHeader));
    lbl_803003C8.value1914 = header.value1;
    lbl_803003C8.value1916 = header.value40;
    fn_801E8DE4(header.value8, header.valueC);
    fn_800427E0(header.value4);
    lbl_8064D18C = header.value2;
    fn_801E81C0(header.value10);
    lbl_803003C8.value191A = header.value14;
    lbl_8064C578 = header.value15;
    offset = fn_801E7508(data + sizeof(SaveHeader), lbl_8064C4E0) + sizeof(SaveHeader);
    fn_801E79A0(lbl_8064C4E0, 0x29B);
    fn_801E79A0(lbl_8064C4E0, 0x29A);
    fn_801E79A0(lbl_8064C4E0, 0x48);
    fn_801E79A0(lbl_8064C4E0, 0x467);
    fn_801E79A0(lbl_8064C4E0, 0x22B);
    for (i = 0; i < 3; i++) {
        offset += fn_801E7508(data + (u16)offset, lbl_8024E388[i]);
    }
    offset += fn_801E7508(data + (u16)offset, lbl_8064D158);
    offset += fn_800877FC(data + (u16)offset);
    offset += fn_800E507C(data + (u16)offset);
    offset += fn_801F4E94(data + (u16)offset);
    lbl_8064D18C = header.value2 + 1;
    fn_80159440(header.value2, 0x5C);
    lbl_8064D184 = header.value16;
    offset += fn_800B0704(data + (u16)offset, 0);
    player = fn_8015C28C(2);
    if (player->value8143 != 0 && player->value8142 != 0) {
        fn_80046B0C(player);
    }
    fn_8015AC3C(1);
    if (fn_8007D834() != -1) {
        fn_8007D94C();
    }
    offset += fn_80028E0C(data + (u16)offset);
    offset += fn_80071324(data + (u16)offset);
    offset += fn_8016B21C(data + (u16)offset);
    fn_8015AC94(2, 1);
    offset += fn_801FAD4C(data + (u16)offset);
    offset += fn_801F6794(data + (u16)offset);
    offset += fn_801E9068(data + (u16)offset);
    offset += fn_801A8268(data + (u16)offset);
    offset += fn_8011E98C(data + (u16)offset);
    offset += fn_801A9A20(data + (u16)offset);
    offset += fn_80117AAC(data + (u16)offset);
    offset += fn_80111750(data + (u16)offset);
    memcpy(lbl_803003C8.data, data + (u16)offset, lbl_803003C8.value1916);
    offset += lbl_803003C8.value1916;
    if (fn_801E79FC(lbl_8064C4E0, 0xD) != 0) {
        fn_80201B44();
        card = fn_80201814();
        if (card != 0) {
            fn_80201F80(card, 1, 0x33800);
        }
    }
    fn_80200EAC(0x3E, 0, 0, lbl_8064F010, header.value2);
    return offset;
}
