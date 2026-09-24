#ifndef GAME_TARGETING_TYPES_H
#define GAME_TARGETING_TYPES_H

#include "src/game/types.h"

typedef struct TargetVec3s {
    s16 x, y, z;
} TargetVec3s;

typedef struct TargetVec3f {
    float x, y, z;
} TargetVec3f;

extern s32 lbl_8064D18C;
extern const u32 lbl_8023A760[3];
extern const u32 lbl_8023A76C[3];
extern const u32 lbl_8023A778[4];

extern TargetVec3s* fn_8017FDA8(void*, s32);
extern int fn_801AC9F4(s32, s32, TargetVec3f*, s32);
extern void fn_8017D700(TargetVec3s*, TargetVec3s*, s16, TargetVec3s*, s16, s16, s16, s16);
extern void fn_8017D908(TargetVec3s*, TargetVec3s*, TargetVec3s*, s16, s16, s16);
extern u32 fn_8019BBB4(void*);
extern void* fn_8019BB9C(void*);
extern void fn_8019BBCC(void*, s32, s32);
extern void* fn_801809A0(void*);
extern void *fn_80201814();
extern void *fn_80201890(s32);
extern void *fn_80201B9C();
extern void *fn_80201BC8();
extern void* fn_80201BC0(void*);
extern void *fn_80201B8C();
extern s32 fn_80201B4C(void*);
extern int fn_80201B54();
extern int fn_80201EB8();
extern void fn_8011F114();
extern s32 fn_8011EB1C(void*);
extern u32 fn_80179004(TargetVec3f*, TargetVec3f*);
extern float fn_8011F6F8(void);
extern unsigned long long fn_8020123C();
extern void* fn_801A717C(void);
extern void fn_801A74A0(void*, s32);
extern void fn_801A74A8(void*, u32);
extern void fn_801A7538(void*, s32);
extern void fn_801A7518(void*, s32);
extern void fn_801A7588(void*, s32);
extern void fn_801A764C(void*, TargetVec3f*);
extern void fn_801A74D8(void*, s32);
extern void fn_801A7668(void*, u32);
extern void fn_801A7670(void*, s32);
extern void fn_801A7228(void*);
extern void fn_801D38BC(s32, u32*, s16*);
extern void fn_80152404(TargetVec3f*, s16, u16, u8, u32*);
extern void fn_80149E28(void*);


#endif
