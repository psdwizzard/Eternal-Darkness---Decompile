typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;

extern int fn_80201B44(void);
extern void *fn_80201814(int);
extern void *fn_80201C2C(void *);
extern int fn_80201948(int, void *);
extern void *fn_80201BC8(void *);
extern int fn_801261F4(void *);
extern void fn_80201E78(void *, void *);
extern void fn_8011F0E8(void *, Vec3 *);
extern void fn_8011FB54(void *, int);
extern void *fn_80204A8C(void);
extern int fn_80204E0C(void *, void *);
extern void *fn_80155DB4(u32);
extern void fn_801568E4(void *);
extern void fn_801568D8(void *);
extern void fn_801568F0(void *);
extern void *fn_8012C62C(void *, int, void *, signed char *, void *, int);
extern void fn_80201D34(void *, int);
extern void *fn_80201C24(void *);
/* Both accessors return a zero-extended byte in the integer return register. */
extern int fn_80157BC4(void *);
extern int fn_80157BF4(void *);
extern void *fn_801E6CA0(void *, int, int, int, int);
extern void fn_80027948(void *, int, void *, void *, int, int, int);
extern void *lbl_8064C504;
extern int lbl_8064D18C;
extern const u32 lbl_8064F1E0;
extern const u32 lbl_80651A5C;
extern const u32 lbl_80651A60;

void fn_800C510C(void)
{
    Vec3 position;
    u32 start;
    u32 end;
    u32 color;
    int current_id;
    void *current;
    void *target;
    void *runtime;
    int target_id;
    void *action;
    void *data;
    int bank;
    int entry;
    void *event;
    void *node;

    current_id = fn_80201B44();
    current = fn_80201814(current_id);
    node = fn_80201C2C(current);
    target_id = fn_80201948(0x358, node);
    target = fn_80201814(target_id);
    runtime = fn_80201BC8(target);
    fn_801261F4(runtime);
    fn_80201E78(&position, current);
    fn_8011F0E8(runtime, &position);
    fn_8011FB54(runtime, lbl_8064D18C);
    fn_80204E0C(target, fn_80204A8C());
    action = fn_80155DB4((u32)target);
    fn_801568E4(action);
    fn_801568D8(action);
    fn_801568F0(action);
    color = lbl_80651A60;
    end = lbl_80651A5C;
    start = lbl_8064F1E0;
    fn_8012C62C(runtime, 0xF, &start, (signed char *)&end, &color, 0);
    fn_80201D34(target, 0x1E);
    data = fn_80201C24(target);
    bank = fn_80157BC4(data);
    entry = fn_80157BF4(data);
    event = fn_801E6CA0(lbl_8064C504, entry, bank, 0, 1);
    fn_80027948(event, 0, (void *)current_id, (void *)target_id, 0, 0, 0);
}
