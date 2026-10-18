typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Actor {
    u8 pad0[0xBC];
    float unkBC;
    float unkC0;
    float unkC4;
    u8 padC8[0x4];
    Vec3 unkCC;
    Vec3 unkD8;
    u8 padE4[0x10];
    u32 flags;
    u16 flags2;
    u16 pad;
    u16 state;
} Actor;

extern float fn_8003315C(float);
extern float fn_800490E8(float, float);
extern void fn_80128BE4(void *);
extern void fn_8012ABEC(void *, Vec3 *);
extern float fn_8012B750(void *);
extern void fn_8012B7A0(void *, float);
extern int fn_8017A010(float *, int, float, float, float);
extern void fn_8017A12C(float *, float, float);
extern void fn_8017A1C0(float *, int, float, float);
extern void PSVECSubtract(const Vec3 *, const Vec3 *, Vec3 *);
extern float PSVECMag(const Vec3 *);
extern float PSVECDotProduct(const Vec3 *, const Vec3 *);
extern float lbl_806501A8;
extern float lbl_806501B8;
extern float lbl_806501BC;
extern float lbl_806501C0;
extern float lbl_806501C4;

int fn_8012A7C8(Vec3 *pos, Actor *actor)
{
    Vec3 toPos;
    Vec3 toTarget;
    Vec3 start;
    Vec3 delta;
    Vec3 facing;
    Vec3 dir;
    float current;
    float diff;
    float dist;
    float dot;
    float len;
    float a;
    int inFront = 1;
    int turn = 0;
    int ok = 1;
    int aligned = 1;
    int dirSign;
    int result;

    if (actor->flags2 & 1) {
        PSVECSubtract(&actor->unkCC, pos, &toPos);
        dist = PSVECMag(&toPos);
        PSVECSubtract(&actor->unkCC, &actor->unkD8, &toTarget);
        start = *pos;
        if ((actor->flags2 & 2) && dist > lbl_806501B8 && !(actor->flags & 0x800)) {
            turn = 1;
        }
        inFront = PSVECDotProduct(&toPos, &toTarget) > lbl_806501A8;
        if (!inFront && (actor->flags & 0x800)) {
            fn_80128BE4(pos);
        }
    }

    if (actor->flags2 & 2) {
        if (turn) {
            actor->unkC0 = lbl_806501BC + fn_800490E8(toPos.y, toPos.x);
        }
        dirSign = 0;
        if (actor->flags & 0x6000) {
            if (actor->flags & 0x4000) {
                dirSign = -1;
            } else if (actor->flags & 0x2000) {
                dirSign = 1;
            }
            fn_8017A010(&actor->unkC4, dirSign, actor->unkC0, actor->unkBC, lbl_806501C0);
            fn_8012B7A0(pos, actor->unkC4);
        } else {
            current = fn_8012B750(pos);
            fn_8017A010(&current, 0, actor->unkC0, actor->unkBC, lbl_806501C0);
            fn_8012B7A0(pos, current);
        }
    }

    if (inFront && !(actor->flags & 4)) {
        fn_8012ABEC(pos, &facing);
        PSVECSubtract(&facing, &start, &dir);
    }

    if ((actor->flags2 & 1) && inFront) {
        PSVECSubtract(&actor->unkCC, pos, &toPos);
        PSVECMag(&toPos);
        ok = PSVECDotProduct(&toPos, &toTarget) <= lbl_806501A8;
        if ((actor->flags & 0x8000) && !ok) {
            PSVECSubtract(pos, &start, &delta);
            dot = PSVECDotProduct(&delta, &dir);
            len = PSVECMag(&dir);
            if (len > lbl_806501A8) {
                if (dot <= lbl_806501A8) {
                    ok = 1;
                } else {
                    a = fn_8003315C(dot / (len * PSVECMag(&delta)));
                    if (a < lbl_806501A8) {
                        a = -a;
                    }
                    if (a > lbl_806501C4) {
                        ok = 1;
                    }
                }
            }
        }
    }

    if (actor->flags2 & 2) {
        if (actor->flags & 0x6000) {
            fn_8017A1C0(&diff, dirSign, actor->unkC4, actor->unkC0);
        } else {
            current = fn_8012B750(pos);
            /* the round trip reproduces retail's frsp on the passed value */
            fn_8017A12C(&diff, (float)(double)current, actor->unkC0);
        }
        a = diff;
        if (a < lbl_806501A8) {
            a = -a;
        }
        if (a > lbl_806501C0) {
            aligned = 0;
        }
    }

    result = 0;
    if (ok && aligned && !(actor->flags & 0x100)) {
        result = 1;
        actor->state = 8;
    }
    return result;
}
