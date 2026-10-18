typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct StateOwner {
    u8 pad00[0x20];
    u32 flags;
} StateOwner;

typedef struct Animation Animation;

typedef struct PlayerState {
    u8 pad00[0x12];
    u16 animation_count;
    Animation *animations;
    u8 pad18[0x74];
    u16 minimum_delay;
    u16 maximum_delay;
    u8 pad90[2];
    u8 sound_variant;
} PlayerState;

extern void *fn_8015C348(int);
extern void *fn_8015C28C(int);
/* This call site also passes the player state through the old-style interface. */
extern void fn_800E4AC4();
extern u32 fn_800E5044(void);
extern u32 fn_800E4834(void);
extern u32 fn_800E4750(void);
extern u16 fn_800E4954(void);
extern u16 fn_800E4918(void);
extern u16 fn_800E5000(void);
extern u16 fn_800E4A50(void);
extern void fn_800E4AB8(void);
extern void fn_800E4980(void);
extern u32 rand(void);
extern int fn_801AAE68(u16, u8, u8, float, Vec3 *, s8, u8, u8, u16, u32);
extern void fn_801F74C8(int, int, int);
extern void fn_801441C0(int, int, int);
extern int fn_801F5F98(u32, u32, u16, u16, Animation *);
extern int fn_800DE354(void);
extern u64 fn_8020123C(int, int, int, int);

extern u16 lbl_80325C40[5][16];
extern Vec3 lbl_80325CE0;
extern int lbl_8064CAD8;
extern u8 lbl_8064CADC;
extern u8 lbl_8064CADD;
extern int lbl_8064CAE0;
extern u16 lbl_8064CAE8;
extern u16 lbl_8064CAEA;
extern u16 lbl_8064CAEC;
extern u16 lbl_8064CAEE;
extern u16 lbl_8064CAF0;
extern u16 lbl_8064CAF2;
extern u16 lbl_8064CAF4;
extern int lbl_8064D18C;
extern u8 lbl_8064D5F8;
extern const float lbl_8064F6C0;

void fn_800E4B1C(void)
{
    StateOwner *owner;
    PlayerState *player;
    u16 minimum_delay;
    u16 maximum_delay;
    u8 sound_variant;
    int enabled;

    owner = fn_8015C348(2);
    player = fn_8015C28C(2);
    if (player != 0 && owner != 0) {
        fn_800E4AC4(owner, player);
        if ((int)fn_800E5044() != 0) {
            maximum_delay = player->maximum_delay;
            minimum_delay = player->minimum_delay;
            sound_variant = player->sound_variant;
            if (maximum_delay == 0) {
                lbl_8064D5F8 = 0;
                lbl_8064CADD = 0;
                return;
            }

            if (lbl_8064CAEA == 0 && (int)fn_800E4834() != 0) {
                fn_801AAE68(fn_800E4954(), sound_variant, 0,
                            lbl_8064F6C0, &lbl_80325CE0, 2, 1, 0,
                            (u16)lbl_8064D18C, 0);
            }

            if (lbl_8064CAF0 >= lbl_80325C40[lbl_8064CAF4][lbl_8064CAF2]) {
                lbl_8064CAF0 = 0;
                lbl_8064CAF2++;
                lbl_8064CADC ^= 1;
                if (lbl_8064CAF2 >= lbl_8064CAE8 ||
                    lbl_80325C40[lbl_8064CAF4][lbl_8064CAF2] == 0) {
                    lbl_8064CAF2 = 0;
                    lbl_8064CAF4 = fn_800E5000();
                    lbl_8064CAE8 = fn_800E4A50();
                    fn_800E4AB8();
                    lbl_8064CADC = 0;
                }
                if (lbl_8064CAF2 == 0) {
                    int random = (int)rand();
                    int range = maximum_delay - minimum_delay;
                    lbl_80325C40[lbl_8064CAF4][0] = minimum_delay + random % range;
                    lbl_8064CAEA = lbl_80325C40[lbl_8064CAF4][0] - 170;
                    fn_800E4980();
                }
                if ((int)fn_800E4834() != 0) {
                    if ((s8)lbl_8064CADC != 0) {
                        fn_801F74C8(15, 1, 5);
                        fn_801441C0(2, 1, 30);
                        lbl_8064CAEE = 0;
                        lbl_8064CAE0 = 1;
                    }
                } else if (lbl_8064CAF2 == 1 || lbl_8064CAF2 == 13) {
                    lbl_8064CAEE = 0;
                    lbl_8064CAE0 = 1;
                }
            }

            if (lbl_8064CAE0 != 0 && lbl_8064CAEE == lbl_8064CAEC) {
                fn_801AAE68(fn_800E4918(), sound_variant, 0,
                            lbl_8064F6C0, &lbl_80325CE0, 2, 1, 0,
                            (u16)lbl_8064D18C, 0);
                lbl_8064CAE0 = 0;
            }

            if (owner->flags & 0x40) {
                if ((s8)lbl_8064CADC != 0) {
                    lbl_8064D5F8 = 1;
                    fn_801F5F98(0x3C5E3A12, 0, 8, 
                                player->animation_count, player->animations);
                    fn_801F5F98(0x1CF45AB8, 0, 8, 
                                player->animation_count, player->animations);
                    fn_801F5F98(0x036DE521, 0, 8, 
                                player->animation_count, player->animations);
                    fn_801F5F98(0x5DA09BEC, 0, 8, 
                                player->animation_count, player->animations);
                    fn_801F5F98(0x42392475, 0, 8, 
                                player->animation_count, player->animations);
                    fn_801F5F98(0x629344DF, 0, 8, 
                                player->animation_count, player->animations);
                    fn_8020123C(123, 0, fn_800DE354(), 1);
                    lbl_8064CAD8 = 1;
                } else {
                    if (lbl_8064CAD8 != 0) {
                        fn_801F5F98(0x3C5E3A12, 0, 1, 
                                    player->animation_count, player->animations);
                        fn_801F5F98(0x1CF45AB8, 0, 1, 
                                    player->animation_count, player->animations);
                        fn_801F5F98(0x036DE521, 0, 1, 
                                    player->animation_count, player->animations);
                        fn_801F5F98(0x5DA09BEC, 0, 1, 
                                    player->animation_count, player->animations);
                        fn_801F5F98(0x42392475, 0, 1, 
                                    player->animation_count, player->animations);
                        fn_801F5F98(0x629344DF, 0, 1, 
                                    player->animation_count, player->animations);
                        fn_8020123C(123, 0, fn_800DE354(), 0);
                        lbl_8064CAD8 = 0;
                    }
                    lbl_8064D5F8 = 0;
                }
            } else {
                enabled = 0;
                if ((int)fn_800E4750() != 0 && (owner->flags & 0x100)) {
                    enabled = 1;
                }
                lbl_8064D5F8 = enabled ? 2 : 0;
            }
            lbl_8064CAF0++;
            lbl_8064CAEE++;
            lbl_8064CAEA--;
        } else {
            enabled = 0;
            if ((int)fn_800E4750() != 0 && (owner->flags & 0x100)) {
                enabled = 1;
            }
            lbl_8064D5F8 = enabled ? 2 : 0;
        }
    }
    lbl_8064CADD = lbl_8064D5F8;
}
