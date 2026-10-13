#include "src/game/types.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef float f32;

typedef struct CamEntry {
    u32 id;
    u32 anim;
    u8 pad08[0x5];
    u8 flags0D;
} CamEntry;

typedef struct CamState {
    u8 pad000[0xB0];
    void *unkB0;
    s32 unkB4;
    CamEntry *entry;
    u8 padBC[0xC8 - 0xBC];
    s32 unkC8;
    u8 padCC[0xF0 - 0xCC];
    u32 entryId;
    u32 flagsF4;
    u16 unkF8;
    u16 unkFA;
    u16 unkFC;
    u16 timer;
    u8 pad100[2];
    u8 bits[14];
} CamState;

typedef struct CamOwner {
    u8 pad000[0x40];
    CamState *states;
    u8 pad044[0x178 - 0x44];
    s32 (*callback)(struct CamOwner *, s32);
    u8 pad17C[0x254 - 0x17C];
    u32 flags254;
    u8 pad258[0x2CE - 0x258];
    s16 delay;
} CamOwner;

extern u32 fn_8011FAEC(void *);
extern void fn_8011FB44(void *, u32);
extern void fn_80124750(void *, s32, s32, s32, s32, f32, f32, f32, f32);
extern void fn_80124DBC(void *);
extern s32 fn_80126050(void);
extern s32 fn_80126B3C(void *, s32);
extern void fn_801285F8(s32);
extern void fn_80128610(void);
extern void fn_80128754(void *, s32);
extern CamState *fn_80128E30(void *);
extern s32 fn_80128EAC(void *);
extern void fn_80129DE0(void *, void *, s32, s32);
extern CamEntry *fn_8012A13C(void *, u32);
extern s32 fn_8012A7C8(void *, CamState *);
extern void fn_8012ABEC(void *, void *);
extern void fn_8012AE78(void *);
extern s32 fn_8012AFE8(CamState *);
extern s32 fn_8012B018(void *, s32);
extern void fn_8012B070(void *);
extern void fn_8012B290(void *, CamState *);
extern void fn_8012D0D0(void *);
extern void fn_80134FF8(void *, u32);
extern void fn_801E82B4(void *, s32, void *, s32);

extern f32 lbl_806501A8;
extern f32 lbl_806501B0;
extern f32 lbl_806501B4;

void fn_8012A254(CamOwner *owner) {
    u8 buf[0x18];
    CamState *st;
    CamEntry *entry;
    u32 inFlags;
    s32 active;
    s32 done;
    s32 moved;
    s32 ok;
    s32 i;
    u32 stFlags;
    s32 notHandled;
    CamState *other;
    s16 delay;

    active = 0;
    done = 0;
    moved = 0;
    if (fn_80126050() == 0) {
        return;
    }
    st = fn_80128E30(owner);
    if (st->entry != NULL) {
        inFlags = fn_8011FAEC(owner);
        if (!(inFlags & 0x400)) {
            if (owner->flags254 & 0x1000) {
                st->entry = fn_8012A13C(owner, st->entryId);
            }
            fn_80129DE0(owner, st, 0, 0);
        }
        fn_80134FF8(owner, st->entry->anim);
        if (st->unkFA < 4 && fn_8012B018(owner, 0) != 0) {
            done = 1;
            st->unkFC = 8;
        } else {
            if (!(owner->flags254 & 4)) {
                active = fn_80126B3C(owner, st->unkC8);
                if (st->unkF8 & 3) {
                    done = fn_8012A7C8(owner, st);
                    moved = fn_8012AFE8(st);
                } else if (!(st->flagsF4 & 4)) {
                    fn_8012ABEC(owner, buf);
                }
            }
            fn_8012AE78(owner);
            if ((moved != 0 && done != 0) || (moved == 0 && active != 0)) {
                if (st->unkB0 != NULL) {
                    fn_801E82B4(owner, st->unkB4, st->unkB0, 0);
                }
            }
            if (st->flagsF4 & 8) {
                st->timer--;
                if (st->timer == 0) {
                    st->flagsF4 = st->flagsF4 & ~8;
                    owner->flags254 = owner->flags254 & ~4;
                    if (st->flagsF4 & 0x200) {
                        fn_8012B290(owner, st);
                        done = 1;
                    }
                }
            } else if (st->flagsF4 & 0x400) {
                st->timer--;
                if (st->timer == 0) {
                    st->flagsF4 = st->flagsF4 & ~0x400;
                    st->unkC8 = 0x10000;
                }
            }
            if (active != 0 && done == 0) {
                stFlags = st->flagsF4;
                notHandled = 1;
                if (inFlags & 0x1000) {
                    for (i = 0; i < 8; i++) {
                        other = &owner->states[i];
                        if ((other->unkFC & 2) && other != st) {
                            other->entry = fn_8012A13C(owner, other->entryId);
                        }
                    }
                    if (stFlags & 1) {
                        entry = fn_8012A13C(owner, st->entryId);
                        if ((st->unkF8 & 3) || (entry->flags0D & 0x20)) {
                            st->entry = entry;
                            st->entryId = entry->id;
                            fn_80129DE0(owner, st, 0, 0);
                            notHandled = 0;
                        }
                    }
                    if (notHandled) {
                        if (fn_80128EAC(owner) == 1 || fn_80128EAC(owner) == 2 ||
                            fn_80128EAC(owner) == 3) {
                            fn_80128EAC(owner);
                            fn_80128610();
                            fn_801285F8(1);
                        }
                        done = 1;
                        st->unkFC = 8;
                    }
                    fn_8011FB44(owner, 0x10000);
                } else if (stFlags & 1) {
                    ok = 1;
                    if (st->entry->flags0D == 0x10 && owner->callback != NULL) {
                        ok = owner->callback(owner, 1);
                    }
                    if (ok) {
                        fn_80129DE0(owner, st, 0, 0);
                        for (i = 0; i < 14; i++) {
                            st->bits[i] &= ~1;
                        }
                    }
                } else {
                    done = 1;
                    st->unkFC = 8;
                }
            }
        }
        if (done) {
            fn_8012B070(owner);
        }
        delay = owner->delay;
        if (delay > 0) {
            owner->delay = delay - 1;
        } else if (delay != -1) {
            fn_80124750(owner, 0x10, 4, 1, 2, lbl_806501A8, lbl_806501B0, lbl_806501B4, lbl_806501B4);
            fn_80124750(owner, 0xF, 4, 1, 2, lbl_806501A8, lbl_806501B0, lbl_806501B4, lbl_806501B4);
            fn_80128754(owner, -2);
        }
    }
    fn_8012D0D0(owner);
    fn_80124DBC(owner);
}
