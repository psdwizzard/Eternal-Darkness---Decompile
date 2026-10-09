/*
 * Front-end/menu presentation dispatcher.
 *
 * This reconstruction deliberately remains ordinary C.  The retail routine is
 * a large mode dispatcher which composes menu text, controller state, save-game
 * state, and several display-list paths; keeping those paths visible is more
 * useful than hiding the function behind an assembly replacement.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned short ushort;
typedef unsigned int u32;
typedef union { u32 word; u8 channel[4]; } PackedColor;
typedef PackedColor* Color;
typedef unsigned int uint;
typedef int s32;

typedef u8 undefined1;
typedef u32 undefined4;


/* Typed small-data objects recover the retail r2/r13-relative accesses. */
extern float lbl_8064DEA8;
extern float lbl_8064DEB8;
extern float lbl_8064DEBC;
extern float lbl_8064DEC0;
extern float lbl_8064DEE0;
extern float lbl_8064DEE4;
extern PackedColor lbl_8064DEEC;
extern PackedColor lbl_8064DEF0;
extern PackedColor lbl_8064DEF4;
extern PackedColor lbl_8064DEF8;
extern PackedColor lbl_8064DEFC;
extern PackedColor lbl_8064DF00;
extern PackedColor lbl_8064DF04;
extern PackedColor lbl_8064DF08;
extern PackedColor lbl_8064DF0C;
extern PackedColor lbl_8064DF10;
extern PackedColor lbl_8064DF14;
extern PackedColor lbl_8064DF18;
extern PackedColor lbl_8064DF1C;
extern float lbl_8064DF20;
extern float lbl_8064DF24;
extern double lbl_8064DF28;
extern PackedColor lbl_806518E0;
extern PackedColor lbl_806518E4;
extern PackedColor lbl_806518E8;
extern PackedColor lbl_806518EC;

extern u32 lbl_8064C518;
extern u32 lbl_8064C520;
extern PackedColor lbl_8064C2C4;
extern s32 lbl_8064C59C;
extern s32 lbl_8064C600;
extern void* lbl_8064C674;
extern float lbl_8064C678;
extern float lbl_8064C67C;
extern s32 lbl_8064C680;
extern s32 lbl_8064C684;
extern s32 lbl_8064C688;
extern s32 lbl_8064C68C;
extern s32 lbl_8064C690;
extern u32 lbl_8064C694;
extern s32 lbl_8064C698;
extern s32 lbl_8064C6A4[2];
extern u32 lbl_8064C6AC[2];
extern s32 lbl_8064C6D4;
extern s32 lbl_8064CBA0;
extern s32 lbl_8064CBA4;
extern u32 lbl_8064CE80;
extern s32 lbl_8064D294;
extern s32 lbl_8064D738;
/* Retail addresses the front-end data block (0x8023D020) through a single
 * base register; every menu string and table below is a member of it. */
/* Intro sequence script: one 16-byte record per step. */
typedef struct {
  s32 movie;    /* +0x0 */
  s32 track;    /* +0x4 */
  s32 duration; /* +0x8 */
  s32 fade;     /* +0xc */
} SeqEntry;

typedef struct {
  char title[0x288];            /* 0x000 */
  SeqEntry seq[33];             /* 0x288 */
  u8 pad498[8];                 /* 0x498 */
  char s4a0[0x20];              /* 0x4a0 */
  char s4c0[0x18];              /* 0x4c0 */
  char s4d8[0x28];              /* 0x4d8 */
  char s500[0x20];              /* 0x500 */
  char s520[0x574];             /* 0x520 */
  u8 introText[0x11c];          /* 0xa94 */
  PackedColor roomColorsA[3];   /* 0xbb0 */
  PackedColor roomColorsB[7];   /* 0xbbc */
  char chooseRoom[0x10];        /* 0xbd8 */
  char room261[0xc];            /* 0xbe8 */
  char room264[0xc];            /* 0xbf4 */
  char room266[0xc];            /* 0xc00 */
  char alexRoom94[0x10];        /* 0xc0c */
  char edwardRoom271[0x14];     /* 0xc1c */
  char edwardRoom275[0x14];     /* 0xc30 */
  char edwardRoom278[0x14];     /* 0xc44 */
  char edwardRoom282[0x14];     /* 0xc58 */
  char abduleRoom213[0x14];     /* 0xc6c */
  char majorMikeRoom219[0x14];  /* 0xc80 */
  char chooseYourFate[0x14];    /* 0xc94 */
  char fateC[0xc];              /* 0xca8 */
  char fateU[0xc];              /* 0xcb4 */
  char fateX[0xc];              /* 0xcc0 */
  char eternalQuestion[0x34];   /* 0xccc */
  char yesNoYes[0x10];          /* 0xd00 */
  char yesNoNo[0x10];           /* 0xd10 */
  char controllerFmt[0x10];     /* 0xd20 */
  char record[0xc];             /* 0xd30 */
  char playback[0xc];           /* 0xd3c */
} FrontData;
extern FrontData lbl_8023D020;
#define seqTable (front->seq)
#define lbl_8023D4C0 (front->s4a0)
#define lbl_8023D4E0 (front->s4c0)
#define lbl_8023D4F8 (front->s4d8)
#define lbl_8023D520 (front->s500)
#define lbl_8023D540 (front->s520)
#define lbl_8023DAB4 (front->introText)
#define lbl_8023DBD0 (front->roomColorsA)
#define lbl_8023DBDC (front->roomColorsB)
extern u8 lbl_802515D0[];
extern u8 lbl_80265DA0[];
extern u8 lbl_80265FD8[];
extern u8 lbl_803003C8[];
#define lbl_803003D8 ((u32*)(lbl_803003C8 + 0x10))
#define lbl_80301CE0 (lbl_803003C8 + 0x1918)
extern u32 lbl_8030241C[];
extern u8 lbl_8063C638[];
extern u8 lbl_8063B260[];
extern u8 lbl_8063B2A0[];
extern u8 lbl_8063B2AC[];
extern u8 lbl_8063B2C4[];
extern u8 lbl_8063B31C[];
extern u8 lbl_8063B35C[];
extern u8 lbl_8063B374[];

/* Recovered callees use the original ABI; declarations are intentionally loose. */
extern void* memset(void*, int, u32);
extern s32 fn_8001E134();
extern s32 fn_80021234();
extern s32 fn_80021490();
extern s32 fn_80021714();
extern void fn_800217F4(float*, float*, float, float, s32, s32*);
extern s32 fn_80023230();
extern s32 fn_80042FE8();
extern s32 fn_800472B0();
extern s32 fn_800B193C();
extern s32 fn_800B194C();
extern s32 fn_800B2EC0();
extern s32 fn_8011C900();
extern unsigned int fn_80144470(int);
extern void fn_801A852C(Color, int, int, u32);
extern s32 fn_801A8660();
extern void fn_801A872C(short, short, short, short, int, int, PackedColor*);
extern void fn_801A8D38(int);
extern s32 fn_801A8F08();
extern s32 fn_801A8FE8();
extern s32 fn_801A90BC();
extern s32 fn_801A9118();
extern s32 fn_801A91D4();
extern s32 fn_801A9250();
extern s32 fn_801AD4B4();
extern s32 fn_801E3A34();
extern s32 fn_801E3AA4();
extern s32 fn_801E5430();
extern void fn_801E56AC(float, const char*, ...);
extern s32 fn_801E5AD0();
extern void fn_801E5FB0(void*);
#define fn_801E5FB0(a) fn_801E5FB0((void*)(a))

extern s32 fn_801E5FE4();
extern void* fn_801E6CA0(void*, int, int, int, int);
extern u32 fn_801E7578(u32);
extern s32 fn_801E8D34();
extern s32 fn_801EB080();
extern s32 fn_801EC67C();
extern s32 fn_801EC7F4();
extern s32 fn_801ECB40();
extern s32 fn_801ECC4C();
extern s32 fn_801ED3F4();
extern s32 fn_801ED5F4();
extern s32 fn_801F3960();
extern s32 fn_802119B0();
extern s32 fn_802262B8();
extern s32 fn_802266B0();
extern s32 fn_80226EA0();
extern s32 fn_80226FA4();
extern s32 fn_802276AC();
extern s32 fn_80228474();
extern s32 fn_80228730();
extern s32 fn_80228AFC();
extern s32 fn_80228B98();
extern s32 fn_80229330();
extern s32 fn_80229490();
extern s32 fn_80229664();
extern s32 fn_8022979C();
extern s32 fn_802297C8();
extern s32 fn_80229810();
extern s32 fn_80229B08();
extern s32 fn_80229B88();
extern s32 fn_80229C0C();
extern s32 fn_80229CCC();
extern s32 fn_80229D8C();
extern s32 fn_80229E74();
extern s32 fn_80229F4C();
extern s32 fn_80229FA4();
extern s32 fn_8022A044();
extern s32 fn_8022A118();
extern s32 fn_8022A2F4();
extern s32 fn_8022A5D8();
extern s32 fn_8022B4B8();


/* Retail-owned menu/debug strings. */
#define s_Abdule_Room_213_8023dc8c (front->abduleRoom213)
#define s_Alex_Room_94_8023dc2c (front->alexRoom94)
#define s_CHOOSE_YOUR_FATE_8023dcb4 (front->chooseYourFate)
#define s_Choose_Room_8023dbf8 (front->chooseRoom)
#define s_Controller___s_8023dd40 (front->controllerFmt)
#define s_Do_you_want_to_set_the__ar_Etern_8023dcec (front->eternalQuestion)
#define s_Edward_Room_271_8023dc3c (front->edwardRoom271)
#define s_Edward_Room_275_8023dc50 (front->edwardRoom275)
#define s_Edward_Room_278_8023dc64 (front->edwardRoom278)
#define s_Edward_Room_282_8023dc78 (front->edwardRoom282)
#define s_Major_Mike_Room_219_8023dca0 (front->majorMikeRoom219)
#define s_Room_261_8023dc08 (front->room261)
#define s_Room_264_8023dc14 (front->room264)
#define s_Room_266_8023dc20 (front->room266)
#define s__ac_c__i27_8023dcc8 (front->fateC)
#define s__agPLAYBACK_8023dd5c (front->playback)
#define s__arRECORD_8023dd50 (front->record)
#define s__au_u__i28_8023dcd4 (front->fateU)
#define s__awYes__ayNo_8023dd30 (front->yesNoNo)
#define s__ax_x__i29_8023dce0 (front->fateX)
#define s__ayYes__awNo_8023dd20 (front->yesNoYes)
 
void fn_8002188C(int param_1,int param_2,uint param_3)

{
  FrontData *front;
  PackedColor *selA;
  PackedColor *selB;
  s32 uVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  char *pcVar8;
  s32 uVar9;
  double dVar11;
  PackedColor local_90;
  PackedColor local_94;
  PackedColor local_98;
  PackedColor local_9c;
  PackedColor local_a0;
  PackedColor local_a4;
  PackedColor local_a8;
  PackedColor local_ac;
  PackedColor local_b0;
  PackedColor local_b4;
  PackedColor local_b8;
  PackedColor local_bc;
  PackedColor local_c0;
  PackedColor local_c4;
  PackedColor local_c8;
  PackedColor local_cc;
  PackedColor local_d0;
  PackedColor local_d4;
  PackedColor local_d8;
  PackedColor local_dc;
  PackedColor local_e0;
  PackedColor local_e4;
  PackedColor local_e8;
  PackedColor local_ec;
  PackedColor local_f0;
  PackedColor local_f4;
  PackedColor local_f8;
  PackedColor local_fc;
  PackedColor local_100;
  PackedColor local_104;
  PackedColor local_108;
  PackedColor local_10c;
  PackedColor local_110;
  PackedColor local_114;
  PackedColor local_118;
  PackedColor local_11c;
  PackedColor local_120;
  PackedColor local_124;
  PackedColor local_128;
  PackedColor local_12c;
  PackedColor local_130;
  PackedColor local_134;
  PackedColor local_138;
  PackedColor local_13c;
  PackedColor local_140;
  PackedColor local_144;
  PackedColor local_148;
  PackedColor local_14c;
  PackedColor local_150;
  PackedColor local_154;
  PackedColor local_158;
  PackedColor local_15c;
  PackedColor local_160;
  PackedColor local_164;
  PackedColor local_168;
  PackedColor local_16c;
  PackedColor local_170;
  PackedColor local_174;
  PackedColor local_178;
  PackedColor local_17c;
  PackedColor local_180;
  PackedColor local_184;
  PackedColor local_188;
  PackedColor local_18c;
  PackedColor local_190;
  PackedColor local_194;
  PackedColor local_198;
  PackedColor local_19c;
  PackedColor local_1a0;
  PackedColor local_1a4;
  PackedColor local_1a8;
  PackedColor local_1ac;
  PackedColor local_1b0;
  PackedColor local_1b4;
  PackedColor local_1b8;
  /* Two rows of a 2x3 texture matrix; retail clears all 24 bytes. */
  float local_8c [6];
  undefined1 auStack_74 [68];
  SeqEntry *entry;
  s32 *track;
  int slot;
  float scale;

  front = &lbl_8023D020;
  local_90 = lbl_8064DEEC;
  ((u8*)&local_90)[3] = param_3;
  local_94 = lbl_8064DEF0;
  ((u8*)&local_94)[3] = param_3;
  fn_801ED3F4(lbl_8030241C[4]);
  fn_801A8D38(5);
  switch (param_1) {
  case 18:
  case 19:
    fn_801ED3F4(lbl_8030241C[3]);
    if (lbl_8064CBA4 == 1) {
      fn_801A9250(2,param_3,1);
    }
    else {
      fn_801A91D4(2,param_3,1);
    }
    fn_801A90BC(lbl_802515D0,front->title);
    break;
  case 2:
  case 5:
    if (lbl_8064C6D4 == 0) {
      lbl_8064C600 = lbl_8064C600 + 1;
    }
    else {
      fn_801ED3F4(lbl_8030241C[3]);
      local_b0 = lbl_8064DEF4;
      ((u8*)&local_b0)[3] = param_3;
      local_ac = local_b0;
      fn_801A852C(&local_ac,0,1,0x80000000);
      fn_801A8FE8(lbl_802515D0,lbl_8023D4E0,0,0,5);
    }
    break;
  case 6:
    fn_801A9250(0x47,param_3,1);
    fn_801A90BC(lbl_802515D0,front->title);
    iVar4 = fn_800B193C();
    if (iVar4 != 0) {
      iVar4 = fn_800B194C();
      if (iVar4 == 0xc) {
        local_b8 = lbl_8064DEF8;
        ((u8*)&local_b8)[3] = param_3;
        local_b4 = local_b8;
        fn_801A852C(&local_b4,0,0x48,0x80000000);
        if (lbl_8064CBA4 != 0) {
          fn_801A8F08(0x8c,0x46,500,0x1aa,0xffffffff,0,5);
        }
        else {
          fn_801A8F08(0x8c,0x46,500,0x1aa,0xffffffff,0,5);
        }
      }
      fn_800B2EC0(param_3);
    }
    break;
  case 7:
    fn_8001E134(1);
    fn_801A9250(1,param_3,1);
    fn_801A90BC(lbl_802515D0,front->title);
    if (lbl_8064C520 != 0) {
      local_98 = local_90;
      iVar4 = fn_801E7578(lbl_80301CE0[0]);
      if (iVar4 != 0) {
        local_9c = lbl_8064DEFC;
        ((u8*)&local_9c)[3] = param_3;
        local_bc = local_9c;
        fn_801A852C(&local_bc,0,0x45,0x80000000);
        fn_801A9118(0,0x10,5);
        iVar4 = fn_801E7578(lbl_80301CE0[0]);
        if (1 < iVar4) {
          local_c0 = local_9c;
          fn_801A852C(&local_c0,0,0x46,0x80000000);
          fn_801A9118(0,0xc,5);
        }
      }
      if ((param_2 == 3) && (iVar4 = fn_801E7578(lbl_80301CE0[0]), 2 < iVar4)) {
        ((u8*)&local_98)[0] = 0xff;
        ((u8*)&local_98)[1] = 0xf9;
        ((u8*)&local_98)[2] = 0xb7;
      }
      local_c4 = local_98;
      fn_801A852C(&local_c4,5,(short)(param_2 + 6),0x80000000);
      fn_801A9118(0,(param_2 & 0x3fff) << 2,5);
    }
    break;
  case 8:
  case 30:
    fn_80021234(param_3);
    break;
  case 13:
    fn_80021490(param_3);
    break;
  case 14:
  case 16:
    local_a0 = lbl_8064DF00;
    fn_801A9250(2,param_3,1);
    fn_801A90BC(lbl_802515D0,front->title);
    if ((lbl_803003D8[0] & 1) != 0) {
      local_c8 = local_a0;
      fn_801A852C(&local_c8,5,0x23,0x80000000);
      fn_801A9118(0,0x4c,5);
    }
    else {
      local_cc = local_a0;
      fn_801A852C(&local_cc,5,0x24,0x80000000);
      fn_801A9118(0,0x50,5);
    }
    if (fn_80144470(1) != 0) {
      local_d0 = local_a0;
      fn_801A852C(&local_d0,5,0x24,0x80000000);
      fn_801A9118(0,0x30,5);
    }
    else {
      local_d4 = local_a0;
      fn_801A852C(&local_d4,5,0x23,0x80000000);
      fn_801A9118(0,0x2c,5);
    }
    if (lbl_8064CBA4 != 0) {
      local_d8 = local_a0;
      fn_801A852C(&local_d8,5,0x27,0x80000000);
      fn_801A9118(0,0x54,5);
    }
    else {
      local_dc = local_a0;
      fn_801A852C(&local_dc,5,0x25,0x80000000);
      fn_801A9118(0,0x58,5);
    }
    iVar4 = lbl_8064D294;
    switch (iVar4) {
    case 0: {
        local_e0 = local_a0;
        fn_801A852C(&local_e0,5,0x2d,0x80000000);
        fn_801A9118(0,0x5c,5);
      }
      break;
    case 1: {
        local_e4 = local_a0;
        fn_801A852C(&local_e4,5,0x2e,0x80000000);
        fn_801A9118(0,0x60,5);
      }
      break;
    case 2: {
        local_e8 = local_a0;
        fn_801A852C(&local_e8,5,0x2f,0x80000000);
        fn_801A9118(0,100,5);
      }
      break;
    }
    switch(param_2) {
    case 0:
      local_ec = local_90;
      fn_801A852C(&local_ec,5,0x30,0x80000000);
      fn_801A9118(0,0x68,5);
      break;
    case 1:
      local_f0 = local_90;
      fn_801A852C(&local_f0,5,0x22,0x80000000);
      fn_801A9118(0,0x44,5);
      if ((lbl_803003D8[0] & 1) != 0) {
        local_f4 = local_90;
        fn_801A852C(&local_f4,5,0x23,0x80000000);
        fn_801A9118(0,0x4c,5);
      }
      else {
        local_f8 = local_90;
        fn_801A852C(&local_f8,5,0x24,0x80000000);
        fn_801A9118(0,0x50,5);
      }
      break;
    case 2:
      local_fc = local_90;
      fn_801A852C(&local_fc,5,0x26,0x80000000);
      fn_801A9118(0,0x48,5);
      if (lbl_8064CBA4 != 0) {
        local_100 = local_90;
        fn_801A852C(&local_100,5,0x27,0x80000000);
        fn_801A9118(0,0x54,5);
      }
      else {
        local_104 = local_90;
        fn_801A852C(&local_104,5,0x25,0x80000000);
        fn_801A9118(0,0x58,5);
      }
      break;
    case 3:
      local_108 = local_90;
      fn_801A852C(&local_108,5,0xe,0x80000000);
      fn_801A9118(0,0x14,5);
      if (fn_80144470(1) != 0) {
        local_10c = local_90;
        fn_801A852C(&local_10c,5,0x24,0x80000000);
        fn_801A9118(0,0x30,5);
      }
      else {
        local_110 = local_90;
        fn_801A852C(&local_110,5,0x23,0x80000000);
        fn_801A9118(0,0x2c,5);
      }
      break;
    case 4:
      local_114 = local_90;
      fn_801A852C(&local_114,5,0xf,0x80000000);
      fn_801A9118(0,0x18,5);
      break;
    case 5:
      local_118 = local_90;
      fn_801A852C(&local_118,5,0x10,0x80000000);
      fn_801A9118(0,0x1c,5);
      break;
    case 6:
      local_11c = local_90;
      fn_801A852C(&local_11c,5,0x29,0x80000000);
      fn_801A9118(0,0x20,5);
      iVar4 = lbl_8064D294;
      switch (iVar4) {
      case 0: {
          local_120 = local_90;
          fn_801A852C(&local_120,5,0x2a,0x80000000);
          fn_801A9118(0,0x5c,5);
        }
        break;
      case 1: {
          local_124 = local_90;
          fn_801A852C(&local_124,5,0x2b,0x80000000);
          fn_801A9118(0,0x60,5);
        }
        break;
      case 2: {
          local_128 = local_90;
          fn_801A852C(&local_128,5,0x2c,0x80000000);
          fn_801A9118(0,100,5);
        }
        break;
      }
    }
    iVar4 = fn_800B193C();
    if (iVar4 != 0) {
      fn_800B2EC0(param_3);
    }
    if (param_1 == 0x10) {
      local_12c = lbl_8064C2C4;
      fn_8011C900(0x13,0x14,0x44,&local_12c,0x40,0xfe);
      fn_801A8D38(5);
    }
    break;
  case 10:
    uVar5 = fn_801EB080();
    local_a4 = lbl_8064DF04;
    iVar4 = 0x20;
    /* Retail clamps signed indices, but tests sequence bounds unsigned below. */
    if ((s32)lbl_8064C694 < 0x20) {
      iVar4 = lbl_8064C694;
    }
    fn_800472B0(1);
    fn_80228B98(lbl_8063B2A0,0);
    fn_80228B98(lbl_8063B2C4,4);
    fn_80228B98(lbl_8063B2AC,2);
    memset(local_8c,0,sizeof(local_8c));
    if ((iVar4 == 3) && (lbl_8064DEA8 == lbl_8064C67C)) {
      fn_801AD4B4(0,0,1,0);
    }
    if (seqTable[iVar4].fade == 1) {
      scale = lbl_8064DEC0 - lbl_8064C67C;
      local_8c[0] = scale;
      local_8c[4] = scale;
    }
    else {
      scale = lbl_8064DEA8;
      local_8c[0] = scale;
      local_8c[4] = scale;
    }
    iVar7 = 0xff;
    if (lbl_8064C68C < 0xff) {
      iVar7 = lbl_8064C68C + 1;
    }
    lbl_8064C68C = iVar7;
    fn_800217F4(&lbl_8064C67C, &lbl_8064C678, lbl_8064DEA8, lbl_8064DEC0,
      seqTable[iVar4].duration, &lbl_8064C680);
    iVar7 = (int)(lbl_8064DF20 * lbl_8064C67C);
    ((u8*)&local_a4)[3] = (u8)iVar7;
    fn_80021714();
    fn_801EC67C(lbl_8023DAB4);
    fn_801EC7F4(lbl_80265FD8,lbl_8063B35C);
    fn_801EC7F4(lbl_80265DA0,lbl_8063B374);
    if ((u32)lbl_8064C694 < 0x21) {
      lbl_8064C698 = lbl_8064C698 + 1;
    }
    if (lbl_8064C698 > seqTable[iVar4].duration + 0xc9) {
      if (lbl_8064C674 != 0) {
        fn_801E5FB0(lbl_8064C674);
      }
      if ((u32)lbl_8064C694 < 0x21) {
        lbl_8064C694 = lbl_8064C694 + 1;
      }
      iVar4 = 0x20;
      if ((s32)lbl_8064C694 < 0x20) {
        iVar4 = lbl_8064C694;
      }
      uVar2 = iVar4 + 1;
      lbl_8064C690 = uVar2;
      if ((u32)uVar2 >= 0x21) {
        uVar6 = 0xffffffff;
      }
      else {
        uVar6 = seqTable[uVar2].track;
      }
      entry = &seqTable[iVar4];
      lbl_8064C690 = uVar6;
      if (entry->movie != -1) {
        uVar6 = (unsigned int)fn_801E6CA0((void*)lbl_8064C518,0,
          entry->movie,0,1);
      }
      else {
        uVar6 = 0;
      }
      track = &entry->track;
      lbl_8064C674 = (void*)uVar6;
      lbl_8064C698 = 0;
      lbl_8064C688 = lbl_8064C684;
      /* Record which streaming slot already holds the step's track. */
      for (slot = 0; slot < 2; slot++) {
        if (*track != -1) {
          if (lbl_8064C6A4[slot] == *track) {
            lbl_8064C684 = slot;
            break;
          }
          lbl_8064C684 = -1;
        }
        else {
          lbl_8064C684 = -1;
        }
      }
      uVar9 = lbl_8064C688;
      uVar2 = lbl_8064C684;
      if (uVar9 != uVar2) {
        lbl_8064C68C = 0;
      }
      if ((uVar2 == -1) ||
        (lbl_8064C690 != lbl_8064C6A4[uVar2])) {
        if (lbl_8064C690 != -1) {
          if (uVar2 != -1) {
            fn_80042FE8(lbl_8064C690,uVar2 ^ 1);
          }
          else {
            fn_80042FE8(lbl_8064C690,0);
          }
        }
        else if (uVar9 != -1) {
          lbl_8064C6A4[uVar9] = 0xffffffff;
        }
      }
    }
    fn_801E5FE4();
    fn_8022A5D8(1,4,5,0);
    fn_801A8D38(5);
    fn_802119B0((double)lbl_8064DEA8,(double)lbl_8064DEBC,
      (double)lbl_8064DEA8,(double)lbl_8064DEB8,
      (double)lbl_8064DEC0,(double)lbl_8064DF24,
      auStack_74);
    fn_8022B4B8(auStack_74,1);
    fn_801ED3F4(lbl_8030241C[4]);
    fn_801A91D4(0xb,0xff - local_a4.channel[3] & 0xff,1);
    fn_80226EA0(0,0,0x280,0x1e0);
    fn_80226FA4(0x280,0x1e0,4,0);
    fn_802276AC(uVar5,1);
    fn_802266B0();
    fn_80228474(lbl_8063C638 + lbl_8064D738 * 0x20,uVar5,0x280,0x1e0,4,0,0,0);
    dVar11 = (double)lbl_8064DEA8;
    fn_80228730(dVar11,dVar11,dVar11,lbl_8063C638 + lbl_8064D738 * 0x20,1,1,0,0,0
      );
    fn_8022A5D8(1,4,5,0);
    if ((lbl_8064C688 != -1) &&
      (iVar4 = lbl_8064C68C, iVar4 != 0xff)) {
      fn_801ED3F4(lbl_8064C6AC[lbl_8064C688]);
      local_134 = lbl_8064DF08;
      ((u8*)&local_134)[3] = 0xff - iVar4;
      local_130 = local_134;
      fn_801A852C(&local_130,0,0,0x80000000);
      if (lbl_8064CBA4 != 0) {
        fn_801A8FE8(lbl_8023D4F8,lbl_8023D4C0,0,0,5);
      }
      else {
        fn_801A8FE8(lbl_8023D4F8,lbl_8023D4E0,0,0,5);
      }
    }
    if ((lbl_8064C684 != -1) &&
      (iVar4 = lbl_8064C68C, iVar4 != 0)) {
      fn_801ED3F4(lbl_8064C6AC[lbl_8064C684]);
      local_13c = lbl_8064DF0C;
      ((u8*)&local_13c)[3] = (char)iVar4;
      local_138 = local_13c;
      fn_801A852C(&local_138,0,0,0x80000000);
      if (lbl_8064CBA4 != 0) {
        fn_801A8FE8(lbl_8023D4F8,lbl_8023D4C0,0,0,5);
      }
      else {
        fn_801A8FE8(lbl_8023D4F8,lbl_8023D4E0,0,0,5);
      }
    }
    fn_80228AFC(lbl_8063C638 + lbl_8064D738 * 0x20,0);
    fn_80228AFC(lbl_8063B260,7);
    fn_80228AFC(lbl_8063B31C,1);
    local_140 = local_a4;
    fn_80229D8C(1,&local_140);
    fn_80229FA4(0,0,1,2,0);
    fn_80229F4C(0,0,0);
    fn_801ECB40(lbl_8064CBA0 + 1U & 0xff);
    fn_801ECB40(lbl_8064CBA0 & 0xff);
    fn_80229E74(0,0xd);
    fn_8022A5D8(1,4,5,3);
    fn_8022A118(0,0,0,0xff);
    fn_80023230(0,1,4,0x3c);
    fn_80229C0C(0,0,0,0,1,0);
    fn_80229CCC(0,0,0,0,1,0);
    fn_80229B88(0,7,4,1,7);
    fn_80229664(0,0,1);
    fn_80229490(0,0,0);
    fn_80229330(1,local_8c,2);
    fn_80229810(0,0,1,0,1);
    fn_802262B8(1);
    fn_8022A2F4(1);
    fn_8022979C(1);
    fn_80229B08(0,0xf,0xe,8,0xf);
    fn_801A8FE8(lbl_8023D4F8,lbl_8023D4E0,0,0,5);
    fn_801A8FE8(lbl_8023D4F8,lbl_8023D540,0,0,5);
    fn_801A8FE8(lbl_8023D4F8,lbl_8023D520,0,0,5);
    fn_80229B08(0,0xf,8,0xc,0xf);
    fn_801A8FE8(lbl_8023D4F8,lbl_8023D4E0,0,0,5);
    fn_8022A044(7,0,0,3,0xff);
    fn_801ED3F4(lbl_8030241C[4]);
    fn_801ECC4C();
    fn_8022979C(0);
    fn_802297C8(0);
    fn_8022A5D8(1,4,5,0);
    break;
  case 15:
    fn_801A91D4(0x18,param_3,1);
    fn_801A90BC(lbl_802515D0,front->title);
    iVar4 = fn_801E8D34(lbl_8064CE80);
    iVar4 = (iVar4 * 0xff) / 0x32;
    cVar3 = 0xff - iVar4;
    ((u8*)&local_a8)[0] = cVar3;
    ((u8*)&local_a8)[1] = cVar3;
    ((u8*)&local_a8)[2] = cVar3;
    ((u8*)&local_a8)[3] = param_3;
    local_144 = local_a8;
    iVar4 = fn_801E8D34(lbl_8064CE80);
    iVar4 = (iVar4 * 400) / 0x32;
    fn_801A8660(0,(short)(0x1b8 - iVar4),0x280,4,
      0xffffffff,&local_144);
    break;
  case 9:
  case 17:
    if (param_1 == 9) {
      fn_801A91D4(5,param_3,1);
    }
    else {
      fn_801A91D4(0xd,param_3,1);
    }
    fn_801A90BC(lbl_802515D0,front->title);
    fn_801ED5F4((double)lbl_8064DEE0,1,0x502,1,0,0);
    local_14c = lbl_8064DF10;
    ((u8*)&local_14c)[3] = param_3;
    local_148 = local_14c;
    fn_801A872C((short)(((param_2 & 3) << 7) + 0x40),
      (short)(((param_2 >> 2) << 7) + 0x30),0x80,0x80,0xffffffff,4,
      &local_148);
    fn_801ED5F4((double)lbl_8064DEC0,0,2,1,0,0);
    fn_801A8D38(5);
    break;
  case 20:
    fn_801A91D4(0xd,param_3,1);
    fn_801A90BC(lbl_802515D0,front->title);
    local_154 = lbl_806518E0;
    ((u8*)&local_154)[3] = param_3;
    selA = &lbl_8023DBD0[param_2];
    selA->channel[2] = 0;
    local_150 = local_154;
    fn_801A8660(100,0xb4,0x1b8,0x78,0xffffffff,&local_150);
    fn_801E3AA4(0);
    fn_801E5AD0(99);
    local_158 = local_94;
    fn_801E3A34(&local_158);
    fn_801E5430(0x140,0xbe);
    fn_801E56AC((double)lbl_8064DEC0,s_Choose_Room_8023dbf8);
    local_15c = lbl_8023DBD0[0];
    fn_801E3A34(&local_15c);
    fn_801E56AC((double)lbl_8064DEC0,s_Room_261_8023dc08);
    local_160 = lbl_8023DBD0[1];
    fn_801E3A34(&local_160);
    fn_801E56AC((double)lbl_8064DEC0,s_Room_264_8023dc14);
    local_164 = lbl_8023DBD0[2];
    fn_801E3A34(&local_164);
    fn_801E56AC((double)lbl_8064DEC0,s_Room_266_8023dc20);
    selA->channel[2] = 0xff;
    break;
  case 21:
    fn_801A91D4(0xd,param_3,1);
    fn_801A90BC(lbl_802515D0,front->title);
    local_16c = lbl_806518E4;
    ((u8*)&local_16c)[3] = param_3;
    selB = &lbl_8023DBDC[param_2];
    selB->channel[2] = 0;
    local_168 = local_16c;
    fn_801A8660(100,0xb4,0x1b8,0xdc,0xffffffff,&local_168);
    fn_801E3AA4(0);
    fn_801E5AD0(99);
    local_170 = local_94;
    fn_801E3A34(&local_170);
    fn_801E5430(0x140,0xbe);
    fn_801E56AC((double)lbl_8064DEC0,s_Choose_Room_8023dbf8);
    local_174 = lbl_8023DBDC[0];
    fn_801E3A34(&local_174);
    fn_801E56AC((double)lbl_8064DEC0,s_Alex_Room_94_8023dc2c);
    local_178 = lbl_8023DBDC[1];
    fn_801E3A34(&local_178);
    fn_801E56AC((double)lbl_8064DEC0,s_Edward_Room_271_8023dc3c);
    local_17c = lbl_8023DBDC[2];
    fn_801E3A34(&local_17c);
    fn_801E56AC((double)lbl_8064DEC0,s_Edward_Room_275_8023dc50);
    local_180 = lbl_8023DBDC[3];
    fn_801E3A34(&local_180);
    fn_801E56AC((double)lbl_8064DEC0,s_Edward_Room_278_8023dc64);
    local_184 = lbl_8023DBDC[4];
    fn_801E3A34(&local_184);
    fn_801E56AC((double)lbl_8064DEC0,s_Edward_Room_282_8023dc78);
    local_188 = lbl_8023DBDC[5];
    fn_801E3A34(&local_188);
    fn_801E56AC((double)lbl_8064DEC0,s_Abdule_Room_213_8023dc8c);
    local_18c = lbl_8023DBDC[6];
    fn_801E3A34(&local_18c);
    fn_801E56AC((double)lbl_8064DEC0,s_Major_Mike_Room_219_8023dca0);
    selB->channel[2] = 0xff;
    break;
  case 11:
  case 22:
    if (param_1 == 0xb) {
      fn_801A91D4(5,param_3,1);
    }
    else {
      fn_801A91D4(0xd,param_3,1);
    }
    fn_801A90BC(lbl_802515D0,front->title);
    local_194 = lbl_806518E8;
    ((u8*)&local_194)[3] = param_3;
    local_190 = local_194;
    fn_801A8660(100,0xb4,0x1b8,0x78,0xffffffff,&local_190);
    fn_801E3AA4(0);
    fn_801E5AD0(99);
    local_198 = local_94;
    fn_801E3A34(&local_198);
    fn_801E5430(0x140,0xbe);
    fn_801E56AC((double)lbl_8064DEC0,s_CHOOSE_YOUR_FATE_8023dcb4);
    switch (param_2 + 1) {
    case 1:
      fn_801E56AC(lbl_8064DEC0,s__ac_c__i27_8023dcc8);
      break;
    case 2:
      fn_801E56AC(lbl_8064DEC0,s__au_u__i28_8023dcd4);
      break;
    case 3:
      fn_801E56AC(lbl_8064DEC0,s__ax_x__i29_8023dce0);
      break;
    }
    break;
  case 250:
    fn_801A91D4(5,param_3,1);
    fn_801A90BC(lbl_802515D0,front->title);
    local_1a0 = lbl_806518EC;
    ((u8*)&local_1a0)[3] = param_3;
    local_19c = local_1a0;
    fn_801A8660(100,0xb4,0x1b8,0x78,0xffffffff,&local_19c);
    fn_801E3AA4(0);
    fn_801E5AD0(99);
    local_1a4 = local_94;
    fn_801E3A34(&local_1a4);
    fn_801E5430(0x140,0xbe);
    fn_801E56AC((double)lbl_8064DEC0,
      s_Do_you_want_to_set_the__ar_Etern_8023dcec);
    if (param_2 == 1) {
      fn_801E56AC((double)lbl_8064DEC0,s__ayYes__awNo_8023dd20);
    }
    else {
      fn_801E56AC((double)lbl_8064DEC0,s__awYes__ayNo_8023dd30);
    }
    break;
  case 1:
  case 4:
  case 24:
  case 31:
    if (lbl_8064C6D4 == 0) {
      lbl_8064C600 = lbl_8064C600 + 1;
    }
    else {
      local_1a8 = lbl_8064DF14;
      fn_801F3960(&local_1a8);
      fn_801ED3F4(lbl_8030241C[3]);
      local_1b0 = lbl_8064DF18;
      ((u8*)&local_1b0)[3] = param_3;
      local_1ac = local_1b0;
      fn_801A852C(&local_1ac,0,0,0x80000000);
      fn_801A8FE8(lbl_802515D0,lbl_8023D4E0,0,0,5);
    }
    break;
  case 26:
    fn_801ED3F4(lbl_8030241C[3]);
    local_1b8 = lbl_8064DF1C;
    ((u8*)&local_1b8)[3] = param_3;
    local_1b4 = local_1b8;
    fn_801A852C(&local_1b4,0,3,0x80000000);
    fn_801A8FE8(lbl_802515D0,lbl_8023D4E0,0,0,5);
    break;
  case 3:
    fn_801ED3F4(lbl_8030241C[3]);
    if (lbl_8064CBA4 == 1) {
      fn_801A9250(2,param_3,1);
    }
    else {
      fn_801A91D4(2,param_3,1);
    }
    break;
  case 253:
    fn_801A91D4(0xc,param_3,1);
    break;
  case 251:
    fn_801A91D4(0xc,0xff,1);
    iVar4 = (int)(lbl_8064DEE4 * (float)(param_3 & 0xff));
    fn_801A91D4(0xb,iVar4,1);
    break;
  case 252:
    fn_801A91D4(0xd,param_3,1);
    break;
  case 254:
    fn_801A91D4(0x19,param_3,1);
    break;
  default:
    break;
  }
  if (lbl_8064C59C != 0) {
    fn_801E3AA4(0);
    fn_801E5AD0(99);
    fn_801E5430(0x140,0x32);
    pcVar8 = s__agPLAYBACK_8023dd5c;
    if (lbl_8064C59C == 1) {
      pcVar8 = s__arRECORD_8023dd50;
    }
    fn_801E56AC(lbl_8064DEC0,s_Controller___s_8023dd40,pcVar8);
  }
  return;
}
