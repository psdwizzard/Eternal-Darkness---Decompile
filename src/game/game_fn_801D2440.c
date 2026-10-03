typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Ring {
    u8 count;
    u8 pad;
    u16 radius;
    Vec3 center;
} Ring;

typedef struct Effect {
    u8 pad0[6];
    u16 value06;
    u8 pad8[0xC];
    u8 data14[2];
    u8 value16;
    u8 pad17[0x21];
    int flags38;
    u8 pad3C[0x6C];
    int valueA8;
    Ring ring;
    u8 valueBC;
    u8 padBD[3];
    u8* valueC0;
} Effect;

typedef struct EventRecord {
    Vec3 position;
    float scale;
    u32 words[7];
    int object;
    u32 tail[2];
} EventRecord;

typedef struct ActorState {
    u32** table;
} ActorState;

typedef struct GameObject GameObject;

struct GameObject {
    u8 pad00[4];
    int owner;
    int type;
    int id;
    int handle;
    u8 pad14[0x14];
    void (*callback)(GameObject*, void*);
    void* callback_arg;
    u8 pad30[8];
    Vec3 position;
    int resource;
    u8 pad48[0x74];
    int actorBC;
    int actorC0;
    int actorC4;
    u8 payloadC8[0xF28];
    u8 flags;
    u8 padFF1[3];
    u16 state;
};

extern int lbl_8064D18C;
extern void* lbl_8064C504;
extern int lbl_8064D558;
extern Color lbl_80651088;
extern Color lbl_8065108C;
extern Color lbl_80651090;
extern Color lbl_80651094;
extern Color lbl_80651098;
extern Color lbl_8065109C;
extern float lbl_806510A0;

extern void fn_80027948(void*, int, int, int, int, int, int);
extern void fn_8002A4C8(void);
extern void fn_8002A508(void);
extern void fn_8002A590(void);
extern void fn_8002A754(void);
extern void fn_8002AA18(void);
extern void fn_8002AC60(void);
extern void* fn_80034708(EventRecord*);
extern void* fn_80047D6C(void);
extern void fn_800CC140(int, int, int, u32, int);
extern void fn_800CCA44(void*);
extern void fn_800DBF60(int, void*, int, void*, float);
extern void fn_800DC2B8(int, int, int, float);
extern float fn_800DC398(int);
extern void fn_8011ECF8(void*, void*);
extern void fn_8011F114(Vec3*, void*);
extern u32 fn_8011FA8C(void*, u32, u32);
extern int fn_8011FCB0(void*);
extern void fn_8011FE3C(void*, void*);
extern int fn_801261F4(void*);
extern void* fn_80128E30(void*);
extern void fn_8012B7A0(void*, float);
extern void* fn_8012C62C(void*, int, Color*, Color*, Color*, int);
extern void fn_80147E88(Effect*);
extern void fn_80149B38(u8*);
extern u8* fn_80149E04(void);
extern void fn_8014A178(Effect*, u8*);
extern void* fn_80155DB4(void*);
extern void fn_801568B8(void*, void (*)(void));
extern void fn_801568C0(void*, void (*)(void));
extern void fn_801568C8(void*, void (*)(void), void (*)(void), void (*)(void));
extern void fn_801568D8(void*);
extern void fn_801568E4(void*);
extern void fn_801568F0(void*);
extern void fn_801568FC(void*, void (*)(void));
extern void fn_80156904(void*, void (*)(void));
extern void fn_8015690C(void*, void (*)(void));
extern void fn_80156918(void*, void*);
extern void* fn_80156DA0(int, Vec3*);
extern void fn_80156F80(void*, void*);
extern void fn_801570F8(void*, void*);
extern int fn_80157888(ActorState*);
extern int fn_80157894(ActorState*);
extern int fn_801579F4(ActorState*);
extern void fn_80157B3C(ActorState*, int);
extern void fn_80157B60(ActorState*, int);
extern void fn_80157B80(ActorState*, u32);
extern u32 fn_80157BD0(ActorState*);
extern int fn_80157BE8(ActorState*);
extern int fn_8015821C(ActorState*);
extern int fn_80158264(void*, ActorState*, int);
extern u32 fn_80158550(void*, int);
extern void* fn_80158598(int, int);
extern void fn_801938FC(Effect*);
extern void fn_801B05B0(int, int);
extern s16 fn_801CEB2C(int);
extern void fn_801D1318(int);
extern void fn_801D1C34(EventRecord*, int, Vec3*);
extern void fn_801D1F78(u8*, Ring*, int);
extern void fn_801D2FA4(GameObject*);
extern void fn_801D3024(void);
extern void fn_801D3088(void);
extern int fn_801D38E8(int);
extern void fn_801D3CAC(int, int, u8*);
extern void fn_801E2CF4(GameObject*, u8*, int, int, int, int, u8, int, u8, u8, u8, u16);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern void fn_801E8328(int, Effect*);
extern void fn_801FDF74(int, int);
extern void fn_801FE22C(int);
extern void fn_801FE934(int, u8);
extern int fn_802006D4(int, int, int, int, int);
extern void fn_8020123C(int, int, int, int);
extern void fn_802015A4(void*);
extern void* fn_80201814(int);
extern void* fn_80201ADC(void);
extern int fn_80201AE4(void);
extern int fn_80201B54(void*);
extern void* fn_80201BC8(void*);
extern ActorState* fn_80201C24(void*);
extern void* fn_80201C2C(void*);
extern void fn_80201D24(void*, int);
extern void fn_80201D54(void*, int);
extern void* fn_80204A8C(void);
extern void fn_80204CE4(void*, void*);
extern void fn_80204E0C(void*, void*);
extern void fn_80204F54(void*);

void fn_801D2440(GameObject* object)
{
    int object_owner;
    void* own_model;
    void* data;
    u8 index;
    int count;
    void* info;

    if (object->type != lbl_8064D18C) {
        void* result;
        void* link;
        int actor;
        ActorState* current;
        int value;
        void* model;
        int owner;
        void* target;
        void* other_info;
        void* info;
        void* data;
        void* other_current;
        void* other;
        int count;

        actor = object->actorBC;
        info = fn_80201814(actor);
        current = fn_80201C24(info);
        if (fn_80157894(current) & 1) {
            other_current = fn_80201C2C(fn_80201ADC());
            if (object->state <= 80) {
                fn_80204E0C(info, other_current);
            } else {
                other_info = fn_80201814(object->actorC0);
                fn_80204F54(info);
                fn_8020123C(57, actor, actor, 0);
                fn_80204E0C(other_info, other_current);
            }
        } else if (object->state != 0) {
            owner = fn_80201AE4();
            target = fn_80201ADC();
            if (target != 0) {
                other = fn_80201C2C(target);
                data = fn_80155DB4(info);
                fn_80204E0C(info, other);
                count = fn_801579F4(current);
                if (count > 0) {
                    fn_80204E0C(fn_80201814(count), other);
                }
                fn_801568F0(data);
                fn_801568E4(data);
                fn_801568D8(data);
                result = fn_80201BC8(info);
                model = fn_80201BC8(target);
                fn_8011FE3C(result, model);
                fn_80156904(data, fn_8002A754);
                link = fn_80155DB4(target);
                fn_80156F80(data, link);
                value = fn_80158264(fn_80158598(owner, 0), current, 1);
                fn_800CC140(owner, actor, 0,
                             (*current->table)[value], 0);
            }
        }
        fn_801FE22C(object->resource);
        if (object->handle != -1) {
            fn_801B05B0(object->handle, 10);
        }
        fn_801D2FA4(object);
        if (object->flags & 0x10) {
            fn_801D1318(0);
        }
        return;
    }

    object_owner = object->owner;
    switch (object->state) {
    case 0: {
        Ring* ring;
        int owner;
        int actor;
        int value;
        void* target;
        Effect* payload;
        void* link;
        void* info;
        u8 color;
        void* other_data;
        int count;
        int other;
        ActorState* current;
        int flag;
        void* other_info;
        void* result;
        void* data;

        actor = object->actorBC;
        info = fn_80201814(actor);
        current = fn_80201C24(info);
        flag = fn_80157888(current);
        other = object->actorC4;
        count = fn_801579F4(current);
        other_info = fn_80201814(count);
        if (flag & 1) {
            lbl_8064D558 = actor;
            value = fn_80158550(fn_80158598(other, 0), actor);
            fn_800CC140(other, actor, 0, value, 0);
            lbl_8064D558 = 0;
            fn_80204E0C(info, fn_80204A8C());
            if (count > 0) {
                fn_80204E0C(other_info, fn_80204A8C());
            }
        }
        data = fn_80155DB4(info);
        result = fn_80201BC8(info);
        fn_8011FE3C(result, result);
        fn_801568C0(data, fn_801D3024);
        fn_801568B8(data, fn_8002AC60);
        fn_801568FC(data, 0);
        fn_80156904(data, 0);
        if (count > 0) {
            other_data = fn_80155DB4(other_info);
            target = fn_80201BC8(other_info);
            fn_8011FE3C(target, target);
            fn_801568C0(other_data, fn_801D3024);
            fn_801568B8(other_data, fn_8002AC60);
            fn_801568FC(other_data, 0);
            fn_80156904(other_data, 0);
        }
        if (other != fn_80201AE4()) {
            link = fn_80155DB4(fn_80201814(other));
            fn_801570F8(data, link);
        }
        payload = (Effect*)object->payloadC8;
        payload->valueC0 = fn_80149E04();
        if (payload->valueC0 == 0) {
            break;
        }
        fn_80147E88(payload);
        fn_8014A178(payload, payload->valueC0);
        payload->valueBC = 4;
        owner = object->owner;
        color = fn_801CEB2C(owner);
        *payload->valueC0 = color;
        fn_80149B38(payload->valueC0);
        fn_801938FC(payload);
        payload->value06 = 80;
        fn_801D3CAC(fn_801D38E8(owner), 0, payload->data14);
        ring = &payload->ring;
        payload->value16 = 0;
        payload->flags38 |= 0x4800;
        payload->valueA8 = object->actorBC;
        ring->count = color;
        ring->radius = 250;
        ring->center = object->position;
        fn_801D1F78(payload->valueC0, ring, payload->valueA8);
        fn_801E8328(17, payload);
        break;
    }
    case 20:
        fn_801FDF74(object->resource, 0x7A120);
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 1, 15, 53, 4, 10, 15, 1, 1, 80);
        break;
    case 30:
        info = fn_80201814(object->actorBC);
        fn_8011FA8C(fn_80201BC8(info), 0, 0x10000);
        data = fn_80155DB4(info);
        fn_801568C0(data, fn_801D3088);
        count = fn_801579F4(fn_80201C24(info));
        if (count > 0) {
            data = fn_80155DB4(fn_80201814(count));
            fn_801568C0(data, fn_801D3088);
        }
        fn_801FE934(object->resource, 9);
        break;
    case 40:
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 1, 15, 53, 4, 10, 15, 1, 2, 60);
        break;
    case 60:
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 1, 15, 53, 4, 10, 15, 1, 3, 40);
        break;
    case 80: {
        int actor;
        ActorState* current;
        void* info;
        void* model;
        void* item;
        void* runtime;
        void* target;
        void* data;
        Vec3 point;
        Color a2;
        Color a1;
        Color a0;
        Color b2;
        Color b1;
        Color b0;
        EventRecord query;

        if (object->actorC4 != fn_80201AE4()) {
            break;
        }
        actor = object->actorBC;
        info = fn_80201814(actor);
        current = fn_80201C24(info);
        if (!(fn_80157894(current) & 1)) {
            break;
        }
        model = fn_80201BC8(info);
        a0 = lbl_80651090;
        a1 = lbl_8065108C;
        a2 = lbl_80651088;
        fn_8012C62C(model, 15, &a2, &a1, &a0, 4);
        fn_8011F114(&point, model);
        fn_801D1C34(&query, actor, &point);
        item = fn_80034708(&query);
        target = fn_80201BC8(item);
        if (target != 0) {
            fn_801261F4(target);
            fn_8012B7A0(target, query.scale);
            if (fn_8011FCB0(target)) {
                runtime = fn_80128E30(target);
                fn_8011ECF8(target, runtime);
            }
        }
        fn_80201D54(item, query.object);
        fn_80201D24(item, 1);
        fn_802015A4(item);
        fn_800CCA44(item);
        data = fn_80156DA0(3, &point);
        if (data != 0) {
            void (*cb)(void);
            if (fn_8011FCB0(target)) {
                cb = fn_8002A508;
            } else {
                cb = fn_8002A590;
            }
            fn_801568C8(data, cb, fn_8002AC60, fn_8002AA18);
            fn_801568C0(data, fn_801D3088);
            fn_801568B8(data, fn_8002AC60);
            fn_801568FC(data, 0);
            fn_80156904(data, 0);
            fn_8015690C(data, fn_8002A4C8);
            fn_80156918(data, item);
        }
        b0 = lbl_8065109C;
        b1 = lbl_80651098;
        b2 = lbl_80651094;
        fn_8012C62C(target, 15, &b2, &b1, &b0, 4);
        fn_80204CE4(item, fn_80204A8C());
        object->actorC0 = fn_80201B54(item);
        break;
    }
    case 100: {
        void* result;
        int player;
        int other;
        void* info;
        void* model;
        int actor;
        void* data;
        int count;
        int color;
        int flag;
        ActorState* target;
        void* other_info;
        u8 tint;
        ActorState* current;
        void* link;
        void* effect;
        int owned;
        int value;

        player = fn_80201AE4();
        actor = object->actorBC;
        other = object->actorC4;
        info = fn_80201814(actor);
        data = fn_80155DB4(info);
        current = fn_80201C24(info);
        if (other == player) {
            flag = fn_80157888(current);
            fn_801568FC(data, fn_8002AA18);
            if (flag & 1) {
                fn_802006D4(actor, actor, -1, 75, 0);
                fn_80157B60(current, (u8)fn_801D38E8(object_owner));
                color = (fn_801CEB2C(object_owner) >> 1) + 1;
                fn_80157B3C(current, (u8)color);
                fn_80157B80(current, 2);
                owned = 1;
                count = fn_801579F4(current);
                if (count > 0) {
                    target = fn_80201C24(fn_80201814(count));
                    fn_802006D4(count, count, -1, 75, 0);
                    fn_80157B60(target, (u8)fn_801D38E8(object_owner));
                    color = (fn_801CEB2C(object_owner) >> 1) + 1;
                    fn_80157B3C(target, (u8)color);
                }
            } else {
                fn_80204F54(info);
                fn_8020123C(57, actor, actor, 0);
                actor = object->actorC0;
                info = fn_80201814(actor);
                current = fn_80201C24(info);
                owned = 0;
                if (fn_8015821C(current) == 131) {
                    index = fn_801D38E8(object_owner);
                    tint = (fn_801CEB2C(object_owner) >> 1) + 1;
                    fn_80157B60(current, index);
                    fn_80157B3C(current, tint);
                    fn_800DC2B8(actor, index, tint, fn_800DC398(tint));
                }
                fn_80157B80(current, 0x200);
            }
            if (object->id != player && fn_80157BD0(current) == 18) {
                value = 24;
            } else {
                value = fn_80157BE8(current);
            }
            result = fn_801E6CA0(lbl_8064C504, 0, value, 0, 1);
            fn_80027948(result, 0, player, actor, owned, 0, 0);
        } else {
            effect = fn_80047D6C();
            fn_802006D4(actor, actor, -1, 75, 0);
            fn_80157B60(current, (u8)fn_801D38E8(object_owner));
            color = (u8)((fn_801CEB2C(object_owner) >> 1) + 1);
            fn_80157B3C(current, color);
            fn_800DBF60(other, info, color, effect, lbl_806510A0);
            fn_801568F0(data);
            fn_801568E4(data);
            fn_801568D8(data);
            own_model = fn_80201BC8(info);
            other_info = fn_80201814(other);
            model = fn_80201BC8(other_info);
            fn_8011FE3C(own_model, model);
            fn_80156904(data, fn_8002A754);
            link = fn_80155DB4(other_info);
            fn_80156F80(data, link);
            value = fn_80158264(fn_80158598(other, 0), current, 1);
            fn_800CC140(other, actor, 0,
                         (*current->table)[value], 0);
        }
        if (object->callback != 0) {
            object->callback(object, object->callback_arg);
        }
        fn_801D2FA4(object);
        break;
    }
    }
}
