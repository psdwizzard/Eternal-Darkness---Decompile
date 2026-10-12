typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Particle {
    u8 pad00;
    u8 unk01;
    u8 pad02;
    s8 unk03;
    u16 pad04;
    u16 unk06;
    u16 unk08;
    u8 pad0A[0x14 - 0x0A];
    s8 unk14;
    u8 pad15[0x18 - 0x15];
    u8 unk18;
    u8 unk19;
    u8 pad1A[0x1C - 0x1A];
    u16 unk1C;
    u8 pad1E[0x78 - 0x1E];
    u8 unk78[0x90 - 0x78];
    void *callback;
    u32 unk94;
    Vec3 position;
    u8 config[6];
    u8 flags;
} Particle;

typedef struct State800EA548 {
    int id;
    Vec3 position;
    void *objects[3];
    int resolved[3];
    u8 pad28[0x50 - 0x28];
    Particle particle;
    u8 padFC[0x100 - 0xFC];
    u8 text[0x178 - 0x100];
    int unk178;
    u8 pad17C[0x180 - 0x17C];
    int targetId;
    int unk184;
    int area;
    int active;
} State800EA548;

typedef struct Config {
    u32 word;
    u16 half;
} Config;

extern int fn_80036D5C(void *object);
extern void fn_80036DA4(void *object, int flags);
extern int fn_800460EC(void);
extern void fn_800EAC84(void *object, int value);
extern void fn_800EAD50(void *object);
extern int fn_800EB068(void *object, void *self, State800EA548 *state);
extern int fn_800EB328(State800EA548 *state, int index);
extern void fn_800EB3A4(State800EA548 *state);
extern void fn_8012B344(void *object);
extern void fn_8014CBC0(void *text);
extern unsigned int fn_8015C910(void);
extern void fn_8017FD6C(void *object);
extern int fn_8017FDDC(void *object);
extern void fn_8017FF1C(void *object, u8 flags);
extern void fn_801858E0(void *particle);
extern void fn_80185AE8(void);
extern void *fn_801A717C(void);
extern void fn_801A7228(void *object);
extern void fn_801A7470(void *object, int value);
extern void fn_801A74A0(void *object, int value);
extern void fn_801A74A8(void *object, void *value);
extern void fn_801A74C8(void *object, int value);
extern void fn_801D38BC(int id, void *a, void *b);
extern int fn_801D39E0(int id);
extern void fn_801E2B28(void *text, void *position, int *value, int a, int b);
extern int fn_801E8328();
extern void fn_802006D4(void *object, void *target, int a, int b, int c);
extern int fn_80200C10(void *);
extern int fn_80200C38(void *);
extern void fn_8020104C(int, void *, void *, int, float);
extern unsigned long long fn_8020123C();
extern void *fn_80201814();
extern void fn_80201B3C(void);
extern int fn_80201B54(void *object);
extern int fn_80201B5C(void *object);
extern void *fn_80201B8C(void *object);
extern void *fn_80201B9C(void);
extern void *fn_80201BC0(void *object);
extern void *fn_80201BC8(void);
extern void fn_80201D14(void *object, int value);
extern void fn_80201D2C(void *object, int value);
extern void fn_802020B4(void *object, int value);
extern void *memcpy(void *, const void *, unsigned int);

extern int lbl_8064D18C;
extern u32 lbl_8064D5A8;
extern float lbl_8064F848;
extern float lbl_8064F84C;
extern float lbl_8064F850;
extern float lbl_8064F854;
extern u32 lbl_80651B70;
extern u16 lbl_80651B74;

int fn_800EA548(void *object, int event, void *message)
{
    int type;
    State800EA548 *state;
    void *self;
    int i;

    type = fn_80200C10(message);
    state = *(State800EA548 **)((u8 *)fn_80201B8C(object) + 0x60);
    self = (void *)fn_80201B54(object);

    if (event == 0) {
        if (type == 1) {
            fn_8020104C(0x84, self, self, 0, lbl_8064F848);
            fn_8020104C(0x84, self, self, 1, lbl_8064F84C);
            fn_8020104C(0x84, self, self, 2, lbl_8064F850);
            fn_8020104C(0x39, self, self, 0, lbl_8064F854);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (type == 0x39) {
            fn_802006D4(self, self, -1, -1, 0);
            for (i = 0; i < 3; i++) {
                if (fn_800EB328(state, i)) {
                    fn_8017FD6C(state->objects[i]);
                    state->objects[i] = 0;
                    state->resolved[i] = 0;
                }
            }
            fn_801E8328(2, object);
            return 1;
        } else if (type == 0x3D) {
            fn_8020123C(0x39, self, self, 0);
            return 1;
        } else if (type == 0x59) {
            fn_8020123C(0x39, self, self, 0);
            return 1;
        }
    } else if (event == 1) {
        if (type == 0x84) {
            if (lbl_8064D18C == state->area) {
                Config config;
                int value;
                Particle *particle;
                Vec3 position;

                config.word = lbl_80651B70;
                config.half = lbl_80651B74;
                fn_8014CBC0(state->text);
                value = fn_801D39E0(state->unk184);
                fn_801E2B28(state->text, &state->position, &value, 0x20, 0x1E);
                state->unk178 = fn_80200C38(message);
                particle = &state->particle;
                fn_801858E0(particle);
                particle->unk01 = 100;
                particle->unk03 = -10;
                particle->unk18 |= 2;
                particle->unk19 = 8;
                particle->unk1C = 100;
                fn_801D38BC(state->unk184, particle->unk78, &particle->pad04);
                particle->unk14 = 10;
                particle->unk08 = (600 - particle->unk01) / particle->unk14;
                particle->unk06 = particle->unk08 + 25;
                particle->callback = fn_80185AE8;
                position = state->position;
                position.z += 100.0f;
                particle->position = position;
                memcpy(particle->config, &config, 6);
                particle->unk94 = 0;
                particle->flags = 4;
                if (state->active != 0) {
                    particle->flags |= 8;
                }
                fn_801E8328(0x10, particle);
            }
            return 1;
        } else if (type == 3) {
            fn_800EB3A4(state);
            if (!(lbl_8064D5A8 & 7) && fn_8015C910() == 0 && fn_800460EC() == 0 &&
                fn_800EB068(object, self, state) != 0) {
                if ((u32)(fn_8020123C(0x85, self, state->targetId, 0) & 0xFFFFFFFF) == 1) {
                    void *player;
                    void *effect;
                    int j;
                    void *iter;

                    fn_80201B3C();
                    player = fn_80201BC8();
                    effect = fn_801A717C();
                    for (iter = fn_80201B9C(); iter != 0; iter = fn_80201BC0(iter)) {
                        if (fn_80201B5C(iter) == 0x27) {
                            State800EA548 *other = *(State800EA548 **)((u8 *)fn_80201B8C(iter) + 0x60);
                            for (j = 0; j < 3; j++) {
                                void *obj = other->objects[j];
                                if (obj != 0) {
                                    fn_8017FF1C(obj, fn_8017FDDC(obj) & ~8);
                                }
                            }
                            fn_802020B4(iter, 0);
                            other->active = 0;
                        }
                    }
                    fn_801A74C8(effect, 0x100);
                    fn_801A7470(effect, 0xB);
                    fn_801A74A0(effect, 0);
                    fn_801A74A8(effect, self);
                    fn_8012B344(player);
                    fn_8020123C(0x35, self, state->targetId, effect);
                    fn_801A7228(effect);
                    fn_800EAD50(object);
                } else if (state->targetId != state->id) {
                    void *target = fn_80201814();
                    int targetType = fn_80201B5C(target);
                    u8 *data = fn_80201B8C(target);
                    int kind;
                    int flags;

                    if (data != 0) {
                        kind = data[0x9F];
                    } else {
                        kind = 0;
                    }
                    if (kind != 0xD && targetType != 2 && targetType != 0x13 &&
                        targetType != 0x52 && targetType != 0x56) {
                        if (target != 0) {
                            flags = fn_80036D5C(object);
                        } else {
                            flags = 0;
                        }
                        fn_80036DA4(target, flags & 0xFFFF7F7F);
                        fn_8020123C(8, self, state->targetId, 0);
                        fn_800EAC84(target, state->unk184);
                    }
                }
            }
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
