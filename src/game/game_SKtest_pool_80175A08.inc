/*
 * Original SKtest translation-unit prefix used to reproduce its shared
 * string pool. Non-promoted functions are emitted into a removable code
 * section; the three promoted handlers each use an isolated code section.
 */
#include "src/game/game_SKtest_pool_types.h"

typedef unsigned long size_t;
typedef struct Pair {
    const char* name;
    void* value;
} Pair;
typedef signed short s16;
typedef unsigned short u16;
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
typedef struct RuntimeEntry {
    unsigned char pad_00[0x2C];
    u32 id;
    unsigned char pad_30[0x38];
    u32 flags;
    unsigned char pad_6C[8];
} RuntimeEntry;
typedef struct RuntimeInfo {
    unsigned char pad_00[0xB0];
    u16 count;
    u16 pad_B2;
    RuntimeEntry* entries;
} RuntimeInfo;
typedef struct RuntimeObject {
    unsigned char pad_00[0x68];
    unsigned int flags;
} RuntimeObject;
typedef struct ShortVector {
    short x;
    short y;
    short z;
} ShortVector;
typedef struct FloatVector {
    float x;
    float y;
    float z;
} FloatVector;
typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;
typedef struct Descriptor { u32 word; u16 half; } Descriptor;
typedef struct EffectParams {
    u8 pad0[2]; u8 value2; signed char value3; u8 pad4[2]; u16 value6;
    u8 pad8[0xC];
    u8 value14, value15, value16, value17, value18, value19, value1A, pad1B;
    u32 value1C;
    u8 pad20[0x70];
} EffectParams;
typedef struct EffectDescriptor {
    u8 pad00;
    u8 byte01;
    u8 byte02;
    u8 byte03;
    u16 value04;
    u16 value06;
    u8 pad08[0xE];
    u8 byte16;
    u8 byte17;
    u8 pad18[4];
    u32 value1C;
    u32 value20;
    u32 value24;
    u32 value28;
    u8 pad2C[8];
    float value34;
    u32 value38;
    u8 pad3C[0x6C];
    u32 owner;
    u8 padAC[0x14];
} EffectDescriptor;
typedef struct SpawnedEffect {
    u8 pad00[8];
    int kind;
    u8 pad0C[0x3C];
    int channel;
} SpawnedEffect;
typedef struct CommandDescriptor {
    u32 value00;
    u8 pad04[4];
    int value08;
    int value0C;
    u8 pad10[8];
    Vec3f position;
    u8 bytes24[4];
    u16 value28;
    u8 pad2A[9];
    u8 byte33;
    u8 byte34;
    u8 pad35[0xF];
    void (*callback)(void);
    u8 pad48[0x28];
} CommandDescriptor;
typedef struct ResourceRef {
    u32 value;
} ResourceRef;
typedef signed char s8;
typedef struct ColorStep {
    s8 r, g, b, a;
} ColorStep;
typedef struct Object Object;
typedef struct PacketTemplate {
    u32 word0;
    u32 word1;
    u32 word2;
} PacketTemplate;

typedef struct EffectDescriptor_80173BDC {
    u8 bytes[144];
} EffectDescriptor_80173BDC;
typedef struct CommandDescriptor_801752B0 {
    u32 value00;
    u8 pad04[0x14];
    Vec3f position;
    u8 bytes24[4];
    u8 pad28[0xB];
    u8 byte33;
    u8 byte34;
    u8 pad35[0xF];
    int (*callback)(void*);
    u8 pad48[0x28];
} CommandDescriptor_801752B0;

#pragma section code_type ".discard"
  int seed_8016A5F4(void* context, int index);
  int fn_8016A5F4(void* context, int index);
#pragma section code_type ".discard"
 void* seed_8016A628(void* context, int index);
 void* fn_8016A628(void* context, int index);
#pragma section code_type ".discard"
 int seed_8016A650(void* context, int index);
 int fn_8016A650(void* context, int index);
#pragma section code_type ".discard"
  double seed_8016A694(void* context, int index);
  double fn_8016A694(void* context, int index);
#pragma section code_type ".discard"
  void* seed_8016A700(void* context, int index);
  void* fn_8016A700(void* context, int index);
#pragma section code_type ".discard"
  void* seed_8016A784(void* context, int index);
  void* fn_8016A784(void* context, int index);
#pragma section code_type ".discard"
   void seed_8016A7D8(Context* context);
   void fn_8016A7D8(Context* context);
#pragma section code_type ".discard"
   void seed_8016A830(Context* context, double value);
   void fn_8016A830(Context* context, double value);
#pragma section code_type ".discard"
   void seed_8016A890(Context* context, const char* string, int length);
   void fn_8016A890(Context* context, const char* string, int length);
#pragma section code_type ".discard"
  void seed_8016A8F8(void* context, const char* string);
  void fn_8016A8F8(void* context, const char* string);
#pragma section code_type ".discard"
 void seed_8016A950(void* context, void* unused1, int unused2);
 void fn_8016A950(void* context, void* unused1, int unused2);
#pragma section code_type ".discard"
   void seed_8016A970(Context* context, void* value, int index);
   void fn_8016A970(Context* context, void* value, int index);
#pragma section code_type ".discard"
   void seed_8016AA34(Context* context, const char* name);
   void fn_8016AA34(Context* context, const char* name);
#pragma section code_type ".discard"
   void seed_8016AAB4(Context* context);
   void fn_8016AAB4(Context* context);
#pragma section code_type ".discard"
  void seed_8016AB20(Context* context, const char* name);
  void fn_8016AB20(Context* context, const char* name);
#pragma section code_type ".discard"
    int seed_8016AB6C(Context* context, int special);
    int fn_8016AB6C(Context* context, int special);
#pragma section code_type ".discard"
  void seed_8016AC68(Context* context, int value);
  void fn_8016AC68(Context* context, int value);
#pragma section code_type ".discard"
   void seed_8016ACAC(Context* context, Pair* pairs, int count);
   void fn_8016ACAC(Context* context, Pair* pairs, int count);
#pragma section code_type ".discard"
   void seed_8016AD28(void);
   void fn_8016AD28(void);
#pragma section code_type ".discard"
   void seed_8016ADF0(s16 id, s16 value2, s16 value4);
   void fn_8016ADF0(s16 id, s16 value2, s16 value4);
#pragma section code_type ".discard"
   void seed_8016AF2C(void);
   void fn_8016AF2C(void);
#pragma section code_type ".discard"
   void seed_8016AFB0(s16 id);
   void fn_8016AFB0(s16 id);
#pragma section code_type ".discard"
   void seed_8016B030(int clear_all);
   void fn_8016B030(int clear_all);
#pragma section code_type ".discard"
   void seed_8016B0B4(s16 id, int value);
   void fn_8016B0B4(s16 id, int value);
#pragma section code_type ".discard"
 int seed_8016B1D0(void* output);
 int fn_8016B1D0(void* output);
#pragma section code_type ".discard"
 int seed_8016B21C(void* input);
 int fn_8016B21C(void* input);
#pragma section code_type ".discard"
  void seed_8016B26C(Pair* pairs, int count);
  void fn_8016B26C(Pair* pairs, int count);
#pragma section code_type ".discard"
   void seed_8016B29C(u32 size, Callback callback);
   void fn_8016B29C(u32 size, Callback callback);
#pragma section code_type ".discard"
  void* seed_8016B3A4(void* value, int alternate);
  void* fn_8016B3A4(void* value, int alternate);
#pragma section code_type ".discard"
   void seed_8016B400(int id, void* context, void* value);
   void fn_8016B400(int id, void* context, void* value);
#pragma section code_type ".discard"
 void* seed_8016B4B4(void* data, void* size, char* name, void* context, void* value);
 void* fn_8016B4B4(void* data, void* size, char* name, void* context, void* value);
#pragma section code_type ".discard"
  void* seed_8016B5CC(void* context, void* allocation, int size, const char* file, int line);
  void* fn_8016B5CC(void* context, void* allocation, int size, const char* file, int line);
#pragma section code_type ".discard"
  void seed_8016B914(int checkpoint);
  void fn_8016B914(int checkpoint);
#pragma section code_type ".discard"
 void* seed_8016BA38(int index);
 void* fn_8016BA38(int index);
#pragma section code_type ".discard"
double seed_8016BA4C(signed char* text, signed char** end);
double fn_8016BA4C(signed char* text, signed char** end);
#pragma section code_type ".discard"
 int seed_8016BD0C(void* state);
 int fn_8016BD0C(void* state);
#pragma section code_type ".discard"
 int seed_8016BDD8(void* state);
 int fn_8016BDD8(void* state);
#pragma section code_type ".discard"
 int seed_8016BE1C(void* state);
 int fn_8016BE1C(void* state);
#pragma section code_type ".discard"
 int seed_8016BEC8(void* state);
 int fn_8016BEC8(void* state);
#pragma section code_type ".discard"
 int seed_8016BF60(void* state);
 int fn_8016BF60(void* state);
#pragma section code_type ".discard"
 int seed_8016C008(void* state);
 int fn_8016C008(void* state);
#pragma section code_type ".discard"
 int seed_8016C0BC(void* state);
 int fn_8016C0BC(void* state);
#pragma section code_type ".discard"
 int seed_8016C164(void* state);
 int fn_8016C164(void* state);
#pragma section code_type ".discard"
  int seed_8016C238(void* state);
  int fn_8016C238(void* state);
#pragma section code_type ".discard"
  int seed_8016C3B4(void* state);
  int fn_8016C3B4(void* state);
#pragma section code_type ".discard"
  int seed_8016C4BC(void* state);
  int fn_8016C4BC(void* state);
#pragma section code_type ".discard"
 int seed_8016C668(void* state);
 int fn_8016C668(void* state);
#pragma section code_type ".discard"
 int seed_8016C6EC(void* state);
 int fn_8016C6EC(void* state);
#pragma section code_type ".discard"
 int seed_8016C774(void* state);
 int fn_8016C774(void* state);
#pragma section code_type ".discard"
 int seed_8016C7C4(void* state);
 int fn_8016C7C4(void* state);
#pragma section code_type ".discard"
 int seed_8016C890(void* state);
 int fn_8016C890(void* state);
#pragma section code_type ".discard"
 int seed_8016C96C(void* state);
 int fn_8016C96C(void* state);
#pragma section code_type ".discard"
 int seed_8016CA2C(void* state);
 int fn_8016CA2C(void* state);
#pragma section code_type ".discard"
 int seed_8016CB24(void* state);
 int fn_8016CB24(void* state);
#pragma section code_type ".discard"
 int seed_8016CBFC(void* state);
 int fn_8016CBFC(void* state);
#pragma section code_type ".discard"
 int seed_8016CDA0(void* state);
 int fn_8016CDA0(void* state);
#pragma section code_type ".discard"
 int seed_8016CE48(void* state);
 int fn_8016CE48(void* state);
#pragma section code_type ".discard"
 int seed_8016CEF0(void* state);
 int fn_8016CEF0(void* state);
#pragma section code_type ".discard"
 int seed_8016D040(void* state);
 int fn_8016D040(void* state);
#pragma section code_type ".discard"
 int seed_8016D0D4(void* state);
 int fn_8016D0D4(void* state);
#pragma section code_type ".discard"
 int seed_8016D144(void* state);
 int fn_8016D144(void* state);
#pragma section code_type ".discard"
 int seed_8016D1F8(void* state);
 int fn_8016D1F8(void* state);
#pragma section code_type ".discard"
 int seed_8016D2B8(void* state);
 int fn_8016D2B8(void* state);
#pragma section code_type ".discard"
int seed_8016D480(void* state);
int fn_8016D480(void* state);
#pragma section code_type ".discard"
 int seed_8016D574(void* state);
 int fn_8016D574(void* state);
#pragma section code_type ".discard"
 int seed_8016D680(void* state);
 int fn_8016D680(void* state);
#pragma section code_type ".discard"
 int seed_8016D7AC(void* state);
 int fn_8016D7AC(void* state);
#pragma section code_type ".discard"
 int seed_8016D8A4(void* state);
 int fn_8016D8A4(void* state);
#pragma section code_type ".discard"
 int seed_8016D92C(void* state);
 int fn_8016D92C(void* state);
#pragma section code_type ".discard"
 void seed_8016D9C0(unsigned int type, u16* first, u16* second);
 void fn_8016D9C0(unsigned int type, u16* first, u16* second);
#pragma section code_type ".discard"
  int seed_8016DA80(void* state);
  int fn_8016DA80(void* state);
#pragma section code_type ".discard"
  int seed_8016DB38(void* state);
  int fn_8016DB38(void* state);
#pragma section code_type ".discard"
 int seed_8016DBF0(void* state);
 int fn_8016DBF0(void* state);
#pragma section code_type ".discard"
 int seed_8016DCB0(void* state);
 int fn_8016DCB0(void* state);
#pragma section code_type ".discard"
 int seed_8016DD70(void);
 int fn_8016DD70(void);
#pragma section code_type ".discard"
 int seed_8016DD94(void* state);
 int fn_8016DD94(void* state);
#pragma section code_type ".discard"
 int seed_8016DE30(void* state);
 int fn_8016DE30(void* state);
#pragma section code_type ".discard"
 int seed_8016DECC(void* state);
 int fn_8016DECC(void* state);
#pragma section code_type ".discard"
 int seed_8016DF4C(void* state);
 int fn_8016DF4C(void* state);
#pragma section code_type ".discard"
 void seed_8016E254(int value);
 void fn_8016E254(int value);
#pragma section code_type ".discard"
   int seed_8016E294(void* state);
   int fn_8016E294(void* state);
#pragma section code_type ".discard"
 int seed_8016E3F0(void* state);
 int fn_8016E3F0(void* state);
#pragma section code_type ".discard"
 int seed_8016E514(void* state);
 int fn_8016E514(void* state);
#pragma section code_type ".discard"
 int seed_8016E5A8(void* state);
 int fn_8016E5A8(void* state);
#pragma section code_type ".discard"
 int seed_8016E634(void* state);
 int fn_8016E634(void* state);
#pragma section code_type ".discard"
 int seed_8016E6D4(void* state);
 int fn_8016E6D4(void* state);
#pragma section code_type ".discard"
 int seed_8016E7B8(void* state);
 int fn_8016E7B8(void* state);
#pragma section code_type ".discard"
 int seed_8016E854(void* state);
 int fn_8016E854(void* state);
#pragma section code_type ".discard"
 int seed_8016E8C4(void* state);
 int fn_8016E8C4(void* state);
#pragma section code_type ".discard"
   int seed_8016E8F8(void* state, int alternate);
   int fn_8016E8F8(void* state, int alternate);
#pragma section code_type ".discard"
 int seed_8016EACC(void* state);
 int fn_8016EACC(void* state);
#pragma section code_type ".discard"
 int seed_8016EAF4(void* state);
 int fn_8016EAF4(void* state);
#pragma section code_type ".discard"
 int seed_8016EB1C(void* state);
 int fn_8016EB1C(void* state);
#pragma section code_type ".discard"
 int seed_8016EC50(void* state);
 int fn_8016EC50(void* state);
#pragma section code_type ".discard"
 int seed_8016ED78(void* state);
 int fn_8016ED78(void* state);
#pragma section code_type ".discard"
 int seed_8016EEE4(void* state);
 int fn_8016EEE4(void* state);
#pragma section code_type ".discard"
 int seed_8016EFC4(void* state);
 int fn_8016EFC4(void* state);
#pragma section code_type ".discard"
 int seed_8016F088(void* state);
 int fn_8016F088(void* state);
#pragma section code_type ".discard"
 int seed_8016F128(void* state);
 int fn_8016F128(void* state);
#pragma section code_type ".discard"
 int seed_8016F1D0(void* state);
 int fn_8016F1D0(void* state);
#pragma section code_type ".discard"
  int seed_8016F2AC(void* state);
  int fn_8016F2AC(void* state);
#pragma section code_type ".discard"
    int seed_8016F400(void* state);
    int fn_8016F400(void* state);
#pragma section code_type ".discard"
 int seed_8016F4CC(void* state);
 int fn_8016F4CC(void* state);
#pragma section code_type ".discard"
 int seed_8016F580(void* state);
 int fn_8016F580(void* state);
#pragma section code_type ".discard"
 int seed_8016F678(void* state);
 int fn_8016F678(void* state);
#pragma section code_type ".discard"
 int seed_8016F78C(void* state);
 int fn_8016F78C(void* state);
#pragma section code_type ".discard"
  int seed_8016F8F8(void* state);
  int fn_8016F8F8(void* state);
#pragma section code_type ".discard"
 int seed_8016FA08(void* state);
 int fn_8016FA08(void* state);
#pragma section code_type ".discard"
 int seed_8016FB94(void* state);
 int fn_8016FB94(void* state);
#pragma section code_type ".discard"
 int seed_8016FC68(void* state);
 int fn_8016FC68(void* state);
#pragma section code_type ".discard"
 int seed_8016FD3C(void* state);
 int fn_8016FD3C(void* state);
#pragma section code_type ".discard"
 int seed_8016FE4C(void* state);
 int fn_8016FE4C(void* state);
#pragma section code_type ".discard"
 int seed_8016FEF8(void* state);
 int fn_8016FEF8(void* state);
#pragma section code_type ".discard"
 int seed_8016FFA8(void* first, void* second);
 int fn_8016FFA8(void* first, void* second);
#pragma section code_type ".discard"
  int seed_8016FFDC(void* state);
  int fn_8016FFDC(void* state);
#pragma section code_type ".discard"
  int seed_80170090(void* state);
  int fn_80170090(void* state);
#pragma section code_type ".discard"
  int seed_80170144(void* state);
  int fn_80170144(void* state);
#pragma section code_type ".discard"
  int seed_801701D4(void* state);
  int fn_801701D4(void* state);
#pragma section code_type ".discard"
  int seed_8017026C(void* state);
  int fn_8017026C(void* state);
#pragma section code_type ".discard"
  int seed_801702FC(void* state);
  int fn_801702FC(void* state);
#pragma section code_type ".discard"
 int seed_8017038C(void* state);
 int fn_8017038C(void* state);
#pragma section code_type ".discard"
 int seed_80170438(void* state);
 int fn_80170438(void* state);
#pragma section code_type ".discard"
 int seed_801704F8(void* state);
 int fn_801704F8(void* state);
#pragma section code_type ".discard"
 int seed_801705D4(void* state);
 int fn_801705D4(void* state);
#pragma section code_type ".discard"
 int seed_80170658(void* state);
 int fn_80170658(void* state);
#pragma section code_type ".discard"
 int seed_801706DC(void* state);
 int fn_801706DC(void* state);
#pragma section code_type ".discard"
 int seed_80170814(void* state);
 int fn_80170814(void* state);
#pragma section code_type ".discard"
 int seed_80170880(void* state);
 int fn_80170880(void* state);
#pragma section code_type ".discard"
  int seed_80170980(void* state);
  int fn_80170980(void* state);
#pragma section code_type ".discard"
   int seed_80170A40(void* state);
   int fn_80170A40(void* state);
#pragma section code_type ".discard"
  int seed_80170B5C(void* state);
  int fn_80170B5C(void* state);
#pragma section code_type ".discard"
 int seed_80170C18(void* state);
 int fn_80170C18(void* state);
#pragma section code_type ".discard"
 int seed_80170C84(void* state);
 int fn_80170C84(void* state);
#pragma section code_type ".discard"
 int seed_80170D04(void* state);
 int fn_80170D04(void* state);
#pragma section code_type ".discard"
 int seed_80170DF4(void* state);
 int fn_80170DF4(void* state);
#pragma section code_type ".discard"
 int seed_80170E9C(void* state);
 int fn_80170E9C(void* state);
#pragma section code_type ".discard"
 int seed_80170F44(void* state);
 int fn_80170F44(void* state);
#pragma section code_type ".discard"
 int seed_80171020(void* state);
 int fn_80171020(void* state);
#pragma section code_type ".discard"
 int seed_801710FC(void* state);
 int fn_801710FC(void* state);
#pragma section code_type ".discard"
    int seed_801711D0(void* state);
    int fn_801711D0(void* state);
#pragma section code_type ".discard"
 int seed_8017138C(void* state);
 int fn_8017138C(void* state);
#pragma section code_type ".discard"
 int seed_80171418(void* state);
 int fn_80171418(void* state);
#pragma section code_type ".discard"
 int seed_801714BC(void* state);
 int fn_801714BC(void* state);
#pragma section code_type ".discard"
int seed_80171560(void* state);
int fn_80171560(void* state);
#pragma section code_type ".discard"
 int seed_80171664(void* state);
 int fn_80171664(void* state);
#pragma section code_type ".discard"
 int seed_80171780(void* state);
 int fn_80171780(void* state);
#pragma section code_type ".discard"
 int seed_8017187C(void* state);
 int fn_8017187C(void* state);
#pragma section code_type ".discard"
 int seed_801718F4(void* state);
 int fn_801718F4(void* state);
#pragma section code_type ".discard"
 int seed_801719B4(void* state);
 int fn_801719B4(void* state);
#pragma section code_type ".discard"
 int seed_80171AF0(void* state);
 int fn_80171AF0(void* state);
#pragma section code_type ".discard"
 int seed_80171BB4(void* state);
 int fn_80171BB4(void* state);
#pragma section code_type ".discard"
 int seed_80171D6C(void* state);
 int fn_80171D6C(void* state);
#pragma section code_type ".discard"
 int seed_80171F30(void* state);
 int fn_80171F30(void* state);
#pragma section code_type ".discard"
 int seed_80171FBC(void* state);
 int fn_80171FBC(void* state);
#pragma section code_type ".discard"
 int seed_80172058(void* state);
 int fn_80172058(void* state);
#pragma section code_type ".discard"
 int seed_801720E8(void* state);
 int fn_801720E8(void* state);
#pragma section code_type ".discard"
 int seed_80172150(void* state);
 int fn_80172150(void* state);
#pragma section code_type ".discard"
 int seed_80172204(void* state);
 int fn_80172204(void* state);
#pragma section code_type ".discard"
 int seed_8017230C(void* state);
 int fn_8017230C(void* state);
#pragma section code_type ".discard"
 int seed_801723B8(void* state);
 int fn_801723B8(void* state);
#pragma section code_type ".discard"
 int seed_80172470(void* state);
 int fn_80172470(void* state);
#pragma section code_type ".discard"
 int seed_8017250C(void* state);
 int fn_8017250C(void* state);
#pragma section code_type ".discard"
 int seed_801725A8(void* state);
 int fn_801725A8(void* state);
#pragma section code_type ".discard"
 int seed_80172610(void* state);
 int fn_80172610(void* state);
#pragma section code_type ".discard"
   int seed_801726EC(void* state);
   int fn_801726EC(void* state);
#pragma section code_type ".discard"
 int seed_8017288C(void* state);
 int fn_8017288C(void* state);
#pragma section code_type ".discard"
 int seed_80172944(void* state);
 int fn_80172944(void* state);
#pragma section code_type ".discard"
 int seed_801729CC(void* state);
 int fn_801729CC(void* state);
#pragma section code_type ".discard"
 int seed_80172A4C(void* state);
 int fn_80172A4C(void* state);
#pragma section code_type ".discard"
    int seed_80172ACC(void* state);
    int fn_80172ACC(void* state);
#pragma section code_type ".discard"
 int seed_80172BB0(void* state);
 int fn_80172BB0(void* state);
#pragma section code_type ".discard"
 int seed_80172C78(void* state);
 int fn_80172C78(void* state);
#pragma section code_type ".discard"
 int seed_80172D04(void* state);
 int fn_80172D04(void* state);
#pragma section code_type ".discard"
  int seed_80172DB8(void* state);
  int fn_80172DB8(void* state);
#pragma section code_type ".discard"
int seed_80172E78(void);
int fn_80172E78(void);
#pragma section code_type ".discard"
 int seed_80172E80(void* state);
 int fn_80172E80(void* state);
#pragma section code_type ".discard"
  int seed_80172EEC(void* state);
  int fn_80172EEC(void* state);
#pragma section code_type ".discard"
   int seed_80172FF0(void* state);
   int fn_80172FF0(void* state);
#pragma section code_type ".discard"
  int seed_80173104(void* state);
  int fn_80173104(void* state);
#pragma section code_type ".discard"
 int seed_8017320C(void* state);
 int fn_8017320C(void* state);
#pragma section code_type ".discard"
   int seed_80173270(void* state);
   int fn_80173270(void* state);
#pragma section code_type ".discard"
     int seed_801734B4(void* state);
     int fn_801734B4(void* state);
#pragma section code_type ".discard"
     int seed_80173770(void* state);
     int fn_80173770(void* state);
#pragma section code_type ".discard"
    int seed_801739E8(void* state);
    int fn_801739E8(void* state);
#pragma section code_type ".discard"
float seed_80173B6C(register short* source, register float* destination);
float fn_80173B6C(register short* source, register float* destination);
#pragma section code_type ".discard"
 int seed_80173B78(void* state);
 int fn_80173B78(void* state);
#pragma section code_type ".discard"
     int seed_80173BDC(void* arg);
     int fn_80173BDC(void* arg);
#pragma section code_type ".discard"
   int seed_80173D44(void* arg);
   int fn_80173D44(void* arg);
#pragma section code_type ".discard"
   int seed_80173F04(void* arg);
   int fn_80173F04(void* arg);
#pragma section code_type ".discard"
   int seed_80174184(void* state);
   int fn_80174184(void* state);
#pragma section code_type ".discard"
   int seed_80174358(void* state);
   int fn_80174358(void* state);
#pragma section code_type ".discard"
 int seed_80174610(void* state);
 int fn_80174610(void* state);
#pragma section code_type ".discard"
    int seed_80174694(void* state);
    int fn_80174694(void* state);
#pragma section code_type ".discard"
  int seed_801748EC(void* state);
  int fn_801748EC(void* state);
#pragma section code_type ".discard"
 int seed_801749A8(void* state);
 int fn_801749A8(void* state);
#pragma section code_type ".discard"
 int seed_80174A94(void* state);
 int fn_80174A94(void* state);
#pragma section code_type ".discard"
 int seed_80174B14(void* state);
 int fn_80174B14(void* state);
#pragma section code_type ".discard"
 int seed_80174B94(void* state);
 int fn_80174B94(void* state);
#pragma section code_type ".discard"
 int seed_80174C34(void* state);
 int fn_80174C34(void* state);
#pragma section code_type ".discard"
 int seed_80174CD4(void* state);
 int fn_80174CD4(void* state);
#pragma section code_type ".discard"
 int seed_80174DB8(void* state);
 int fn_80174DB8(void* state);
#pragma section code_type ".discard"
 int seed_80174EB4(void* state);
 int fn_80174EB4(void* state);
#pragma section code_type ".discard"
int seed_80174F2C(void* state);
int fn_80174F2C(void* state);
#pragma section code_type ".discard"
 int seed_80175164(void* state);
 int fn_80175164(void* state);
#pragma section code_type ".discard"
 int seed_801751DC(void* state);
 int fn_801751DC(void* state);
#pragma section code_type ".discard"
 int seed_80175244(void* state);
 int fn_80175244(void* state);
#pragma section code_type ".discard"
 int seed_801752B0(void* state);
 int fn_801752B0(void* state);
#pragma section code_type ".discard"
 int seed_80175464(void* state);
 int fn_80175464(void* state);
#pragma section code_type ".discard"
  int seed_801754D0(void* state);
  int fn_801754D0(void* state);
#pragma section code_type ".discard"
 void seed_80175534(int value);
 void fn_80175534(int value);
#pragma section code_type ".discard"
 int seed_8017553C(void* state);
 int fn_8017553C(void* state);
#pragma section code_type ".discard"
    int seed_801755FC(void* state);
    int fn_801755FC(void* state);
#pragma section code_type ".discard"
  int seed_8017583C(void* state);
  int fn_8017583C(void* state);
#pragma section code_type ".discard"
 int seed_801758F8(void* state);
 int fn_801758F8(void* state);
#pragma section code_type ".discard"
 int seed_80175964(void* state);
 int fn_80175964(void* state);
#pragma section code_type ".text_80175A08"
  int fn_80175A08(void* state);
#pragma section code_type ".text_80175BB8"
  int fn_80175BB8(void* state);
#pragma section code_type ".discard"
 int seed_80175E64(void* state);
 int fn_80175E64(void* state);
#pragma section code_type ".discard"
  int seed_80175F0C(void* state);
  int fn_80175F0C(void* state);
#pragma section code_type ".discard"
 int seed_80175FD4(void* state);
 int fn_80175FD4(void* state);
#pragma section code_type ".discard"
 int seed_80176098(void* state);
 int fn_80176098(void* state);
#pragma section code_type ".discard"
 int seed_80176160(void* state);
 int fn_80176160(void* state);
#pragma section code_type ".discard"
 int seed_80176220(void* state);
 int fn_80176220(void* state);
#pragma section code_type ".discard"
 int seed_801762E8(void* state);
 int fn_801762E8(void* state);
#pragma section code_type ".discard"
 int seed_801763D8(void* state);
 int fn_801763D8(void* state);
#pragma section code_type ".discard"
 int seed_80176488(void* state);
 int fn_80176488(void* state);
#pragma section code_type ".discard"
 int seed_8017652C(void* state);
 int fn_8017652C(void* state);
#pragma section code_type ".discard"
 int seed_801765C4(void* state);
 int fn_801765C4(void* state);
#pragma section code_type ".discard"
 int seed_80176644(void* state);
 int fn_80176644(void* state);
#pragma section code_type ".discard"
 int seed_801766F0(void* state);
 int fn_801766F0(void* state);
#pragma section code_type ".discard"
 int seed_80176770(void* state);
 int fn_80176770(void* state);
#pragma section code_type ".discard"
 int seed_801767F0(void* state);
 int fn_801767F0(void* state);
#pragma section code_type ".discard"
 int seed_80176870(void* state);
 int fn_80176870(void* state);
#pragma section code_type ".discard"
 int seed_80176914(void* state);
 int fn_80176914(void* state);
#pragma section code_type ".discard"
 int seed_80176994(void* state);
 int fn_80176994(void* state);
#pragma section code_type ".discard"
 int seed_80176A14(void* state);
 int fn_80176A14(void* state);
#pragma section code_type ".text_80176A94"
 int fn_80176A94(void* state);
#pragma section code_type ".discard"
 int seed_80176BA4(void* state);
 int fn_80176BA4(void* state);
#pragma section code_type ".discard"
 int seed_80176C64(void* state);
 int fn_80176C64(void* state);
#pragma section code_type ".discard"
   int seed_80176D14(void* state);
   int fn_80176D14(void* state);
#pragma section code_type ".discard"
 int seed_80176DF4(void* state);
 int fn_80176DF4(void* state);
#pragma section code_type ".discard"
 int seed_80176E98(void* state);
 int fn_80176E98(void* state);
#pragma section code_type ".discard"
 int seed_80176F34(void* state);
 int fn_80176F34(void* state);
#pragma section code_type ".discard"
 int seed_80176FA0(void* state);
 int fn_80176FA0(void* state);
#pragma section code_type ".discard"
 int seed_80177034(void* state);
 int fn_80177034(void* state);
#pragma section code_type ".discard"
 int seed_801770F8(void* state);
 int fn_801770F8(void* state);
#pragma section code_type ".discard"
 int seed_8017718C(void* state);
 int fn_8017718C(void* state);
#pragma section code_type ".discard"
 int seed_80177244(void* state);
 int fn_80177244(void* state);
#pragma section code_type ".discard"
  int seed_801772C8(void* state);
  int fn_801772C8(void* state);
#pragma section code_type ".discard"
 int seed_80177388(void* state);
 int fn_80177388(void* state);

extern void* fn_80024638(void*, void*, u32*);
extern void fn_80045A24(int, int);
extern void fn_80045BE0(int);
extern int fn_800460EC(void);
extern int fn_800467F0(int, int);
extern void fn_80046CE4(int);
extern void fn_80046D38(int);
extern void fn_80046DB4(int);
extern int fn_80047180(void);
extern int fn_800471F8(void);
extern void fn_80047240(int);
extern int fn_800473AC(void);
extern int fn_800480D4(void*, void*);
extern int fn_800483A0(void*, void*);
extern int fn_80048610(s16);
extern void fn_80048620(int);
extern void fn_800486A8(int);
extern void fn_80049774(int);
extern unsigned int fn_80052310(int, void*);
extern unsigned int fn_800F5C54(double);
extern int fn_800F8CF0(int);
extern int fn_800F8D14(int);
extern int fn_800F8D2C(int);
extern int fn_800F9D4C(char*, const char*, ...);
extern unsigned int fn_800FBFB0(void);
extern int fn_800FD228(void*, const char*);
extern char* fn_800FD40C(char*, const char*);
extern void fn_8011DD8C(int, int);
extern void fn_8011E26C(int);
extern void fn_8011F0E8(void*, Vec3*);
extern unsigned int fn_8011FA8C(void*, int, int);
extern void fn_8011FABC(void*, int, int);
extern void fn_8011FB5C(void*, int);
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
extern void fn_801296F8(void*, int);
extern void* fn_8012976C(void*, int, unsigned short, Vec3*, float);
extern void* fn_80129878(void*, int, unsigned short, Vec3*, float);
extern void* fn_80129AF4(void*, int, unsigned short, float, float);
extern int fn_8012A1BC(void*, int);
extern void fn_8012B344(void*);
extern void fn_8012B7A0(void*, float);
extern float fn_8012B7D0(void*, Vec3*);
extern u8 fn_8012B8A8(void*, const Vec3f*);
extern void fn_8012C478(void*, int, int);
extern void* fn_8012C62C(void*, int, void*, void*, void*, int);
extern void* fn_8012C62C_c(void*, int, Color*, ColorStep*, Color*, int);
extern void fn_801301B0(void*, int, int);
extern void fn_80130214(void*, u8);
extern void fn_80130258(void*, unsigned int, unsigned int);
extern u8 fn_801303BC(void*);
extern void fn_80130434(void*, int);
extern void* fn_80138B90(void*, int, int);
extern void fn_801441C0(int, int, int);
extern void fn_80147E88(EffectDescriptor*);
extern void* fn_80148008(Vec3f*, const Vec3s*, EffectDescriptor*, void (*)(void));
extern void* fn_80148008_d(Vec3f*, void*, EffectParams*, void (*)(void));
extern void* fn_80148300(void*, EffectDescriptor*, SpawnedEffect*);
extern SpawnedEffect* fn_80149E04(void);
extern void fn_80149EB8(SpawnedEffect*);
extern void fn_8014C37C(int, ResourceRef*);
extern void fn_8014C988(ResourceRef*, int);
extern void fn_8014CBC0(ResourceRef*);
extern void fn_8014D478(void*, Vec3*, Vec3*, int, int, void*, int);
extern void fn_8014F4CC(EffectDescriptor*, SpawnedEffect*);
extern void* fn_80153050(Vec3f*, Vec3s*, int, int, int, int, u8*, int, int, int, int, int);
extern void fn_80153104(void*);
extern void fn_801533A8(Vec3f*, Vec3s*, int, int, int, int, int);
extern void fn_80153F00(u8, u8, u8, u8, Color*, int, Vec3f*, void*, u8, u8, int);
extern void fn_80154A98(Vec3*, Vec3s*, int, u16*, float);
extern void* fn_80155DB4(void*);
extern void* fn_80155DB4_w(void);
extern void fn_801568B8(void*, int);
extern void* fn_80156938(void*);
extern int fn_80156940(void*);
extern void* fn_80156948(int);
extern s16 fn_801578E8(void*);
extern s16 fn_801578F4(void*);
extern unsigned int fn_80157900(void*);
extern u8 fn_80157918(void*);
extern unsigned short fn_80157948(Object*);
extern unsigned short fn_80157994(Object*);
extern void fn_80157A28(Object*, unsigned short);
extern u8 fn_80157AB8(void*);
extern void fn_80157B3C(void*, u8);
extern void fn_80157B48(void*, s16);
extern void fn_80157B54(void*, s16);
extern void fn_80157B60(void*, u8);
extern void fn_80157B94(void*, u8);
extern void fn_80157BA0(void*, s16);
extern void fn_80157BAC(void*, u8);
extern void fn_80157BB8(void*, u8);
extern unsigned int fn_80157BC4(void*);
extern unsigned int fn_80157BD0(void*);
extern unsigned int fn_80157BDC(void*);
extern unsigned int fn_80157BF4(Object*);
extern int fn_8015821C(Object*);
extern unsigned short fn_80158234(Object*);
extern int fn_801589AC(int, int, Vec3*, Vec3*, float*);
extern Vec3s* fn_80158ABC(int, int, void*);
extern int fn_80158B20(int, int, Vec3*, Vec3*, float*);
extern Vec3s* fn_80158CC8(int, int, Vec3s*);
extern void fn_801593B4(int);
extern void fn_801593FC(int);
extern void fn_8015977C(int, int, int, int, int);
extern RuntimeInfo* fn_8015C28C(int);
extern int fn_8015C4A4(int, int);
extern int fn_8015C524(unsigned int, int);
extern void fn_8015C7D8(int);
extern void fn_8015C8A4(int, int);
extern unsigned int fn_8015C910(void);
extern void fn_8015C948(int, void*, void*, int, int, int, int, int, int, int, int);
extern void* fn_8015E4A4(void);
extern void fn_8016057C(Context*, int);
extern void* fn_80160EBC(void*, void*, void*, void*);
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
extern u32 fn_80178F14(int, int, int, int, int, int);
extern void fn_801798DC(Vec3*, float);
extern void fn_80179904(Vec3s*, short);
extern void fn_80179DB0(float*, short*);
extern void fn_8017A244(const void*, void*, float);
extern void fn_8017A34C(Vec4*, Vec4*, Vec4*);
extern void* fn_8017AF64(void);
extern void fn_8017AF78(void);
extern void fn_8017BA60(const char*, int);
extern void fn_8017FF1C(void*, int);
extern void fn_80183454(void);
extern void fn_801834F0(void);
extern void fn_8018358C(EffectParams*);
extern void fn_801839A4(EffectDescriptor*);
extern void fn_801839D8(void);
extern void fn_8019B13C(EffectDescriptor*);
extern void fn_801A5C30(int);
extern int fn_801A5CE0(void);
extern int fn_801A5D04(void);
extern void fn_801A7DEC(int);
extern unsigned int fn_801A98F4(unsigned short, unsigned char);
extern void fn_801A9964(int);
extern void fn_801A9984(int, unsigned char);
extern void fn_801A9DCC(int, int, int);
extern void fn_801AC350(int, int, int);
extern void fn_801AC5E4(int, unsigned char, unsigned char, int, signed char, int, int);
extern int fn_801AC9F4(unsigned short, unsigned char, Vec3f*, signed char);
extern void fn_801ACACC(int, int, int, int);
extern void fn_801ACD8C(void);
extern void fn_801AD404(unsigned char, unsigned char, int);
extern void fn_801AD46C(unsigned char*, unsigned char*);
extern void fn_801AD490(void);
extern void fn_801AD4B4(int, int, int, int);
extern void fn_801AD6F4(int);
extern int fn_801AD72C(void);
extern void fn_801AD734(int);
extern void fn_801AD770(unsigned short, int);
extern int fn_801AF824(void);
extern int fn_801AF924(void);
extern int fn_801B002C(int, int, int, int, int);
extern void fn_801B05B0(int, u8);
extern int fn_801B05E8(int, int, int, int, void*, int, int, int);
extern void fn_801B08BC(int, int, int);
extern int fn_801B0B30(int);
extern void fn_801B0CA4(int, int);
extern void fn_801B0D30(void);
extern void fn_801B1A1C(void*, int);
extern void fn_801B2348(int);
extern void fn_801B2380(int);
extern int fn_801B243C(void);
extern void fn_801E7974(void*, int);
extern void fn_801E79A0(void*, int);
extern int fn_801E79C4(void*, int);
extern int fn_801E79FC(void*, int);
extern void fn_801E7DC8(int);
extern void fn_801E7DCC(char*, ...);
extern void fn_801E807C(int, int, char*, ...);
extern void fn_801E8170(int, int, int);
extern int fn_801E8328();
extern void fn_801E8EFC(int, int);
extern void fn_801EB2FC(int);
extern void fn_801ED57C(int);
extern void fn_801EF36C(int);
extern void fn_801F0294(float, int);
extern void fn_801F348C(void*, int);
extern void fn_801F3528(void*);
extern void fn_801F53E8(int);
extern void fn_801F5980(void);
extern void fn_801F6198(void*, u16, u16);
extern void fn_801F6228(void*, u16, u16);
extern void fn_801F6370(void*, int);
extern void fn_801F63E4(void*, int);
extern void fn_801F640C(void*, int, int);
extern void fn_801F64A8(void*, int, int);
extern void fn_801F6540(void);
extern void fn_801F6FD8(Vec3);
extern void fn_801F6FFC(void*);
extern void fn_801F700C(int, void*);
extern void fn_801F7034(void*, int);
extern void fn_801F70B0(void*, float);
extern void fn_801F70C4(void*, float);
extern void fn_801F70D8(void*, int);
extern void fn_801F7208(void*, float);
extern void fn_801F7210(void*, float);
extern void fn_801F74C8(int, int, int);
extern void fn_801F75FC(int, int, float);
extern void fn_801F86F4(int);
extern int fn_801F8748(int, void*, int, int, int);
extern void fn_801F898C(void*, int);
extern unsigned int fn_801F99B8(void*);
extern void fn_801FA198(unsigned int, void*, int, int, int, int, int, int, int);
extern void fn_801FA454(int, u16);
extern void fn_801FD240(void);
extern void* fn_801FD24C(void);
extern void fn_801FD534(void*);
extern void* fn_801FD6F4(void*);
extern void fn_801FD8F0(void);
extern int fn_801FE05C(void*);
extern void fn_801FE8DC(CommandDescriptor*, float, float, float);
extern void* fn_801FEA8C(u32, int, const char*, int);
extern void fn_8020034C(int);
extern void fn_80200EAC(int, int, int, int, float);
extern int fn_80200F3C(int, int);
extern void fn_8020104C(int, void*, void*, int, float);
extern void fn_80201138(int, void*, int, int, int, float);
extern unsigned long long fn_8020123C();
extern void *fn_80201814();
extern int fn_80201948(int, int);
extern void* fn_802019EC(int, void*);
extern void* fn_80201ADC(void);
extern void* fn_80201B3C(void);
extern int fn_80201B44();
extern int fn_80201B54();
extern int fn_80201B5C(void*);
extern int fn_80201B64(void*);
extern void *fn_80201B94();
extern void *fn_80201B9C();
extern void* fn_80201BC0(void*);
extern void *fn_80201BC8();
extern void *fn_80201C24();
extern int fn_80201C2C(void*);
extern int fn_80201C48(void);
extern void fn_80201D14(void*, int);
extern void fn_80201D1C(void*, int);
extern void fn_80201D2C(void*, int);
extern void fn_80201D34(void*, int);
extern void fn_80201E78(FloatVector*, void*);
extern int fn_80201EB8();
extern void fn_80201F80(void*, int, int);
extern void fn_802020B4(void*, int);
extern int fn_80204888(int);
extern void* fn_80204A8C(void);
extern int fn_80204C2C(void*);
extern void fn_80204CE4(void*, void*);
extern void fn_80204EC8(void*, void*);
extern void fn_80205868(void*, int, const PacketTemplate*, int);
extern int fn_80206634(void*);
extern int fn_802066E0(int, int);
extern void fn_8020AFE4(void*);
extern void fn_8020B344(void*);
extern int fn_80213394(const char*, DVDFileInfo*);
extern void fn_8021345C(DVDFileInfo*);
extern int fn_802136A4(const char*);
extern int fn_80220A68(int, void*, int);
extern int fn_80220B4C(int);
extern int fn_802213DC(int);
extern void* lbl_8023A878[];
extern const double lbl_8023A900[17];
extern const PacketTemplate lbl_8023A988;
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
extern const char lbl_80250358[];
extern const char lbl_8025038C[];
extern const char lbl_802503C8[];
extern const char lbl_80250404[];
extern const char lbl_80250414[];
extern const char lbl_80250450[];
extern const char lbl_8025047C[];
extern RefEntry lbl_805FAA60[10];
extern char lbl_805FAAB0[];
extern int lbl_805FAAD8[1537];
extern char lbl_805FC2DC[];
extern ShortVector lbl_805FC2E8[];
extern char lbl_8063C6B8[];
extern unsigned char lbl_8063CD18[];
extern char lbl_8063D378[];
extern char lbl_8063D400[];
extern float lbl_8063D400_f[];
extern int lbl_8064B814;
extern char lbl_8064BC00;
extern char lbl_8064BC08;
extern char lbl_8064BC10;
extern char lbl_8064BC18;
extern void* lbl_8064C3C8;
extern void* lbl_8064C4E0;
extern void* lbl_8064C4E4;
extern int lbl_8064C600;
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
extern int lbl_8064D1E8;
extern ShortVector lbl_8064D1EC;
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
extern const double lbl_806506D8;
extern int lbl_806506E0;
extern const Vec3s lbl_806506E4;
extern const Vec3s lbl_806506EC;
extern const u32 lbl_806506F4;
extern const float lbl_806506F8;
extern const u32 lbl_806506FC;
extern const float lbl_80650700;
extern const float lbl_80650704;
extern const u32 lbl_80651CA0;
extern const u16 lbl_80651CA4;
extern const u32 lbl_80651CA8;
extern const u16 lbl_80651CAC;
extern const u32 lbl_80651CB0;
extern const u32 lbl_80651CB4;
extern const u32 lbl_80651CB8;
extern void* memcpy(void*, const void*, unsigned long);
extern void* memset(void*, int, unsigned long);
extern size_t strlen(const char*);

#pragma section code_type ".discard"


int seed_8016A5F4(void* context, int index)
{
    Value* value = fn_8016A55C(context, index);
    if (value == 0) {
        return -1;
    }
    return value->type;
}


#pragma section code_type ".discard"

void* seed_8016A628(void* context, int index)
{
    if (index == -1) {
        return lbl_8024FE60;
    }
    return lbl_8023A878[index];
}


#pragma section code_type ".discard"

int seed_8016A650(void* context, int index)
{
    int type = fn_8016A5F4(context, index);
    return type == 2 || type == 3;
}


#pragma section code_type ".discard"


double seed_8016A694(void* context, int index)
{
    int invalid;
    Value* value = fn_8016A55C(context, index);
    invalid = value == 0 || (value->type != 2 && fn_80168A08(value) != 0);
    return invalid ? lbl_80650688 : value->number;
}


#pragma section code_type ".discard"


void* seed_8016A700(void* context, int index)
{
    Value* value = fn_8016A55C(context, index);
    int invalid = value == 0 ||
                  (value->type != 3 && fn_80168A70(context, value) != 0);
    return invalid ? 0 : (char*)value->pointer + 20;
}


#pragma section code_type ".discard"


void* seed_8016A784(void* context, int index)
{
    Value* value = fn_8016A55C(context, index);
    int invalid = value == 0 || value->type != 0;
    return invalid ? 0 : value->pointer2[1];
}


#pragma section code_type ".discard"



void seed_8016A7D8(Context* context)
{
    ((Value*)context->current)->type = 1;
    if (context->current == context->end) {
        fn_8016057C(context, 1);
    }
    context->current = (char*)context->current + 16;
}


#pragma section code_type ".discard"



void seed_8016A830(Context* context, double value)
{
    ((Value*)context->current)->number = value;
    ((Value*)context->current)->type = 2;
    if (context->current == context->end) {
        fn_8016057C(context, 1);
    }
    context->current = (char*)context->current + 16;
}


#pragma section code_type ".discard"



void seed_8016A890(Context* context, const char* string, int length)
{
    ((Value*)context->current)->value = fn_80166E3C(context, string, length);
    ((Value*)context->current)->type = 3;
    if (context->current == context->end) {
        fn_8016057C(context, 1);
    }
    context->current = (char*)context->current + 16;
}


#pragma section code_type ".discard"


void seed_8016A8F8(void* context, const char* string)
{
    if (string == 0) {
        fn_8016A7D8(context);
    } else {
        fn_8016A890(context, string, strlen(string));
    }
}


#pragma section code_type ".discard"

void seed_8016A950(void* context, void* unused1, int unused2)
{
    fn_80168C74(context);
}


#pragma section code_type ".discard"



void seed_8016A970(Context* context, void* value, int index)
{
    if ((unsigned)(index + 1) > 1) {
        if (index < 6 || index > context->limit) {
            fn_80163BB4(context, lbl_8024FE6C, index);
        }
    }
    ((Value*)context->current)->value = fn_80167014(context, value, index);
    ((Value*)context->current)->type = 0;
    if (context->current == context->end) {
        fn_8016057C(context, 1);
    }
    context->current = (char*)context->current + 16;
}


#pragma section code_type ".discard"



void seed_8016AA34(Context* context, const char* name)
{
    Value* current = (Value*)context->current;
    *current = *fn_80168F84(context, fn_801670A8(context, name));
    context->current = current;
    if (context->current == context->end) {
        fn_8016057C(context, 1);
    }
    context->current = (char*)context->current + 16;
}


#pragma section code_type ".discard"



void seed_8016AAB4(Context* context)
{
    ((Value*)context->current)->value = fn_80167798(context, 0);
    ((Value*)context->current)->type = 4;
    if (context->current == context->end) {
        fn_8016057C(context, 1);
    }
    context->current = (char*)context->current + 16;
}


#pragma section code_type ".discard"


void seed_8016AB20(Context* context, const char* name)
{
    void* current = context->current;
    fn_80169068(context, fn_801670A8(context, name));
    context->current = (char*)current - 16;
}


#pragma section code_type ".discard"




int seed_8016AB6C(Context* context, int special)
{
    int index;

    if (((int*)&((Value*)context->current)[-1])[0] == 1) {
        index = -1;
    } else {
        if (context->free != -1) {
            index = context->free;
            context->free = context->entries[index].next;
        } else {
            context->entries = fn_8016393C(context, context->entries,
                                            context->count, 1, sizeof(Entry),
                                            lbl_8024FE8C, 0x7FFFFFFD);
            context->allocated_size += sizeof(Entry);
            index = context->count++;
        }
        context->entries[index].value = ((Value*)context->current)[-1];
        context->entries[index].next = special ? -4 : -2;
    }
    context->current = (Value*)context->current - 1;
    return index;
}


#pragma section code_type ".discard"


void seed_8016AC68(Context* context, int value)
{
    if (value > 0x3FFFFF) {
        context->limit_5C = -1;
    } else {
        context->limit_5C = value << 10;
    }
    fn_80161FA0(context, value);
}


#pragma section code_type ".discard"



void seed_8016ACAC(Context* context, Pair* pairs, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        fn_8016A950(context, pairs[i].value, 0);
        fn_8016AB20(context, pairs[i].name);
    }
}


#pragma section code_type ".discard"



void seed_8016AD28(void)
{
    int i;
    int count;

    i = 0;
    count = 0;

    do {
        if (fn_80048610(lbl_805FAA60[i].id) == 0 && lbl_805FAA60[i].id > 0 &&
            lbl_805FAA60[i].value6 != 0) {
            count++;
        }
        i++;
    } while (i < 10);

    if ((u16)count != 0) {
        u16 value = count;
        fn_801E7DCC(lbl_8024FEA8, value);
        fn_801E807C(0x50, 0x2D, lbl_8024FECC, value);
        fn_801E8170(0x50, 0x2D, 1);
    }
}


#pragma section code_type ".discard"



void seed_8016ADF0(s16 id, s16 value2, s16 value4)
{
    int i;
    int selected = -1;

    for (i = 0; i < 10; i++) {
        if (lbl_805FAA60[i].id == id) {
            selected = i;
            break;
        }
        if (selected == -1 && lbl_805FAA60[i].id == 0) {
            selected = i;
        }
    }

    lbl_805FAA60[selected].id = id;
    if (value2 >= 0) {
        lbl_805FAA60[selected].value2 = value2;
    }
    if (value4 >= 0) {
        lbl_805FAA60[selected].value4 = value4;
    }
}


#pragma section code_type ".discard"



void seed_8016AF2C(void)
{
    int i;

    i = 0;

    do {
        if (lbl_805FAA60[i].id != 0 && lbl_805FAA60[i].value4 != 0) {
            lbl_805FAA60[i].value4--;
            if (lbl_805FAA60[i].value4 == 0) {
                fn_8016B400(lbl_805FAA60[i].id, 0, 0);
            }
        }
        i++;
    } while (i < 10);
}


#pragma section code_type ".discard"



void seed_8016AFB0(s16 id)
{
    int i;

    if (id > 0) {
        for (i = 0; i < 10; i++) {
            if (lbl_805FAA60[i].id == id) {
                if (lbl_805FAA60[i].value6 == 0) {
                    memset(&lbl_805FAA60[i], 0, sizeof(RefEntry));
                }
                break;
            }
        }
    }
}


#pragma section code_type ".discard"



void seed_8016B030(int clear_all)
{
    int i;

    if (clear_all == 0) {
        memset(lbl_805FAA60, 0, sizeof(lbl_805FAA60));
    } else {
        for (i = 0; i < 10; i++) {
            if (lbl_805FAA60[i].value6 == 0) {
                memset(&lbl_805FAA60[i], 0, sizeof(RefEntry));
            }
        }
    }
}


#pragma section code_type ".discard"



void seed_8016B0B4(s16 id, int value)
{
    int i;
    int selected = -1;

    for (i = 0; i < 10; i++) {
        if (lbl_805FAA60[i].id == id) {
            selected = i;
            break;
        }
        if (selected == -1 && lbl_805FAA60[i].id == 0) {
            selected = i;
        }
    }

    lbl_805FAA60[selected].id = id;
    lbl_805FAA60[selected].value6 = value;
}


#pragma section code_type ".discard"

int seed_8016B1D0(void* output)
{
    int result;

    memcpy(output, lbl_805FAA60, 80);
    result = fn_800480D4(lbl_8064D1C0, (unsigned char*)output + 80);
    return (result + 111) & 0xFFE0;
}


#pragma section code_type ".discard"

int seed_8016B21C(void* input)
{
    int result;

    memcpy(lbl_805FAA60, input, 80);
    result = fn_800483A0(lbl_8064D1C0, (unsigned char*)input + 80);
    return (result + 111) & 0xFFE0;
}


#pragma section code_type ".discard"


void seed_8016B26C(Pair* pairs, int count)
{
    fn_8016ACAC(lbl_8064D1C0, pairs, count);
}


#pragma section code_type ".discard"



void seed_8016B29C(u32 size, Callback callback)
{
    lbl_8064D1C8 = fn_801FEA8C(0x25BB8, 1, lbl_8024FEDC, 452);
    lbl_8064D1D0 = callback;
    lbl_8064D1CC = 0;
    lbl_8064D1D4 = 0;

    if (size != 0) {
        lbl_8064D1CC = fn_801FEA8C(size, 1, lbl_8024FEDC, 460);
        memset(lbl_8064D1CC, 0, size);
        lbl_8064D1D4 = size;
    }

    fn_8016B5CC(0, 0, -1, lbl_8024FEDC, 468);
    fn_8016B030(0);
    lbl_8064D1C0 = fn_80166894(0);
    fn_80177408();
    fn_80177434(lbl_8064D1C0, 0, &lbl_8064BC00);
    if (lbl_8064D1D0 != 0) {
        lbl_8064D1D0(lbl_8064D1C0, 0, &lbl_8064BC00);
    }
    fn_8016AC68(lbl_8064D1C0, 0);
}


#pragma section code_type ".discard"


void* seed_8016B3A4(void* value, int alternate)
{
    u32 size = 0;
    void* result;

    if (alternate != 0) {
        result = fn_80138B90(value, 3, 0);
    } else {
        result = fn_80024638(value, lbl_8064D1CC, &size);
    }

    lbl_8064D1CC = result;
    return (unsigned char*)result + ((size + 31) & ~31);
}


#pragma section code_type ".discard"



void seed_8016B400(int id, void* context, void* value)
{
    char name[256];
    unsigned char* base;
    u32 index;
    u32 size;
    u32* tbl;
    unsigned char* data;

    lbl_8064D1C4 = 0;
    base = lbl_8064D1CC;
    if (id > 0 && lbl_8064D1BC == 0) {
        lbl_8064D1E0 = context;
        lbl_8064D1DC = value;
        lbl_8064D1BC = id;
        tbl = (u32*)base;
        index = id * 2 + 2;
        size = tbl[index + 1];
        data = base + tbl[index];
        if (size != 0) {
            fn_800F9D4C(name, lbl_8024FEE8, id);
            fn_8016B4B4(data, (void*)size, name, lbl_8064D1E0, lbl_8064D1DC);
        }
        lbl_8064D1BC = 0;
    }
}


#pragma section code_type ".discard"


#pragma use_lmw_stmw on

void* seed_8016B4B4(void* data, void* size, char* name, void* context, void* value)
{
    void* result;

    fn_800FD40C(lbl_805FAAB0, name);
    fn_8016B914(-1);
    fn_8016A970(lbl_8064D1C0, context, 0);
    fn_8016AB20(lbl_8064D1C0, lbl_8024FEF4);
    fn_8016A970(lbl_8064D1C0, value, 0);
    fn_8016AB20(lbl_8064D1C0, &lbl_8064BC08);
    result = fn_80160EBC(lbl_8064D1C0, data, size, name);
    fn_8016AA34(lbl_8064D1C0, lbl_8024FEF4);
    fn_8016A5B0(lbl_8064D1C0, -2);
    fn_8016AA34(lbl_8064D1C0, &lbl_8064BC08);
    fn_8016A5B0(lbl_8064D1C0, -2);
    fn_8016AC68(lbl_8064D1C0, 0);
    lbl_8064D1BC = 0;
    fn_8016B914(-2);
    if (lbl_8064D1C4 != 0) {
        fn_8016B400(lbl_8064D1C4, lbl_8064D1E0, lbl_8064D1DC);
    }
    return result;
}


#pragma section code_type ".discard"


void* seed_8016B5CC(void* context, void* allocation, int size,
                  const char* file, int line)
{
    int words;
    int offset;
    int index;
    int* entry;
    void* replacement;
    int value;

    fn_8020AFE4(lbl_8064C3C8);

    if (size < 0) {
        lbl_8064D1B8 = 0;
        memset(lbl_805FAAD8, 0, sizeof(lbl_805FAAD8));
        lbl_805FAAD8[0] = 0x25BB8;
    } else if (allocation == 0) {
        words = (size + 3) / 4;
        offset = 0;
        if (words == 0) {
            return 0;
        }

        for (index = 0; index < 1536; index++) {
            value = lbl_805FAAD8[index];
            if (words < value) {
                entry = &lbl_805FAAD8[index + 1];
                if (*entry == 0) {
                    *entry = value - words;
                    lbl_805FAAD8[index] = -words;
                } else {
                    lbl_805FAAD8[index] = -value;
                }
                lbl_8064D1B8 -= lbl_805FAAD8[index];
                return lbl_8064D1C8 + offset * 4;
            }
            offset += value < 0 ? -value : value;
        }
    } else {
        words = (size + 3) / 4;
        if (words == 0) {
            int target = ((char*)allocation - lbl_8064D1C8) / 4;
            int covered = 0;

            for (index = 0; index < 1536; index++) {
                value = lbl_805FAAD8[index];
                covered += value < 0 ? -value : value;
                if (covered > target) {
                    break;
                }
            }

            entry = &lbl_805FAAD8[index];
            lbl_8064D1B8 += *entry;
            *entry = -*entry;
            if (index < 1535 && entry[1] > 0) {
                *entry += entry[1];
                entry[1] = 0;
            }
            for (; index > 0; index--) {
                if (entry[-1] < 0) {
                    break;
                }
                entry[-1] += *entry;
                *entry = 0;
                entry--;
            }
            allocation = 0;
        } else {
            int bytes = words * 4;
            replacement = fn_8016B5CC(context, 0, bytes, lbl_8024FEDC, 0x36F);
            memcpy(replacement, allocation, bytes);
            fn_8016B5CC(context, allocation, 0, lbl_8024FEDC, 0x371);
            allocation = replacement;
        }
    }

done:
    fn_8020AFE4(lbl_8064C3C8);
    return allocation;
}


#pragma section code_type ".discard"


void seed_8016B914(int checkpoint)
{
    int total = 0;
    int i;

    for (i = 0; i < 1536; i++) {
        total += __abs(lbl_805FAAD8[i]);
    }

    if (checkpoint == -1) {
        fn_801E7DC8(0x112);
        fn_801E7DC8(0x100);
        lbl_8064D1D8 = lbl_8064D1B8;
    }
    if (checkpoint == -2) {
        fn_801E7DC8(0x112);
        fn_801E7DC8(0x100);
        lbl_8064D1D8 = lbl_8064D1B8;
    }
}


#pragma section code_type ".discard"

void* seed_8016BA38(int index)
{
    return lbl_805FC2DC + index * 6;
}


#pragma section code_type ".discard"

#pragma use_lmw_stmw on
#pragma opt_lifetimes off
double seed_8016BA4C(signed char* text, signed char** end)
{
    int sign;
    double value;
    int exponent;
    const double* limit;
    int exponent_char;
    int digit;
    int exponent_sign;
    const double* scale;
    double factor;

    while (fn_800F8D14(*text)) {
        text++;
    }

    sign = 1;
    if (*text == '+') {
        text++;
    } else if (*text == '-') {
        sign = -1;
        text++;
    }

    value = 0.0;

    while (fn_800F8D2C(digit = *text)) {
        value = 10.0 * value + (digit - '0');
        text++;
    }

    if (*text == '.') {
        scale = lbl_8023A900;
        limit = lbl_8023A900 + 17;
        factor = *scale;

        text++;
        while (fn_800F8D2C(digit = *text) && scale < limit) {
            value = factor * (digit - '0') + value;
            factor = *++scale;
            text++;
        }
    }

    while (fn_800F8D2C(*text)) {
        text++;
    }

    if (fn_800F8CF0(*text) == 'e') {
        text++;
        exponent_char = *text;
        exponent_sign = 1;
        if (!fn_800F8D2C(exponent_char)) {
            if (exponent_char == '-') {
                exponent_sign = -1;
            }
            text++;
        }

        exponent = 0;
        while (fn_800F8D2C(exponent_char = *text)) {
            exponent = exponent_char + exponent * 10;
            exponent -= '0';
            text++;
        }
        if (exponent_sign == -1) {
            exponent = exponent - exponent * 2;
        }

        while (exponent < 0) {
            value /= 10.0;
            exponent++;
        }
        while (exponent > 0) {
            value = 10.0 * value;
            exponent--;
        }
    }

    if (end != 0) {
        *end = text;
    }
    return value * sign;
}
#pragma opt_lifetimes reset
#pragma use_lmw_stmw reset


#pragma section code_type ".discard"

int seed_8016BD0C(void* state)
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


#pragma section code_type ".discard"

int seed_8016BDD8(void* state)
{
    void* value = fn_80201B3C();
    fn_8016A970(state, value, 0);
    return 1;
}


#pragma section code_type ".discard"

int seed_8016BE1C(void* state)
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


#pragma section code_type ".discard"

int seed_8016BEC8(void* state)
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


#pragma section code_type ".discard"

int seed_8016BF60(void* state)
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


#pragma section code_type ".discard"

int seed_8016C008(void* state)
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


#pragma section code_type ".discard"

int seed_8016C0BC(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801B0B30((int)fn_8016A694(state, 1));
    fn_8016A830(state, fn_801AF824());
    return 1;
}


#pragma section code_type ".discard"

int seed_8016C164(void* state)
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


#pragma section code_type ".discard"


int seed_8016C238(void* state)
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


#pragma section code_type ".discard"


int seed_8016C3B4(void* state)
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


#pragma section code_type ".discard"


int seed_8016C4BC(void* state)
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


#pragma section code_type ".discard"

int seed_8016C668(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801B0CA4(-1, (int)fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".discard"

int seed_8016C6EC(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801B08BC(-1, (int)fn_8016A694(state, 1), 0);
    return 0;
}


#pragma section code_type ".discard"

int seed_8016C774(void* state)
{
    fn_8016A830(state, fn_8015C910());
    return 1;
}


#pragma section code_type ".discard"

int seed_8016C7C4(void* state)
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


#pragma section code_type ".discard"

int seed_8016C890(void* state)
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


#pragma section code_type ".discard"

int seed_8016C96C(void* state)
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


#pragma section code_type ".discard"

int seed_8016CA2C(void* state)
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


#pragma section code_type ".discard"

int seed_8016CB24(void* state)
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


#pragma section code_type ".discard"

int seed_8016CBFC(void* state)
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


#pragma section code_type ".discard"

int seed_8016CDA0(void* state)
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


#pragma section code_type ".discard"

int seed_8016CE48(void* state)
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


#pragma section code_type ".discard"

int seed_8016CEF0(void* state)
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


#pragma section code_type ".discard"

int seed_8016D040(void* state)
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


#pragma section code_type ".discard"

int seed_8016D0D4(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }
    lbl_8064CB54 ^= 1;
    return 0;
}


#pragma section code_type ".discard"

int seed_8016D144(void* state)
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


#pragma section code_type ".discard"

int seed_8016D1F8(void* state)
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


#pragma section code_type ".discard"

int seed_8016D2B8(void* state)
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


#pragma section code_type ".discard"

#pragma opt_propagation off
int seed_8016D480(void* state)
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


#pragma section code_type ".discard"

int seed_8016D574(void* state)
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


#pragma section code_type ".discard"

int seed_8016D680(void* state)
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


#pragma section code_type ".discard"

int seed_8016D7AC(void* state)
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


#pragma section code_type ".discard"

int seed_8016D8A4(void* state)
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


#pragma section code_type ".discard"

int seed_8016D92C(void* state)
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


#pragma section code_type ".discard"

void seed_8016D9C0(unsigned int type, u16* first, u16* second)
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


#pragma section code_type ".discard"


int seed_8016DA80(void* state)
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


#pragma section code_type ".discard"


int seed_8016DB38(void* state)
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


#pragma section code_type ".discard"

int seed_8016DBF0(void* state)
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


#pragma section code_type ".discard"

int seed_8016DCB0(void* state)
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


#pragma section code_type ".discard"

int seed_8016DD70(void)
{
    fn_801F6540();
    return 1;
}


#pragma section code_type ".discard"

int seed_8016DD94(void* state)
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


#pragma section code_type ".discard"

int seed_8016DE30(void* state)
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


#pragma section code_type ".discard"

int seed_8016DECC(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_8020034C((int)fn_8016A694(state, 1));
    return 1;
}


#pragma section code_type ".discard"

int seed_8016DF4C(void* state)
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


#pragma section code_type ".discard"

void seed_8016E254(int value)
{
    int current = fn_80201B44();
    fn_8020123C(253, 0, current, value);
}


#pragma section code_type ".discard"



int seed_8016E294(void* state)
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


#pragma section code_type ".discard"

int seed_8016E3F0(void* state)
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


#pragma section code_type ".discard"

int seed_8016E514(void* state)
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


#pragma section code_type ".discard"

int seed_8016E5A8(void* state)
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


#pragma section code_type ".discard"

int seed_8016E634(void* state)
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


#pragma section code_type ".discard"

int seed_8016E6D4(void* state)
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


#pragma section code_type ".discard"

int seed_8016E7B8(void* state)
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


#pragma section code_type ".discard"

int seed_8016E854(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    fn_8016A694(state, 1);
    return 0;
}


#pragma section code_type ".discard"

int seed_8016E8C4(void* state)
{
    fn_80163BB4(state, "\nError Requested Button is Obsolete", 0);
    return 0;
}


#pragma section code_type ".discard"



int seed_8016E8F8(void* state, int alternate)
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


#pragma section code_type ".discard"

int seed_8016EACC(void* state)
{
    fn_8016E8F8(state, 1);
    return 1;
}


#pragma section code_type ".discard"

int seed_8016EAF4(void* state)
{
    fn_8016E8F8(state, 0);
    return 1;
}


#pragma section code_type ".discard"

int seed_8016EB1C(void* state)
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


#pragma section code_type ".discard"

int seed_8016EC50(void* state)
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


#pragma section code_type ".discard"

int seed_8016ED78(void* state)
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


#pragma section code_type ".discard"

int seed_8016EEE4(void* state)
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


#pragma section code_type ".discard"

int seed_8016EFC4(void* state)
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


#pragma section code_type ".discard"

int seed_8016F088(void* state)
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


#pragma section code_type ".discard"

int seed_8016F128(void* state)
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


#pragma section code_type ".discard"

int seed_8016F1D0(void* state)
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


#pragma section code_type ".discard"


int seed_8016F2AC(void* state)
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


#pragma section code_type ".discard"




int seed_8016F400(void* state)
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


#pragma section code_type ".discard"

int seed_8016F4CC(void* state)
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


#pragma section code_type ".discard"

int seed_8016F580(void* state)
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


#pragma section code_type ".discard"

int seed_8016F678(void* state)
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


#pragma section code_type ".discard"
static Vec3 UP_F78C = { 0.0f, 0.0f, 1.0f };

int seed_8016F78C(void* state)
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

#pragma section code_type ".discard"


int seed_8016F8F8(void* state)
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


#pragma section code_type ".discard"
static Vec3 UP_FA08 = { 0.0f, 0.0f, 1.0f };

int seed_8016FA08(void* state)
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

#pragma section code_type ".discard"

int seed_8016FB94(void* state)
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


#pragma section code_type ".discard"

int seed_8016FC68(void* state)
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


#pragma section code_type ".discard"

int seed_8016FD3C(void* state)
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


#pragma section code_type ".discard"

int seed_8016FE4C(void* state)
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


#pragma section code_type ".discard"

int seed_8016FEF8(void* state)
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


#pragma section code_type ".discard"

int seed_8016FFA8(void* first, void* second)
{
    fn_8016B400((int)second, first, 0);
    return 0;
}


#pragma section code_type ".discard"


int seed_8016FFDC(void* state)
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


#pragma section code_type ".discard"


int seed_80170090(void* state)
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


#pragma section code_type ".discard"


int seed_80170144(void* state)
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


#pragma section code_type ".discard"


int seed_801701D4(void* state)
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


#pragma section code_type ".discard"


int seed_8017026C(void* state)
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


#pragma section code_type ".discard"


int seed_801702FC(void* state)
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


#pragma section code_type ".discard"

int seed_8017038C(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    lbl_8063D400_f[2] -= value;
    return 0;
}


#pragma section code_type ".discard"

int seed_80170438(void* state)
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


#pragma section code_type ".discard"

int seed_801704F8(void* state)
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


#pragma section code_type ".discard"

int seed_801705D4(void* state)
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


#pragma section code_type ".discard"

int seed_80170658(void* state)
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


#pragma section code_type ".discard"

int seed_801706DC(void* state)
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


#pragma section code_type ".discard"

int seed_80170814(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801F86F4(0);
    return 0;
}


#pragma section code_type ".discard"

int seed_80170880(void* state)
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


#pragma section code_type ".discard"


int seed_80170980(void* state)
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


#pragma section code_type ".discard"



int seed_80170A40(void* state)
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


#pragma section code_type ".discard"


int seed_80170B5C(void* state)
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


#pragma section code_type ".discard"

int seed_80170C18(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    lbl_8064D1C4 = lbl_8064D1BC;
    return 0;
}


#pragma section code_type ".discard"

int seed_80170C84(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    lbl_8064D1C4 = fn_8016A694(state, 1);
    return 0;
}


#pragma section code_type ".discard"

int seed_80170D04(void* state)
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


#pragma section code_type ".discard"

int seed_80170DF4(void* state)
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


#pragma section code_type ".discard"

int seed_80170E9C(void* state)
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


#pragma section code_type ".discard"

int seed_80170F44(void* state)
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


#pragma section code_type ".discard"

int seed_80171020(void* state)
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


#pragma section code_type ".discard"

int seed_801710FC(void* state)
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


#pragma section code_type ".discard"




int seed_801711D0(void* state)
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


#pragma section code_type ".discard"

int seed_8017138C(void* state)
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


#pragma section code_type ".discard"

int seed_80171418(void* state)
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


#pragma section code_type ".discard"

int seed_801714BC(void* state)
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


#pragma section code_type ".discard"
int seed_80171560(void* state)
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

#pragma section code_type ".discard"

int seed_80171664(void* state)
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


#pragma section code_type ".discard"

int seed_80171780(void* state)
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


#pragma section code_type ".discard"

int seed_8017187C(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801A9964(fn_800F5C54(fn_8016A694(state, 1)));
    return 0;
}


#pragma section code_type ".discard"

int seed_801718F4(void* state)
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


#pragma section code_type ".discard"

int seed_801719B4(void* state)
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


#pragma section code_type ".discard"

int seed_80171AF0(void* state)
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


#pragma section code_type ".discard"

int seed_80171BB4(void* state)
{
    int arg3;
    int arg4;
    int arg2;
    int arg1;
    unsigned char clamped3;
    int arg5;
    signed char clamped5;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    arg1 = (int)fn_8016A694(state, 1);
    arg2 = (int)fn_8016A694(state, 2);
    arg3 = (int)fn_8016A694(state, 3);
    arg4 = (int)fn_8016A694(state, 4);
    arg5 = (int)fn_8016A694(state, 5);

    clamped3 = (arg3 > 0 ? arg3 : 0) > 0x7F
                   ? 0x7F
                   : (arg3 > 0 ? arg3 : 0);
    if (arg3 != clamped3) {
        fn_80163BB4(state, "Invalid Volume %i (range is 0-%i)", arg3, 0x7F);
    }

    clamped5 = (arg5 > 0 ? arg5 : 0) > 0xFF
                   ? 0xFF
                   : (arg5 > 0 ? arg5 : 0);
    if (arg5 != clamped5) {
        fn_80163BB4(state, "Invalid FadeFrames %i (range is 0-255)", arg5);
    }

    if (arg2 != 1 && arg2 != 2) {
        fn_80163BB4(state, "Invalid AudioType %d", arg2);
    }

    fn_801AC5E4((unsigned short)arg1, 0, clamped3, arg4, clamped5, arg2, 0);
    return 0;
}


#pragma section code_type ".discard"

int seed_80171D6C(void* state)
{
    int arg1;
    int arg2;
    unsigned char clamped2;
    int arg3;
    int arg4;
    unsigned char clamped1;
    signed char clamped4;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }
    arg1 = (int)fn_8016A694(state, 1);
    arg2 = (int)fn_8016A694(state, 2);
    arg3 = (int)fn_8016A694(state, 3);
    arg4 = (int)fn_8016A694(state, 4);
    clamped2 = (arg2 > 0 ? arg2 : 0) > 0x7F ? 0x7F : (arg2 > 0 ? arg2 : 0);
    if (arg2 != clamped2)
        fn_80163BB4(state, "Invalid Volume %i (range is 0-%i)", arg2, 0x7F);
    clamped4 = (arg4 > 0 ? arg4 : 0) > 0x7F ? 0x7F : (arg4 > 0 ? arg4 : 0);
    if (arg4 != clamped4)
        fn_80163BB4(state, "Invalid FadeFrames %i (range is 0-127)", arg4);
    clamped1 = (arg1 > 0 ? arg1 : 0) > 0xFF ? 0xFF : (arg1 > 0 ? arg1 : 0);
    if (arg1 != clamped1)
        fn_80163BB4(state, "Invalid GroupID %i (range is 0-255)", arg4);
    fn_801AC5E4(0, clamped1, clamped2, arg3, clamped4, 0, 0);
    return 0;
}


#pragma section code_type ".discard"

int seed_80171F30(void* state)
{
    int result;

    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }
    result = fn_801AD72C();
    fn_8016A830(state, result);
    return 1;
}


#pragma section code_type ".discard"

int seed_80171FBC(void* state)
{
    int value;
    unsigned char arg0;
    unsigned char arg1;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    fn_801AD46C(&arg0, &arg1);
    fn_801AD4B4(value, 0, 0, 0);
    return 0;
}


#pragma section code_type ".discard"

int seed_80172058(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    fn_801AD4B4(value, 0, 0, (unsigned short)lbl_8064D1BC);
    return 0;
}


#pragma section code_type ".discard"

int seed_801720E8(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801AD490();
    return 0;
}


#pragma section code_type ".discard"

int seed_80172150(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    if (value != 0 && value != 1) {
        fn_80163BB4(state, "Pause value must be 0 or 1, received a value of %d", value);
    }
    fn_801AD6F4(value);
    return 0;
}


#pragma section code_type ".discard"

int seed_80172204(void* state)
{
    int value;
    unsigned char clamped;
    int other;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    other = (int)fn_8016A694(state, 2);
    clamped = (value > 0 ? value : 0) > 0x7F
                  ? 0x7F
                  : (value > 0 ? value : 0);
    if (value != clamped) {
        fn_80163BB4(state, "Volume value must be from 0 to 127, received a value of %d", value);
    }
    fn_801AD404(clamped, clamped, other);
    return 0;
}


#pragma section code_type ".discard"

int seed_8017230C(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    if (value < 0) {
        fn_80163BB4(state, "Frame value must be 0 or greater, received a value of %d", value);
    }
    fn_801AD734(value);
    return 0;
}


#pragma section code_type ".discard"

int seed_801723B8(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    if (value == 1) {
        fn_801B2380(0);
    } else if (value == 0) {
        fn_801B2348(0);
    } else {
        fn_80163BB4(state, "Bad value %d", value);
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_80172470(void* state)
{
    int first;
    int second;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    fn_801B1A1C((void*)first, second);
    return 0;
}


#pragma section code_type ".discard"

int seed_8017250C(void* state)
{
    int value;

    value = fn_801B243C();
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_8016A830(state, value);
    return 1;
}


#pragma section code_type ".discard"

int seed_801725A8(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801ACD8C();
    return 0;
}


#pragma section code_type ".discard"

int seed_80172610(void* state)
{
    int value;
    signed char clamped;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    clamped = (value > 0 ? value : 0) > 0x7F
                  ? 0x7F
                  : (value > 0 ? value : 0);
    if (value != clamped) {
        fn_80163BB4(state, "Fade value must be from 0 to 127, received a value of %d", value);
    }
    fn_801AC350(clamped, 0, 0);
    return 0;
}


#pragma section code_type ".discard"



int seed_801726EC(void* state)
{
    int first;
    int second;
    Vec3s* position;
    int fourth;
    unsigned short arg1;
    unsigned char clamped;
    Vec3f converted;
    int result;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    position = fn_8016A784(state, 3);
    fourth = (int)fn_8016A694(state, 4);

    arg1 = (unsigned short)first;
    clamped = (second > 0 ? second : 0) > 0x7F
                  ? 0x7F
                  : (second > 0 ? second : 0);
    if (second != clamped) {
        fn_80163BB4(state, "Volume value must be from 0 to 127, received a value of %d", second);
    }

    converted.x = position->x;
    converted.y = position->y;
    converted.z = position->z;
    result = fn_801AC9F4(arg1, clamped, &converted, (signed char)fourth);
    fn_8016A830(state, result);
    return 1;
}


#pragma section code_type ".discard"

int seed_8017288C(void* state)
{
    int first;
    int flags = 0;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    if ((int)fn_8016A694(state, 2) == 1) {
        flags |= 1;
    }
    fn_80045A24(first, flags);
    return 0;
}


#pragma section code_type ".discard"

int seed_80172944(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    if (fn_800460EC() != 0) {
        fn_8016A830(state, lbl_806506D8);
    } else {
        fn_8016A7D8(state);
    }
    return 1;
}


#pragma section code_type ".discard"

int seed_801729CC(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = fn_8016A694(state, 1);
    fn_80045BE0(value);
    return 0;
}


#pragma section code_type ".discard"

int seed_80172A4C(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = fn_8016A694(state, 1);
    fn_8015C7D8(value);
    return 0;
}


#pragma section code_type ".discard"




int seed_80172ACC(void* state)
{
    RuntimeInfo* info = fn_8015C28C(2);
    int i;
    u32 id;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    id = fn_800F5C54(fn_8016A694(state, 1));
    for (i = 0; i < info->count; i++) {
        RuntimeEntry* entry = &info->entries[i];
        if (id == entry->id && (entry->flags & 1) != 0) {
            fn_8016A830(state, lbl_806506D8);
            return 1;
        }
    }

    fn_8016A7D8(state);
    return 1;
}


#pragma section code_type ".discard"

int seed_80172BB0(void* state)
{
    int first;
    int second;
    int result;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = fn_800F5C54(fn_8016A694(state, 2));
    result = fn_802066E0(first, second);
    fn_8016A830(state, result);
    return 1;
}


#pragma section code_type ".discard"

int seed_80172C78(void* state)
{
    int value;

    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    value = (int)lbl_8064D18C;
    fn_8016A830(state, value);
    return 1;
}


#pragma section code_type ".discard"

int seed_80172D04(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = (int)fn_8016A694(state, 1);
    if (value > 1 || value < 0) {
        fn_80163BB4(state, "Invalid Region Setting %d (must be 0 or 1)", value);
    }
    fn_801A7DEC(value);
    return 0;
}


#pragma section code_type ".discard"


int seed_80172DB8(void* state)
{
    int value = 0;
    RuntimeObject* object;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object = fn_8016A784(state, 1);
    if ((object->flags & 4) != 0) {
        value = 1;
    } else if ((object->flags & 8) != 0) {
        value = 2;
    }
    fn_8016A830(state, value);
    return 1;
}


#pragma section code_type ".discard"
int seed_80172E78(void)
{
    return 0;
}


#pragma section code_type ".discard"

int seed_80172E80(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_8020B344(lbl_8064C3C8);
    return 0;
}


#pragma section code_type ".discard"


int seed_80172EEC(void* state)
{
    int index;
    int x;
    int y;
    int z;
    ShortVector* vector;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }

    index = fn_8016A694(state, 1);
    x = fn_8016A694(state, 2);
    y = fn_8016A694(state, 3);
    z = fn_8016A694(state, 4);
    vector = &lbl_805FC2E8[index];
    vector->x = x;
    vector->y = y;
    vector->z = z;
    fn_8016A970(state, vector, 0);
    return 1;
}


#pragma section code_type ".discard"



int seed_80172FF0(void* state)
{
    int index;
    int handle;
    ShortVector* vector;
    void* object;
    FloatVector position;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    index = fn_8016A694(state, 1);
    handle = fn_8016A694(state, 2);
    vector = fn_8016BA38(index);
    object = fn_80201814(handle);
    if (object != 0) {
        fn_80201E78(&position, object);
        vector->x = position.x;
        vector->y = position.y;
        vector->z = position.z;
    }
    fn_8016A970(state, vector, 0);
    return 1;
}


#pragma section code_type ".discard"


int seed_80173104(void* state)
{
    ShortVector* first;
    ShortVector* second;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = fn_8016A784(state, 1);
    second = fn_8016A784(state, 2);
    if (first == 0 || second == 0) {
        fn_80163BB4(state, " (Error: pAddend1 or 2 is NULL = (%p, %p))", first, second);
    }
    lbl_8064D1EC.x = first->x + second->x;
    lbl_8064D1EC.y = first->y + second->y;
    lbl_8064D1EC.z = first->z + second->z;
    fn_8016A970(state, &lbl_8064D1EC, 0);
    return 1;
}


#pragma section code_type ".discard"

int seed_8017320C(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    return 0;
}


#pragma section code_type ".discard"



int seed_80173270(void* state)
{
    int resource;
    int arg2;
    int arg3;
    short arg8;
    int arg9;
    int index;
    Vec3s lookup;
    Vec3s* source;
    Vec3 position;
    Vec3 rotation;
    int effect = lbl_806506E0;

    if (fn_8016A598(state) != 9) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 9, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    arg2 = fn_8016A694(state, 2);
    arg3 = fn_8016A694(state, 3);
    fn_8016A694(state, 4);
    fn_8016A694(state, 5);
    fn_8016A694(state, 6);
    fn_8016A694(state, 7);
    arg8 = fn_8016A694(state, 8);
    arg9 = fn_8016A694(state, 9);

    index = fn_8015C4A4(resource, 2);
    if (index != -1) {
        source = fn_80158CC8(index, 2, &lookup);
    } else {
        fn_80163BB4(state, "Could not find marker %u", resource);
    }

    position.x = source->x;
    position.y = source->y;
    position.z = source->z;
    rotation.x = lookup.x;
    rotation.y = lookup.y;
    rotation.z = lookup.z;
    fn_801798DC(&rotation, arg8);
    fn_8014D478(0, &position, &rotation, arg2, arg3, &effect, arg9);
    return 0;
}


#pragma section code_type ".discard"





int seed_801734B4(void* state)
{
    int arg1, arg2, arg3;
    int arg13;
    int arg16;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;
    int arg12;
    int arg14;
    int arg15;
    int arg17;
    Color color;
    Vec3s resource;
    Vec3f position;

    if (fn_8016A598(state) != 17) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 17, fn_8016A598(state));
        return 0;
    }

    arg1 = fn_8016A694(state, 1);
    arg2 = fn_8016A694(state, 2);
    arg3 = fn_8016A694(state, 3);
    resource.x = fn_8016A694(state, 4);
    resource.y = fn_8016A694(state, 5);
    resource.z = fn_8016A694(state, 6);
    arg7 = fn_8016A694(state, 7);
    arg8 = fn_8016A694(state, 8);
    arg9 = fn_8016A694(state, 9);
    arg10 = fn_8016A694(state, 10);
    arg11 = fn_8016A694(state, 11);
    arg12 = fn_8016A694(state, 12);
    arg13 = fn_8016A694(state, 13);
    arg14 = fn_8016A694(state, 14);
    arg15 = fn_8016A694(state, 15);
    arg16 = fn_8016A694(state, 16);
    arg17 = fn_8016A694(state, 17);

    arg15 += (u16)arg17;
    color.r = arg7;
    color.g = arg8;
    color.b = arg9;
    color.a = arg10;
    position.x = (short)arg1;
    position.y = (short)arg2;
    position.z = (short)arg3;
    fn_80179904(&resource, arg16);
    fn_80153F00((u8)arg13, (u8)arg12, (u8)arg14, (u8)arg11, &color,
                arg15, &position, &resource, 1, 1, arg17);
    return 0;
}


#pragma section code_type ".discard"





int seed_80173770(void* state)
{
    int resource;
    int arg2;
    int arg8;
    int arg11;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    int arg9;
    int arg10;
    int index;
    Vec3s lookup;
    Vec3s* source;
    int arg12;
    Color color;
    Vec3f position;

    if (fn_8016A598(state) != 12) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 12, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    arg2 = fn_8016A694(state, 2);
    arg3 = fn_8016A694(state, 3);
    arg4 = fn_8016A694(state, 4);
    arg5 = fn_8016A694(state, 5);
    arg6 = fn_8016A694(state, 6);
    arg7 = fn_8016A694(state, 7);
    arg8 = fn_8016A694(state, 8);
    arg9 = fn_8016A694(state, 9);
    arg10 = fn_8016A694(state, 10);
    arg11 = fn_8016A694(state, 11);
    arg12 = fn_8016A694(state, 12);

    index = fn_8015C4A4(resource, 2);
    if (index != -1) {
        source = fn_80158CC8(index, 2, &lookup);
    } else {
        fn_80163BB4(state, "Could not find marker %u", resource);
    }

    color.r = arg2;
    color.g = arg3;
    color.b = arg4;
    color.a = arg5;
    arg10 += (u16)arg12;
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;
    fn_80179904(&lookup, arg11);
    fn_80153F00((u8)arg8, (u8)arg7, (u8)arg9, (u8)arg6, &color, arg10,
                &position, &lookup, 1, 1, arg12);
    return 0;
}


#pragma section code_type ".discard"




int seed_801739E8(void* state)
{
    int resource;
    float scale;
    u16 limits[2];
    int kind;
    int index;
    Vec3s* source;
    Vec3 position;
    Vec3s rotation;

    rotation = lbl_806506E4;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    scale = fn_8016A694(state, 2);
    limits[0] = fn_8016A694(state, 3);
    limits[1] = fn_8016A694(state, 4);
    kind = fn_8016A694(state, 5);

    index = fn_8015C4A4(resource, 2);
    if (index != -1) {
        source = fn_80158ABC(index, 2, 0);
        fn_80173B6C(&source->x, &position.x);
        fn_80173B6C(&source->y, &position.y);
        fn_80173B6C(&source->z, &position.z);
    } else {
        fn_80163BB4(state, "Could not find marker %u", resource);
    }

    fn_80154A98(&position, &rotation, kind, limits, scale);
    return 0;
}


#pragma section code_type ".discard"
float seed_80173B6C(register short* source, register float* destination)
{
    register float value;

    asm { psq_l value, 0(source), 1, 5 }
    *destination = value;
    return value;
}


#pragma section code_type ".discard"

int seed_80173B78(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    return 0;
}


#pragma section code_type ".discard"





int seed_80173BDC(void* arg)
{
    void* state = arg;
    int resource;
    int kind;
    Vec3s* source;
    Vec3s rotation;
    Vec3f position;
    Vec3f submit_position;
    EffectDescriptor_80173BDC descriptor;

    rotation = lbl_806506EC;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    kind = fn_8016A694(state, 2);
    source = fn_80158ABC(fn_8015C4A4(resource, 2), 2, 0);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;

    fn_801839A4((EffectDescriptor*)&descriptor);
    descriptor.bytes[20] = kind;
    submit_position = position;
    {
        void* effect = fn_80148008(&submit_position, &rotation, (EffectDescriptor*)&descriptor,
                                   fn_801839D8);
        if (effect != 0) {
            fn_8017FF1C(fn_80156938(effect), 4);
        }
    }
    return 0;
}


#pragma section code_type ".discard"



int seed_80173D44(void* arg)
{
    void* state = arg;
    int resource;
    int kind;
    Vec3s* source;
    u32 value;
    Descriptor descriptor;
    Vec3f position;
    Vec3f submit_position;
    EffectParams params;
    descriptor.word = lbl_80651CA0;
    descriptor.half = lbl_80651CA4;
    value = lbl_806506F4;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }
    resource = fn_800F5C54(fn_8016A694(state, 1));
    kind = fn_8016A694(state, 2);
    source = fn_80158ABC(fn_8015C4A4(resource, 2), 2, 0);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z - lbl_806506F8;
    fn_8018358C(&params);
    params.value2 = 250;
    params.value3 = -5;
    params.value6 = 20;
    params.value17 = 10;
    params.value18 = 1;
    params.value14 = 10;
    params.value15 = 250;
    params.value19 = 2;
    params.value1C = value;
    if (kind == 1) params.value1A = 2;
    submit_position = position;
    {
        void* effect = fn_80148008_d(&submit_position, &descriptor, &params, fn_801834F0);
        if (effect != 0) fn_8017FF1C(fn_80156938(effect), 4);
    }
    return 0;
}


#pragma section code_type ".discard"



int seed_80173F04(void* arg)
{
    void* state = arg;
    int resource;
    int kind;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;
    Vec3s* source;
    Descriptor descriptor;
    u32 value;
    Vec3f position;
    Vec3f submit_position;
    EffectParams params;

    descriptor.word = lbl_80651CA8;
    descriptor.half = lbl_80651CAC;
    value = lbl_806506FC;

    if (fn_8016A598(state) != 11) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 11, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    kind = fn_8016A694(state, 2);
    arg3 = fn_8016A694(state, 3);
    arg4 = fn_8016A694(state, 4);
    arg5 = fn_8016A694(state, 5);
    arg6 = fn_8016A694(state, 6);
    arg7 = fn_8016A694(state, 7);
    arg8 = fn_8016A694(state, 8);
    arg9 = fn_8016A694(state, 9);
    arg10 = fn_8016A694(state, 10);
    arg11 = fn_8016A694(state, 11);

    source = fn_80158ABC(fn_8015C4A4(resource, 2), 2, 0);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;

    fn_8018358C(&params);
    params.value2 = arg10;
    params.value3 = arg11;
    params.value6 = arg9;
    params.value17 = arg3;
    params.value18 = arg4;
    params.value16 = arg5;
    params.value14 = arg6;
    params.value15 = arg7;
    params.value19 = arg8;
    params.value1C = value;
    if (kind == 1) params.value1A = 2;

    submit_position = position;
    {
        void* effect = fn_80148008_d(&submit_position, &descriptor, &params, fn_80183454);
        if (effect != 0) fn_8017FF1C(fn_80156938(effect), 4);
    }
    return 0;
}


#pragma section code_type ".discard"



int seed_80174184(void* state)
{
    int resource;
    int arg7;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int index;
    Vec3s lookup;
    Vec3s* source;
    Vec3f position;

    if (fn_8016A598(state) != 7) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 7, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    arg2 = fn_8016A694(state, 2);
    arg3 = fn_8016A694(state, 3);
    arg4 = fn_8016A694(state, 4);
    arg5 = fn_8016A694(state, 5);
    arg6 = fn_8016A694(state, 6);
    arg7 = fn_8016A694(state, 7);

    index = fn_8015C4A4(resource, 2);
    if (index != -1) {
        source = fn_80158CC8(index, 2, &lookup);
    } else {
        fn_80163BB4(state, "Could not find marker %u", resource);
    }

    /* Retail intentionally falls through with source and lookup uninitialized
     * when the lookup above returns -1. Preserve that matching behavior. */
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;
    fn_80179904(&lookup, (short)arg7);
    fn_801533A8(&position, &lookup, arg2, arg3, arg5, arg4, arg6);
    return 0;
}


#pragma section code_type ".discard"



int seed_80174358(void* state)
{
    int resource;
    int arg12;
    int arg2;
    int arg3;
    int arg13;
    int arg7;
    int arg4;
    int arg5;
    int arg6;
    u8 values[4];
    Vec3s lookup;
    Vec3s* source;
    Vec3f position;
    int index;
    int result;

    if (fn_8016A598(state) != 13) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 13, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    arg2 = fn_8016A694(state, 2);
    arg3 = fn_8016A694(state, 3);
    arg4 = fn_8016A694(state, 4);
    arg5 = fn_8016A694(state, 5);
    arg6 = fn_8016A694(state, 6);
    arg7 = fn_8016A694(state, 7);
    values[0] = fn_8016A694(state, 8);
    values[1] = fn_8016A694(state, 9);
    values[2] = fn_8016A694(state, 10);
    values[3] = fn_8016A694(state, 11);
    arg12 = fn_8016A694(state, 12);
    arg13 = fn_8016A694(state, 13);

    index = fn_8015C4A4(resource, 2);
    if (index != -1) {
        source = fn_80158CC8(index, 2, &lookup);
    } else {
        fn_80163BB4(state, "Could not find marker %u", resource);
    }

    position.x = source->x;
    position.y = source->y;
    position.z = source->z;
    fn_80179904(&lookup, (short)arg12);
    result = fn_80156940(fn_80153050(
        &position, &lookup, arg2, arg3, arg5, arg4, values, arg13,
        arg7, arg6, 2, 128));
    fn_8016A830(state, (double)result);
    return 1;
}


#pragma section code_type ".discard"

int seed_80174610(void* state)
{
    void* object;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object = fn_80156948(fn_800F5C54(fn_8016A694(state, 1)));
    if (object != 0) {
        fn_80153104(object);
    }
    return 0;
}


#pragma section code_type ".discard"




int seed_80174694(void* state)
{
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;
    float arg12;
    int arg13;
    SpawnedEffect* spawned;
    void* manager;
    EffectDescriptor effect;

    if (fn_8016A598(state) != 13) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 13, fn_8016A598(state));
        return 0;
    }

    arg1 = fn_800F5C54(fn_8016A694(state, 1));
    arg2 = fn_8016A694(state, 2);
    arg3 = fn_8016A694(state, 3);
    arg4 = fn_8016A694(state, 4);
    arg5 = fn_8016A694(state, 5);
    arg6 = fn_8016A694(state, 6);
    arg7 = fn_8016A694(state, 7);
    arg8 = fn_8016A694(state, 8);
    arg9 = fn_8016A694(state, 9);
    arg10 = fn_8016A694(state, 10);
    arg11 = fn_8016A694(state, 11);
    arg12 = fn_8016A694(state, 12);
    arg13 = fn_8016A694(state, 13);

    spawned = fn_80149E04();
    if (spawned != 0) {
        fn_80147E88(&effect);
        fn_8014F4CC(&effect, spawned);
        effect.owner = arg1;
        spawned->kind = arg2;
        spawned->channel = arg3;
        fn_8019B13C(&effect);
        effect.value04 = arg4;
        effect.byte01 = arg6;
        effect.value06 = arg7;
        effect.byte02 = arg8;
        effect.byte03 = arg9;
        effect.value1C = 0;
        effect.value20 = 0;
        effect.value24 = arg5;
        if (arg5 != 0) {
            effect.value28 = 1;
        }
        effect.byte16 = arg10;
        effect.byte17 = arg11;
        effect.value34 = arg12;
        effect.value38 = arg13;
        fn_80201814(arg1);
        manager = fn_80155DB4_w();
        if (manager != 0) {
            if (fn_80148300(manager, &effect, spawned) == 0) {
                fn_80149EB8(spawned);
            }
        } else {
            fn_80149EB8(spawned);
        }
    }
    return 0;
}


#pragma section code_type ".discard"


int seed_801748EC(void* state)
{
    int count;
    s16 id;

    count = fn_8016A598(state);
    id = lbl_8064D1BC;
    switch (count) {
    case 2:
        id = fn_8016A694(state, 2);
    case 1:
        fn_8016A694(state, 1);
        break;
    default:
        fn_80163BB4(state, "\nInvalid Num of Args Expecting 1 or 2, and got %i\n", count);
        break;
    }

    fn_8016ADF0(id, -1, fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".discard"

int seed_801749A8(void* state)
{
    int value;
    double second_value;

    switch (fn_8016A598(state)) {
    case 2:
        value = fn_8016A694(state, 1);
        second_value = fn_8016A694(state, 2);
        if (second_value == lbl_806506D0) {
            fn_80046CE4(value);
        } else {
            fn_80046DB4(value);
        }
        break;
    case 1:
        fn_80046CE4(fn_8016A694(state, 1));
        break;
    default:
        if (fn_8016A598(state) != 1) {
            fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
            return 0;
        }
        break;
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_80174A94(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_80046D38(fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".discard"

int seed_80174B14(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_80048620(fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".discard"

int seed_80174B94(void* state)
{
    void* object;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object = fn_80201814((int)fn_8016A694(state, 1));
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            fn_8012C478(object, 15, 0);
        }
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_80174C34(void* state)
{
    void* object;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object = fn_80201814((int)fn_8016A694(state, 1));
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            fn_8012C478(object, 15, 1);
        }
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_80174CD4(void* state)
{
    struct Bytes {
        unsigned char data[4];
    } converted, value;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 4, fn_8016A598(state));
        return 0;
    }

    converted.data[0] = fn_8016A694(state, 1);
    converted.data[1] = fn_8016A694(state, 2);
    converted.data[2] = fn_8016A694(state, 3);
    converted.data[3] = fn_8016A694(state, 4);
    value = converted;
    fn_801F3528(&value);
    return 0;
}


#pragma section code_type ".discard"

int seed_80174DB8(void* state)
{
    struct Bytes {
        unsigned char data[4];
    } converted, value;
    int parameter;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 5, fn_8016A598(state));
        return 0;
    }

    converted.data[0] = fn_8016A694(state, 1);
    converted.data[1] = fn_8016A694(state, 2);
    converted.data[2] = fn_8016A694(state, 3);
    converted.data[3] = fn_8016A694(state, 4);
    parameter = fn_8016A694(state, 5);
    value = converted;
    fn_801F348C(&value, parameter);
    return 0;
}


#pragma section code_type ".discard"

int seed_80174EB4(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_801FD534((void *)fn_800F5C54(fn_8016A694(state, 1)));
    return 0;
}


#pragma section code_type ".discard"






#pragma opt_common_subs off
#pragma opt_propagation off
int seed_80174F2C(void* state)
{
    ResourceRef resource;
    Vec3s* source;
    int resource_id;
    CommandDescriptor* descriptor;
    CommandDescriptor command;
    u16 value00;

    if (fn_8016A598(state) != 10) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 10, fn_8016A598(state));
        return 0;
    }

    fn_8014CBC0(&resource);
    source = fn_8016A784(state, 1);
    command.bytes24[0] = fn_8016A694(state, 2);
    command.bytes24[1] = fn_8016A694(state, 3);
    command.bytes24[2] = fn_8016A694(state, 4);
    command.bytes24[3] = fn_8016A694(state, 5);
    resource_id = fn_8016A694(state, 6);
    command.value28 = fn_8016A694(state, 7);
    value00 = fn_8016A694(state, 8);
    descriptor = &command;
    descriptor->value00 = value00;
    descriptor->value08 = fn_8016A694(state, 9);
    descriptor->value0C = fn_8016A694(state, 10);
    command.byte34 = 2;
    command.position.x = source->x;
    command.position.y = source->y;
    command.position.z = source->z;
    command.callback = fn_801FD8F0;
    command.byte33 = 0;
    fn_801FE8DC(descriptor, lbl_806506B8, lbl_806506B8, lbl_80650700);
    fn_8014C988(&resource, resource_id);
    fn_8014C37C(0, &resource);
    return 0;
}
#pragma opt_propagation reset
#pragma opt_common_subs reset


#pragma section code_type ".discard"

int seed_80175164(void* state)
{
    fn_801FD240();
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    asm {
        li r0, 12
        mtctr r0
    delay_loop:
        bdnz delay_loop
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_801751DC(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801F5980();
    return 0;
}


#pragma section code_type ".discard"

int seed_80175244(void* state)
{
    fn_801FD24C();
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    return 0;
}


#pragma section code_type ".discard"






static inline void set_value00(CommandDescriptor_801752B0* descriptor, double value)
{
    descriptor->value00 = (u16)value;
}

int seed_801752B0(void* state)
{
    ResourceRef resource;
    Vec3s* source;
    CommandDescriptor_801752B0 command;

    if (fn_8016A598(state) != 6) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 6, fn_8016A598(state));
        return 0;
    }

    fn_8014CBC0(&resource);
    source = fn_8016A784(state, 1);
    command.bytes24[0] = fn_8016A694(state, 2);
    command.bytes24[1] = fn_8016A694(state, 3);
    command.bytes24[2] = fn_8016A694(state, 4);
    command.bytes24[3] = fn_8016A694(state, 5);
    set_value00(&command, fn_8016A694(state, 6));
    command.position.x = source->x;
    command.position.y = source->y;
    command.position.z = source->z;
    command.byte34 = 2;
    command.callback = fn_801754D0;
    command.byte33 = 0;
    fn_801FE8DC((CommandDescriptor*)&command, lbl_806506B8, lbl_806506B8, lbl_80650704);
    fn_8014C37C(0, &resource);
    lbl_8064D1E8 = 1;
    return 0;
}


#pragma section code_type ".discard"

int seed_80175464(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    lbl_8064D1E8 = 0;
    return 0;
}


#pragma section code_type ".discard"


int seed_801754D0(void* state)
{
    void* object;

    object = fn_801FD6F4(state);
    if (object != 0 && lbl_8064D1E8 == 0 && fn_801FE05C(state) != 0) {
        *(u16*)((char*)object + 0x22) = 2;
    }
    return 0;
}


#pragma section code_type ".discard"

void seed_80175534(int value)
{
    lbl_8064D1E8 = value;
}


#pragma section code_type ".discard"

int seed_8017553C(void* state)
{
    int first;
    int second;
    int result;

    first = fn_80201B44();
    fn_80201814();
    second = fn_80201EB8();
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    result = fn_80200F3C(first, second);
    fn_8016A830(state, result);
    return 1;
}


#pragma section code_type ".discard"




int seed_801755FC(void* state)
{
    Color first;
    Color second;
    ColorStep directions;
    Color call_first;
    ColorStep call_directions;
    Color call_second;
    s8 delta;
    int index;
    void* runtime;
    void* object;

    if (fn_8016A598(state) != 10) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 10, fn_8016A598(state));
        return 0;
    }

    runtime = fn_80201814((int)fn_8016A694(state, 1));
    if (runtime != 0) {
        object = fn_80201BC8();
        if (object != 0) {
            index = fn_8016A694(state, 2);
            first.r = fn_8016A694(state, 3);
            first.g = fn_8016A694(state, 4);
            first.b = fn_8016A694(state, 5);
            first.a = fn_8016A694(state, 6);
            second.r = fn_8016A694(state, 7);
            second.g = fn_8016A694(state, 8);
            second.b = fn_8016A694(state, 9);
            second.a = fn_8016A694(state, 10);

            delta = -5;
            if (second.r >= first.r) delta = 5;
            directions.r = delta;
            delta = -5;
            if (second.g >= first.g) delta = 5;
            directions.g = delta;
            delta = -5;
            if (second.b >= first.b) delta = 5;
            directions.b = delta;
            delta = -5;
            if (second.a >= first.a) delta = 5;
            directions.a = delta;

            call_second = second;
            call_directions = directions;
            call_first = first;
            fn_8012C62C_c(object, index, &call_first, &call_directions,
                         &call_second, 4);
        }
    }
    return 0;
}


#pragma section code_type ".discard"


int seed_8017583C(void* state)
{
    u32 first;
    u32 second;
    u32 third;
    void* runtime;
    void* object;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    runtime = fn_80201814((int)fn_8016A694(state, 1));
    if (runtime != 0) {
        object = fn_80201BC8();
        third = lbl_80651CB8;
        second = lbl_80651CB4;
        first = lbl_80651CB0;
        fn_8012C62C(object, 15, &first, &second, &third, 4);
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_801758F8(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_8011E26C(1);
    return 0;
}


#pragma section code_type ".discard"

int seed_80175964(void* state)
{
    int second;
    int first;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    fn_8011E26C(1);
    second = fn_8016A694(state, 2);
    first = fn_8016A694(state, 1);
    fn_8011DD8C(first, second);
    return 0;
}


#pragma section code_type ".text_80175A08"


int fn_80175A08(void* state)
{
    int kind;
    int object_id;
    void* object;
    int value;
    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    object_id = fn_8016A694(state, 1);
    kind = fn_8016A694(state, 2);
    if (fn_80201814(object_id) != 0) {
        object = fn_80201C24();
        value = fn_8016A694(state, 3);
        switch (kind) {
        case 0:
            fn_80157B48(object, value);
            break;
        case 1:
            fn_80157B54(object, value);
            break;
        case 2:
            fn_80157B94(object, value);
            break;
        case 3:
            fn_80157BAC(object, value);
            break;
        case 4:
            fn_80157BB8(object, value);
            break;
        case 5:
            fn_80157BA0(object, value);
            break;
        case 6:
            fn_80157B60(object, value);
            break;
        case 7:
            fn_80157B3C(object, value);
            break;
        default:
            fn_80163BB4(state, "WTF no inventory datatype of %i\n", kind);
            break;
        }
    } else {
        fn_80163BB4(state, "Not Valid GO for %i\n", object_id);
    }
    return 0;
}


#pragma section code_type ".text_80175BB8"


int fn_80175BB8(void* state)
{
    int kind;
    int object_id;
    void* object;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }
    object_id = fn_8016A694(state, 1);
    kind = fn_8016A694(state, 2);
    if (fn_80201814(object_id) != 0) {
        object = fn_80201C24();
        fn_8016A694(state, 3);
        switch (kind) {
        case 0: fn_8016A830(state, fn_801578E8(object)); break;
        case 1: fn_8016A830(state, fn_801578F4(object)); break;
        case 2: fn_8016A830(state, fn_80157BC4(object)); break;
        case 3: fn_8016A830(state, fn_80157BDC(object)); break;
        case 4: fn_8016A830(state, fn_80157BD0(object)); break;
        case 5: fn_8016A830(state, fn_80157900(object)); break;
        case 6: fn_8016A830(state, fn_80157AB8(object)); break;
        case 7: fn_8016A830(state, fn_80157918(object)); break;
        default:
            fn_8016A7D8(state);
            fn_80163BB4(state, "WTF no inventory datatype of %i\n", kind);
            break;
        }
    } else {
        fn_8016A7D8(state);
        fn_80163BB4(state, "Not Valid GO for %i\n", object_id);
    }
    return 1;
}


#pragma section code_type ".discard"

int seed_80175E64(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    value = fn_8016A694(state, 1);
    value = fn_800467F0(value, 0);
    fn_8016A830(state, (double)value);
    return 1;
}


#pragma section code_type ".discard"


int seed_80175F0C(void* state)
{
    s16* first;
    s16* second;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (s16*)fn_8016A784(state, 1);
    second = (s16*)fn_8016A784(state, 2);
    fn_8016A830(state, (double)fn_80178F14(first[0], first[1], first[2],
                                           second[0], second[1], second[2]));
    return 1;
}


#pragma section code_type ".discard"

int seed_80175FD4(void* state)
{
    int object_id;
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    if (fn_80201814(object_id) != 0) {
        value = fn_8015821C(fn_80201C24());
        fn_8016A830(state, (double)value);
    } else {
        fn_8016A830(state, -1.0);
    }
    return 1;
}


#pragma section code_type ".discard"

int seed_80176098(void* state)
{
    int object_id;
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    if (fn_80201814(object_id) != 0) {
        value = fn_80158234(fn_80201C24());
        fn_8016A830(state, (double)value);
    } else {
        fn_8016A830(state, -1.0);
    }
    return 1;
}


#pragma section code_type ".discard"

int seed_80176160(void* state)
{
    int object_id;
    unsigned int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    if (fn_80201814(object_id) != 0) {
        value = fn_80157BF4(fn_80201C24());
        fn_8016A830(state, (double)value);
    } else {
        fn_8016A830(state, -1.0);
    }
    return 1;
}


#pragma section code_type ".discard"

int seed_80176220(void* state)
{
    int object_id;
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    if (fn_80201814(object_id) != 0) {
        value = fn_80157994(fn_80201C24());
        fn_8016A830(state, (double)value);
    } else {
        fn_8016A830(state, -1.0);
    }
    return 1;
}


#pragma section code_type ".discard"

int seed_801762E8(void* state)
{
    Object* object;
    unsigned short first;
    int object_id;
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    if (fn_80201814(object_id) != 0) {
        object = fn_80201C24();
        first = fn_80157948(object);
        value = first - fn_80157994(object);
        fn_8016A830(state, (double)value);
    } else {
        fn_8016A830(state, -1.0);
    }
    return 1;
}


#pragma section code_type ".discard"

int seed_801763D8(void* state)
{
    int object_id;
    int value;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    value = (int)fn_8016A694(state, 2);
    if (fn_80201814(object_id) != 0) {
        fn_80157A28(fn_80201C24(), (unsigned short)value);
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_80176488(void* state)
{
    void* object;
    int object_id;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    object_id = (int)fn_8016A694(state, 1);
    if (object_id != 0) {
        object = fn_80201814(object_id);
        fn_80204EC8(fn_80201ADC(), object);
        fn_801E8328(2, object);
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_8017652C(void* state)
{
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = fn_80206634(fn_8016A784(state, 1));
    fn_8016A830(state, (double)value);
    return 1;
}


#pragma section code_type ".discard"

int seed_801765C4(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    fn_800486A8((int)fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".discard"

int seed_80176644(void* state)
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
        fn_802020B4(object, value);
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_801766F0(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    fn_80049774((int)fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".discard"

int seed_80176770(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    fn_80047240((int)fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".discard"

int seed_801767F0(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    fn_801ED57C((int)fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".discard"

int seed_80176870(void* state)
{
    float value;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }
    value = (float)fn_8016A694(state, 1);
    fn_801F0294(value, (int)fn_8016A694(state, 2));
    return 0;
}


#pragma section code_type ".discard"

int seed_80176914(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    lbl_8064C600 = (int)fn_8016A694(state, 1);
    return 0;
}


#pragma section code_type ".discard"

int seed_80176994(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    lbl_8064B814 = (int)fn_8016A694(state, 1);
    return 0;
}


#pragma section code_type ".discard"

int seed_80176A14(void* state)
{
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }
    fn_801F53E8((int)fn_8016A694(state, 1));
    return 0;
}


#pragma section code_type ".text_80176A94"

int fn_80176A94(void* state)
{
    void* handle;
    int id;
    int result;

    handle = fn_8017AF64();
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    result = (int)fn_8016A694(state, 1);
    id = result;
    result = fn_80220A68(result, handle, 0);
    if (result == 0 || result == -6) {
        result = fn_802213DC(id);
        if (result == 0) {
            int name = fn_80220B4C(id);
            if (name != 0) {
                fn_8017BA60("Couldn't unmount: ", name);
            }
        } else {
            fn_8017BA60("Couldn't format: ", result);
        }
    } else {
        fn_8017BA60("Couldn't mount card: ", result);
    }

    fn_8017AF78();
    return 0;
}


#pragma section code_type ".discard"

int seed_80176BA4(void* state)
{
    int first;
    int second;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    fn_801441C0(first, second, (int)fn_8016A694(state, 3));
    return 0;
}


#pragma section code_type ".discard"

int seed_80176C64(void* state)
{
    int id;
    int enabled;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    id = (int)fn_8016A694(state, 1);
    enabled = (int)fn_8016A694(state, 2);
    if (enabled != 0) {
        fn_801593B4(id);
    } else {
        fn_801593FC(id);
    }
    return 0;
}


#pragma section code_type ".discard"



int seed_80176D14(void* state)
{
    PacketTemplate packet;
    int first;
    int second;
    void* object;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    object = fn_80201814(first);
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            packet = lbl_8023A988;
            fn_80205868(object, second, &packet, 0x2000);
        }
    }
    return 0;
}


#pragma section code_type ".discard"

int seed_80176DF4(void* state)
{
    int id;
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    id = (int)fn_8016A694(state, 1);
    value = fn_80204888(id);
    fn_8016A830(state, (double)value);
    return 1;
}


#pragma section code_type ".discard"

int seed_80176E98(void* state)
{
    int first;
    int second;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    fn_801E8EFC(first, second);
    return 0;
}


#pragma section code_type ".discard"

int seed_80176F34(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801EB2FC(1);
    return 1;
}


#pragma section code_type ".discard"

int seed_80176FA0(void* state)
{
    unsigned int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    value = *(unsigned int*)((char*)fn_8016A784(state, 1) + 0x2C);
    fn_8016A830(state, (double)value);
    return 1;
}


#pragma section code_type ".discard"

int seed_80177034(void* state)
{
    int first;
    int second;
    void* object;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 2, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    object = fn_80201BC8(fn_80201814(first));
    if (second != 0) {
        fn_8011FA8C(object, 0x800, 0);
    } else {
        fn_8011FA8C(object, 0, 0x800);
    }
    return 1;
}


#pragma section code_type ".discard"

int seed_801770F8(void* state)
{
    unsigned int value;

    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    value = fn_801F99B8(*(void**)(lbl_8063CD18 + 0x18C));
    fn_8016A830(state, (double)value);
    return 1;
}


#pragma section code_type ".discard"

int seed_8017718C(void* state)
{
    int divisor;
    int value;

    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, fn_8016A598(state));
        return 0;
    }

    divisor = (int)fn_8016A694(state, 1);
    value = (int)fn_800FBFB0() % divisor;
    fn_8016A830(state, (double)value);
    return 1;
}


#pragma section code_type ".discard"

int seed_80177244(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    fn_801F6FFC(lbl_8063CD18 + 0x198);
    fn_801F6FFC(lbl_8063C6B8 + 0x198);
    return 1;
}


#pragma section code_type ".discard"


int seed_801772C8(void* state)
{
    Vec3 value;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 3, fn_8016A598(state));
        return 0;
    }

    value.x = (float)fn_8016A694(state, 1);
    value.y = (float)fn_8016A694(state, 2);
    value.z = (float)fn_8016A694(state, 3);
    fn_801F6FD8(value);
    return 1;
}


#pragma section code_type ".discard"

int seed_80177388(void* state)
{
    if (fn_8016A598(state) != 0) {
        fn_80163BB4(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 0, fn_8016A598(state));
        return 0;
    }

    *(int*)(lbl_8063D378 + 0x40) = 1;
    *(int*)(lbl_8063D400 + 0x40) = 1;
    return 1;
}
