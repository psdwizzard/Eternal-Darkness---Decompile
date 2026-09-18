typedef struct Vec3i {
    int x, y, z;
} Vec3i;

typedef struct Effect {
    int state;
    int handle;
    int field8;
    int duration;
    int limit;
    unsigned char pad14[8];
    Vec3i position;
    int value;
    unsigned short kind;
    unsigned char pad2E[6];
    unsigned short owner;
    unsigned char pad36;
    unsigned char flag;
    unsigned char mode;
    unsigned char pad39[0xF];
    void *callback;
    unsigned char pad4C[0x30];
} Effect;

extern int lbl_8064D18C;
extern float lbl_8064F6C8;
extern float lbl_8064F6CC;
extern void fn_801FD8F0(void);
extern void fn_8014CBC0(Effect *);
extern void fn_801FE8DC(int *, void *, float, float, float);
extern void fn_8014C988(Effect *, int);
extern void fn_8014C37C(int, Effect *);

/* NonMatching: behavior-complete, size-exact reconstruction. Explicit source
 * temporaries recover the retail load-before-store shape; register allocation
 * and scheduling within the stack Effect initializer still differ. */
void fn_800E50AC(Vec3i *position, int *value)
{
    volatile Effect effect;
    float first;
    float second;
    float third;
    int position_x;
    int position_y;
    int position_z;
    int effect_value;
    int owner;
    void *callback;

    fn_8014CBC0((Effect *)&effect);
    first = lbl_8064F6C8;
    owner = lbl_8064D18C;
    callback = fn_801FD8F0;
    effect_value = *value;
    position_x = position->x;
    position_y = position->y;
    position_z = position->z;
    second = first;
    third = lbl_8064F6CC;
    effect.value = effect_value;
    effect.kind = 750;
    effect.handle = 10000;
    effect.duration = 10000;
    effect.limit = 1000;
    effect.mode = 2;
    effect.owner = owner;
    effect.position.x = position_x;
    effect.position.y = position_y;
    effect.position.z = position_z;
    effect.callback = callback;
    effect.flag = 0;
    fn_801FE8DC((int *)&effect.handle, fn_801FD8F0, first, second, third);
    fn_8014C988((Effect *)&effect, 2);
    fn_8014C37C(0, (Effect *)&effect);
}
