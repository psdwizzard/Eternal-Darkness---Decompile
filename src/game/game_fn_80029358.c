typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct EventDesc {
    s32 a;
    s32 b;
    s32 c;
} EventDesc;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct RoomEntry {
    void* name;
    s32 kind;
    u8 pad08[4];
    s32 music;
    u8 pad10[4];
    s32 sound;
    u8 pad18[2];
    s8 bank;
    u8 pad1B;
    s16 ambient;
    s16 map;
    s16 transition;
    s16 target;
    u8 pad24[4];
} RoomEntry;

typedef struct TypeEntry {
    u8 pad00[0xC];
    s16 music;
    u8 pad0E[0xA];
} TypeEntry;

typedef struct WorldState {
    u8 pad00[0x1D0];
    s16 sound;
    s16 field_1D2;
    u8 pad1D4[6];
    u8 room;
    u8 pad1DB;
    s8 mode;
    s8 skip;
    u8 pad1DE[6];
    s8 field_1E4;
    u8 field_1E5;
    u8 field_1E6;
} WorldState;

typedef struct GameState {
    s32 f0;
    s32 f4;
    s32 f8;
    u8 pad0C[0x1908];
    u8 f1914;
} GameState;

typedef struct Resource {
    u8 pad00[0xA8];
    void* handle;
    u8 padAC[0x12];
    u8 flags;
    u8 padBF;
    void* data;
} Resource;

typedef struct ResourcePair {
    Resource first;
    Resource second;
} ResourcePair;

typedef struct ResourceHolder {
    u8 pad00[0xB0];
    Resource res;
} ResourceHolder;

typedef struct Counter {
    s32 value;
    u8 data[1];
} Counter;

typedef struct Actor Actor;

typedef struct Trigger {
    void* target;
    u8 pad04[0x60];
    void* handle;
    u8 pad68[4];
    void* object;
} Trigger;

extern EventDesc lbl_80238C70[7];
extern u8 lbl_8063CD18[];
extern WorldState lbl_8030F540;
extern GameState lbl_803003C8;
extern RoomEntry lbl_80241DE8[];
extern TypeEntry lbl_802417D0[];
extern void* lbl_8024E388[];
extern void* lbl_8064D1A0;
extern void* lbl_8064C4E4;
extern void* lbl_8064C4E0;
extern s32 lbl_8064B998;
extern s32 lbl_8064B810;
extern s32 lbl_8064C624;
extern const Color lbl_8064E000;
extern const Color lbl_80651900;

extern void* fn_801E8494(void);
extern void* fn_801E849C(void*);
extern s32 fn_801E84A4(void*);
extern void* fn_801E84AC(void*);
extern void fn_801E8430(void*);
extern void* fn_80201BC8(void*);
extern void fn_8011F114(EventDesc*, void*);
extern void* fn_80156DA0(s32, EventDesc*);
extern s32 fn_8011FCB0(void*);
extern void fn_801568C8(void*, void*, void*, void*);
extern void fn_80156904(void*, void*);
extern void fn_801568FC(void*, void*);
extern void fn_8015690C(void*, void*);
extern void fn_80156918(void*, void*);
extern void fn_801568C0(void*, void*);
extern void fn_801568B8(void*, void*);
extern void fn_800291A0(void*);
extern void* fn_80155DB4(void*);
extern void fn_80156FF4(void*);
extern void fn_8011E174(void*, s32);
extern void* fn_8015C28C(s32);
extern void fn_8015AC74(s32);
extern void fn_8015AC84(s32);
extern void fn_80132D50(void);
extern void fn_801E7974(void*, s32);
extern void fn_80237C28(void);
extern void fn_8015D5B0(void*);
extern void fn_801FA01C(void*, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void fn_801F8598(void);
extern void fn_801FA354(void);
extern void fn_801FA410(s32);
extern void fn_8011FABC(void*, s32, s32);
extern s32 fn_80008724(s32);
extern void fn_8015E5DC(s32, s32);
extern void fn_8001D9FC(s32);
extern void fn_80025A78(s32);
extern void* fn_800AD1D0(s32);
extern void fn_8004525C(void);
extern void fn_80045200(void*);
extern void fn_80043034(s32);
extern void fn_80042818(s32);
extern void* fn_80201BD0(void*);
extern s32 fn_80201B5C(void*);
extern void* fn_80201B8C(void*);
extern void* fn_80201890(void*);
extern void fn_8011F7E0(void*, s32);
extern void fn_8011FC38(void*, s32, s32);
extern void fn_8012B344(void*);
extern void fn_8011FE6C(void*);
extern void fn_8004736C(s32);
extern void fn_80144430(s32, s32);
extern void fn_80048620(s32);
extern void fn_801EF38C(s32);
extern s32 fn_801A98F4(s32, s32);
extern void fn_80046C98(s32);
extern void fn_800073DC(s32);
extern void fn_801F3528(Color*);
extern void fn_801F348C(Color*, s32);
extern void fn_8011B740(void);
extern void fn_801453FC(void);
extern s32 fn_800ACFE0(void);
extern void fn_800AD430(void);
extern void fn_8016B400(s32, s32, s32);
extern void* fn_80201ADC(void);
extern void fn_80156F80(void*, void*);
extern void* fn_80201814(void*);
extern void* fn_80148300(void*, Resource*, void*);
extern void fn_80149EB8(void*);
extern void fn_800073D8(s32);
extern void fn_80157438(s32, s32);
extern void* fn_80147EC4(void*);
extern void* fn_8018095C(void*);
extern s32 fn_801FD63C(void*);
extern void fn_8014C37C(void*, void*);
extern s32 fn_8014CB90(void*);
extern void fn_8020123C(void*, s32, void*, void*);
extern void fn_80036E8C(void*);
extern void fn_80201750(void*);
extern void fn_80052580(s32, s32, s32, s32, s32);
extern void fn_8001DA0C(void);
extern void fn_80052424(s32, s32, s32, s32);
extern s32 fn_80054844(s32, s32);
extern void fn_800B9454(s32, s32);
extern void fn_800E45F4(void);
extern void fn_801ACC94(s32);
extern void fn_801B2380(s32);
extern void fn_801AB154(void*);

extern s32 fn_8002A590(void*);
extern s32 fn_8002A508(void*);
extern s32 fn_8002A6CC(void*);
extern void fn_8002AC60(void);
extern s32 fn_8002AA18(void*, void*, s32);
extern void fn_8002A4C8(void*);
extern s32 fn_8002AB08(void*, void*, s32);
extern void fn_8002B624(void*);
extern void fn_8002B650(void*);
extern void fn_8002F428(void*, void*);
extern void fn_801487AC(void*);

void fn_80029358(void)
{
    void* data;
    s32 type;
    s32 loaded;
    void* next;
    void* node;
    EventDesc* descs;

    loaded = 0;
    descs = lbl_80238C70;
    for (node = fn_801E849C(fn_801E8494()); node != 0; node = next) {
        type = fn_801E84A4(node);
        next = fn_801E849C(node);
        data = fn_801E84AC(node);

        switch (type) {
        case 1:
        case 29: {
            EventDesc desc;
            void* object;
            void* event;

            object = fn_80201BC8((void*)data);
            fn_8011F114(&desc, object);
            event = fn_80156DA0(3, &desc);
            if (event != 0) {
                fn_801568C8(event, fn_8011FCB0(object) != 0 ? fn_8002A508 : fn_8002A590,
                            fn_8002AC60, fn_8002AA18);
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AA18);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, (void*)data);
            }
            if (type == 29) {
                fn_800291A0((void*)data);
            }
            break;
        }

        case 3: {
            EventDesc desc;
            void* object;
            void* event;

            object = fn_80201BC8((void*)data);
            fn_8011F114(&desc, object);
            event = fn_80156DA0(3, &desc);
            if (event != 0) {
                fn_801568C8(event, fn_8002A590, fn_8002AC60, fn_8002AA18);
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AA18);
                fn_801568C0(event, fn_8002A590);
                fn_801568B8(event, fn_8002AC60);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, (void*)data);
            }
            break;
        }

        case 15: {
            EventDesc desc;
            void* object;
            void* event;

            object = fn_80201BC8((void*)data);
            fn_8011F114(&desc, object);
            event = fn_80156DA0(3, &desc);
            if (event != 0) {
                fn_801568C8(event, fn_8002A6CC, fn_8002AC60, fn_8002AA18);
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AA18);
                fn_801568C0(event, fn_8002A6CC);
                fn_801568B8(event, fn_8002AC60);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, (void*)data);
            }
            break;
        }

        case 2: {
            void* event = fn_80155DB4((void*)data);
            if (event != 0) {
                fn_80156FF4(event);
            }
            break;
        }

        case 30:
            fn_8011E174((void*)data, 0);
            break;

        case 23: {
            RoomEntry* room;
            s8 bank;
            s16 transition;
            void* object;

            fn_8015C28C(2);
            fn_8015AC74(1);
            fn_8015AC84(1);
            fn_80132D50();

            room = &lbl_80241DE8[lbl_8030F540.room];
            if (room->ambient != -1 && lbl_8030F540.mode != 1) {
                bank = room->bank;
                if (bank == -1) {
                    bank = 0;
                }
                fn_801E7974(lbl_8024E388[bank], room->ambient);
            }

            room = &lbl_80241DE8[lbl_8030F540.room];
            transition = room->transition;
            if (transition != -1 && lbl_8030F540.field_1E4 == 0) {
                s16 target = room->target;
                if (transition == 1) {
                    s16 music = lbl_802417D0[target].music;
                    if (music != -1 && music != 0x3C) {
                        fn_80237C28();
                    }
                } else {
                    s32 music = lbl_80241DE8[target].music;
                    if (music != -1 && music != 0x3C) {
                        fn_80237C28();
                    }
                }
            } else {
                fn_80237C28();
            }

            fn_8015D5B0(lbl_8064D1A0);
            fn_801FA01C(lbl_8063CD18 + 0x110, 0, 0, 0, 0, 0, 0, 1, 0, 1);
            fn_801F8598();
            fn_801FA354();
            fn_801FA410(2);
            loaded = 1;
            if (lbl_8064C4E4 != 0) {
                fn_8011FABC(lbl_8064C4E4, 0x2000, 0);
            }

            {
                u8 id = lbl_8030F540.room;
                if (lbl_80241DE8[id].map != -1 && lbl_8030F540.mode == 0 &&
                    (lbl_803003C8.f1914 != 0 || id == 0x60 || id == 0x57 ||
                     id == 0x83 || id == 0x84)) {
                    if (id == 0x49 || id == 0x4A || id == 0x4B) {
                        fn_8015E5DC(1, fn_80008724(lbl_803003C8.f0));
                    } else {
                        fn_8015E5DC(0, fn_80008724(lbl_803003C8.f0));
                    }
                } else {
                    fn_8015E5DC(1, fn_80008724(lbl_803003C8.f0));
                }
            }

            if (lbl_8030F540.mode == 2) {
                fn_8001D9FC(3);
            } else {
                if ((lbl_8030F540.room == 0x5B || lbl_8030F540.room == 0x61 ||
                     lbl_8030F540.room == 0x62) &&
                    lbl_8030F540.mode == 0) {
                    fn_80025A78(3);
                } else {
                    fn_8001D9FC(2);
                }
                if ((lbl_8030F540.room == 0x91 || lbl_8030F540.room == 0xA8 ||
                     lbl_8030F540.room == 0xA7) &&
                    lbl_8030F540.mode == 0) {
                    void* save = fn_800AD1D0(0);
                    fn_8004525C();
                    fn_80045200(save);
                }
            }

            if (lbl_8030F540.mode == 0) {
                if (lbl_8030F540.room == 0x49 || lbl_8030F540.room == 0x4A ||
                    lbl_8030F540.room == 0x4B) {
                    fn_80043034(0xA1BEEF);
                } else if (lbl_80241DE8[lbl_8030F540.room].map != -1 &&
                           lbl_8030F540.mode == 0 &&
                           (lbl_803003C8.f1914 != 0 || lbl_8030F540.room == 0x60 ||
                            lbl_8030F540.room == 0x57 || lbl_8030F540.room == 0x83 ||
                            lbl_8030F540.room == 0x84)) {
                    fn_80043034(0);
                    fn_80042818(lbl_803003C8.f8);
                }
            }

            if ((object = fn_80201BD0(lbl_8064C4E4)) != 0 && fn_80201B5C(object) == 0x32) {
                object = fn_80201890(*(void**)(*(u8**)((u8*)fn_80201B8C(
                    fn_80201BD0(lbl_8064C4E4)) + 0x8C) + 0xBC));
                if (object != 0) {
                    fn_8011F7E0(object, 0);
                    fn_8011FC38(object, 0, 1);
                    fn_8012B344(object);
                    fn_8011FE6C(object);
                }
            }

            if (lbl_8030F540.room == 0 && lbl_8030F540.mode == 0) {
                lbl_803003C8.f8 = 0;
                fn_8004736C(0);
            }
            fn_80144430(2, 0);
            fn_80048620(0);
            if (lbl_8030F540.room != 0x56) {
                fn_8004736C(lbl_8030F540.field_1E5);
                fn_801EF38C(lbl_8030F540.field_1E6);
                if (lbl_8030F540.field_1E6 != 0) {
                    fn_801E7974(lbl_8064C4E0, 0x2ED);
                    lbl_8064B998 = fn_801A98F4(0x1FD, 0x64);
                }
            }
            lbl_8064B810 = 1;
            fn_80046C98(1);
            fn_800073DC(3);
            if (lbl_8030F540.room != 0x52 && lbl_8030F540.room != 0xA3 &&
                lbl_8030F540.room != 0xA4 && lbl_8030F540.room != 0x60) {
                Color color = lbl_8064E000;
                Color fog;
                fn_801F3528(&color);
                fog = lbl_80651900;
                fn_801F348C(&fog, 10);
            }
            fn_8011B740();
            fn_801453FC();
            if (lbl_803003C8.f8 == 0xD && fn_800ACFE0() < 5) {
                fn_800AD430();
            }

            if (lbl_8030F540.mode == 0) {
                RoomEntry* entry = &lbl_80241DE8[lbl_8030F540.room];
                s32 kind = entry->kind;
                if (kind != 0x60 && kind != 0 && kind != 0x49 && kind != 0x4A &&
                    kind != 0x4B && kind != 0x57 && kind != 0x83 && kind != 0x84 &&
                    entry->map != -1 && lbl_803003C8.f1914 == 0) {
                    fn_80025A78(1);
                    return;
                }
            }
            break;
        }

        case 24:
            fn_8016B400((s16)(u32)data, 0, 0);
            break;

        case 4: {
            Actor* owner = (Actor*)data;
            EventDesc desc = descs[0];
            void* event = fn_80156DA0(7, &desc);
            if (event != 0) {
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AA18);
                fn_801568B8(event, fn_8002B624);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, owner);
            }
            break;
        }

        case 21: {
            Actor* owner = (Actor*)data;
            EventDesc desc = descs[1];
            void* event = fn_80156DA0(7, &desc);
            if (event != 0) {
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AB08);
                fn_801568B8(event, 0);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, owner);
            }
            break;
        }

        case 31: {
            Actor* owner = (Actor*)data;
            EventDesc desc = descs[2];
            void* event = fn_80156DA0(7, &desc);
            void* list;
            if (event != 0) {
                fn_801568FC(event, fn_8002AB08);
                fn_801568B8(event, 0);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, owner);
                list = fn_80155DB4(fn_80201ADC());
                fn_80156904(event, fn_8002F428);
                fn_80156F80(event, list);
            }
            break;
        }

        case 11: {
            Actor* owner = (Actor*)data;
            EventDesc desc = descs[3];
            void* event = fn_80156DA0(7, &desc);
            if (event != 0) {
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AB08);
                fn_801568B8(event, 0);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, owner);
            }
            break;
        }

        case 13: {
            Actor* owner = (Actor*)data;
            EventDesc desc = descs[4];
            void* event = fn_80156DA0(7, &desc);
            if (event != 0) {
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AB08);
                fn_801568B8(event, 0);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, owner);
            }
            break;
        }

        case 7: {
            Actor* owner = (Actor*)data;
            EventDesc desc = descs[5];
            void* event = fn_80156DA0(7, &desc);
            if (event != 0) {
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AB08);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, owner);
            }
            break;
        }

        case 9: {
            Actor* owner = (Actor*)data;
            EventDesc desc = descs[6];
            void* event = fn_80156DA0(7, &desc);
            if (event != 0) {
                fn_80156904(event, 0);
                fn_801568FC(event, fn_8002AB08);
                fn_801568B8(event, fn_8002B650);
                fn_8015690C(event, fn_8002A4C8);
                fn_80156918(event, owner);
            }
            break;
        }

        case 6: {
            ResourcePair* pair = (ResourcePair*)data;
            u8 release = 0;
            void* handle;
            void* owner;

            handle = fn_80201814(pair->first.handle);
            if (handle != 0) {
                owner = fn_80148300(fn_80155DB4(handle), &pair->first, pair->first.data);
                if (owner != 0) {
                    if (fn_80148300(owner, &pair->second, pair->second.data) == 0) {
                        fn_80156FF4(owner);
                        fn_80149EB8(pair->second.data);
                        pair->second.data = 0;
                    }
                } else {
                    release = 1;
                }
            } else {
                release = 1;
            }
            if (release) {
                fn_80149EB8(pair->first.data);
                pair->first.data = 0;
                fn_80149EB8(pair->second.data);
                pair->second.data = 0;
            }
            break;
        }

        case 17: {
            Resource* res = (Resource*)data;
            void* handle;
            void* owner;

            if (res == 0) {
                break;
            }
            handle = fn_80201814(res->handle);
            if (handle != 0) {
                owner = fn_80155DB4(handle);
                if (owner == 0) {
                    fn_800073D8(-1);
                    fn_80157438(9, 0);
                    fn_80149EB8(res->data);
                    res->data = 0;
                } else {
                    res->flags = 0x80;
                    if (fn_80148300(owner, res, res->data) == 0) {
                        fn_80149EB8(res->data);
                        res->data = 0;
                    }
                }
            } else {
                fn_80149EB8(res->data);
                res->data = 0;
            }
            break;
        }

        case 16:
            fn_80147EC4((void*)data);
            break;

        case 18: {
            Resource* res = (Resource*)data;
            void* owner = 0;
            void* handle;

            handle = fn_8018095C(res->handle);
            if (handle != 0) {
                owner = fn_80155DB4(handle);
            }
            if (owner != 0) {
                if (fn_80148300(owner, res, res->data) == 0) {
                    fn_80149EB8(res->data);
                    res->data = 0;
                }
            } else {
                fn_80149EB8(res->data);
                res->data = 0;
            }
            break;
        }

        case 22: {
            ResourceHolder* holder = (ResourceHolder*)data;
            void* owner = fn_80147EC4(holder);
            if (owner != 0) {
                if (fn_80148300(owner, &holder->res, holder->res.data) == 0) {
                    fn_80149EB8(holder->res.data);
                    holder->res.data = 0;
                }
            } else {
                fn_80149EB8(holder->res.data);
                holder->res.data = 0;
            }
            break;
        }

        case 25: {
            ResourceHolder* holder = (ResourceHolder*)data;
            void* owner = fn_80147EC4(holder);
            if (owner != 0) {
                void* event = fn_80148300(owner, &holder->res, holder->res.data);
                if (event != 0) {
                    fn_801568B8(event, fn_801487AC);
                } else {
                    fn_80149EB8(holder->res.data);
                    holder->res.data = 0;
                }
            } else {
                fn_80149EB8(holder->res.data);
                holder->res.data = 0;
            }
            break;
        }

        case 26: {
            Resource* res = (Resource*)data;
            void* owner = 0;
            void* handle;

            handle = fn_8018095C(res->handle);
            if (handle != 0) {
                owner = fn_80155DB4(handle);
            }
            if (owner != 0) {
                void* event = fn_80148300(owner, res, res->data);
                if (event != 0) {
                    fn_801568B8(event, fn_801487AC);
                } else {
                    fn_80149EB8(res->data);
                    res->data = 0;
                }
            } else {
                fn_80149EB8(res->data);
                res->data = 0;
            }
            break;
        }

        case 27: {
            ResourcePair* pair = (ResourcePair*)data;
            void* handle;
            void* owner;

            handle = fn_80201814(pair->first.handle);
            if (handle != 0) {
                owner = fn_80148300(fn_80155DB4(handle), &pair->first, pair->first.data);
                if (owner != 0) {
                    void* event = fn_80148300(owner, &pair->second, pair->second.data);
                    if (event != 0) {
                        fn_801568B8(event, fn_801487AC);
                    } else {
                        fn_80156FF4(owner);
                        fn_80149EB8(pair->second.data);
                        pair->second.data = 0;
                    }
                } else {
                    fn_80149EB8(pair->first.data);
                    pair->first.data = 0;
                    fn_80149EB8(pair->second.data);
                    pair->second.data = 0;
                }
            } else {
                fn_80149EB8(pair->first.data);
                pair->first.data = 0;
                fn_80149EB8(pair->second.data);
                pair->second.data = 0;
            }
            break;
        }

        case 32: {
            Counter* counter = (Counter*)data;
            if (counter != 0) {
                counter->value = fn_801FD63C(counter->data);
            }
            break;
        }

        case 19:
            if (data != 0) {
                fn_8014C37C(0, (void*)data);
            }
            break;

        case 20: {
            Trigger* trigger = (Trigger*)data;
            void* handle = trigger->handle;
            void* owner;

            if ((owner = fn_80201814(handle)) != 0) {
                owner = fn_80155DB4(owner);
                if (owner != 0) {
                    void* target;
                    fn_8014C37C(owner, trigger);
                    target = trigger->target;
                    if (target != 0) {
                        void* object = trigger->object;
                        if (fn_8014CB90(object) != 0) {
                            fn_8020123C(object, 0, handle, target);
                        }
                    }
                }
            }
            break;
        }

        case 28: {
            Actor* object = (Actor*)data;
            fn_80036E8C(object);
            fn_80201750(object);
            break;
        }
        }

        fn_801E8430(node);
    }

    if (loaded != 0) {
        WorldState* state = &lbl_8030F540;
        s8 mode = lbl_8030F540.mode;

        if (state->skip != 1) {
            if (mode == 0) {
                if (state->sound != -1) {
                    fn_8016B400(state->sound, 0, 0);
                    state->sound = -1;
                } else if (lbl_80241DE8[lbl_8030F540.room].sound != -1) {
                    fn_8016B400(lbl_80241DE8[lbl_8030F540.room].sound, 0, 0);
                }
            } else if (mode != 0) {
                s16 transition = lbl_80241DE8[lbl_8030F540.room].transition;
                if (transition == 1) {
                    fn_80052580(2, lbl_80241DE8[lbl_8030F540.room].target, 1, -1, 0);
                    fn_8001DA0C();
                } else if (transition == 0) {
                    fn_8001DA0C();
                    fn_80052424(lbl_80241DE8[lbl_8030F540.room].target, -1, 0, 0);
                } else if (fn_80054844(0, 1) == 0) {
                    fn_800B9454(0x20, 0);
                    lbl_8030F540.mode = 0;
                    lbl_8030F540.field_1D2 = 0;
                }
            }
            fn_800E45F4();
        }

        if (lbl_8064C624 != 6 && lbl_8064C624 != 4) {
            void* scene = fn_8015C28C(2);
            fn_801ACC94(1);
            fn_801B2380(1);
            fn_801AB154(scene);
        }
    }
}
