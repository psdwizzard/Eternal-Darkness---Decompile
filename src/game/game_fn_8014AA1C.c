typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef struct Set { u8 count; u8 p1[3]; u16 mask; u16 active; u32 ids[16]; u32 values[16]; void* objects[16]; } Set;
typedef struct Vec { float x,y,z; } Vec;
typedef struct Result { u8 pad[8]; Vec position; u8 tail[16]; } Result;
extern void *fn_80156938(); extern int fn_80157034(void*); extern u32 fn_80036D5C(void);
extern void fn_8017FD6C(void*); extern void *fn_80201BC8(); extern int fn_8012FA54(void*,u32);
extern int fn_8012DC94(void*,u32); extern void* fn_80193848(void*); extern void *fn_80201814();
extern void* fn_80155DB4(void*); extern u32 fn_80193838(void*); extern int fn_8011F6A4(void*,u32,u32,int,void*,int);
extern short* fn_8017FDE4(void*); extern u32 fn_80193840(void*); extern short* fn_801938A8(void*);
extern void fn_8014B604(float*,short*);
void fn_8014AA1C(void* left, void* right) {
    int ready,i; Set* source; Set* set; u16 bit,current; Result result; u8 count;
    if(!left)return; ready=0; source=0; if(right && !fn_80157034(right) && (source=fn_80156938(right)) && !(fn_80036D5C()&0x04000000)) ready=1;
    if(!(set=fn_80156938(left)))return;
    count=set->count;
    if(!ready){for(bit=1,i=0;i<count;i++,bit=current<<1){current=bit;if((set->mask&current)&&set->objects[i]){fn_8017FD6C(set->objects[i]);set->mask&=~current;}}return;}
    {void* src=fn_80201BC8(source);for(bit=1,i=0;i<count;i++,bit=current<<1){int keep;current=bit;
      if(!(set->mask&current)||!set->objects[i])continue;
      keep=0;
      if(fn_8012FA54(src,set->values[i])||!fn_8012DC94(src,set->values[i])){void* link=fn_80201814(fn_80193848(set->objects[i])); void* checked;
       if(link && !(fn_80036D5C()&0x04000000) && (checked=fn_80155DB4(link)) && !fn_80157034(checked)) {void* dst=fn_80201BC8(link);u32 id=fn_80193838(set->objects[i]);
        if(fn_8012FA54(dst,id)||!fn_8012DC94(dst,id)){short* p;fn_8011F6A4(src,set->ids[i],set->values[i],-1,&result,1);p=fn_8017FDE4(set->objects[i]);p[0]=(short)result.position.x;p[1]=(short)result.position.y;p[2]=(short)result.position.z;
         {u32 source_id=fn_80193840(set->objects[i]);fn_8011F6A4(dst,source_id,id,-1,&result,1);}p=fn_801938A8(set->objects[i]);fn_8014B604(&result.position.x,p);fn_8014B604(&result.position.y,p+1);fn_8014B604(&result.position.z,p+2);keep=1;}}}
      if(!keep){fn_8017FD6C(set->objects[i]);set->mask&=~current;}
    }}
}
