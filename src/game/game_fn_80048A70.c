typedef unsigned int u32;

typedef void (*Callback)(void);

typedef struct CallbackDescriptor {
    u32 type;
    u32 flags;
    Callback callback;
    u32 value;
    u32 parameter;
    u32 reserved[3];
} CallbackDescriptor;

extern void* lbl_8064C824;
extern void* lbl_8064C828;
extern void* lbl_8064C830;
extern CallbackDescriptor lbl_8023EE40[];

extern void* fn_801A6D10(void);
extern void* fn_801A717C(void);
extern u32 fn_801A743C(void*, int);
extern void fn_801A59CC(void*);
extern void fn_801A5AA0(void*, void*);
extern void* fn_80144628(int, CallbackDescriptor*, int);
extern void fn_801446DC(void*, Callback);
extern void fn_80048B68(void);

void fn_80048A70(void)
{
    lbl_8064C824 = fn_801A6D10();
    fn_801A743C(lbl_8064C828 = fn_801A717C(), 1);
    fn_801A59CC(lbl_8064C824);
    fn_801A5AA0(lbl_8064C824, lbl_8064C828);
    fn_801446DC(lbl_8064C830 = fn_80144628(2, lbl_8023EE40, 0),
                fn_80048B68);
}
