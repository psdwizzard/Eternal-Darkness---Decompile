typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Object { u8 b[0x1000]; } Object;

extern int lbl_8064D18C;
extern int lbl_8064C270;
extern void* fn_80201814(u32);
extern int fn_80201B64(void*);
extern void fn_8020123C(int, u32, u32, int);
extern u8* fn_80201B8C(void*);
extern int fn_80201EB8(void*);
extern int fn_800A1060(void);
extern u8 fn_801911D0(void*); extern void fn_801911D8(void*,void*);
extern void fn_801911F4(void*,u8); extern u8* fn_801911C8(void*);
extern u8 fn_80180130(void*); extern int fn_80180138(void*,u8);
extern u8 fn_801911B0(void*,int); extern void fn_8019120C(void*,int);
extern s16* fn_8017FDA8(void*,int); extern s16* fn_8017FDE4(void*);
extern u8 fn_8017FDFC(void*); extern void fn_80149B60(void*,void*,int,int,int);
extern float fn_80048C2C(float); extern float fn_80048C50(float);
extern u8 fn_800FBFB0(void); extern void fn_801850FC(void*,void*);
extern void fn_80185108(void*); extern void fn_801851A0(void*,void*);
extern void fn_801D0E78(void*);

static void alter(Object* o, void* state, void* actor, u8* table, int index, int count)
{
    s16* source; s16* dest; float angle;
    if (fn_801911B0(state,index)) return;
    source=fn_8017FDA8(state,index); dest=fn_8017FDA8(state,index);
    angle=360.0f*(float)index/(float)count;
    dest[0]=(s16)((float)source[0]+127.0f*fn_80048C2C(angle));
    dest[1]=(s16)((float)source[1]+127.0f*fn_80048C50(angle));
    dest[2]=(s16)(source[2]+127-(u8)fn_800FBFB0());
}

void fn_801DB140(Object* o)
{
    void* state=0; void* actor; int special; int changed=0; int i;
    u8* table; u8 flags=o->b[0xC4];
    if (*(void**)(o->b+0x18C)) state=*(void**)(*(u8**)(o->b+0x18C)+0x88);
    actor=fn_80201814(*(u32*)(o->b+0xC));
    if (!actor || (fn_80201B64(actor)==8 && !fn_800A1060()))
        fn_8020123C(0x39,*(u32*)(o->b+0xBC),*(u32*)(o->b+0xBC),0);
    if (!(flags&1)) {
        if (state) { u8 f=fn_801911D0(state); if (*(void**)(o->b+0xC8)) { f|=4; fn_801911D8(state,state); } else f&=~1; fn_801911F4(state,f); }
        fn_801D0E78(o); return;
    }
    special=fn_80201EB8(actor)==lbl_8064D18C;
    if (state && actor && o->b[0xC6]) {
        u8* info=fn_80201B8C(actor);
        if (info && *(void**)(info+0x8C) && fn_80201814(*(u32*)(*(u8**)(info+0x8C)+0x24))) {
            info=fn_80201B8C(fn_80201814(*(u32*)(*(u8**)(info+0x8C)+0x24)));
            if (info && *(void**)(info+0x24)) fn_801911D8(state,info+0xEC);
        }
        table=fn_801911C8(state);
        for(i=(u8)fn_80180130(state)-1;i>=0 && changed<o->b[0xC6];i--)
            if(fn_80180138(state,(u8)i) && !fn_801911B0(state,i)) { fn_8019120C(state,i); *table|=1<<i; changed++; }
        o->b[0xC6]=0;
    }
    if (flags&4) {
        if(o->b[0xC5]) { o->b[0xC5]--; changed=1; }
        else if(state) {
            fn_801911F4(state,fn_801911D0(state)|0x40); table=*(u8**)(o->b+0x250);
            if(flags&0x30) { s16* v=fn_8017FDE4(state); fn_80149B60(actor,v,0,0,0); for(i=0;i<table[0];i++) alter(o,state,actor,table,i,table[0]); }
            for(i=0;i<table[0];i++) if(!fn_801911B0(state,i)) { void* x=*(void**)(table+0x88+i*4); fn_801850FC(x,&lbl_8064C270); fn_80185108(x); fn_801851A0(x,fn_8017FDA8(state,i)); }
        }
        if(!(flags&0x10)) { o->b[0xC4]&=~6; o->b[0xC5]=40; }
    } else if(flags&2) { if(state) fn_801911F4(state,fn_801911D0(state)|0x20); o->b[0xC4]&=~2; }
    if(!special || *(u32*)(o->b+0xC0)!=lbl_8064D18C || (o->b[0xFF0]&2)) {
        if(state && !(o->b[0xC4]&0x30)) { table=*(u8**)(o->b+0x250); fn_80149B60(actor,fn_8017FDE4(state),0,0,0); for(i=0;i<table[0];i++) alter(o,state,actor,table,i,table[0]); }
        *(u32*)(o->b+0xC0)=lbl_8064D18C; o->b[0xFF0]&=~2;
    }
    if(o->b[0xC4]&0x10) o->b[0xC4]|=0x20; else o->b[0xC4]&=~0x30;
    o->b[0xC4]&=~0x18;
}
