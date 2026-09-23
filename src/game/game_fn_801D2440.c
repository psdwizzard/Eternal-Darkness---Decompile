typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct GameObject GameObject;
typedef struct Vec3 { float x, y, z; } Vec3;

struct GameObject {
    u8 pad00[4]; void* owner; int type; int id; int handle;
    u8 pad14[0x14]; void (*callback)(GameObject*, void*); void* callback_arg;
    u8 pad30[8]; Vec3 position; void* resource44; u8 pad48[0x74];
    void* actorBC; void* actorC0; void* actorC4; u8 payloadC8[0xF28];
    u8 flagsFF0; u8 padFF1[3]; u16 stateFF4;
};

extern int lbl_8064D18C, lbl_8064C504;
extern void* lbl_8064D558;
extern Color lbl_80651088, lbl_8065108C, lbl_80651090;
extern Color lbl_80651094, lbl_80651098, lbl_8065109C;
extern float lbl_806510A0;

extern int fn_80027948(); extern void fn_8002A4C8(void); extern void fn_8002A508(void);
extern void fn_8002A590(void); extern void fn_8002A754(void); extern void fn_8002AA18(void);
extern void fn_8002AC60(void); extern void* fn_80034708(); extern int fn_80047D6C();
extern int fn_800CC140(); extern int fn_800CCA44(); extern int fn_800DC2B8();
extern int fn_800DC398(); extern int fn_800DBF60(); extern int fn_8011ECF8();
extern int fn_8011F114(); extern int fn_8011FA8C(); extern int fn_8011FCB0();
extern int fn_8011FE3C(); extern int fn_801261F4(); extern int fn_80128E30();
extern int fn_8012B7A0(); extern int fn_8012C62C(); extern int fn_80147E88();
extern void* fn_80149E04(); extern int fn_80149B38(); extern int fn_8014A178();
extern int fn_80155DB4(); extern int fn_801568B8(); extern int fn_801568C0();
extern int fn_801568C8(); extern int fn_801568D8(); extern int fn_801568E4();
extern int fn_801568F0(); extern int fn_801568FC(); extern int fn_80156904();
extern int fn_8015690C(); extern int fn_80156918(); extern void* fn_80156DA0();
extern int fn_80156F80(); extern int fn_801570F8(); extern int fn_80157888(void*);
extern int fn_80157894(void*); extern int fn_801579F4(); extern int fn_80157B3C();
extern int fn_80157B60(); extern int fn_80157B80(); extern unsigned int fn_80157BD0();
extern int fn_80157BE8(); extern int fn_8015821C(); extern int fn_80158264();
extern int fn_80158550(); extern int fn_80158598(); extern int fn_801938FC();
extern int fn_801B05B0(); extern int fn_801CEB2C(); extern int fn_801D1318();
extern int fn_801D1C34(); extern int fn_801D1F78(); extern void fn_801D2FA4(GameObject*);
extern void fn_801D3024(void); extern void fn_801D3088(void); extern int fn_801D38E8();
extern int fn_801D3CAC(); extern int fn_801E2CF4(); extern int fn_801E6CA0();
extern int fn_801E8328(); extern int fn_801FDF74(); extern int fn_801FE22C();
extern int fn_801FE934(); extern int fn_802006D4(); extern void* fn_802015A4();
extern void* fn_80201814(); extern int fn_80201ADC(); extern void* fn_80201AE4();
extern void* fn_80201B54(); extern void* fn_80201BC8(); extern void* fn_80201C24(void*);
extern void* fn_80201C2C(void*); extern int fn_80201D24(); extern int fn_80201D54();
extern void* fn_80204A8C(); extern int fn_80204CE4(); extern int fn_80204E0C();
extern int fn_80204F54(); extern int fn_8020123C();

void fn_801D2440(GameObject* object)
{
    void* object_owner;
    void* info;
    void* data;
    int count;

    if (object->type != lbl_8064D18C) {
        void* actor;
        void* info;
        void* current;
        void* data;
        void* other;
        void* other_info;
        void* owner;
        void* result;
        void* target;
        int count;
        int value;

        actor = object->actorBC;
        info = fn_80201814(actor);
        current = fn_80201C24(info);
        if (fn_80157894(current) & 1) {
            target = (void*)fn_80201ADC();
            current = fn_80201C2C(target);
            if (object->stateFF4 <= 80) fn_80204E0C(info, current);
            else {
                other_info = fn_80201814(object->actorC0);
                fn_80204F54(info);
                fn_8020123C(57, actor, actor, 0);
                fn_80204E0C(other_info, current);
            }
        } else if (object->stateFF4 != 0) {
            owner = fn_80201AE4();
            target = (void*)fn_80201ADC();
            if (target != 0) {
                other = fn_80201C2C(target);
                data = (void*)fn_80155DB4(info);
                fn_80204E0C(info, other);
                count = fn_801579F4(current);
                if (count > 0) fn_80204E0C(fn_80201814((void*)count), other);
                fn_801568F0(data); fn_801568E4(data); fn_801568D8(data);
                result = fn_80201BC8(info);
                fn_8011FE3C(result, fn_80201BC8(target));
                fn_80156904(data, fn_8002A754);
                fn_80156F80(data, fn_80155DB4(target));
                value = fn_80158598(owner, 0);
                value = fn_80158264(value, current, 1);
                fn_800CC140(owner, actor, 0,
                             ((void**)*(void**)(*(void**)current))[value], 0);
            }
        }
        fn_801FE22C(object->resource44);
        if (object->handle != -1) fn_801B05B0(object->handle, 10);
        fn_801D2FA4(object);
        if (object->flagsFF0 & 0x10) fn_801D1318(0);
        return;
    }

    object_owner = object->owner;
    switch (object->stateFF4) {
    case 0: {
        void* actor;
        void* info;
        void* current;
        void* data;
        void* other;
        void* other_info;
        void* owner;
        void* result;
        void* target;
        int count;
        int value;
        int flag;
        int color;
        u8* payload;

        actor = object->actorBC; info = fn_80201814(actor); current = fn_80201C24(info);
        flag = fn_80157888(current); other = object->actorC4;
        count = fn_801579F4(current); other_info = fn_80201814((void*)count);
        if (flag & 1) {
            lbl_8064D558 = actor;
            value = fn_80158598(other, 0); value = fn_80158550(value, actor);
            fn_800CC140(other, actor, 0, value, 0); lbl_8064D558 = 0;
            fn_80204E0C(info, fn_80204A8C());
            if (count > 0) fn_80204E0C(other_info, fn_80204A8C());
        }
        data = (void*)fn_80155DB4(info);
        result = fn_80201BC8(info);
        fn_8011FE3C(result, result);
        fn_801568C0(data, fn_801D3024); fn_801568B8(data, fn_8002AC60);
        fn_801568FC(data, 0); fn_80156904(data, 0);
        if (count > 0) {
            result = (void*)fn_80155DB4(other_info);
            target = fn_80201BC8(other_info);
            fn_8011FE3C(target, target);
            fn_801568C0(result, fn_801D3024); fn_801568B8(result, fn_8002AC60);
            fn_801568FC(result, 0); fn_80156904(result, 0);
        }
        if ((int)other != (int)fn_80201AE4()) fn_801570F8(data, fn_80155DB4(fn_80201814(other)));
        payload = object->payloadC8; *(void**)(payload + 0xC0) = fn_80149E04();
        if (*(void**)(payload + 0xC0) == 0) break;
        fn_80147E88(payload); fn_8014A178(payload, *(void**)(payload + 0xC0));
        payload[0xBC] = 4; actor = object->owner; color = (u8)fn_801CEB2C(actor);
        *(u8*)*(void**)(payload + 0xC0) = color; fn_80149B38(*(void**)(payload + 0xC0));
        fn_801938FC(payload); *(u16*)(payload + 6) = 80;
        result = (void*)fn_801D38E8(actor); fn_801D3CAC(result, 0, payload + 0x14);
        payload[0x16] = 0; *(int*)(payload + 0x38) |= 0x4800;
        *(void**)(payload + 0xA8) = object->actorBC; payload[0xAC] = (u8)color;
        *(u16*)(payload + 0xAE) = 250; *(Vec3*)(payload + 0xB0) = object->position;
        fn_801D1F78(*(void**)(payload + 0xC0), payload + 0xAC, *(void**)(payload + 0xA8));
        fn_801E8328(17, payload); break;
    }
    case 20:
        fn_801FDF74(object->resource44, 0x7A120);
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 1, 15, 53, 4, 10, 15, 1, 1, 80); break;
    case 30:
        info = fn_80201814(object->actorBC); fn_8011FA8C(fn_80201BC8(info), 0, 0x10000);
        data = (void*)fn_80155DB4(info); fn_801568C0(data, fn_801D3088);
        count = fn_801579F4(fn_80201C24(info));
        if (count > 0) { data = (void*)fn_80155DB4(fn_80201814((void*)count)); fn_801568C0(data, fn_801D3088); }
        fn_801FE934(object->resource44, 9); break;
    case 40:
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 1, 15, 53, 4, 10, 15, 1, 2, 60); break;
    case 60:
        fn_801E2CF4(object, object->payloadC8, object->actorBC, 1, 15, 53, 4, 10, 15, 1, 3, 40); break;
    case 80: {
        void* actor;
        void* info;
        void* current;
        void* data;
        void* item;
        void* target;
        Vec3 point;
        Color a2;
        Color a1;
        Color a0;
        Color b2;
        Color b1;
        Color b0;
        u8 query[0x30];

        if ((int)object->actorC4 != (int)fn_80201AE4()) break;
        actor = object->actorBC; info = fn_80201814(actor); current = fn_80201C24(info);
        if (!(fn_80157894(current) & 1)) break;
        current = fn_80201BC8(info);
        a0 = lbl_80651090; a1 = lbl_8065108C; a2 = lbl_80651088;
        fn_8012C62C(current, 15, &a2, &a1, &a0, 4);
        fn_8011F114(&point, current); fn_801D1C34(query, actor, &point);
        item = fn_80034708(query); target = fn_80201BC8(item);
        if (target != 0) {
            fn_801261F4(target); fn_8012B7A0(target, *(float*)(query + 0xC));
            if (fn_8011FCB0(target)) fn_8011ECF8(target, fn_80128E30(target));
        }
        fn_80201D54(item, *(void**)(query + 0x2C)); fn_80201D24(item, 1);
        fn_802015A4(item); fn_800CCA44(item); data = fn_80156DA0(3, &point);
        if (data != 0) {
            void (*cb)(void);
            if (fn_8011FCB0(target)) cb = fn_8002A508;
            else cb = fn_8002A590;
            fn_801568C8(data, cb, fn_8002AC60, fn_8002AA18);
            fn_801568C0(data, fn_801D3088); fn_801568B8(data, fn_8002AC60);
            fn_801568FC(data, 0); fn_80156904(data, 0);
            fn_8015690C(data, fn_8002A4C8); fn_80156918(data, item);
        }
        b0 = lbl_8065109C; b1 = lbl_80651098; b2 = lbl_80651094;
        fn_8012C62C(target, 15, &b2, &b1, &b0, 4);
        fn_80204CE4(item, fn_80204A8C()); object->actorC0 = fn_80201B54(item); break;
    }
    case 100: {
        void* actor;
        void* info;
        void* current;
        void* data;
        void* other;
        void* other_info;
        void* result;
        void* target;
        int count;
        int value;
        int flag;
        int color;
        void* player;
        int effect;

        player = fn_80201AE4(); actor = object->actorBC; other = object->actorC4;
        info = fn_80201814(actor); data = (void*)fn_80155DB4(info); current = fn_80201C24(info);
        if ((int)other == (int)player) {
            flag = fn_80157888(current); fn_801568FC(data, fn_8002AA18);
            if (flag & 1) {
                fn_802006D4(actor, actor, -1, 75, 0);
                fn_80157B60(current, (u8)fn_801D38E8(object_owner));
                color = ((short)fn_801CEB2C(object_owner) >> 1) + 1;
                fn_80157B3C(current, (u8)color); fn_80157B80(current, 2); flag = 1;
                count = fn_801579F4(current);
                if (count > 0) {
                    other_info = fn_80201814((void*)count); target = fn_80201C24(other_info);
                    fn_802006D4((void*)count, (void*)count, -1, 75, 0);
                    fn_80157B60(target, (u8)fn_801D38E8(object_owner));
                    color = ((short)fn_801CEB2C(object_owner) >> 1) + 1;
                    fn_80157B3C(target, (u8)color);
                }
            } else {
                fn_80204F54(info); fn_8020123C(57, actor, actor, 0);
                actor = object->actorC0; info = fn_80201814(actor); current = fn_80201C24(info); flag = 0;
                if (fn_8015821C(current) == 131) {
                    value = (u8)fn_801D38E8(object_owner);
                    color = (u8)(((short)fn_801CEB2C(object_owner) >> 1) + 1);
                    fn_80157B60(current, value); fn_80157B3C(current, color);
                    fn_800DC398(color); fn_800DC2B8(actor, value, color);
                }
                fn_80157B80(current, 0x200);
            }
            if (object->id != (int)player && fn_80157BD0(current) == 18) value = 24;
            else value = fn_80157BE8(current);
            result = (void*)fn_801E6CA0(lbl_8064C504, 0, value, 0, 1);
            fn_80027948(result, 0, player, actor, flag, 0, 0);
        } else {
            effect = fn_80047D6C(); fn_802006D4(actor, actor, -1, 75, 0);
            fn_80157B60(current, (u8)fn_801D38E8(object_owner));
            color = (u8)(((short)fn_801CEB2C(object_owner) >> 1) + 1);
            fn_80157B3C(current, color); fn_800DBF60(other, info, color, effect, lbl_806510A0);
            fn_801568F0(data); fn_801568E4(data); fn_801568D8(data);
            result = fn_80201BC8(info); other_info = fn_80201814(other);
            fn_8011FE3C(result, fn_80201BC8(other_info));
            fn_80156904(data, fn_8002A754); fn_80156F80(data, fn_80155DB4(other_info));
            value = fn_80158598(other, 0); value = fn_80158264(value, current, 1);
            fn_800CC140(other, actor, 0,
                         ((void**)*(void**)(*(void**)current))[value], 0);
        }
        if (object->callback != 0) object->callback(object, object->callback_arg);
        fn_801D2FA4(object); break;
    }
    }
}
