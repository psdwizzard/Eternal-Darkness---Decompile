typedef unsigned int u32;
typedef unsigned short u16;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;

typedef struct CodecSlot {
    int unk0;
    int unk4;
    int unk8;
    void *model;
    char pad10[0x28 - 0x10];
    void *parent;
} CodecSlot;

typedef struct ButtonIds {
    int ids[9];
} ButtonIds;

typedef struct CodecLayout {
    u32 coords[21];
    u32 buttonMasks[12];
    u32 pad84[12];
    u32 spriteIds[12];
    u32 padE4[90];
    ButtonIds buttons;
} CodecLayout;

extern const CodecLayout lbl_8023A3C0;
extern u32 lbl_80331748[];
extern CodecSlot lbl_803317F8[];
extern u32 lbl_8064CD4C;
extern int lbl_8064D18C;
extern const float lbl_8064FF58;

extern int fn_80112230(int);
extern int fn_80112258(int);
extern void fn_80117EF0(void);
extern void fn_80117F30(void);
extern void fn_80117FA0(void);
extern void fn_80117FDC(void);
extern void *fn_800070E4(int, unsigned char, float, float, float, int, u16);
extern void fn_8011F7E0(void *, int);
extern void fn_8011FB54(void *, int);
extern void fn_801261F4(void *);
extern void fn_8012C478(void *, int, int);
extern void fn_8012CDF0(void *, int, Vec4, int);
extern void fn_801568B8(void *, void (*)(void));
extern void fn_801568C0(void *, void (*)(void));
extern void fn_801568FC(void *, int);
extern void fn_80156904(void *, int);
extern void fn_8015690C(void *, void (*)(void));
extern void fn_80156918(void *, void *);
extern void *fn_80156DA0();
extern void *fn_80157760(int, int);
extern void fn_801577E0(void *);
extern void fn_80157824(Vec4 *, void *);
extern int fn_8015784C(void *);
extern int fn_80157858(void *);
extern void fn_801F69F0(int *, Vec3 *, int);
extern int fn_80201B44(void);
extern void *fn_80201814(int);
extern unsigned int fn_8020216C(void *);

void fn_80112278(int first)
{
    int slot;
    int sprite;
    const CodecLayout *const layout = &lbl_8023A3C0;
    ButtonIds buttons;
    Vec4 color;
    Vec3 world;
    int pos[3];

    const u32 *spriteIds;
    const u32 *masks;

    /* These scopes preserve the retail register lifetimes. */
    {
        int i;
        {
            void *parent;
            parent = fn_80157760(6, 0x47);
            fn_80117EF0();
            spriteIds = layout->spriteIds;
            masks = layout->buttonMasks;
            for (i = 0; i < 12; i++, spriteIds++, masks++) {
                slot = i - first;
                if (!((lbl_80331748[i + 2] & 0x0C000000) || (fn_8020216C(fn_80201814(fn_80201B44())) & 0x4000))) {
                    continue;
                }
                if (i < first || slot >= 9) {
                    continue;
                }
                {
                    CodecSlot *entry = &lbl_803317F8[slot];
                    if ((lbl_80331748[i + 2] & 0x08000000) || (fn_8020216C(fn_80201814(fn_80201B44())) & 0x4000)) {
                        sprite = *spriteIds;
                    } else {
                        sprite = 0xDF;
                    }
                    entry->parent = parent;
                    pos[0] = fn_80112230(slot);
                    pos[1] = fn_80112258(slot);
                    entry->unk4 = pos[2] = fn_8015784C(parent);
                    entry->unk0 = pos[2];
                    entry->unk8 = fn_80157858(parent);
                    fn_801F69F0(pos, &world, 0);
                    entry->model = fn_800070E4(sprite, 4, world.x, world.y, world.z, lbl_8064D18C, 0);
                    fn_8011FB54(entry->model, lbl_8064D18C);
                    fn_801261F4(entry->model);
                    fn_8011F7E0(entry->model, 1);
                    fn_80157824(&color, parent);
                    if (color.x != lbl_8064FF58 || color.y != lbl_8064FF58 || color.z != lbl_8064FF58 ||
                        color.w != lbl_8064FF58) {
                        fn_8012CDF0(entry->model, 0xF, color, 1);
                    }
                    {
                        void *handle = fn_80156DA0(3, 0);
                        if ((lbl_80331748[i + 2] & 0x08000000) || (fn_8020216C(fn_80201814(fn_80201B44())) & 0x4000)) {
                            if (lbl_8064CD4C & ((*masks << 16) & 0x01F00000)) {
                                fn_8012C478(entry->model, 9, 1);
                            } else {
                                fn_8012C478(entry->model, 9, 0);
                            }
                            if (lbl_8064CD4C & ((*masks << 16) & 0x1E000000)) {
                                fn_8012C478(entry->model, 8, 1);
                            } else {
                                fn_8012C478(entry->model, 8, 0);
                            }
                        } else {
                            int j;
                            buttons = layout->buttons;
                            for (j = 0; j < 9; j++) {
                                if (((0x10 << j) & (*masks & 0x1FF0)) && (lbl_8064CD4C & (0x100000 << j))) {
                                    fn_8012C478(entry->model, buttons.ids[j], 1);
                                } else {
                                    fn_8012C478(entry->model, buttons.ids[j], 0);
                                }
                            }
                        }
                        fn_80156904(handle, 0);
                        fn_801568FC(handle, 0);
                        fn_801568C0(handle, fn_80117FDC);
                        fn_801568B8(handle, fn_80117F30);
                        fn_8015690C(handle, fn_80117FA0);
                        fn_80156918(handle, entry->model);
                    }
                }
            }
            fn_80157858(parent);
            fn_801577E0(parent);
        }
    }
}
