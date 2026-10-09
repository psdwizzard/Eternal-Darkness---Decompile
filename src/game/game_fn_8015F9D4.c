/* Lua 4.0 lcode.c: luaK_code */

typedef unsigned long Instruction;

typedef struct Proto {
    char pad0[0x18];
    Instruction* code;
} Proto;

typedef struct FuncState {
    Proto* f;
    char pad4[8];
    void* L;
    int pc;
} FuncState;

typedef struct OpProperties {
    signed char mode;
    unsigned char push;
    unsigned char pop;
} OpProperties;

enum Mode { iO, iU, iS, iAB };

enum OpCode {
    OP_END, OP_RETURN, OP_CALL, OP_TAILCALL, OP_PUSHNIL, OP_POP, OP_PUSHINT,
    OP_PUSHSTRING, OP_PUSHNUM, OP_PUSHNEGNUM, OP_PUSHUPVALUE, OP_GETLOCAL,
    OP_GETGLOBAL, OP_GETTABLE, OP_GETDOTTED, OP_GETINDEXED, OP_PUSHSELF,
    OP_CREATETABLE, OP_SETLOCAL, OP_SETGLOBAL, OP_SETTABLE, OP_SETLIST,
    OP_SETMAP, OP_ADD, OP_ADDI, OP_SUB, OP_MULT, OP_DIV, OP_POW, OP_CONCAT,
    OP_MINUS, OP_NOT, OP_JMPNE, OP_JMPEQ, OP_JMPLT, OP_JMPLE, OP_JMPGT,
    OP_JMPGE, OP_JMPT, OP_JMPF, OP_JMPONT, OP_JMPONF, OP_JMP, OP_PUSHNILJMP,
    OP_FORPREP, OP_FORLOOP, OP_LFORPREP, OP_LFORLOOP, OP_CLOSURE
};

#define NO_JUMP (-1)
#define MAX_INT (0x7FFFFFFF - 2)

#define SIZE_OP 6
#define SIZE_B 9
#define POS_U SIZE_OP
#define POS_B SIZE_OP
#define POS_A (SIZE_OP + SIZE_B)
#define MAXARG_S 0x1FFFFFF

#define MASK1(n, p) ((~((~(Instruction)0) << n)) << p)
#define MASK0(n, p) (~MASK1(n, p))

#define CREATE_0(o) ((Instruction)(o))
#define GET_OPCODE(i) ((int)((i) & MASK1(SIZE_OP, 0)))
#define SET_OPCODE(i, o) ((i) = (((i) & MASK0(SIZE_OP, 0)) | (Instruction)(o)))

#define CREATE_U(o, u) ((Instruction)(o) | ((Instruction)(u) << POS_U))
#define GETARG_U(i) ((int)((i) >> POS_U))
#define SETARG_U(i, u) ((i) = (((i) & MASK1(SIZE_OP, 0)) | ((Instruction)(u) << POS_U)))

#define CREATE_S(o, s) CREATE_U((o), (s) + MAXARG_S)
#define GETARG_S(i) (GETARG_U(i) - MAXARG_S)
#define SETARG_S(i, s) SETARG_U((i), (s) + MAXARG_S)

#define CREATE_AB(o, a, b) ((Instruction)(o) | ((Instruction)(a) << POS_A) | ((Instruction)(b) << POS_B))
#define GETARG_B(i) ((int)(((i) >> POS_B) & (~((~(Instruction)0) << SIZE_B))))
#define SETARG_B(i, b) ((i) = (((i) & MASK0(SIZE_B, POS_B)) | ((Instruction)(b) << POS_B)))

#define MULT_RET 255

extern OpProperties lbl_8024F3AC[];
extern char lbl_8024F2D4[];
extern Instruction fn_8015EAA0(FuncState*);
extern void fn_8015EC60(FuncState*, int);
extern void fn_8015F8B4(FuncState*);
extern Instruction* fn_8016393C(void*, Instruction*, int, int, int, const char*, int);

int fn_8015F9D4(FuncState* fs, int o, int arg1, int arg2)
{
    Instruction i = fn_8015EAA0(fs);
    int delta = lbl_8024F3AC[o].push - lbl_8024F3AC[o].pop;
    int optm = 0;

    switch (o) {
    case OP_CLOSURE:
        delta = -arg2 + 1;
        break;
    case OP_SETTABLE:
        delta = -arg2;
        break;
    case OP_SETLIST:
        if (arg2 == 0)
            return NO_JUMP;
        delta = -arg2;
        break;
    case OP_SETMAP:
        if (arg1 == 0)
            return NO_JUMP;
        delta = -2 * arg1;
        break;
    case OP_RETURN:
        if (GET_OPCODE(i) == OP_CALL && GETARG_B(i) == MULT_RET) {
            SET_OPCODE(i, OP_TAILCALL);
            SETARG_B(i, arg1);
            optm = 1;
        }
        break;
    case OP_PUSHNIL:
        if (arg1 == 0)
            return NO_JUMP;
        delta = arg1;
        switch (GET_OPCODE(i)) {
        case OP_PUSHNIL:
            SETARG_U(i, GETARG_U(i) + arg1);
            optm = 1;
            break;
        default:
            break;
        }
        break;
    case OP_POP:
        if (arg1 == 0)
            return NO_JUMP;
        delta = -arg1;
        switch (GET_OPCODE(i)) {
        case OP_SETTABLE:
            SETARG_B(i, GETARG_B(i) + arg1);
            optm = 1;
            break;
        default:
            break;
        }
        break;
    case OP_GETTABLE:
        switch (GET_OPCODE(i)) {
        case OP_PUSHSTRING:
            SET_OPCODE(i, OP_GETDOTTED);
            optm = 1;
            break;
        case OP_GETLOCAL:
            SET_OPCODE(i, OP_GETINDEXED);
            optm = 1;
            break;
        default:
            break;
        }
        break;
    case OP_ADD:
        switch (GET_OPCODE(i)) {
        case OP_PUSHINT:
            SET_OPCODE(i, OP_ADDI);
            optm = 1;
            break;
        default:
            break;
        }
        break;
    case OP_SUB:
        switch (GET_OPCODE(i)) {
        case OP_PUSHINT:
            i = CREATE_S(OP_ADDI, -GETARG_S(i));
            optm = 1;
            break;
        default:
            break;
        }
        break;
    case OP_CONCAT:
        delta = -arg1 + 1;
        switch (GET_OPCODE(i)) {
        case OP_CONCAT:
            SETARG_U(i, GETARG_U(i) + 1);
            optm = 1;
            break;
        default:
            break;
        }
        break;
    case OP_MINUS:
        switch (GET_OPCODE(i)) {
        case OP_PUSHINT:
            SETARG_S(i, -GETARG_S(i));
            optm = 1;
            break;
        case OP_PUSHNUM:
            SET_OPCODE(i, OP_PUSHNEGNUM);
            optm = 1;
            break;
        default:
            break;
        }
        break;
    case OP_JMPNE:
        if (i == CREATE_U(OP_PUSHNIL, 1)) {
            i = CREATE_S(OP_JMPT, NO_JUMP);
            optm = 1;
        }
        break;
    case OP_JMPEQ:
        if (i == CREATE_U(OP_PUSHNIL, 1)) {
            i = CREATE_0(OP_NOT);
            delta = -1;
            optm = 1;
        }
        break;
    case OP_JMPT:
    case OP_JMPONT:
        switch (GET_OPCODE(i)) {
        case OP_NOT:
            i = CREATE_S(OP_JMPF, NO_JUMP);
            optm = 1;
            break;
        case OP_PUSHINT:
            if (o == OP_JMPT) {
                i = CREATE_S(OP_JMP, NO_JUMP);
                optm = 1;
            }
            break;
        case OP_PUSHNIL:
            if (GETARG_U(i) == 1) {
                fs->pc--;
                fn_8015EC60(fs, -1);
                return NO_JUMP;
            }
            break;
        default:
            break;
        }
        break;
    case OP_JMPF:
    case OP_JMPONF:
        switch (GET_OPCODE(i)) {
        case OP_NOT:
            i = CREATE_S(OP_JMPT, NO_JUMP);
            optm = 1;
            break;
        case OP_PUSHINT:
            fs->pc--;
            fn_8015EC60(fs, -1);
            return NO_JUMP;
        case OP_PUSHNIL:
            if (GETARG_U(i) == 1) {
                i = CREATE_S(OP_JMP, NO_JUMP);
                optm = 1;
            }
            break;
        default:
            break;
        }
        break;
    case OP_GETDOTTED:
    case OP_GETINDEXED:
    case OP_TAILCALL:
    case OP_ADDI:
        break;
    default:
        break;
    }
    fn_8015EC60(fs, delta);
    if (optm) {
        fs->f->code[fs->pc - 1] = i;
        return fs->pc - 1;
    }
    switch ((enum Mode)lbl_8024F3AC[o].mode) {
    case iO: i = CREATE_0(o); break;
    case iU: i = CREATE_U(o, arg1); break;
    case iS: i = CREATE_S(o, arg1); break;
    case iAB: i = CREATE_AB(o, arg1, arg2); break;
    }
    fn_8015F8B4(fs);
    fs->f->code = fn_8016393C(fs->L, fs->f->code, fs->pc, 1, sizeof(Instruction),
                              lbl_8024F2D4, MAX_INT);
    fs->f->code[fs->pc] = i;
    return fs->pc++;
}
