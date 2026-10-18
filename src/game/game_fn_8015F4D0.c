typedef struct ObjectData {
    char pad0[0x18];
    unsigned int* entries;
} ObjectData;

typedef struct Object {
    ObjectData* data;
    char pad4[0xC];
    int count;
} Object;

typedef struct OuterObject {
    char pad0[0x28];
    Object* object;
} OuterObject;

typedef struct Command {
    int type;
    int first;
    int second;
} Command;

extern int discharge(Object*);
extern void luaK_setcallreturns(Object*, int);
extern int need_value(Object*, int, int);
extern void luaK_concat(Object*, int*, int);
extern int code_label(Object*, int, int);
extern void luaK_adjuststack(Object*, int);
extern int luaK_getlabel(Object*);
extern void luaK_patchlist(Object*, int, int);
extern void luaK_patchlistaux(Object*, int, int, int, int);

#pragma use_lmw_stmw on

void luaK_tostack(OuterObject* outer, Command* command, int finish)
{
    Object* object = outer->object;
    int type;
    int position;
    int extra_index;
    int second_index;
    int first_index;

    if (discharge(object) != 0) {
        return;
    }

    type = object->data->entries[object->count - 1] & 0x3F;
    if ((type < 32 || type > 42) && command->second == -1 &&
        command->first == -1) {
        if (finish != 0) {
            luaK_setcallreturns(object, 1);
        }
        return;
    }

    extra_index = -1;
    second_index = -1;
    first_index = -1;
    if (type < 32 || type > 42) {
        if (need_value(object, command->second, 41) == 0 &&
            need_value(object, command->first, 40) == 0) {
            goto emit;
        }
    }

    if (type >= 32 && type <= 42) {
        luaK_concat(object, &command->first, object->count - 1);
    } else {
        extra_index = code_label(object, 42, -1);
        luaK_adjuststack(object, 1);
    }

    second_index = code_label(object, 43, 0);
    first_index = code_label(object, 6, 1);
    luaK_patchlist(object, extra_index, luaK_getlabel(object));

emit:
    position = luaK_getlabel(object);
    luaK_patchlistaux(object, command->second, second_index, 41, position);
    luaK_patchlistaux(object, command->first, first_index, 40, position);
    command->first = -1;
    command->second = -1;
}
