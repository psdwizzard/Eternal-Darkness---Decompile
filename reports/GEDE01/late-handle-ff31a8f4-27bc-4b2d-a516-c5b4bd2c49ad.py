import runpy
m=runpy.run_path('reports/GEDE01/probe-ff31a8f4-27bc-4b2d-a516-c5b4bd2c49ad.py')
BASE=m['BASE'];trial=m['trial'];region=m['region']
s=BASE.replace('    void* found;','    void* attachment;\n    void* found;')
s=region(s,'        found = fn_80201C2C','        array = fn_80201C24','found','attachment')
s=s.replace('        void* object;\n','').replace('    void* script_reg;','    void* object;\n    void* script_reg;')
for name in ['array','attachment','found','position']:
 a=region(s,'    } else if (req.f30 == 3)','        fn_801568C8(object','handle',name)
 r=trial('late_handle_as_'+name,a,'After split-found/hoisted-object improvement, reuse a dead pointer local for late handle. Lifetimes do not overlap; all calls accept void pointers.')
 if r.get('measurement',{}).get('match_percent')==100:break
else:
 for anchor in ['void* object','void* script_reg','void* view','Vec3s* position','s32 mode','void* handle','void* callback','s32 controller','void* attachment','void* found','ItemArray* array','s32 index']:
  a=region(s,'    } else if (req.f30 == 3)','        fn_801568C8(object','handle','late_handle')
  a=a.replace('    '+anchor+';','    void* late_handle;\n    '+anchor+';')
  r=trial('late_handle_before_'+anchor.split()[-1],a,'Separate late handle web and place before '+anchor+' in improved split-found/hoisted-object source; test graph coloring tie order.')
  if r.get('measurement',{}).get('match_percent')==100:break
