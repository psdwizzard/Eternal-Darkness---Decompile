/* UI overlays, timed effects, and the rotating object-selection ring. */

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef f32 Mtx[3][4];
typedef struct Quad { Vec3 v[4]; } Quad;
typedef struct ScreenPoint { s16 x, y; } ScreenPoint;
typedef struct PointTable { ScreenPoint v[7]; } PointTable;
typedef struct IndexTable { s32 v[4]; } IndexTable;

typedef struct TimedEffect {
    f32 target, step, current;
    s16 period, duration, elapsed, sound;
} TimedEffect;
typedef struct IconAngles { f32 angles[2]; u8 pad[0x2C]; } IconAngles;
typedef struct IconObjects {
    f32 angles[2];
    u32 enabled[2];
    u8 pad10[0x10];
    ScreenPoint positions[2];
    u8 pad28[0x90];
} IconObjects;
typedef struct UiState {
    u8 pad0[0x1C];
    IconAngles icons[5];
    u8 pad120[8];
    TimedEffect effects[5];
    u8 pad18C[0x34];
    f32 ringAngle;
    u8 pad1C4[7];
    u8 display;
    s8 direction;
} UiState;
typedef struct UiObjects {
    u8 pad0[0xF8];
    IconObjects icons[4];
    u8 pad3D8[0x54];
    s8 selected;
    u8 pad42D[0x63];
    s8 symbols[7];
    s8 symbolCount;
    u8 pad498[0x178];
    void* selection;
    Vec3* objects[5];
    u32 mask;
    s32 shift;
} UiObjects;
typedef struct ModeState { u8 pad[8]; s32 mode; u32 padC, flags; } ModeState;
typedef struct Resource { u8 pad[0x11C]; u32 image; } Resource;
typedef struct UiConstants {
    u8 pad[0x2B8];
    Quad quad;
    PointTable points;
    IndexTable indices;
} UiConstants;
typedef struct Label { const char* name; const char* detail; } Label;
typedef union Color { u32 word; u8 rgba[4]; } Color;

extern UiState lbl_8031CBA0;
extern UiObjects lbl_8031CD84;
extern ModeState lbl_803003C8;
extern UiConstants lbl_80239208;
extern s16 lbl_80244870[];
extern Label lbl_8024DDC8[];
extern u8 lbl_802515D0[];
extern const char lbl_8064B5B0[4], lbl_8064B5B4[4], lbl_8064B5B8[4];
extern u32 lbl_8064C2A8, lbl_8064C2B0, lbl_8064C2B8;
extern u32* lbl_8064C4E0;
extern u32 lbl_8064C8E8;
extern s32 lbl_8064C908, lbl_8064D18C, lbl_8064D5A8;
extern const f32 lbl_8064EA08, lbl_8064EA14, lbl_8064EA50;
extern const volatile f32 lbl_8064EA0C;
extern u32 lbl_8064EB04, lbl_8064EB08, lbl_8064EB0C, lbl_8064EB10;
extern const f32 lbl_8064EB14, lbl_8064EB18, lbl_8064EB1C, lbl_8064EB20;
extern const f32 lbl_8064EB24, lbl_8064EB28, lbl_8064EB30;
extern const volatile f32 lbl_8064EB2C;
extern const f32 lbl_8064EB34, lbl_8064EB38;
extern u32 lbl_806519A8;

extern void fn_800861F4(void);
extern void fn_800861F8(u16);
extern void fn_80086204(u16, u16, u16);
extern u32 fn_80113B64(void);
extern void fn_8011F0E8(Vec3*, Vec3*);
extern void* fn_8011F130(void*);
extern void* fn_8012C62C(u8*, int, void*, s8*, void*, int);
extern s16 fn_80144A2C(u32, s16, s16, int);
extern void* fn_8015C2FC(int);
extern u32 fn_8015C910(void);
extern void* fn_801A717C(void);
extern void fn_801A7228(void*);
extern void fn_801A74A0(void*, u32);
extern void fn_801A74A8(void*, u32);
extern void fn_801A7518(void*, s16);
extern void fn_801A7538(void*, u16);
extern void fn_801A764C(void*, const void*);
extern void fn_801A852C(u32*, int, u16, u32);
extern void fn_801A8660(s32, s32, s32, s32, s32, const u32*);
extern void fn_801A8D38(s32);
extern void fn_801A8EDC(void*);
extern void fn_801A8F08(s32, s32, s32, s32, s32, s32, void*);
extern void fn_801AC5E4(u16, u8, u8, int, s8, int, int);
extern u32 fn_801E3A34(void*);
extern void fn_801E3AA4(int);
extern void fn_801E5430(s16, s16);
extern void fn_801E56AC(f32, const char*, ...);
extern s8 fn_801E5AD0(s8);
extern u32 fn_801E7578(u32);
extern int fn_801E75A4(u32, int);
extern int fn_801E79FC(u32*, u32);
extern int fn_801E8D34(void*);
extern int fn_801E8D3C(void*);
extern void fn_801ECF50(u32);
extern u32 fn_801ED3F4(u32);
extern void fn_801F0294(int, f32);
extern void fn_801F68B0(Vec3*);
extern void fn_801F68F8(Vec3*);
extern void fn_801FCCEC(u32*);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void* fn_80201B3C(void);
extern int fn_80201B54(int*);
extern void* fn_80201BC8(void*);
extern void PSMTXRotRad(Mtx, char, f32);
extern void PSMTXRotAxisRad(Mtx, const Vec3*, f32);
extern void PSMTXMultVec(Mtx, const Vec3*, Vec3*);
extern void PSVECAdd(const Vec3*, const Vec3*, Vec3*);
extern void PSVECScale(const Vec3*, Vec3*, f32);
extern void PSVECNormalize(const Vec3*, Vec3*);
extern void PSVECCrossProduct(const Vec3*, const Vec3*, Vec3*);
extern void GXBegin(s32, void*, s32);

static inline void drawIconVertex(const Vec3* vertex, s16 x, s16 y, s16 inset)
{
    register u16 depth;
    /* ASM: li preserves the retail all-ones depth register. A C call with
     * a constant u16 argument instead materializes the zero-extended 65535. */
    asm { li depth, -1 }
    fn_80086204(vertex->x + (f32)(s16)(x + inset), vertex->y + (f32)(s16)(y + inset), depth);
}

void fn_80084F38(void)
{
    Quad quad;
    Mtx iconRotation, ringStep, tilt, ringRotation;
    PointTable points;
    IndexTable indices;
    Vec3 camera, target, center, radial, forward, horizontal, axis, position;
    Vec3 cameraResult, targetResult;
    Color color;
    u32 borderColor, iconColor, shadowColor, faceColor;
    u32 upperPanelColor, middlePanelColor, specialPanelColor, lowerPanelColor;
    u32 legendColor, symbolColor;
    u32 startColor, colorDelta, endColor, textColor, strongTint, weakTint, defaultTint;
    volatile u32 colorCopy;
    UiState *effectCursor;
    f32 targetValue;
    f32 effectTarget;
    f32 currentValue;
    s16 symbolX;
    s16 symbolY;
    s16 legendX;
    s16 legendY;
    void *objectHandle;
    s32 objectId;
    void *soundObject;
    void *soundEntry;
    s32 panelImage;
    s32 effectIndex;
    s32 legendIndex;
    s32 symbolIndex;
    TimedEffect *effect;

    UiConstants* constants = &lbl_80239208;

    /* Advance the five timed effect envelopes. */
    if (fn_8015C910() == 0U) {
        effectCursor = &lbl_8031CBA0;
        for (effectIndex = 0; effectIndex < 5; effectIndex++) {
            targetValue = effectCursor->effects[0].target;
            currentValue = effectCursor->effects[0].current;
            if (targetValue == currentValue) {
                if (targetValue != lbl_8064EA14) {
                    effectCursor->effects[0].elapsed = (s16) (effectCursor->effects[0].elapsed + 1);
                    if ((s16) effectCursor->effects[0].elapsed >= (s16) effectCursor->effects[0].duration) {
                        effectCursor->effects[0].elapsed = 0;
                        effectCursor->effects[0].target = (f32) lbl_8064EA14;
                    }
                }
            } else if (currentValue < targetValue) {
                effectCursor->effects[0].current = (f32) (currentValue + effectCursor->effects[0].step);
                effectCursor->effects[0].current = effectCursor->effects[0].current < effectCursor->effects[0].target ?
                    effectCursor->effects[0].current : effectCursor->effects[0].target;
                effectCursor->effects[0].elapsed = 0;
            } else {
                effectCursor->effects[0].current = (f32) (currentValue - effectCursor->effects[0].step);
                effectCursor->effects[0].current = effectCursor->effects[0].current > effectCursor->effects[0].target ?
                    effectCursor->effects[0].current : effectCursor->effects[0].target;
                effectCursor->effects[0].elapsed = 0;
            }
            effectCursor = (UiState*)((u8*)effectCursor + sizeof(TimedEffect));
        }
    }
    effect = 0;
    switch (lbl_8064D18C) {
    case 0x139:
        effect = &lbl_8031CBA0.effects[0];
        break;
    case 0xE9:
        effect = &lbl_8031CBA0.effects[1];
        break;
    case 0xA8:
        effect = &lbl_8031CBA0.effects[2];
        break;
    case 0x132:
        effect = &lbl_8031CBA0.effects[3];
        break;
    case 0x134:
        effect = &lbl_8031CBA0.effects[4];
        break;
    /* Two rotating icons, with a displaced shadow behind each face. */
    case 0x59: {
        s32 iconIndex;
        s32 image;
        s16 iconX, iconY;
        if (((s32) lbl_803003C8.mode == 0) && ((s8) lbl_8031CD84.selected >= 0)) {
            for (iconIndex = 0; iconIndex < 2; iconIndex++) {
                image = ((Resource*)fn_8015C2FC(2))->image;
                quad = constants->quad;
                PSMTXRotRad(iconRotation, 'z',
                    lbl_8031CBA0.icons[lbl_8031CD84.selected].angles[iconIndex] +
                    lbl_8031CD84.icons[lbl_8031CD84.selected].angles[iconIndex]);
                PSMTXMultVec(iconRotation, &quad.v[0], &quad.v[0]);
                PSMTXMultVec(iconRotation, &quad.v[1], &quad.v[1]);
                PSMTXMultVec(iconRotation, &quad.v[2], &quad.v[2]);
                PSMTXMultVec(iconRotation, &quad.v[3], &quad.v[3]);
                iconX = lbl_8031CD84.icons[lbl_8031CD84.selected].positions[iconIndex].x;
                iconY = lbl_8031CD84.icons[lbl_8031CD84.selected].positions[iconIndex].y;
                fn_801ED3F4(image);
                fn_801A8D38(6);
                borderColor = lbl_8064C2B8;
                fn_801A8660((s16) (iconX - 4), (s16) (iconY - 4), 0x48, 0x48, -2, &borderColor);
                fn_801A8EDC(&lbl_802515D0);
                iconColor = lbl_8064C2A8;
                fn_801A852C(&iconColor, 0, iconIndex * 3, 0x80000000);
                fn_801A8F08(iconX, iconY, (s16) (iconX + 0x40), (s16) (iconY + 0x40), -1, 0, (void*)5);
                shadowColor = lbl_8064EB04;
                fn_801A852C(&shadowColor, 5, 1, 0x80000000);
                if ((u32) lbl_8031CD84.icons[lbl_8031CD84.selected].enabled[iconIndex] != 0U) {
                    fn_801ECF50(6);
                    GXBegin(0x80, (void*)5, 4);
                    drawIconVertex(&quad.v[0], iconX, iconY, 0x25);
                    fn_800861F8(0);
                    drawIconVertex(&quad.v[1], iconX, iconY, 0x25);
                    fn_800861F8(1);
                    drawIconVertex(&quad.v[2], iconX, iconY, 0x25);
                    fn_800861F8(2);
                    drawIconVertex(&quad.v[3], iconX, iconY, 0x25);
                    fn_800861F8(3);
                    fn_800861F4();
                    faceColor = lbl_8064C2A8;
                    fn_801A852C(&faceColor, 0, 2, 0x80000000);
                    fn_801ECF50(6);
                    GXBegin(0x80, (void*)5, 4);
                    drawIconVertex(&quad.v[0], iconX, iconY, 0x20);
                    fn_800861F8(0);
                    drawIconVertex(&quad.v[1], iconX, iconY, 0x20);
                    fn_800861F8(1);
                    drawIconVertex(&quad.v[2], iconX, iconY, 0x20);
                    fn_800861F8(2);
                    drawIconVertex(&quad.v[3], iconX, iconY, 0x20);
                    fn_800861F8(3);
                    fn_800861F4();
                }
            }
        }
        break;
    }
    /* Panel artwork, the symbol guide, and the selected symbols. */
    case 0x159:
    case 0x7B:
    case 0x51:
    case 0x1B:
        if (((u32) lbl_8064C8E8 != 0U) && ((s32) lbl_8031CBA0.display == 2)) {
            panelImage = ((Resource*)fn_8015C2FC(2))->image;
            points = constants->points;
            indices = constants->indices;
            fn_801ED3F4(panelImage);
            fn_801A8D38(6);
            fn_801A8EDC(&lbl_802515D0);
            upperPanelColor = lbl_8064C2A8;
            fn_801A852C(&upperPanelColor, 0, 4, 0x80000000);
            fn_801A8F08(0x1B5, 0x10C, 0x244, 0x18C, -1, 0, (void*)5);
            middlePanelColor = lbl_8064C2A8;
            fn_801A852C(&middlePanelColor, 0, 5, 0x80000000);
            fn_801A8F08(0x92, 0x47, 0x1EF, 0xE7, -1, 0, (void*)5);
            if ((fn_801E79FC(lbl_8064C4E0, 0xFA) != 0) || ((s32) lbl_8064D18C != 0x7B)) {
                if (((s32) lbl_8064D18C == 0x159) || ((s32) lbl_8064D18C == 0x1B)) {
                    specialPanelColor = lbl_8064C2A8;
                    fn_801A852C(&specialPanelColor, 0, 6, 0x80000000);
                    fn_801A8F08(0x3E, 0x100, 0x19B, 0x1A0, -1, 0, (void*)5);
                } else {
                    lowerPanelColor = lbl_8064C2A8;
                    fn_801A852C(&lowerPanelColor, 0, 5, 0x80000000);
                    fn_801A8F08(0x3E, 0x100, 0x19B, 0x1A0, -1, 0, (void*)5);
                    legendIndex = 0;
                    do {
                        legendColor = lbl_8064C2A8;
                        fn_801A852C(&legendColor, 0, indices.v[lbl_80244870[legendIndex]], 0x80000000);
                        legendX = points.v[legendIndex].x;
                        legendY = points.v[indices.v[lbl_80244870[legendIndex]]].y;
                        fn_801A8F08((s16)(legendX - 0x54), (s16)(legendY + 0xB9),
                                    (s16)(legendX - 0x34), (s16)(legendY + 0xF9),
                                    -1, 0, (void*)5);
                        legendIndex += 1;
                    } while (legendIndex < 7);
                }
            }
            symbolIndex = 0;
            while (symbolIndex < (s8) lbl_8031CD84.symbolCount) {
                symbolColor = lbl_8064C2A8;
                fn_801A852C(&symbolColor, 0, indices.v[(s8) lbl_8031CD84.symbols[symbolIndex]], 0x80000000);
                symbolX = points.v[symbolIndex].x;
                symbolY = points.v[indices.v[(s8) lbl_8031CD84.symbols[symbolIndex]]].y;
                fn_801A8F08(symbolX, symbolY, (s16) (symbolX + 0x20), (s16) (symbolY + 0x40), -1, 0, (void*)5);
                symbolIndex += 1;
            }
        }
        break;
    /* Lay out enabled objects on a ring relative to the camera. */
    case 0x25:
    case 0x105:
    case 0x106:
    case 0x107:
    case 0x108:
    case 0x109:
    case 0x10A:
    case 0x10B:
    case 0x10C:
    case 0x10D:
    case 0x11C:
    case 0x11D:
    case 0x11E:
    case 0x11F:
    case 0x120:
    case 0x121:
    case 0x122:
    case 0x123: {
        UiObjects *objectCursor;
        f32 forwardY;
        f32 radialY;
        f32 angleStep;
        f32 radialX;
        f32 forwardX;
        f32 angle;
        s32 labelIndex;
        s32 objectCount;
        s32 selectedIndex;
        s32 objectIndex;
        if ((u32) lbl_8064C8E8 != 0U) {
            fn_801E8D3C(lbl_8031CD84.selection);
            if ((s32)fn_801E7578(lbl_8031CD84.mask >> lbl_8031CD84.shift) < 5) {
                fn_801E7578((u32) lbl_8031CD84.mask >> lbl_8031CD84.shift);
            }
            selectedIndex = fn_801E75A4(
                lbl_8031CD84.mask >> lbl_8031CD84.shift,
                fn_801E8D34(lbl_8031CD84.selection));
            objectCount = (s32)fn_801E7578(lbl_8031CD84.mask);
            fn_801F68B0(&cameraResult);
            camera = cameraResult;
            fn_801F68F8(&targetResult);
            target = targetResult;
            angleStep = lbl_8064EA0C / (f32) objectCount;
            forwardX = target.x - camera.x;
            forwardY = target.y - camera.y;
            forward.x = forwardX;
            forward.y = forwardY;
            forward.z = target.z - camera.z;
            PSVECNormalize(&forward, &forward);
            PSVECScale(&forward, &center, lbl_8064EB14);
            PSVECAdd(&camera, &center, &center);
            radialX = -forward.x;
            radialY = -forward.y;
            radial.x = radialX;
            radial.y = radialY;
            radial.z = -forward.z;
            PSVECScale(&radial, &radial, lbl_8064EB18);
            horizontal.x = forward.x;
            horizontal.y = forward.y;
            horizontal.z = lbl_8064EA14;
            PSMTXRotRad(tilt, 0x7A, lbl_8064EB1C);
            PSMTXMultVec(tilt, &horizontal, &horizontal);
            PSVECCrossProduct(&horizontal, &forward, &axis);
            PSMTXRotAxisRad(tilt, &horizontal, lbl_8064EB20);
            PSMTXMultVec(tilt, &axis, &axis);
            PSMTXMultVec(tilt, &radial, &radial);
            PSMTXRotAxisRad(ringRotation, &axis, lbl_8031CBA0.ringAngle);
            PSMTXRotAxisRad(ringStep, &axis, -angleStep);
            PSMTXMultVec(ringRotation, &radial, &radial);
            angle = lbl_8031CBA0.ringAngle;
            objectCursor = &lbl_8031CD84;
            objectIndex = 0;
            do {
                if ((1 << objectIndex) & ((u32) lbl_8031CD84.mask >> lbl_8031CD84.shift)) {
                    f32 fullTurn = lbl_8064EA0C;
                    if (angle >= fullTurn) {
                        angle -= fullTurn;
                    } else if (angle < lbl_8064EA14) {
                        angle += fullTurn;
                    }
                    PSVECAdd(&center, &radial, &position);
                    {
                        f32 alphaDistance, alphaScale, alphaBase, alphaProduct;
                        alphaDistance = angle - lbl_8064EB2C;
                        alphaBase = lbl_8064EB24;
                        alphaScale = lbl_8064EB28;
                        if (alphaDistance < lbl_8064EA14) {
                            alphaDistance = -alphaDistance;
                        }
                        alphaProduct = alphaScale * alphaDistance;
                        colorDelta = lbl_806519A8;
                        /* Retail initializes only the alpha component here. */
                        color.rgba[3] = (u8)(alphaBase + alphaProduct / lbl_8064EB2C);
                        colorCopy = color.word;
                        endColor = color.word;
                        startColor = color.word;
                        fn_8012C62C((u8*)objectCursor->objects[0], 0xF,
                                    &startColor, (s8*)&colorDelta, &endColor, 4);
                    }
                    fn_8011F0E8(objectCursor->objects[0], &position);
                    PSMTXMultVec(ringStep, &radial, &radial);
                    angle -= angleStep;
                }
                objectIndex += 1;
                objectCursor = (UiObjects*)((u8*)objectCursor + 4);
            } while (objectIndex < 5);
            {
                f32 fullTurn, nextAngle, oldAngle, wantedAngle;
                oldAngle = lbl_8031CBA0.ringAngle;
                wantedAngle = (f32) selectedIndex * angleStep;
                if (wantedAngle != oldAngle) {
                    nextAngle = oldAngle + (f32)(lbl_8064EB30 * (f32) (s8) lbl_8031CBA0.direction);
                    fullTurn = lbl_8064EA0C;
                    lbl_8031CBA0.ringAngle = nextAngle;
                    if (nextAngle >= fullTurn) {
                        lbl_8031CBA0.ringAngle = (f32) (nextAngle - fullTurn);
                    } else if (nextAngle < lbl_8064EA14) {
                        lbl_8031CBA0.ringAngle = (f32) (nextAngle + fullTurn);
                    }
                    if ((s8) lbl_8031CBA0.direction > 0) {
                        if (wantedAngle >= oldAngle) {
                            if (wantedAngle < nextAngle) {
                                lbl_8031CBA0.ringAngle = wantedAngle;
                                lbl_8031CBA0.direction = 0U;
                            }
                        } else {
                            fullTurn = lbl_8064EA0C;
                            if ((nextAngle >= fullTurn) && ((nextAngle - fullTurn) > wantedAngle)) {
                                lbl_8031CBA0.ringAngle = wantedAngle;
                                lbl_8031CBA0.direction = 0U;
                            }
                        }
                    } else if (wantedAngle < oldAngle) {
                        if (wantedAngle > nextAngle) {
                            lbl_8031CBA0.ringAngle = wantedAngle;
                            lbl_8031CBA0.direction = 0U;
                        }
                    } else if ((nextAngle < lbl_8064EA14) && ((nextAngle + lbl_8064EA0C) < wantedAngle)) {
                        lbl_8031CBA0.ringAngle = wantedAngle;
                        lbl_8031CBA0.direction = 0U;
                    }
                }
                if (wantedAngle == lbl_8031CBA0.ringAngle) {
                    lbl_8031CBA0.direction = 0U;
                } else if ((s8) lbl_8031CBA0.direction > 0) {
                    lbl_8031CBA0.direction = 3U;
                } else if ((s8) lbl_8031CBA0.direction < 0) {
                    lbl_8031CBA0.direction = -3U;
                }
            }
            if (((s32)fn_801E7578(lbl_8031CD84.mask) <= 1 ||
                 lbl_803003C8.mode == 0xD ||
                 (lbl_8031CBA0.direction == 0 &&
                  fn_80144A2C(0x10030000, 1, 0x3FF, 0) == 0)) &&
                (!(lbl_803003C8.flags & 1) ||
                 lbl_803003C8.mode != 0xD || lbl_8064C908 == 0)) {
                fn_801E3AA4(0);
                textColor = lbl_8064C2B0;
                fn_801E3A34(&textColor);
                fn_801E5AD0(0x63);
                fn_801E5430(0x140, 0x17C);
                labelIndex = selectedIndex + lbl_8031CD84.shift;
                if ((0x10000 << labelIndex) & fn_80113B64()) {
                    fn_801E56AC(lbl_8064EA08, lbl_8024DDC8[labelIndex].name);
                    fn_801E56AC(lbl_8064EA08, lbl_8064B5B0, lbl_8024DDC8[labelIndex].detail);
                } else if (labelIndex < 4) {
                    fn_801E56AC(lbl_8064EB34, lbl_8064B5B4);
                } else {
                    fn_801E56AC(lbl_8064EB34, lbl_8064B5B8);
                }
            }
        }
        break;
    }
    }
    if (effect != 0) {
        effectTarget = effect->target;
        if ((effectTarget > lbl_8064EA14) && (effect->current < effectTarget)) {
            fn_801AC5E4(0xF5, 0, 0x50, 0, 0, 1, 0);
        } else {
            fn_801AC5E4(0xF5, 0, 0, 0, 0x78, 1, 0);
        }
        fn_801F0294(1, effect->current);
        if (effect->current > lbl_8064EA50) {
            strongTint = lbl_8064EB08;
            fn_801FCCEC(&strongTint);
        } else {
            weakTint = lbl_8064EB0C;
            fn_801FCCEC(&weakTint);
        }
        if ((effect->current > lbl_8064EB38) && ((lbl_8064D5A8 % effect->period) == 0)) {
            objectHandle = fn_80201B3C();
            objectId = fn_80201B54((int*)objectHandle);
            soundObject = fn_80201BC8(objectHandle);
            soundEntry = fn_801A717C();
            fn_801A74A0(soundEntry, 0);
            fn_801A74A8(soundEntry, objectId);
            fn_801A7538(soundEntry, 1);
            fn_801A7518(soundEntry, effect->sound);
            fn_801A764C(soundEntry, fn_8011F130(soundObject));
            fn_8020123C(0x27, 0, objectId, (int)soundEntry);
            fn_801A7228(soundEntry);
        }
    } else {
        defaultTint = lbl_8064EB10;
        fn_801FCCEC(&defaultTint);
    }
}
