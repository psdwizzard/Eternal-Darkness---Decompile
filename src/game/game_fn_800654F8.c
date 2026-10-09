typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef struct { f32 x, y, z; } Vec3;
typedef struct { Vec3 first, second; } VecPair;
typedef struct { s32 first, second; Vec3 position, direction; f32 value; } HitResult;

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef struct DamageStatus {
    s32 flags;
    u8 pad04[0x20];
    s32 linkedId;
    u8 pad28[0x48];
    f32 scales[17];
    s32 attachedLimbs;
    s32 detachableLimbs;
    s32 callbackId;
    u8 padC0[0x2A];
    s16 health[15];
    s16 restoredHealth[15];
    s16 damage[15];
} DamageStatus;

typedef struct ActorInfo {
    void *first;
    void *modelData;
    u8 pad08[0x84];
    DamageStatus *status;
    s32 definitionIndex;
    s32 state;
    u8 pad98[6];
    u8 category;
    u8 kind;
} ActorInfo;

#define FIELD_AT(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

/* Damage and hit-reaction dispatcher. The contact query fills all of
 * HitResult, and the motion query copies both vectors of VecPair. */
u32 fn_800FBFB0(void);
int fn_8011EB04(void *);
void fn_8011F114(Vec3 *, Vec3 *);
s32 fn_8011F6A4(void *, s32, s32, s32, void *, s32);
s32 fn_801207F0(void *);
void fn_80120AD0(void *, const void *, u16, u32, f32, f32);
void fn_8012B690(void *, const void *, void *);
void fn_8012C478(void *, s32, s32);
void *fn_8012C62C(void *, s32, void *, s8 *, void *, s32);
void fn_8012CBE8(void *, s32, Vec3 *, Vec3 *, Vec3 *, s32);
void fn_8012F604(void *, u32, u32, u16);
void fn_8014CBE8(void *, s32, s32, s32 *);
void fn_8014D478(void *, Vec3 *, f32 *, s32, s32, s32 *, s32);
u8 fn_80157918(void *);
u8 fn_801579FC(void *);
u8 fn_80157AB8(void *);
u32 fn_801A7468(void *);
void fn_801A7470(void *, u32);
u32 fn_801A7490(void *);
u32 fn_801A7498(void *);
u32 fn_801A74C0(void *);
void fn_801A74D8(void *, u32);
void fn_801A74E8(void *, u32);
s16 fn_801A74F8(void *);
void fn_801A7518(void *, s16);
u16 fn_801A7530(void *);
void fn_801A7538(void *, u16);
u32 fn_801A7570(void *);
u32 fn_801A7590(void *);
u32 fn_801A76B0(void *);
f32 fn_801A76DC(void *);
void fn_801A76F4(VecPair *, const void *);
void fn_801A7744(Vec3 *, const void *);
void *fn_801A7760(void *);
u8 fn_801A7768(void *);
void fn_801A977C(void *, s32);
s32 fn_801D1B10(s32, s32, s32, s32);
s32 fn_801DD188(void *, s32, u8);
void fn_8020104C(s32, s32, s32, s32, f32);
u64 fn_8020123C(s32, s32, s32, s32);
void *fn_80201814(s32);
s32 fn_80201B44(void);
s32 fn_80201B54(void *);
void *fn_80201B8C(void *);
void *fn_80201B9C(void);
void *fn_80201BC8(void *);
void *fn_80201C24(void *);
s32 fn_80201EB8(void *);
u8 fn_80204578(void *, const Vec3 *);
void *fn_80204844(void *, s32);
void *fn_80205868(void *, s32, void *, u32);
void fn_80211A90(void *, const void *, f32);
void fn_80211AAC(void *, const void *);
f32 fn_80211B08(const Vec3 *);
void fn_800337C8(Vec3 *, const Vec3 *, s32, void *, s32, s32);
s32 fn_80035628(void *);
s32 fn_800359A0(void *, void *);
/* The retail wrapper forwards its incoming r3 to fn_801A7778. */
void *fn_8004910C();
s16 fn_8006534C(void *, void *, s16);
s32 fn_80065428(s32, s16, s32);
s32 fn_80065454();
s32 fn_80066BB8(s32, s32);
s32 fn_80066D80(s32, s32);
s32 fn_80066E78(u32, s16, u8, s32, s32 *, s32 *, s32 *, s8 *);
void fn_80067180(s32);
s32 fn_8006749C(s32);
s32 fn_80067728(u8);
s32 fn_8006D344(void *, s32, s32);
void *fn_8006D444(void *);
void fn_80071D5C(void);
void fn_80071DD8(void);
void *fn_80072354(s32);
s32 fn_800ACFE8(void);
s32 fn_800C1AB8(s32);
void fn_800CEA1C(s32, s32, void *, void *, s32, u8, void *, f32, f32, f32);
void fn_800EA428(void *, void *, s32);
typedef struct { Vec3 origin, direction, scale, position, rotation; } DamageDefaults;
extern DamageDefaults lbl_80239008;
extern u8 lbl_802FC5BC[];
extern s32 lbl_8064D18C;
extern f32 lbl_8064E698;
extern s32 lbl_8064E6A0;
extern s32 lbl_8064E6A4;
extern s32 lbl_8064E6A8;
extern s32 lbl_8064E6AC;
extern s32 lbl_8064E6B0;
extern s32 lbl_8064E6B4;
extern f32 lbl_8064E6B8;
extern f32 lbl_8064E6BC;
extern f32 lbl_8064E6C0;
extern f32 lbl_8064E6C4;
extern f32 lbl_8064E6C8;
extern f32 lbl_8064E6CC;
extern f32 lbl_8064E6D0;
extern f32 lbl_8064E6D4;
extern f32 lbl_8064E6D8;
extern f32 lbl_8064E6DC;

s32 fn_800654F8(void *event) {
    DamageDefaults *defaults = &lbl_80239008;
    u32 eventFlags;
    s32 damageFlags;
    s32 hitMask;
    u32 weapon;
    u32 linkedObject;
    s32 weaponModelType;
    s32 targetType;
    u32 elementalFlags;
    u32 preventSevering;
    void *defaultEffectResource;
    s32 targetId;
    u32 source;
    s32 weaponFlags;
    s16 originalDamage;
    u8 reaction;
    s32 sourceId;
    s32 directPlayerHit;
    s32 spawnedEffect;
    s16 totalDamage;
    s32 limbReaction;
    s32 specialHit;
    s32 applyDamage;
    s32 hit;
    s32 weaponEvent;
    s32 linkedId;
    s32 suppressParticles;
    s32 impactFlags;
    HitResult contact;
    VecPair motion;
    Vec3 eventPosition;
    Vec3 modelPosition;
    Vec3 impactDirection;
    Vec3 fallbackPosition;
    Vec3 localOrigin;
    Vec3 detachDirection;
    Vec3 partScale;
    Vec3 partPosition;
    Vec3 partRotation;
    Vec3 partScaleCopy;
    s32 effectResource;
    s32 effectAmount;
    s32 effectLevel;
    s32 severParam1;
    s32 severParam2;
    s32 severParam3;
    s32 regularParam1;
    s32 regularParam2;
    s32 regularParam3;
    s8 effectVariant;
    u8 facing;
    register u32 returnedWord;
    /* Hit flags initially; weapon sever permission during the limb loop. */
    register u32 workingFlags;
    f32 particleStrength;
    void *targetDefinition;
    void *limbStatus;
    s32 playerId;
    s32 limbMask;
    u32 particleModel;
    s32 randomY;
    void *limbHitPosition;
    u32 weaponModel;
    void *playerObject;
    register s16 damage;
    u32 target;
    s32 result;
    u32 model;
    ActorInfo *targetInfo;
    ActorInfo *sourceInfo;
    DamageStatus *targetStatus;
    s32 limbIndex;
    s32 scaleIndex;
    s32 reactionId;
    u32 elementType;
    void **weaponInfo;
    u64 damageResult;
    register s32 limbByteOffset;
    register s32 healthOffset;
    s32 forceFullBodyHit;
    u32 reactionBits;
    s32 targetGroup;
    s32 inverseLimbMask;
    void *modelData;
    s16 limbHealth;
    s32 hitGroup;
    s32 eventReaction;
    s32 forcedReaction;
    DamageStatus *scaleStatus;
    void *hitPosition;
    void **eventWeaponInfo;
    s32 headReaction;
    s32 failedSeverReaction;
    s32 severReaction;
    s32 defaultReaction;
    register s32 contactOrHealthIndex;
    register s32 doubledDamage;
    register u32 effectKind;
    s32 randomX;
    s32 characterState;
    u8 targetKind;
    s32 eventKind;
    u32 weaponHandle;
    s32 modelType;
    f32 directionX;
    f32 scaleValue;
    f32 directionY;
    s32 specialReaction;
    u8 kind;
    s32 fallbackReaction;
    s32 particleDuration;

    result = 0;
    targetId = fn_801A7490(event);
    target = (u32)fn_80201814(targetId);
    targetGroup = fn_80201EB8((void *)target);
    eventFlags = fn_801A74C0(event);
    if (((s32) lbl_8064D18C == targetGroup) || (targetGroup == -1)) {
        weaponFlags = 0;
        localOrigin = defaults->origin;
        fn_801A74F8(event);
        /* ASM: mr retains the getter's sign-extended result without the
         * compiler's redundant intermediate register for a short local. */
        asm { mr damage, r3 }
        directPlayerHit = 0;
        spawnedEffect = 0;
        sourceId = fn_801A7498(event);
        damageFlags = fn_801A7570(event);
        source = (u32)fn_80201814(sourceId);
        reactionBits = fn_801A76B0(event);
        originalDamage = damage;
        reaction = reactionBits & 0xFF;
        if (reactionBits & 1) {
            damage *= 2;
        }
        if (target != 0U) {
            targetInfo = fn_80201B8C((void *)target);
            sourceInfo = NULL;
            fn_801A7530(event);
            /* ASM: mr retains the getter's zero-extended halfword result;
             * C promotion emits an unnecessary clrlwi. */
            asm { mr returnedWord, r3; mr workingFlags, returnedWord }
            totalDamage = 0;
            limbReaction = 0;
            specialHit = (fn_801A74C0(event) >> 0x10U) & 1;
            if (source != 0U) {
                sourceInfo = fn_80201B8C((void *)source);
            }
            targetStatus = targetInfo->status;
            targetDefinition = fn_80072354(targetInfo->definitionIndex);
            applyDamage = 0;
            limbIndex = 0;
            limbByteOffset = limbIndex;
            hit = 0;
            weaponEvent = 0;
            hitMask = fn_801A7590(event);
            linkedId = targetStatus->linkedId;
            playerId = fn_80201B44();
            weaponHandle = (u32)fn_8004910C(event);
            weapon = weaponHandle;
            if (weaponHandle != 0U) {
                weaponModel = (u32)fn_80201BC8((void *)weapon);
            } else {
                weaponModel = 0U;
            }
            linkedObject = (u32)fn_80201814(linkedId);
            reactionId = -1;
            if (weaponModel != 0U) {
                modelType = fn_8011EB04((void *)weaponModel);
            } else {
                modelType = -1;
            }
            weaponModelType = modelType;
            elementType = 0;
            defaultEffectResource = (void *)((u32)lbl_802FC5BC + 0x18);
            effectAmount = 0;
            effectKind = 0;
            effectLevel = 0;
            suppressParticles = 0;
            effectResource = *(s32 *)defaultEffectResource;
            effectVariant = 0;
            model = (u32)fn_80201BC8((void *)target);
            fn_801A7744(&eventPosition, event);
            fn_8011F114(&modelPosition, (Vec3 *)model);
            if (sourceId == playerId) {
                playerObject = fn_80204844(fn_80201B9C(), 0x20);
                if (fn_8006D344(fn_8006D444(playerObject), 0x80000, 0) != 0) {
                    fn_80067180(target);
                    fn_8020123C(0x56, targetId, fn_80201B54(playerObject), 0U);
                    fn_801A7518(event, originalDamage);
                    return 1;
                }
            }
            if ((sourceInfo != NULL) && (sourceInfo->category == 2) && (sourceInfo->kind == 3) && (sourceInfo->state == 3)) {
                eventKind = fn_801A7468(event);
                if ((eventKind == 4) && (FIELD_AT(sourceInfo->modelData, u8 *, 0xA) & 8)) {
                    fn_801A7538(event, 2U);
                } else if ((eventKind == 5) && (FIELD_AT(sourceInfo->modelData, u8 *, 0xA) & 4)) {
                    fn_801A7538(event, 2U);
                }
            }
            fn_800359A0((void *)target, (void *)source);
            if (weapon != 0U) {
                weaponInfo = fn_80201C24((void *)weapon);
                targetType = fn_80035628((void *)target);
                elementType = fn_80157AB8(weaponInfo);
                effectKind = fn_80157918(weaponInfo);
                fn_801D1B10((s16)damage, targetType, elementType, effectKind & 0xFF);
                /* ASM: mr retains the returned word in the short working value;
                 * C assignment eagerly sign-extends it before the guarded test. */
                asm { mr damage, r3 }
                if (targetId != fn_80201B44()) {
                    fn_80071DD8();
                    /* ASM: cmpwi and beq test the result forwarded in r3 by
                     * this void wrapper; C cannot access its register result. */
                    asm { cmpwi r3, 0; beq skipDamageCap }
                    if (damage > originalDamage) {
                        damage = originalDamage;
                    }
                }
            skipDamageCap:
                fn_801A7518(event, damage);
                suppressParticles = fn_801DD188((void *)target, elementType, effectKind);
                weaponFlags = FIELD_AT(FIELD_AT(weaponInfo, void **, 4), s32 *, 8);
            } else if ((sourceId == playerId) && (weapon == 0U) && (specialHit == 0)) {
                directPlayerHit = 1;
            }
            if (linkedObject != 0U) {
                if (targetId == playerId) {
                    fn_80071D5C();
                    /* ASM: cmpwi and bne test the result forwarded in r3 by
                     * this void wrapper; C cannot access its register result. */
                    asm { cmpwi r3, 0; bne skipLinkedHandler }
                }
                fn_801A74D8(event, 0x400000);
                workingFlags = (u32) fn_8020123C(0xB, targetId, linkedId, (s32)event);
                fn_801A74E8(event, 0x400000);
                if ((u16) workingFlags == 0) {
                    fn_801A7518(event, originalDamage);
                    return 1;
                }
                fn_801A7538(event, workingFlags);
            }
skipLinkedHandler:
            if (eventFlags & 0x800) {
                elementType = (u32)fn_801A7760(event);
                fn_801A7768(event);
                /* ASM: mr preserves the getter's already zero-extended byte;
                 * C promotion inserts an unnecessary clrlwi here. */
                asm { mr effectKind, r3 }
            }
            if (((u8)effectKind > 1U) && (suppressParticles == 0)) {
                particleModel = model;
                if ((u8)effectKind == 5) {
                    particleStrength = lbl_8064E6B8;
                } else {
                    particleStrength = -((lbl_8064E6B8 * (f32) ((s32)(u8)effectKind - 2)) - lbl_8064E6BC);
                }
                targetKind = targetInfo->kind;
                particleDuration = (targetKind == 0xD) ? 0x3E8 : 0x64;
                if ((targetKind == 0x16) && ((characterState = fn_800ACFE8(), (characterState == 1)) || (characterState == 2))) {
                    particleModel = 0U;
                }
                if (particleModel != 0U) {
                    fn_80120AD0((void *)particleModel, 0, particleDuration, (u16) (fn_8006749C((s32) elementType) | 2), lbl_8064E698, particleStrength);
                }
            }
            fn_8012B690((void *)model, &localOrigin, &fallbackPosition);
            if (weapon != 0U) {
                impactFlags = fn_80066E78(workingFlags, damage, fn_801579FC(fn_80201C24((void *)weapon)), target, &effectAmount, &effectLevel, &effectResource, &effectVariant);
            } else if (directPlayerHit != 0) {
                impactFlags = 0;
                effectVariant = 0;
            } else {
                impactFlags = fn_80066E78(workingFlags, damage, 2, target, &effectAmount, &effectLevel, &effectResource, &effectVariant);
            }
            fn_801A76F4(&motion, event);
            if (fn_80211B08(&motion.second) > lbl_8064E6C0) {
                impactDirection = motion.second;
                fn_80211A90(&impactDirection, &impactDirection, lbl_8064E6C4);
            } else {
                randomX = 8 - (fn_800FBFB0() & 0xF);
                impactDirection.x = (f32) randomX;
                randomY = 8 - (fn_800FBFB0() & 0xF);
                impactDirection.y = (f32) randomY;
                impactDirection.z = lbl_8064E6C8;
            }
            if (hitMask & 0x8000) {
                applyDamage = 1;
                forceFullBodyHit = 0;
                totalDamage = damage;
                hit = 1;
                if ((targetInfo->kind == 3) && (targetInfo->state == 3) && !(targetStatus->attachedLimbs & 2)) {
                    forceFullBodyHit = 1;
                }
                if ((fn_80066BB8(model, 1) == 0) || (forceFullBodyHit != 0)) {
                    hitGroup = 0xF;
                } else {
                    hitGroup = 1;
                }
                contactOrHealthIndex = fn_8011F6A4((void *)model, 0, hitGroup, -1, &contact.first, 1);
                hitPosition = &contact.position.x;
                if (contactOrHealthIndex == -1) {
                    hitPosition = &fallbackPosition.x;
                }
                fn_8014D478((void *)model, hitPosition, &impactDirection.x, effectAmount & 0xFF, effectLevel & 0xFF, &effectResource, impactFlags);
                if (fn_801207F0((void *)model) != 0) {
                    fn_800CEA1C(0x17, 3, hitPosition, &impactDirection.x, 2, (u8)effectVariant, defaultEffectResource, lbl_8064E6CC, lbl_8064E6D0, lbl_8064E6D4);
                }
                if (((s32) elementType != 0) && (damageFlags & 0x10018)) {
                    fn_800337C8(hitPosition, 0, (s32) elementType, 0, 0x50, 1);
                    spawnedEffect = 1;
                }
                result |= 1;
            }
            /* Apply damage to each affected limb and collect sever reactions. */
            elementalFlags = damageFlags & 0x10018;
            workingFlags = weaponFlags & 2;
            preventSevering = damageFlags & 0x20000;
            do {
                limbMask = 1 << limbIndex;
                if ((hitMask & limbMask) && (fn_80066D80(model, limbIndex) != 0) && (targetStatus->attachedLimbs & limbMask)) {
                    if ((targetInfo->kind == 4) && (sourceInfo != NULL) && (sourceInfo->category == 1) && (fn_80204578((void *)target, &eventPosition) == 0)) {
                        /* ASM: extsh keeps this signed-halfword conversion in the
                         * affected-limb path; MWCC otherwise hoists it and spills
                         * the doubled value for the entire loop. */
                        asm { extsh doubledDamage, damage }
                        /* ASM: addi preserves the byte index for lhax/sthx.
                         * C folds this addition into the base pointer, or masks
                         * off the low bit when expressed as a halfword index. */
                        asm { addi contactOrHealthIndex, limbByteOffset, 0xEA }
                        doubledDamage *= 2;
                        *(s16 *)((u8 *)targetStatus + contactOrHealthIndex) -= (s16)doubledDamage;
                    } else {
                        limbHealth = fn_8006534C((void *)target, (void *)source, damage);
                        /* ASM: addi preserves the byte index for lhax/sthx;
                         * C otherwise reassociates the address calculation. */
                        asm { addi healthOffset, limbByteOffset, 0xEA }
                        *(s16 *)((u8 *)targetStatus + healthOffset) -= limbHealth;
                    }
                    limbStatus = (void *)((u32)targetStatus + limbByteOffset);
                    limbHealth = FIELD_AT(limbStatus, s16 *, 0xEA);
                    result |= 1;
                    FIELD_AT(limbStatus, s16 *, 0xEA) = limbHealth > 0 ? limbHealth : 0;
                    if (fn_8011F6A4((void *)model, 0x14, limbIndex, -1, &contact, 1) == -1) {
                        limbHitPosition = &fallbackPosition.x;
                    } else {
                        limbHitPosition = &contact.position.x;
                    }
                    fn_8014D478((void *)model, limbHitPosition, &impactDirection.x, effectAmount & 0xFF, effectLevel & 0xFF, &effectResource, impactFlags);
                    if (fn_801207F0((void *)model) != 0) {
                        fn_800CEA1C(0x17, 3, limbHitPosition, &impactDirection.x, 2, (u8)effectVariant, defaultEffectResource, lbl_8064E6D8, lbl_8064E6D0, lbl_8064E6D4);
                    }
                    hit = 1;
                    if (((s32) elementType != 0) && (elementalFlags != 0) && (spawnedEffect == 0)) {
                        fn_800337C8(limbHitPosition, 0, (s32) elementType, 0, 0x50, 1);
                        spawnedEffect = 1;
                    }
                    if (FIELD_AT(limbStatus, s16 *, 0xEA) == 0) {
                        applyDamage = 1;
                        totalDamage += FIELD_AT(limbStatus, s16 *, 0x126);
                        if (((targetStatus->detachableLimbs & limbMask) || (fn_80065454(target, model, (u8 *)targetInfo, limbIndex) != 0)) && (workingFlags != 0) && (preventSevering == 0) && (fn_80065428(weaponModelType, damage, limbIndex) != 0) && (fn_80067728(targetInfo->kind) != 0)) {
                            directionX = modelPosition.x - eventPosition.x;
                            detachDirection = defaults->direction;
                            directionY = modelPosition.y - eventPosition.y;
                            detachDirection.x = directionX;
                            detachDirection.y = directionY;
                            detachDirection.z = lbl_8064E698;
                            fn_80211AAC(&detachDirection, &detachDirection);
                            fn_80211A90(&detachDirection, &detachDirection, lbl_8064E6C8);
                            fn_80205868((void *)model, limbIndex, &detachDirection.x, 0x2000);
                            fn_8014CBE8((void *)target, 0x14, limbIndex, defaultEffectResource);
                            fn_800EA428((void *)target, targetStatus, limbIndex);
                            result |= 2;
                            fn_801A74D8(event, 0x200);
                            if (FIELD_AT(targetDefinition, u8 *, 0xC8) & 2) {
                                scaleIndex = -1;
                                partScale = defaults->scale;
                                fn_8012C478((void *)model, limbIndex, 1);
                                FIELD_AT(limbStatus, s16 *, 0xEA) = (s16) *(s16 *)((u8 *)targetInfo->status + limbByteOffset + 0x108);
                                if ((limbIndex == 0) || (limbIndex == 2) || (limbIndex == 3)) {
                                    scaleIndex = fn_800C1AB8(limbIndex);
                                }
                                if (targetInfo != NULL) {
                                    scaleStatus = targetInfo->status;
                                    if ((scaleStatus != NULL) && (scaleIndex != -1)) {
                                        scaleValue = scaleStatus->scales[scaleIndex];
                                        if ((lbl_8064E6DC != scaleValue) && (lbl_8064E698 != scaleValue)) {
                                            partScale.z = scaleValue;
                                            partScale.y = scaleValue;
                                            partScale.x = scaleValue;
                                        }
                                    }
                                }
                                partScaleCopy = partScale;
                                partRotation = defaults->rotation;
                                partPosition = defaults->position;
                                fn_8012CBE8((void *)model, limbIndex, &partPosition, &partRotation, &partScaleCopy, 1);
                                fn_8012F604((void *)model, limbIndex, 1, 0x3E8);
                            }
                            if (FIELD_AT(targetDefinition, u8 *, 0xC8) & 1) {
                                fn_8012C478((void *)model, limbIndex, 1);
                                FIELD_AT(limbStatus, s16 *, 0xEA) = (s16) *(s16 *)((u8 *)targetInfo->status + limbByteOffset + 0x108);
                                if ((targetInfo->kind == 3) && (targetInfo->state == 3)) {
                                    modelData = targetInfo->modelData;
                                    inverseLimbMask = ~limbMask;
                                    FIELD_AT(modelData, u8 *, 0xA) = (u8) (FIELD_AT(modelData, u8 *, 0xA) | limbMask);
                                    targetStatus->detachableLimbs = targetStatus->detachableLimbs & inverseLimbMask;
                                    targetStatus->attachedLimbs = targetStatus->attachedLimbs & inverseLimbMask;
                                    severParam3 = lbl_8064E6A8;
                                    severParam2 = lbl_8064E6A4;
                                    severParam1 = lbl_8064E6A0;
                                    fn_8012C62C((void *)model, limbIndex, &severParam1, (s8 *)&severParam2, &severParam3, 0x136);
                                } else {
                                    regularParam3 = lbl_8064E6B4;
                                    regularParam2 = lbl_8064E6B0;
                                    regularParam1 = lbl_8064E6AC;
                                    fn_8012C62C((void *)model, limbIndex, &regularParam1, (s8 *)&regularParam2, &regularParam3, 4);
                                }
                                fn_8012F604((void *)model, limbIndex, 0, 0xA);
                            }
                            switch (limbIndex) {
                            case 0:
                                limbReaction = 1;
                                fn_801A977C((void *)model, 0x19);
                                if (fn_8011EB04((void *)model) == 1) {
                                    facing = fn_80204578((void *)target, &eventPosition);
                                    headReaction = 0xC;
                                    if (facing != 0) {
                                        headReaction = 0xB;
                                    }
                                } else {
                                    headReaction = 0x45;
                                }
                                reactionId = headReaction;
                                break;
                            case 2:
                                limbReaction = 1;
                                fn_801A977C((void *)model, 0x18);
                                reactionId = 0x46;
                                break;
                            case 3:
                                limbReaction = 1;
                                fn_801A977C((void *)model, 0x18);
                                reactionId = 0x47;
                                break;
                            default:
                                facing = fn_80204578((void *)target, &eventPosition);
                                severReaction = 0xC;
                                if (facing != 0) {
                                    severReaction = 0xB;
                                }
                                reactionId = severReaction;
                                break;
                            }
                        } else {
                            if (FIELD_AT(targetDefinition, u8 *, 0xC8) & 0x10) {
                                FIELD_AT(limbStatus, s16 *, 0xEA) = 0;
                            } else if (workingFlags != 0) {
                                FIELD_AT(limbStatus, s16 *, 0xEA) = 1;
                            } else {
                                FIELD_AT(limbStatus, s16 *, 0xEA) = (s16) *(s16 *)((u8 *)targetInfo->status + limbByteOffset + 0x108);
                            }
                            facing = fn_80204578((void *)target, &eventPosition);
                            failedSeverReaction = 0xC;
                            if (facing != 0) {
                                failedSeverReaction = 0xB;
                            }
                            reactionId = failedSeverReaction;
                        }
                    }
                }
                limbIndex += 1;
                limbByteOffset += 2;
            } while (limbIndex < 0xF);
            if ((limbReaction == 0) && (hit != 0)) {
                fn_801A977C((void *)model, 0x13);
            }
            /* Resolve the reaction after limb-specific processing. */
            if (!(u32)(fn_8020123C(0x82, sourceId, targetId, reaction) & 0xFFFFFFFFU)) {
                reaction = 0;
                if ((targetStatus->flags & 1) && (directPlayerHit == 0)) {
                    facing = fn_80204578((void *)target, &eventPosition);
                    forcedReaction = 0xC;
                    if (facing != 0) {
                        forcedReaction = 0xB;
                    }
                    reactionId = forcedReaction;
                    fn_801A7470(event, reactionId);
                }
            }
            switch ((s32) reaction) {
            case 8:
                fallbackReaction = reactionId;
                if (reactionId == -1) {
                    fallbackReaction = 0xB;
                }
                reactionId = fallbackReaction;
                break;
            case 16:
                if (fn_80204578((void *)target, &eventPosition) != 0) {
                    if (targetInfo->kind == 4) {
                        fn_8020123C(0xE6, sourceId, targetId, (s32)event);
                    } else {
                        fn_8020104C(0x37, sourceId, targetId, 0, fn_801A76DC(event));
                    }
                    result |= 1;
                } else {
                    reactionId = 0xC;
                }
                break;
            case 32:
                fn_8020123C(0x32, sourceId, targetId, (s32)event);
                result |= 1;
                break;
            case 2:
                fn_801A7470(event, -1);
                reaction = 0;
                fn_8020123C(0xCB, sourceId, targetId, (s32)event);
                result |= 1;
                facing = fn_80204578((void *)target, &eventPosition);
                eventReaction = 0xC;
                if (facing != 0) {
                    eventReaction = 0xB;
                }
                reactionId = eventReaction;
                fn_801A7470(event, reactionId);
                break;
            }
            if ((hit != 0) && (reaction == 0) && (targetStatus->flags & 1) && (reactionId == -1) && (directPlayerHit == 0)) {
                facing = fn_80204578((void *)target, &eventPosition);
                defaultReaction = 0xC;
                if (facing != 0) {
                    defaultReaction = 0xB;
                }
                reactionId = defaultReaction;
            }
            fn_801A7470(event, reactionId);
            if ((reactionId != -1) || (directPlayerHit != 0)) {
                result |= 1;
                if ((targetInfo != NULL) && (eventFlags & 0x1000) && ((kind = targetInfo->kind, (kind == 0x27)) || (kind == 3))) {
                    specialReaction = 1;
                } else {
                    specialReaction = 0;
                }
                if ((specialReaction != 0) || (result & 2) || ((targetInfo->category == 1) && (targetInfo->kind == 1))) {
                    fn_8020123C(0x35, sourceId, targetId, (s32)event);
                } else {
                    fn_8020123C(0xE6, sourceId, targetId, (s32)event);
                }
            }
            if (weapon != 0U) {
                eventWeaponInfo = fn_80201C24((void *)weapon);
                if ((eventWeaponInfo != NULL) && (FIELD_AT(*eventWeaponInfo, s32 *, 0x10) & 0x10)) {
                    weaponEvent = 1;
                }
            }
            if (hit != 0) {
                if (weaponEvent != 0) {
                    fn_8020123C(0x1E, sourceId, targetId, (s32)event);
                }
                if (targetStatus->callbackId != 0) {
                    fn_8020123C(0xF6, targetId, targetStatus->callbackId, (s32)event);
                }
            }
            if (applyDamage != 0) {
                fn_801A7470(event, -1);
                fn_801A7518(event, fn_8006534C((void *)target, (void *)source, totalDamage));
                fn_801A74D8(event, 0x800000);
                damageResult = fn_8020123C(0x27, sourceId, targetId, (s32)event);
                fn_801A74E8(event, 0x800000);
                if ((u32)(damageResult & 0xFFFFFFFFU) & 2) {
                    result |= 4;
                }
            }
        }
        fn_801A7518(event, originalDamage);
    }
    return result;
}
