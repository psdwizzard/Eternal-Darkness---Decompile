/*
 * Original translation unit (its __FILE__ string is "SKtest.c"): script-command
 * handlers and the script allocator, one compilation unit so the -str reuse
 * pool forms with the retail layout. Functions 0x8016BD0C..0x80171D6C.
 * Compiled without -inline auto: the original unit never cross-inlined.
 * The lbl_8024FE60..FEF4 strings belong to the preceding unit and stay extern.
 */

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
/* unified script-VM types reconstructed across the TU */
typedef struct Value {
    union {
        double first;
        int type;
    };
    union {
        void* pointer;
        void** pointer2;
        double number;
        double second;
        void* value;
    };
} Value;

typedef struct Entry {
    Value value;
    int next;
    int pad14;
} Entry;

typedef struct RefEntry {
    s16 id;
    u16 value2;
    u16 value4;
    u16 value6;
} RefEntry;

typedef struct Context {
    void* current;
    char pad04[4];
    void* end;
    char pad0C[0x40];
    union {
        int limit;
        char pad4C[4];
    };
    union {
        struct { Entry* entries; int count; int free; char pad5C[4]; int allocated_size; };
        struct { char pad50[0xC]; int limit_5C; char pad60[4]; };
    };
} Context;

typedef unsigned long size_t;
typedef struct Pair {
    const char* name;
    void* value;
} Pair;
typedef signed short s16;
typedef unsigned short u16;
typedef struct Pair Pair;
typedef unsigned int u32;
typedef void (*Callback)(Context*, int, void*);
typedef unsigned char u8;
typedef struct DVDFileInfo {
    u8 data[0x3C];
} DVDFileInfo;
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;
typedef struct ShortVec3 {
    short x;
    short y;
    short z;
} ShortVec3;
typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;
typedef struct StringBlock {
    char argument_error[0x190];
    char facing_format[0xC];
    char resource_error[0x1C];
    char object_error[1];
} StringBlock;
typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;
typedef struct TargetOwner {
    unsigned char padding[0x110];
    unsigned char target;
} TargetOwner;
typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;
struct ErrorStrings {
    char argument_count;
    char pad_001[0x343];
    char object_not_found[0x1C];
    char component_not_found[1];
};

  int fn_8016A5F4(void* context, int index);
 void* fn_8016A628(void* context, int index);
 int fn_8016A650(void* context, int index);
  double fn_8016A694(void* context, int index);
  void* fn_8016A700(void* context, int index);
  void* fn_8016A784(void* context, int index);
   void fn_8016A7D8(Context* context);
   void fn_8016A830(Context* context, double value);
   void fn_8016A890(Context* context, const char* string, int length);
  void fn_8016A8F8(void* context, const char* string);
 void fn_8016A950(void* context, void* unused1, int unused2);
   void fn_8016A970(Context* context, void* value, int index);
   void fn_8016AA34(Context* context, const char* name);
   void fn_8016AAB4(Context* context);
  void fn_8016AB20(Context* context, const char* name);
    int fn_8016AB6C(Context* context, int special);
  void fn_8016AC68(Context* context, int value);
   void fn_8016ACAC(Context* context, Pair* pairs, int count);
   void fn_8016AD28(void);
   void fn_8016ADF0(s16 id, s16 value2, s16 value4);
   void fn_8016AF2C(void);
   void fn_8016AFB0(s16 id);
   void fn_8016B030(int clear_all);
   void fn_8016B0B4(s16 id, int value);
 int fn_8016B1D0(void* output);
 int fn_8016B21C(void* input);
  void fn_8016B26C(Pair* pairs, int count);
   void fn_8016B29C(u32 size, Callback callback);
  void* fn_8016B3A4(void* value, int alternate);
   void fn_8016B400(int id, void* context, void* value);
 int fn_8016B4B4(void* data, void* size, char* name, void* context, void* value);
  void* fn_8016B5CC(void* context, void* allocation, int size, const char* file, int line);
  void fn_8016B914(int checkpoint);
 void* fn_8016BA38(int index);
double fn_8016BA4C(signed char* text, signed char** end);
 int fn_8016BD0C(void* state);
 int fn_8016BDD8(void* state);
 int fn_8016BE1C(void* state);
 int fn_8016BEC8(void* state);
 int fn_8016BF60(void* state);
 int fn_8016C008(void* state);
 int fn_8016C0BC(void* state);
 int fn_8016C164(void* state);
  int fn_8016C238(void* state);
  int fn_8016C3B4(void* state);
  int fn_8016C4BC(void* state);
 int fn_8016C668(void* state);
 int fn_8016C6EC(void* state);
 int fn_8016C774(void* state);
 int fn_8016C7C4(void* state);
 int fn_8016C890(void* state);
 int fn_8016C96C(void* state);
 int fn_8016CA2C(void* state);
 int fn_8016CB24(void* state);
 int fn_8016CBFC(void* state);
 int fn_8016CDA0(void* state);
 int fn_8016CE48(void* state);
 int fn_8016CEF0(void* state);
 int fn_8016D040(void* state);
 int fn_8016D0D4(void* state);
 int fn_8016D144(void* state);
 int fn_8016D1F8(void* state);
 int fn_8016D2B8(void* state);
int fn_8016D480(void* state);
 int fn_8016D574(void* state);
 int fn_8016D680(void* state);
 int fn_8016D7AC(void* state);
 int fn_8016D8A4(void* state);
 int fn_8016D92C(void* state);
 void fn_8016D9C0(unsigned int type, u16* first, u16* second);
  int fn_8016DA80(void* state);
  int fn_8016DB38(void* state);
 int fn_8016DBF0(void* state);
 int fn_8016DCB0(void* state);
 int fn_8016DD70(void);
 int fn_8016DD94(void* state);
 int fn_8016DE30(void* state);
 int fn_8016DECC(void* state);
 int fn_8016DF4C(void* state);
 void fn_8016E254(int value);
   int fn_8016E294(void* state);
 int fn_8016E3F0(void* state);
 int fn_8016E514(void* state);
 int fn_8016E5A8(void* state);
 int fn_8016E634(void* state);
 int fn_8016E6D4(void* state);
 int fn_8016E7B8(void* state);
 int fn_8016E854(void* state);
 int fn_8016E8C4(void* state);
   int fn_8016E8F8(void* state, int alternate);
 int fn_8016EACC(void* state);
 int fn_8016EAF4(void* state);
 int fn_8016EB1C(void* state);
 int fn_8016EC50(void* state);
 int fn_8016ED78(void* state);
 int fn_8016EEE4(void* state);
 int fn_8016EFC4(void* state);
 int fn_8016F088(void* state);
 int fn_8016F128(void* state);
 int fn_8016F1D0(void* state);
  int fn_8016F2AC(void* state);
    int fn_8016F400(void* state);
 int fn_8016F4CC(void* state);
 int fn_8016F580(void* state);
 int fn_8016F678(void* state);
 int fn_8016F78C(void* state);
  int fn_8016F8F8(void* state);
 int fn_8016FA08(void* state);
 int fn_8016FB94(void* state);
 int fn_8016FC68(void* state);
 int fn_8016FD3C(void* state);
 int fn_8016FE4C(void* state);
 int fn_8016FEF8(void* state);
 int fn_8016FFA8(void* first, void* second);
  int fn_8016FFDC(void* state);
  int fn_80170090(void* state);
  int fn_80170144(void* state);
  int fn_801701D4(void* state);
  int fn_8017026C(void* state);
  int fn_801702FC(void* state);
 int fn_8017038C(void* state);
 int fn_80170438(void* state);
 int fn_801704F8(void* state);
 int fn_801705D4(void* state);
 int fn_80170658(void* state);
 int fn_801706DC(void* state);
 int fn_80170814(void* state);
 int fn_80170880(void* state);
  int fn_80170980(void* state);
   int fn_80170A40(void* state);
  int fn_80170B5C(void* state);
 int fn_80170C18(void* state);
 int fn_80170C84(void* state);
 int fn_80170D04(void* state);
 int fn_80170DF4(void* state);
 int fn_80170E9C(void* state);
 int fn_80170F44(void* state);
 int fn_80171020(void* state);
 int fn_801710FC(void* state);
    int fn_801711D0(void* state);
 int fn_8017138C(void* state);
 int fn_80171418(void* state);
 int fn_801714BC(void* state);
int fn_80171560(void* state);
 int fn_80171664(void* state);
 int fn_80171780(void* state);
 int fn_8017187C(void* state);
 int fn_801718F4(void* state);
 int fn_801719B4(void* state);
 int fn_80171AF0(void* state);
 int fn_80171BB4(void* state);
 int fn_80171D6C(void* state);

extern void* fn_80024638(void*, void*, u32*);
extern int fn_80047180(void);
extern int fn_800471F8(void);
extern int fn_800473AC(void);
extern int fn_800480D4(void*, void*);
extern int fn_800483A0(void*, void*);
extern int fn_80048610(s16);
extern unsigned int fn_80052310(int, void*);
extern unsigned int fn_800F5C54(double);
extern int fn_800F8CF0(int);
extern int fn_800F8D14(int);
extern int fn_800F8D2C(int);
extern int fn_800F9D4C(char*, const char*, ...);
extern int fn_800FD228(void*, const char*);
extern char* fn_800FD40C(char*, const char*);
extern void fn_8011F0E8(void*, Vec3*);
extern unsigned int fn_8011FA8C(void*, int, int);
extern unsigned int fn_8011FABC(void*, int, int);
extern void* fn_8011FB5C(void*, int);
extern void* fn_8011FE34(void*);
extern void fn_80120AD0(void*, int, float, float, int, int);
extern void fn_80124664(void*, int, int, float);
extern void fn_80124750(void*, int, int, int, float, float, float, float, int);
extern void fn_801247F8(void*, int, int, float);
extern void fn_801287C4(void*, void*, unsigned int, unsigned int);
extern void fn_80128A84(void*, unsigned short, unsigned int);
extern void fn_80128C28(void*, void*, unsigned int);
extern void fn_80128F74(void*, int);
extern int fn_801290D0(void*);
extern void* fn_801294DC(void*, int, int, int);
extern void* fn_801295E8(void*, int, unsigned short, int);
extern int fn_801296F8(void*, int);
extern void* fn_8012976C(void*, int, unsigned short, Vec3*, float);
extern void* fn_80129878(void*, int, unsigned short, Vec3*, float);
extern void* fn_80129AF4(void*, int, unsigned short, float, float);
extern int fn_8012A1BC(void*, int);
extern void fn_8012B344(void*);
extern void fn_8012B7A0(void*, float);
extern float fn_8012B7D0(void*, Vec3*);
extern u8 fn_8012B8A8(void*, const Vec3f*);
extern void fn_8012C478(void*, int, int);
extern int fn_801301B0(void*, int, int);
extern void fn_80130214(void*, u8);
extern void fn_80130258(void*, unsigned int, unsigned int);
extern u8 fn_801303BC(void*);
extern void fn_80130434(void*, int);
extern void* fn_80138B90(void*, int, int);
extern void* fn_80155DB4(void*);
extern void fn_801568B8(void*, int);
extern int fn_801589AC(int, int, Vec3*, Vec3*, float*);
extern Vec3s* fn_80158ABC(int, int, void*);
extern int fn_80158B20(int, int, Vec3*, Vec3*, float*);
extern void fn_8015977C(int, int, int, int, int);
extern int fn_8015C4A4(int, int);
extern int fn_8015C524(unsigned int, int);
extern void fn_8015C8A4(int, int);
extern unsigned int fn_8015C910(void);
extern void fn_8015C948(int, void*, void*, int, int, int, int, int, int, int, int);
extern void* fn_8015E4A4(void);
extern void fn_8016057C(Context*, int);
extern int fn_80160EBC(void*, void*, void*, void*);
extern void fn_80161FA0(Context*, int);
extern void* fn_8016393C(void*, void*, unsigned int, unsigned int, unsigned int, char*, unsigned int);
extern void fn_80163BB4(void*, const char*, ...);
extern Context* fn_80166894(int);
extern void* fn_80166E3C(Context*, const char*, int);
extern void* fn_80167014(Context*, void*, int);
extern void* fn_801670A8(Context*, const char*);
extern void* fn_80167798(Context*, int);
extern int fn_80168A08(Value*);
extern int fn_80168A70(void*, Value*);
extern void fn_80168C74(void*);
extern Value* fn_80168F84(Context*, void*);
extern void fn_80169068(Context*, void*);
extern Value* fn_8016A55C(void*, int);
extern int fn_8016A598(void*);
extern void fn_8016A5B0(void*, int);
extern void fn_8016ADF0_w(s16, int, int);
extern void fn_80177408(void);
extern void fn_80177434(Context*, int, void*);
extern void fn_80179DB0(float*, short*);
extern void fn_8017A244(const void*, void*, float);
extern void fn_8017A34C(Vec4*, Vec4*, Vec4*);
extern void fn_801A5C30(int);
extern int fn_801A5CE0(void);
extern int fn_801A5D04(void);
extern unsigned int fn_801A98F4(unsigned short, unsigned char);
extern void fn_801A9964(int);
extern void fn_801A9984(int, unsigned char);
extern void fn_801A9DCC(int, int, int);
extern void fn_801AC350(int, int, int);
extern void fn_801AC5E4(unsigned short, unsigned char, unsigned char, int, signed char, int, int);
extern int fn_801ACACC(int, int, int, int);
extern void* fn_801AD734(int);
extern void* fn_801AD770(unsigned short, int);
extern int fn_801AF824(void);
extern int fn_801AF924(void);
extern int fn_801B002C(int, int, int, int, int);
extern void fn_801B05B0(int, u8);
extern int fn_801B05E8(int, int, int, int, void*, int, int, int);
extern int fn_801B08BC(int, int, int);
extern int fn_801B0B30(int);
extern void fn_801B0CA4(int, int);
extern void fn_801B0D30(void);
extern void fn_801E7974(void*, int);
extern void fn_801E79A0(void*, int);
extern int fn_801E79C4(void*, int);
extern int fn_801E79FC(void*, int);
extern void fn_801E7DC8(int);
extern void fn_801E7DCC(char*, ...);
extern void fn_801E807C(int, int, char*, ...);
extern void fn_801E8170(int, int, int);
extern void fn_801EF36C(int);
extern void fn_801F348C(void*, int);
extern int fn_801F6198(void*, u16, u16);
extern int fn_801F6228(void*, u16, u16);
extern void fn_801F6370(void*, int);
extern void fn_801F63E4(void*, int);
extern void fn_801F640C(void*, int, int);
extern void fn_801F64A8(void*, int, int);
extern void fn_801F6540(void);
extern void fn_801F700C(int, void*);
extern void fn_801F7034(void*, int);
extern void fn_801F70B0(void*, float);
extern void fn_801F70C4(void*, float);
extern void fn_801F70D8(void*, int);
extern void fn_801F7208(void*, float);
extern void fn_801F7210(void*, float);
extern void fn_801F74C8(int, int, int);
extern void fn_801F75FC(int, int, float);
extern int fn_801F86F4(int);
extern int fn_801F8748(int, void*, int, int, int);
extern void fn_801F898C(void*, int);
extern int fn_801FA198(unsigned int, void*, int, int, int, int, int, int, int);
extern void fn_801FA454(int, u16);
extern void* fn_801FEA8C(u32, int, const char*, int);
extern void fn_8020034C(int);
extern void fn_80200EAC(int, int, int, int, float);
extern void fn_8020104C(int, void*, void*, int, float);
extern void fn_80201138(int, void*, int, int, int, float);
extern unsigned long long fn_8020123C();
extern void *fn_80201814();
extern int fn_80201948(int, int);
extern void* fn_802019EC(int, void*);
extern void* fn_80201B3C(void);
extern int fn_80201B44();
extern int fn_80201B54();
extern int fn_80201B5C(void*);
extern int fn_80201B64(void*);
extern void *fn_80201B94();
extern void *fn_80201B9C();
extern void* fn_80201BC0(void*);
extern void *fn_80201BC8();
extern int fn_80201C2C(void*);
extern int fn_80201C48(void);
extern void fn_80201D14(void*, int);
extern void fn_80201D1C(void*, int);
extern void fn_80201D2C(void*, int);
extern void fn_80201D34(void*, int);
extern int fn_80201EB8();
extern void fn_80201F80(void*, int, int);
extern void fn_802020B4(void*, int);
extern void* fn_80204A8C(void);
extern int fn_80204C2C(void*);
extern void fn_80204CE4(void*, void*);
extern void fn_8020AFE4(void*);
extern int fn_80213394(const char*, DVDFileInfo*);
extern void fn_8021345C(DVDFileInfo*);
extern int fn_802136A4(const char*);
extern void* lbl_8023A878[];
extern const double lbl_8023A900[17];
extern char lbl_8024FE60[];
extern char lbl_8024FE6C[];
extern char lbl_8024FE8C[];
extern char lbl_8024FEA8[];
extern char lbl_8024FECC[];
extern char lbl_8024FEDC[];
extern char lbl_8024FEE8[];
extern char lbl_8024FEF4[];
extern const char lbl_80250200[];
extern const char lbl_80250284[];
extern RefEntry lbl_805FAA60[10];
extern char lbl_805FAAB0[];
extern int lbl_805FAAD8[1537];
extern int lbl_805FAAD8_x[1537];
extern int lbl_805FAAD8_y[1537];
extern char lbl_805FC2DC[];
extern unsigned char lbl_8063C6B8[];
extern unsigned char lbl_8063CD18[];
extern unsigned char lbl_8063D378[];
extern float lbl_8063D400[];
extern char lbl_8064BC00;
extern char lbl_8064BC08;
extern char lbl_8064BC10;
extern char lbl_8064BC18;
extern void* lbl_8064C3C8;
extern void* lbl_8064C4E0;
extern void* lbl_8064C4E4;
extern int lbl_8064CB54;
extern void* lbl_8064D18C;
extern int lbl_8064D18C_int;
extern int lbl_8064D1B8;
extern int lbl_8064D1BC;
extern Context* lbl_8064D1C0;
extern int lbl_8064D1C4;
extern char* lbl_8064D1C8;
extern unsigned char* lbl_8064D1CC;
extern Callback lbl_8064D1D0;
extern u32 lbl_8064D1D4;
extern int lbl_8064D1D8;
extern void* lbl_8064D1DC;
extern void* lbl_8064D1E0;
extern int lbl_8064D6DC;
extern int lbl_8064D6E0;
extern int lbl_8064D6EC;
extern const char lbl_8064DC80[];
extern double lbl_80650688;
extern const double lbl_806506A8;
extern const float lbl_806506B8;
extern unsigned int lbl_806506BC;
extern const float lbl_806506C0;
extern const float lbl_806506C4;
extern const float lbl_806506C8;
extern float lbl_806506CC;
extern const double lbl_806506D0;
extern void* memcpy(void*, const void*, unsigned long);
extern void* memset(void*, int, unsigned long);
extern size_t strlen(const char*);



int fn_8016BD0C(void* state)
{
    int result = -1;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    if (fn_80201814((int)fn_8016A694(state, 1)) != 0 && fn_80201B94() != 0) {
        result = fn_80201C48();
    }
    fn_8016A830(state, result);
    return 1;
}



int fn_8016BDD8(void* state)
{
    void* value = fn_80201B3C();
    fn_8016A970(state, value, 0);
    return 1;
}



int fn_8016BE1C(void* state)
{
    void* object = fn_8016A784(state, 1);
    int result;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    result = fn_80201B54(object);
    fn_8016A830(state, result);
    return 1;
}



int fn_8016BEC8(void* state)
{
    int amount;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    amount = (int)fn_8016A694(state, 1);
    fn_801A9DCC(0, amount == 1 ? 25 : 100, 10);
    return 0;
}



int fn_8016BF60(void* state)
{
    int result;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801B0B30((int)fn_8016A694(state, 1));
    result = fn_801AF924();
    fn_8016A830(state, result);
    return 1;
}



int fn_8016C008(void* state)
{
    int first;
    int second;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    fn_801B05E8(first, second, 4, 0, 0, 5, 0, 0);
    return 0;
}



int fn_8016C0BC(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801B0B30((int)fn_8016A694(state, 1));
    fn_8016A830(state, fn_801AF824());
    return 1;
}



int fn_8016C164(void* state)
{
    int first;
    int result;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    result = fn_801B002C(first, (int)fn_8016A694(state, 2), 1, 0, 0);
    fn_8016A830(state, result);
    return 1;
}




int fn_8016C238(void* state)
{
    int first;
    int second;
    int third;
    int fourth;
    s16* source;
    float vector[3];
    void* position;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);
    fourth = (int)fn_8016A694(state, 4);
    source = fn_8016A784(state, 5);
    if (source != 0) {
        vector[0] = source[0];
        vector[1] = source[1];
        vector[2] = source[2];
        position = vector;
    } else {
        position = 0;
        third = 5;
    }

    fn_801B05E8(first, second, fourth, 1, position, third, 0, 0);
    return 0;
}




int fn_8016C3B4(void* state)
{
    int object;
    int value;
    u8 byte_value;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    byte_value = (value > 0 ? value : 0) > 255
                     ? 255
                     : (value > 0 ? value : 0);
    if (value != byte_value) {
        fn_80163BB4(state, "Invalid Frames %i (range is 0-255)", value);
    } else {
        object = fn_801B0B30(object);
        if (object != -1) {
            fn_801B05B0(object, byte_value);
        }
    }
    return 0;
}




int fn_8016C4BC(void* state)
{
    int first;
    void* position;
    int second;
    int third;
    int fourth;
    s16* source;
    float vector[3];
    int result;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);
    fourth = (int)fn_8016A694(state, 4);
    source = fn_8016A784(state, 5);
    if (source != 0) {
        vector[0] = source[0];
        vector[1] = source[1];
        vector[2] = source[2];
        position = vector;
    } else {
        position = 0;
        third = 5;
    }

    result = fn_801B05E8(first, second, fourth, 1, position, third, 0, 1);
    if (result == -1 && first == 493 && lbl_8064D18C_int == 39) {
        fn_801B0D30();
        fn_801B05E8(first, second, fourth, 1, position, third, 0, 1);
    }
    return 0;
}



int fn_8016C668(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801B0CA4(-1, (int)fn_8016A694(state, 1));
    return 0;
}



int fn_8016C6EC(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801B08BC(-1, (int)fn_8016A694(state, 1), 0);
    return 0;
}



int fn_8016C774(void* state)
{
    fn_8016A830(state, fn_8015C910());
    return 1;
}



int fn_8016C7C4(void* state)
{
    switch (fn_8016A598(state)) {
    case 2: {
        int value = (int)fn_8016A694(state, 1);
        fn_8015C8A4(fn_800F5C54(fn_8016A694(state, 2)), value);
        break;
    }
    default:
        if (fn_8016A598(state) != 1) {
            fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
            return 0;
        }
        fn_8015C8A4(1, (int)fn_8016A694(state, 1));
        break;
    }
    return 0;
}



int fn_8016C890(void* state)
{
    void* object;
    int other;
    int value;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }
    value = (int)fn_8016A694(state, 1);
    other = (int)fn_8016A694(state, 2);
    object = fn_80201814(value);
    if (object != 0) {
        fn_80201D34(object, other);
        fn_80201D1C(object, 1);
        fn_8020123C(0x3B, value, value, 0);
    }
    return 0;
}



int fn_8016C96C(void* state)
{
    void* object;
    int second;
    int first;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }
    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    object = fn_80201814(first);
    if (object != 0) {
        fn_80201D2C(object, second);
        fn_80201D14(object, 1);
    }
    return 0;
}



int fn_8016CA2C(void* state)
{
    int second;
    int fourth;
    int first;
    float third;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }
    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (float)fn_8016A694(state, 3);
    fourth = (int)fn_8016A694(state, 4);
    fn_801247F8(fn_80201BC8(fn_80201814(first)), second, fourth, third);
    return 0;
}



int fn_8016CB24(void* state)
{
    int second;
    int first;
    float third;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }
    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (float)fn_8016A694(state, 3);
    fn_80124664(fn_80201BC8(fn_80201814(first)), second, 8, third);
    return 0;
}



int fn_8016CBFC(void* state)
{
    int second;
    int ninth;
    int seventh;
    int eighth;
    int first;
    float third;
    float fourth;
    float fifth;
    float sixth;

    if (fn_8016A598(state) != 9) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 9, fn_8016A598(state));
        return 0;
    }
    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (float)fn_8016A694(state, 3);
    fourth = (float)fn_8016A694(state, 4);
    fifth = (float)fn_8016A694(state, 5);
    sixth = (float)fn_8016A694(state, 6);
    seventh = (int)fn_8016A694(state, 7);
    eighth = (int)fn_8016A694(state, 8);
    ninth = (int)fn_8016A694(state, 9);
    fn_80124750(fn_80201BC8(fn_80201814(first)), second, seventh, eighth,
                third, fourth, fifth, sixth, ninth | 8);
    return 0;
}



int fn_8016CDA0(void* state)
{
    int first = fn_80201B44(state);
    int second = fn_80201EB8(fn_80201814(first));

    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }
    fn_80200EAC(0x39, first, 0, second, lbl_806506B8);
    return 0;
}



int fn_8016CE48(void* state)
{
    int first = fn_80201B44(state);
    int second = fn_80201EB8(fn_80201814(first));

    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }
    fn_80200EAC(8, first, 0, second, lbl_806506B8);
    return 0;
}



int fn_8016CEF0(void* state)
{
    void* result;
    void* source;
    void* target;
    void* handle;
    int third;
    int second;
    int first;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);

    if (first == -2) {
        target = fn_80201814(second);
        if (target != 0) {
            result = fn_80204A8C();
            fn_80204CE4(target, result);
        }
    } else {
        source = fn_80201814(first);
        if (source != 0) {
            target = fn_80201814(second);
            if (target != 0) {
                int value = fn_80201C2C(source);
                if (value == 0) {
                    value = fn_80204C2C(source);
                }
                fn_80204CE4(target, (void*)value);
                if (third == 0) {
                    handle = fn_80155DB4(target);
                    if (handle != 0) {
                        fn_801568B8(handle, 0);
                    }
                }
            }
        }
    }
    return 0;
}



int fn_8016D040(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    value = (int)fn_8016A784(state, 1);
    fn_8016A830(state, (double)value);
    return 1;
}



int fn_8016D0D4(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }
    lbl_8064CB54 ^= 1;
    return 0;
}



int fn_8016D144(void* state)
{
    int object_id;
    int value;
    void* object;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }
    object_id = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    object = fn_80201814(object_id);
    if (object != 0) {
        fn_80201F80(object, value, 0xFF800);
    }
    return 0;
}



int fn_8016D1F8(void* state)
{
    int result = -1;
    void* object;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    object = fn_80201814((int)fn_8016A694(state, 1));
    if (object != 0) {
        result = fn_80201B64(object);
    }
    fn_8016A830(state, (double)result);
    return 1;
}



int fn_8016D2B8(void* state)
{
    int mode;
    int argument;
    int result = 0;
    int resolved;
    void* node;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }
    mode = (int)fn_8016A694(state, 1);
    if (mode == 6) {
        node = fn_8016A784(state, 2);
    }
    if (mode != 6) {
        argument = (int)fn_8016A694(state, 2);
    }
    switch (mode) {
    case 1:
        result = fn_80201B44();
        break;
    case 2:
        result = fn_802019EC_int(argument, lbl_8064D18C);
        break;
    case 4:
        result = fn_802019EC_int(argument, -1);
        break;
    case 5:
        resolved = fn_80201C2C(fn_80201814(fn_80201B44()));
        result = fn_80201948(argument, resolved);
        break;
    case 3:
        node = fn_80201B9C();
        while (node != 0) {
            if (argument == fn_80201B5C(node)) {
                result = fn_80201B54(node);
            }
            node = fn_80201BC0(node);
        }
        break;
    case 6:
        result = fn_80201B54(node);
        break;
    }
    if (result <= 0) {
        fn_8016A7D8(state);
    } else {
        fn_8016A830(state, (double)result);
    }
    return 1;
}



#pragma opt_propagation off
int fn_8016D480(void* state)
{
    int count;
    int x;
    void* context;
    unsigned int flags;
    int y;
    float z;

    context = state;
    count = fn_8016A598(context);
    flags = 0;
    switch (count) {
    case 4:
        flags = (int)fn_8016A694(context, 4);
    case 3:
        x = (int)fn_8016A694(context, 1);
        y = (int)fn_8016A694(context, 2);
        z = (float)fn_8016A694(context, 3);
        break;
    default:
        fn_80163BB4(context, "Invalid Num of Args Expecting 3 or 4, and got %i", count);
        return 0;
    }
    if (x != 0) {
        fn_8020104C(y, 0, (void*)x, flags, z);
    }
    return 0;
}
#pragma opt_propagation reset



int fn_8016D574(void* state)
{
    int x;
    int y;
    float z;
    int flags;

    fn_8016A598(state);
    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }
    fn_8016A694(state, 1);
    x = (int)fn_8016A694(state, 2);
    y = (int)fn_8016A694(state, 3);
    z = (float)fn_8016A694(state, 4);
    flags = (int)fn_8016A694(state, 5);
    if (x != 0) {
        fn_8020104C(y, 0, (void*)x, flags, z);
    }
    return 0;
}



int fn_8016D680(void* state)
{
    int a;
    int b;
    int x;
    int y;
    float z;
    int c;

    if (fn_8016A598(state) != 6) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 6, fn_8016A598(state));
        return 0;
    }
    x = (int)fn_8016A694(state, 1);
    y = (int)fn_8016A694(state, 2);
    z = (float)fn_8016A694(state, 3);
    a = (int)fn_8016A694(state, 4);
    b = (int)fn_8016A694(state, 5);
    c = (int)fn_8016A694(state, 6);
    if (x != 0) {
        void* object = fn_80201814(x);
        if (object != 0) {
            fn_80201138(y, object, a, b, c, z);
        }
    }
    return 0;
}



int fn_8016D7AC(void* state)
{
    int values[4];
    int x;
    int y;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }
    x = (int)fn_8016A694(state, 1);
    y = (int)fn_8016A694(state, 2);
    values[0] = (int)fn_8016A694(state, 3);
    values[1] = (int)fn_8016A694(state, 4);
    if (x != 0) {
        fn_8020123C(y, 0, x, values);
    }
    return 0;
}



int fn_8016D8A4(void* state)
{
    int value;

    switch (fn_8016A598(state)) {
    case 2:
        fn_801EF36C((int)fn_8016A694(state, 2));
    case 1:
        value = (int)fn_8016A694(state, 1);
        break;
    }
    lbl_8064D6EC = value;
    return 0;
}



int fn_8016D92C(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    if (value != lbl_8064D6E0) {
        lbl_8064D6E0 = value;
        lbl_8064D6DC = 1;
    }
    return 0;
}



void fn_8016D9C0(unsigned int type, u16* first, u16* second)
{
    switch (type) {
    case 0:
        *first = 0;
        *second = 1;
        break;
    case 1:
        *first = 0;
        *second = 2;
        break;
    case 2:
        *first = 0;
        *second = 4;
        break;
    case 3:
        *first = 2;
        *second = 5;
        break;
    case 4:
        *first = 0;
        *second = 8;
        break;
    case 5:
        *first = 2;
        *second = 0;
        break;
    case 6:
        *first = 0;
        *second = 0x20;
        break;
    case 7:
        *first = 0x3f;
        *second = 0;
        break;
    }
}




int fn_8016DA80(void* state)
{
    void* object;
    int type;
    u16 second;
    u16 first;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object = (void *)fn_800F5C54(fn_8016A694(state, 1));
    type = (int)fn_8016A694(state, 2);
    if (object != 0) {
        fn_8016D9C0(type, &first, &second);
        fn_801F6198(object, first, second);
    }
    return 1;
}




int fn_8016DB38(void* state)
{
    void* object;
    int type;
    u16 second;
    u16 first;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object = (void *)fn_800F5C54(fn_8016A694(state, 1));
    type = (int)fn_8016A694(state, 2);
    if (object != 0) {
        fn_8016D9C0(type, &first, &second);
        fn_801F6228(object, first, second);
    }
    return 1;
}



int fn_8016DBF0(void* state)
{
    int first;
    void* object;
    int second;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    object = (void *)fn_800F5C54(fn_8016A694(state, 1));
    first = (int)fn_8016A694(state, 2);
    second = (int)fn_8016A694(state, 3);
    fn_801F640C(object, first, second);
    return 1;
}



int fn_8016DCB0(void* state)
{
    int first;
    void* object;
    int second;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    object = (void *)fn_800F5C54(fn_8016A694(state, 1));
    first = (int)fn_8016A694(state, 2);
    second = (int)fn_8016A694(state, 3);
    fn_801F64A8(object, first, second);
    return 1;
}



int fn_8016DD70(void)
{
    fn_801F6540();
    return 1;
}



int fn_8016DD94(void* state)
{
    void* object;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object = (void *)fn_800F5C54(fn_8016A694(state, 1));
    fn_801F63E4(object, (int)fn_8016A694(state, 2));
    return 1;
}



int fn_8016DE30(void* state)
{
    void* object;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object = (void *)fn_800F5C54(fn_8016A694(state, 1));
    fn_801F6370(object, (int)fn_8016A694(state, 2));
    return 0;
}



int fn_8016DECC(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_8020034C((int)fn_8016A694(state, 1));
    return 1;
}



int fn_8016DF4C(void* state)
{
    int arg1;
    void* arg2;
    void* arg3;
    int selector;
    int arg5;
    int arg6;
    int optional = 1;
    int current;
    int mode;
    int extra;
    volatile unsigned int timer_template = lbl_806506BC;

    switch (fn_8016A598(state)) {
    case 7:
        optional = (int)fn_8016A694(state, 7);
    case 6:
        arg1 = (int)fn_8016A694(state, 1);
        arg2 = (void *)fn_800F5C54(fn_8016A694(state, 2));
        arg3 = (void *)fn_800F5C54(fn_8016A694(state, 3));
        selector = (int)fn_8016A694(state, 4);
        arg5 = (int)fn_8016A694(state, 5);
        arg6 = (int)fn_8016A694(state, 6);
        break;
    }

    current = fn_80047180();
    if (current != 0) {
        mode = -1;
        extra = 0;
        fn_802020B4(fn_80201B3C(), 0);

        switch (selector) {
        case 0: mode = -1; break;
        case 1: mode = 5; break;
        case 2: mode = 10; break;
        case 3: mode = 60; break;
        case 16: mode = 188; extra = 128; break;
        case 4: fn_8016E254(2); mode = 5; break;
        case 5: fn_8016E254(2); mode = 10; break;
        case 6: fn_8016E254(2); mode = 60; break;
        case 7: fn_8016E254(25); mode = 5; break;
        case 8: fn_8016E254(25); mode = 10; break;
        case 9: fn_8016E254(25); mode = 60; break;
        case 10: fn_8016E254(103); mode = 5; break;
        case 11: fn_8016E254(103); mode = 10; break;
        case 12: fn_8016E254(103); mode = 60; break;
        case 13: fn_8016E254(104); mode = 5; break;
        case 14: fn_8016E254(104); mode = 10; break;
        case 15: fn_8016E254(104); mode = 60; break;
        }

        if (mode == -1) {
            fn_8015C948(arg1, arg2, arg3, arg5, arg6, 1, extra, selector, 0, 0, optional);
            fn_801AC350(0, 1, 0);
        } else {
            int clamped;
            fn_8015C948(arg1, arg2, arg3, arg5, arg6, mode + 2, extra, selector, 0, 0, optional);
            if (selector != 16) {
                unsigned int timer = timer_template;
                fn_801F348C(&timer, mode);
            }
            clamped = mode > 254 ? 254 : mode;
            fn_801AC350((signed char)clamped, 1, 0);
        }
    }
    fn_8016A830(state, (double)current);
    return 1;
}



void fn_8016E254(int value)
{
    int current = fn_80201B44();
    fn_8020123C(253, 0, current, value);
}





int fn_8016E294(void* state)
{
    signed char path[16];
    DVDFileInfo file;
    int first;
    int second;
    int third;
    int i;
    int opened;

    fn_8015E4A4();
    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);
    fn_800F9D4C((char*)path, "%s%4d.bpe", lbl_8064DC80, first);
    for (i = 0; i < 13; i++) {
        if (path[i] == ' ') {
            path[i] = '0';
        }
    }
    fn_802136A4(&lbl_8064BC10);
    opened = fn_80213394((char*)path, &file);
    fn_802136A4(&lbl_8064BC18);
    if (opened != 0) {
        fn_8021345C(&file);
        fn_8015977C(first, second, third, 0, 0);
    }
    return 0;
}



int fn_8016E3F0(void* state)
{
    int second;
    int fourth;
    int third;
    unsigned int first;
    int fifth;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }
    first = fn_800F5C54(fn_8016A694(state, 1));
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);
    fourth = (int)fn_8016A694(state, 4);
    fifth = (int)fn_8016A694(state, 5);
    fn_801FA198(first, lbl_8063CD18 + 0x110, second, third, fourth, 0, 0, fifth, 0);
    return 0;
}



int fn_8016E514(void* state)
{
    int value;
    void* target;
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    value = (int)fn_8016A694(state, 1);
    fn_80201814(value);
    target = fn_80201BC8();
    fn_801F700C(2, target);
    return 1;
}



int fn_8016E5A8(void* state)
{
    int value;
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    value = (int)fn_8016A694(state, 1);
    fn_801F898C(lbl_8063CD18 + 0x110, value);
    return 0;
}



int fn_8016E634(void* state)
{
    int first;
    u16 second;
    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }
    first = (int)fn_8016A694(state, 1);
    second = (u16)(int)fn_8016A694(state, 2);
    fn_801FA454(first, second);
    return 0;
}



int fn_8016E6D4(void* state)
{
    int second;
    unsigned int first;
    int third;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }
    first = fn_800F5C54(fn_8016A694(state, 1));
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);
    fn_801FA198(first, lbl_8063CD18 + 0x110, 0, 0, third, 1, second, 0, 0);
    return 0;
}



int fn_8016E7B8(void* state)
{
    int count = fn_8016A598(state);
    int i;

    for (i = 1; i <= count; i++) {
        if (fn_8016A650(state, i) == 0) {
            fn_800FD228(fn_8016A628(state, fn_8016A5F4(state, i)), "userdata");
        }
    }
    return 0;
}



int fn_8016E854(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    fn_8016A694(state, 1);
    return 0;
}



int fn_8016E8C4(void* state)
{
    fn_80163BB4(state, "\nError Requested Button is Obsolete", 0);
    return 0;
}





int fn_8016E8F8(void* state, int alternate)
{
    int value;
    unsigned short kind;
    int id;
    ShortVec3* source;
    Vec3 position;
    float scale;
    void* object;
    void* result;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    id = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    kind = (unsigned short)(int)fn_8016A694(state, 3);
    source = fn_8016A784(state, 4);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;
    scale = (float)fn_8016A694(state, 5);
    scale *= lbl_806506C0;

    if (id == 162) {
        asm { nop }
    }
    object = fn_80201814(id);
    object = object != 0 ? fn_80201BC8(object) : 0;

    if (alternate != 0) {
        result = object != 0 ? fn_80129878(object, value, kind, &position, scale) : 0;
    } else {
        result = object != 0 ? fn_8012976C(object, value, kind, &position, scale) : 0;
    }
    fn_8016A970(state, result, 0);
    return 1;
}



int fn_8016EACC(void* state)
{
    fn_8016E8F8(state, 1);
    return 1;
}



int fn_8016EAF4(void* state)
{
    fn_8016E8F8(state, 0);
    return 1;
}



int fn_8016EB1C(void* state)
{
    int value;
    unsigned short kind;
    int object_id;
    int mode;
    void* result;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    kind = (unsigned short)(int)fn_8016A694(state, 3);
    mode = (int)fn_8016A694(state, 4);
    result = fn_801295E8(fn_80201BC8(fn_80201814(object_id)), value, kind, mode);
    fn_8016A970(state, result, 0);
    if (result == 0) {
        fn_80163BB4(state, "Could not Queue anim", 0);
    }
    return 1;
}



int fn_8016EC50(void* state)
{
    int value;
    int converted;
    int object_id;
    int mode;
    void* object;
    void* result;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    converted = fn_800F5C54(fn_8016A694(state, 3));
    mode = (int)fn_8016A694(state, 4);
    object = fn_80201814(object_id);
    object = object != 0 ? fn_80201BC8(object) : 0;
    result = object != 0 ? fn_801294DC(object, value, converted, mode) : 0;
    fn_8016A970(state, result, 0);
    return 1;
}



int fn_8016ED78(void* state)
{
    int value;
    unsigned short kind;
    void* result;
    int object_id;
    float first;
    float second;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    kind = (unsigned short)(int)fn_8016A694(state, 3);
    first = (float)fn_8016A694(state, 4);
    second = (float)fn_8016A694(state, 5);
    first *= lbl_806506C0;
    second *= lbl_806506C0;
    result = fn_80129AF4(fn_80201BC8(fn_80201814(object_id)), value, kind, first, second);
    fn_8016A970(state, result, 0);
    if (result == 0) {
        fn_80163BB4(state, "Could not Queue seek mode", 0);
    }
    return 1;
}



int fn_8016EEE4(void* state)
{
    void* callback;
    void* object;
    int object_id;
    int value;
    int result;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    callback = fn_8016A784(state, 2);
    value = (int)fn_8016A694(state, 3);
    object = fn_80201814(object_id);
    if (object != 0) {
        object = fn_80201BC8(object);
        result = fn_8012A1BC(object, value);
        fn_80128A84(callback, 0, result);
    }
    return 0;
}



int fn_8016EFC4(void* state)
{
    void* queue;
    int first;
    int second;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    queue = fn_8016A784(state, 1);
    first = (int)fn_8016A694(state, 2);
    second = (int)fn_8016A694(state, 3);
    fn_801287C4(queue, fn_8016FFA8, first, second);
    return 0;
}



int fn_8016F088(void* state)
{
    void* queue;
    int value;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    queue = fn_8016A784(state, 1);
    value = (int)fn_8016A694(state, 2);
    fn_80128C28(queue, fn_8016FFA8, value);
    return 0;
}



int fn_8016F128(void* state)
{
    void* handle;
    void* object;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    handle = fn_80201814((int)fn_8016A694(state, 1));
    object = handle != 0 ? fn_80201BC8(handle) : 0;
    if (handle != 0 && object != 0) {
        fn_8012B344(object);
    }
    return 0;
}



int fn_8016F1D0(void* state)
{
    void* object;
    int mode;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object = fn_80201BC8(fn_80201814((int)fn_8016A694(state, 1)));
    mode = (int)fn_8016A694(state, 2);
    if (mode != 0) {
        fn_801301B0(object, 0x20, 0);
    } else {
        fn_80130434(object, 1);
        fn_801301B0(object, 0, 0x20);
    }
    return 0;
}




int fn_8016F2AC(void* state)
{
    int mode;
    void* object;
    int index;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    object = fn_80201BC8(fn_80201814((int)fn_8016A694(state, 1)));
    mode = (int)fn_8016A694(state, 2);
    index = (int)fn_8016A694(state, 3);
    if (mode != 0) {
        if (index < 0) {
            fn_80130214(object, 0);
        } else {
            fn_80130258(object, 1 << index, 0);
        }
    } else {
        if (index < 0) {
            fn_80130434(object, 1);
            fn_80130214(object, 0xFF);
        } else {
            fn_80130258(object, 0, 1 << index);
            if (index == fn_801303BC(object)) {
                fn_80130434(object, 1);
            }
        }
    }
    return 0;
}






int fn_8016F400(void* state)
{
    Vec3 position;
    int object_id;
    Vec3s* source;
    void* object;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    source = fn_8016A784(state, 2);
    if (source != 0) {
        fn_80179DB0((float*)&position, (short*)source);
    } else {
        return 0;
    }
    object = fn_80201814(object_id);
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            fn_8011F0E8(object, &position);
        }
    }
    return 0;
}



int fn_8016F4CC(void* state)
{
    int object_id;
    float value;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    value = (float)fn_8016A694(state, 2);
    fn_8012B7A0(fn_80201BC8(fn_80201814(object_id)), lbl_806506C0 * value);
    return 0;
}



int fn_8016F580(void* state)
{
    int object_id;
    void* object;
    void* runtime;
    int index;
    int enabled;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        runtime = fn_80201BC8(object);
        index = (int)fn_8016A694(state, 2);
        enabled = (int)fn_8016A694(state, 3);
        fn_8012C478(runtime, index, enabled);
    } else {
        fn_80163BB4(state, "Char_Show_Body_Part: No Game object with iUID = %d", object_id);
    }
    return 0;
}



int fn_8016F678(void* state)
{
    int object_id;
    void* object;
    void* runtime;
    int clear_flags = 0;
    int set_flags = 0;
    int enabled;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        runtime = fn_80201BC8(object);
        enabled = (int)fn_8016A694(state, 2);
        if (enabled != 0) {
            set_flags = 4;
        }
        if (enabled == 0) {
            clear_flags = 4;
        }
        fn_8011FA8C(runtime, clear_flags, set_flags);
    } else {
        fn_80163BB4(state, "Char_Show_Body_Part: No Game object with iUID = %d", object_id);
    }
    return 0;
}


static Vec3 UP_F78C = { 0.0f, 0.0f, 1.0f };

int fn_8016F78C(void* state)
{
    int object_id;
    unsigned int resource_id;
    void* object;
    void* runtime;
    int resource_index;
    Vec3 angles;
    Vec3 position;
    float scale;
    Vec3 position_copy;
    float facing;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        runtime = fn_80201BC8(object);
        resource_id = fn_800F5C54(fn_8016A694(state, 2));
        resource_index = fn_8015C4A4(resource_id, 2);
        if (resource_index != -1 &&
            fn_80158B20(resource_index, 2, &position, &angles, &scale)) {
            position_copy = position;
            facing = fn_8012B7D0(runtime, &position_copy);
            fn_8017A244(&UP_F78C, fn_8011FE34(runtime), facing);
        } else {
            fn_80163BB4(state, "Could not find marker %u", resource_id);
        }
    } else {
        fn_80163BB4(state, "CharOrientToFaceMarker: No Game object with iUID = %d", object_id);
    }
    return 0;
}



int fn_8016F8F8(void* state)
{
    int object_id;
    void* source;
    void* object;
    Vec3 position;
    Vec3 copy;
    float value;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    source = fn_8016A784(state, 2);
    if (source != 0) {
        fn_80179DB0((float*)&position, (short*)source);
    } else {
        return 0;
    }

    object = fn_80201814(object_id);
    if (object != 0 && fn_80201BC8(object) != 0) {
        object = fn_80201BC8(object);
        copy = position;
        value = fn_8012B7D0(object, &copy);
        fn_8016A830(state, lbl_806506C4 * value);
    } else {
        return 0;
    }
    return 1;
}


static Vec3 UP_FA08 = { 0.0f, 0.0f, 1.0f };

int fn_8016FA08(void* state)
{
    int object_id;
    unsigned int resource_id;
    void* object;
    void* runtime;
    int resource_index;
    Vec3 direction;
    Vec3 position;
    float scale;
    Vec4 base_rotation;
    Vec4 rotation;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        runtime = fn_80201BC8(object);
        resource_id = fn_800F5C54(fn_8016A694(state, 2));
        resource_index = fn_8015C524(resource_id, 2);
        if (resource_index != -1 &&
            fn_801589AC(resource_index, 2, &position, &direction, &scale)) {
            direction.x = -direction.x;
            direction.y = -direction.y;
            direction.z = -direction.z;
            fn_8017A244(&direction, &rotation, scale);
            fn_8017A244(&UP_FA08, &base_rotation, lbl_806506C8);
            fn_8017A34C(&rotation, &base_rotation, fn_8011FE34(runtime));
            fn_8011F0E8(runtime, &position);
        } else {
            fn_80163BB4(state, "Could not find waypoint %u", resource_id);
        }
    } else {
        fn_80163BB4(state, "CharOrientToMarker: No Game object with iUID = %d", object_id);
    }
    return 0;
}


int fn_8016FB94(void* state)
{
    int object_id;
    int clear_flags;
    int set_flags;
    void* object;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    clear_flags = (int)fn_8016A694(state, 2);
    set_flags = (int)fn_8016A694(state, 3);
    object = fn_80201814(object_id);
    if (object != 0) {
        fn_8011FA8C(fn_80201BC8(object), clear_flags, set_flags);
    }
    return 0;
}



int fn_8016FC68(void* state)
{
    int object_id;
    int clear_flags;
    int set_flags;
    void* object;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    clear_flags = (int)fn_8016A694(state, 2);
    set_flags = (int)fn_8016A694(state, 3);
    object = fn_80201814(object_id);
    if (object != 0) {
        fn_8011FABC(fn_80201BC8(object), clear_flags, set_flags);
    }
    return 0;
}



int fn_8016FD3C(void* state)
{
    int object_id;
    float value;
    int argument;
    int flags;
    void* object;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    value = (float)fn_8016A694(state, 2);
    argument = (int)fn_8016A694(state, 3);
    flags = (int)fn_8016A694(state, 4);
    object = fn_80201814(object_id);
    if (object != 0) {
        object = fn_80201BC8(object);
        if ((unsigned short)flags != 0) {
            flags = (flags | 2) & 0xFFFF;
        }
        fn_80120AD0(object, 0, lbl_806506CC, value, argument, flags);
    }
    return 0;
}



int fn_8016FE4C(void* state)
{
    int value;
    int flags;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    if (value == 0) {
        if (lbl_8064C4E4 != 0) {
            flags = fn_801290D0(lbl_8064C4E4);
            fn_80128F74(lbl_8064C4E4, flags | 4);
        }
    }
    fn_801A5C30(value);
    return 0;
}



int fn_8016FEF8(void* state)
{
    int value;

    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    value = 0;
    if (fn_801A5CE0() != 0 || fn_801A5D04() != 0) {
        value = 1;
    }
    fn_8016A830(state, value);
    return 1;
}



int fn_8016FFA8(void* first, void* second)
{
    fn_8016B400((int)second, first, 0);
    return 0;
}




int fn_8016FFDC(void* state)
{
    float value;
    unsigned char* target;

    target = &((TargetOwner*)lbl_8063C6B8)->target;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (float)fn_8016A694(state, 1);
    fn_801F7208(target, value);
    fn_801F7208(lbl_8063D378, value);
    return 0;
}




int fn_80170090(void* state)
{
    float value;
    unsigned char* target;

    target = &((TargetOwner*)lbl_8063CD18)->target;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (float)fn_8016A694(state, 1);
    fn_801F7208(target, value);
    fn_801F7208(lbl_8063D400, value);
    return 0;
}




int fn_80170144(void* state)
{
    unsigned char* target;

    target = &((TargetOwner*)lbl_8063CD18)->target;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801F7210(target, (float)fn_8016A694(state, 1));
    return 0;
}




int fn_801701D4(void* state)
{
    unsigned char* target;

    target = &((TargetOwner*)lbl_8063CD18)->target;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801F70D8(target, (int)fn_8016A694(state, 1));
    return 0;
}




int fn_8017026C(void* state)
{
    unsigned char* target;

    target = &((TargetOwner*)lbl_8063CD18)->target;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801F70C4(target, (float)fn_8016A694(state, 1));
    return 0;
}




int fn_801702FC(void* state)
{
    unsigned char* target;

    target = &((TargetOwner*)lbl_8063CD18)->target;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801F70B0(target, (float)fn_8016A694(state, 1));
    return 0;
}



int fn_8017038C(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    lbl_8063D400[2] -= value;
    return 0;
}



int fn_80170438(void* state)
{
    int first;
    int second;
    int third;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);
    fn_801F74C8(first, second, third);
    return 0;
}



int fn_801704F8(void* state)
{
    int first;
    int second;
    int third;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);
    fn_801F75FC(first, second, third);
    return 0;
}



int fn_801705D4(void* state)
{
    unsigned char* target;

    target = lbl_8063CD18 + 0x110;
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801F7034(target, 0);
    return 0;
}



int fn_80170658(void* state)
{
    unsigned char* target;

    target = lbl_8063CD18 + 0x110;
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801F7034(target, 0);
    return 0;
}



int fn_801706DC(void* state)
{
    int first;
    int second;
    int third;
    int fourth;
    int result;
    int fifth;
    void* object;

    result = 0;
    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    first = fn_800F5C54(fn_8016A694(state, 1));
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);
    fourth = (int)fn_8016A694(state, 4);
    fifth = (int)fn_8016A694(state, 5);

    object = fn_80201814(second);
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            result = fn_801F8748(first, object, third, fourth, fifth);
        }
    }

    fn_8016A830(state, result);
    return 1;
}



int fn_80170814(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801F86F4(0);
    return 0;
}



int fn_80170880(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    switch ((int)fn_8016A694(state, 1)) {
    case 0:
        fn_8016A970(state, lbl_8064C4E4, 0);
        return 1;
    case 1:
        fn_8016A970(state, 0, 0);
        return 1;
    default:
        fn_80163BB4(state, "Invalid Object Type %i", (int)fn_8016A694(state, 1));
        fn_8016A970(state, 0, 0);
        return 1;
    }
}




int fn_80170980(void* state)
{
    int value;
    s16 id = lbl_8064D1BC;

    switch (fn_8016A598(state)) {
    case 2:
        id = fn_8016A694(state, 2);
    case 1:
        value = (int)fn_8016A694(state, 1);
        break;
    default:
        fn_80163BB4(state, "\nInvalid Num of Args Expecting 1 or 2, and got %i\n", fn_8016A598(state));
        return 0;
    }

    fn_8016ADF0_w(id, value, -1);
    return 0;
}





int fn_80170A40(void* state)
{
    s16 id = lbl_8064D1BC;
    int i = 0;

    if (fn_8016A598(state) > 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting 0 or 1, and got %i\n", fn_8016A598(state));
        return 0;
    }

    if (fn_8016A598(state) > 0) {
        id = fn_8016A694(state, 2);
    }

    while (lbl_805FAA60[i].id != id && i < 10) {
        i++;
    }

    if (i >= 10) {
        fn_8016A830(state, lbl_806506D0);
    } else {
        fn_8016A830(state, (double)lbl_805FAA60[i].value2);
    }
    return 1;
}




int fn_80170B5C(void* state)
{
    s16 first = lbl_8064D1BC;
    int second;

    switch (fn_8016A598(state)) {
    case 2:
        first = fn_8016A694(state, 2);
    case 1:
        second = fn_8016A694(state, 1);
        break;
    default:
        fn_80163BB4(state, "\nInvalid Num of Args Expecting 1 or 2, and got %i\n", fn_8016A598(state));
        return 0;
    }

    fn_8016B0B4(first, second);
    return 0;
}



int fn_80170C18(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    lbl_8064D1C4 = lbl_8064D1BC;
    return 0;
}



int fn_80170C84(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    lbl_8064D1C4 = fn_8016A694(state, 1);
    return 0;
}



int fn_80170D04(void* state)
{
    int handle;
    int mode;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    handle = fn_800F5C54(fn_8016A694(state, 1));
    mode = fn_8016A694(state, 2);
    if (mode != 0 && mode != 1) {
        fn_80163BB4(state, "Bit value must be 0 or 1, received a value of %d", mode);
    }

    if (mode == 0) {
        fn_801E79A0(lbl_8064C4E0, handle);
    } else {
        fn_801E7974(lbl_8064C4E0, handle);
    }
    return 0;
}



int fn_80170DF4(void* state)
{
    int handle;
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    handle = fn_800F5C54(fn_8016A694(state, 1));
    value = fn_801E79FC(lbl_8064C4E0, handle);
    fn_8016A830(state, value);
    return 1;
}



int fn_80170E9C(void* state)
{
    int handle;
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    handle = fn_800F5C54(fn_8016A694(state, 1));
    value = fn_801E79C4(lbl_8064C4E0, handle);
    fn_8016A830(state, value);
    return 1;
}



int fn_80170F44(void* state)
{
    int handle;
    int index;
    void* result;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    handle = fn_800F5C54(fn_8016A694(state, 1));
    index = fn_8015C4A4(handle, 2);
    if (index != -1) {
        result = fn_80158ABC(index, 2, 0);
        fn_8016A970(state, result, 0);
    } else {
        fn_80163BB4(state, "Could not find marker %u", handle);
        fn_8016A970(state, 0, 0);
    }
    return 1;
}



int fn_80171020(void* state)
{
    int handle;
    int index;
    float value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    handle = fn_800F5C54(fn_8016A694(state, 1));
    index = fn_8015C4A4(handle, 2);
    if (index != -1) {
        fn_80158ABC(index, 2, &value);
        fn_8016A830(state, lbl_806506C4 * value);
    } else {
        fn_80163BB4(state, " Could not find marker %u", handle);
        fn_8016A970(state, 0, 0);
    }
    return 1;
}



int fn_801710FC(void* state)
{
    int handle;
    int index;
    float value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    handle = fn_800F5C54(fn_8016A694(state, 1));
    index = fn_8015C4A4(handle, 2);
    if (index != -1) {
        fn_80158ABC(index, 2, &value);
        fn_8016A830(state, value);
    } else {
        fn_80163BB4(state, " Could not find marker %u", handle);
        fn_8016A970(state, 0, 0);
    }
    return 1;
}






int fn_801711D0(void* state)
{
    int object_id;
    void* object;
    int handle;
    int index;
    Vec3s* packed;
    Vec3f position;
    u8 result;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        handle = fn_800F5C54(fn_8016A694(state, 2));
        index = fn_8015C4A4(handle, 2);
        if (index != -1) {
            packed = fn_80158ABC(index, 2, &result);
            position.x = packed->x;
            position.y = packed->y;
            position.z = packed->z;
            object = fn_80201BC8(object);
            fn_8016A830(state, (int)fn_8012B8A8(object, &position));
        } else {
            fn_80163BB4(state, "Could not find marker %u", handle);
            fn_8016A970(state, 0, 0);
        }
    } else {
        fn_80163BB4(state, "Could not find Game Object with UID %d", object_id);
        fn_8016A970(state, 0, 0);
    }
    return 1;
}



int fn_8017138C(void* state)
{
    int value;

    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    value = fn_800473AC();
    fn_8016A830(state, value);
    return 1;
}



int fn_80171418(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = fn_8016A694(state, 1);
    if (value != 0) {
        void* object = fn_802019EC(value, lbl_8064D18C);
        fn_8020123C(0x12, 0, object, 0);
    }
    return 0;
}



int fn_801714BC(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = fn_8016A694(state, 1);
    if (value != 0) {
        void* object = fn_802019EC(value, lbl_8064D18C);
        fn_8020123C(0x13, 0, object, 0);
    }
    return 0;
}


int fn_80171560(void* state)
{
    int object_id;
    int value;
    void* object;
    void* component;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    object = fn_80201814(object_id);
    if (object == 0) {
        fn_80163BB4(state, "Couldn't Find GO for UID %i", object_id);
        return 0;
    }

    component = fn_80201BC8(object);
    if (component == 0) {
        fn_80163BB4(state, "Couldn't Find Char for UID %i GO %p", object_id, object);
        return 0;
    }

    fn_801296F8(component, value);
    fn_8011FB5C(component, value);
    return 0;
}


int fn_80171664(void* state)
{
    int id;
    int value;
    unsigned char clamped;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    id = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    clamped = (value > 0 ? value : 0) > 0x7F
                  ? 0x7F
                  : (value > 0 ? value : 0);
    if (value != clamped) {
        fn_80163BB4(state, "Invalid Volume %i (range is 0-%i) ", value, 0x7F);
    }
    fn_8016A830(state, fn_801A98F4((unsigned short)id, clamped));
    return 1;
}



int fn_80171780(void* state)
{
    unsigned char clamped;
    int handle;
    int value;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    handle = fn_800F5C54(fn_8016A694(state, 1));
    value = (int)fn_8016A694(state, 2);
    clamped = (value > 0 ? value : 0) > 0x7F
                  ? 0x7F
                  : (value > 0 ? value : 0);
    if (value != clamped) {
        fn_80163BB4(state, "Invalid Volume %i (range is 0-%i) ", value, 0x7F);
    }
    fn_801A9984(handle, clamped);
    return 0;
}



int fn_8017187C(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801A9964(fn_800F5C54(fn_8016A694(state, 1)));
    return 0;
}



int fn_801718F4(void* state)
{
    int value;
    unsigned int result;
    void* text;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    text = fn_8016A784(state, 2);
    result = fn_80052310(value, text);
    fn_8016A830(state, result);
    return 1;
}



int fn_801719B4(void* state)
{
    int result;
    int arg2;
    int arg4;
    int arg1;
    int arg3;
    int arg5;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    arg1 = (int)fn_8016A694(state, 1);
    arg2 = (int)fn_8016A694(state, 2);
    arg3 = (int)fn_8016A694(state, 3);
    arg4 = (int)fn_8016A694(state, 4);
    arg5 = (int)fn_8016A694(state, 5);
    result = fn_800471F8();
    if (result != 0) {
        if (arg1 != 0) {
            fn_801AD734(arg1);
        }
        fn_801AD770((unsigned short)arg2, arg5);
        fn_801AD734(arg3);
        fn_801AD770((unsigned short)arg4, arg5);
    }

    fn_8016A830(state, result);
    return 1;
}



int fn_80171AF0(void* state)
{
    int arg1;
    int arg2;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    arg1 = (int)fn_8016A694(state, 1);
    arg2 = (int)fn_8016A694(state, 2);
    fn_801ACACC(arg1, arg2, 0, (int)fn_8016A694(state, 3));
    return 0;
}

int fn_80171BB4(void* state)
{
    int arg1;
    signed char clamped5;
    int arg4;
    unsigned char clamped3;
    int arg3;
    int arg2;
    int arg5;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5,
                    fn_8016A598(state));
        return 0;
    }

    arg1 = (int)fn_8016A694(state, 1);
    arg2 = (int)fn_8016A694(state, 2);
    arg3 = (int)fn_8016A694(state, 3);
    arg4 = (int)fn_8016A694(state, 4);
    arg5 = (int)fn_8016A694(state, 5);

    clamped3 = (arg3 > 0 ? arg3 : 0) > 0x7F ? 0x7F : (arg3 > 0 ? arg3 : 0);
    if (arg3 != clamped3) {
        fn_80163BB4(state, "Invalid Volume %i (range is 0-%i)", arg3, 0x7F);
    }

    clamped5 = (arg5 > 0 ? arg5 : 0) > 0xFF ? 0xFF : (arg5 > 0 ? arg5 : 0);
    if (arg5 != clamped5) {
        fn_80163BB4(state, "Invalid FadeFrames %i (range is 0-255)", arg5);
    }

    if (arg2 != 1 && arg2 != 2) {
        fn_80163BB4(state, "Invalid AudioType %d", arg2);
    }

    fn_801AC5E4(arg1, 0, clamped3, arg4, clamped5, arg2, 0);
    return 0;
}

int fn_80171D6C(void* state)
{
    int arg1;
    int arg2;
    unsigned char clamped2;
    unsigned char clamped1;
    int arg3;
    int arg4;
    signed char clamped4;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4,
                    fn_8016A598(state));
        return 0;
    }

    arg1 = (int)fn_8016A694(state, 1);
    arg2 = (int)fn_8016A694(state, 2);
    arg3 = (int)fn_8016A694(state, 3);
    arg4 = (int)fn_8016A694(state, 4);

    clamped2 = (arg2 > 0 ? arg2 : 0) > 0x7F ? 0x7F : (arg2 > 0 ? arg2 : 0);
    if (arg2 != clamped2) {
        fn_80163BB4(state, "Invalid Volume %i (range is 0-%i)", arg2, 0x7F);
    }

    clamped4 = (arg4 > 0 ? arg4 : 0) > 0x7F ? 0x7F : (arg4 > 0 ? arg4 : 0);
    if (arg4 != clamped4) {
        fn_80163BB4(state, "Invalid FadeFrames %i (range is 0-127)", arg4);
    }

    clamped1 = (arg1 > 0 ? arg1 : 0) > 0xFF ? 0xFF : (arg1 > 0 ? arg1 : 0);
    if (arg1 != clamped1) {
        fn_80163BB4(state, "Invalid GroupID %i (range is 0-255)", arg4);
    }

    fn_801AC5E4(0, clamped1, clamped2, arg3, clamped4, 0, 0);
    return 0;
}
