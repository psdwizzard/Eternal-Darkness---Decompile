typedef unsigned char u8;
typedef unsigned long u32;

typedef struct DrawCommand {
    u32 color;
} DrawCommand;

extern u32 lbl_8064F908;
extern const float lbl_8064F90C;
extern void fn_801F3960(DrawCommand* command);

void fn_800ED98C(float alpha)
{
    u32 color;
    DrawCommand command;

    alpha = lbl_8064F90C * alpha;
    color = lbl_8064F908;
    ((u8*)&color)[3] = (u8)alpha;
    command.color = color;
    fn_801F3960(&command);
}
