import runpy
m=runpy.run_path('reports/GEDE01/probe-ff31a8f4-27bc-4b2d-a516-c5b4bd2c49ad.py')
BASE=m['BASE']; trial=m['trial'];region=m['region']
s=BASE.replace('    void* found;','    void* attachment;\n    void* found;')
s=region(s,'        found = fn_80201C2C','        array = fn_80201C24','found','attachment')
# Distinct callback result for late object configuration.
a=s.replace('        void* object;','        void* object;\n        void* object_callback;')
a=region(a,'    } else if (req.f30 == 3)','        lbl_8064C554 = object;','callback','object_callback').replace('object_object_callback','object_callback')
trial('split_found_and_callback',a,'Separate callback-selection webs as well as found roles; test interference ordering in the remaining nine rows.')
# Reuse the initial integer enum as temporary object pointer: nonoverlapping lifetimes.
a=s.replace('        void* object;\n','')
a=region(a,'    } else if (req.f30 == 3)','        found = fn_80158598', 'object', '(void*)mode')
a=a.replace('(void*)mode = fn_80156DA0','mode = (s32)fn_80156DA0')
trial('split_found_mode_object_web',a,'Reuse dead initial mode scalar for late controller object; no overlap and explicit casts preserve 32-bit pointer bits.')
# Reuse the shared callback controller scalar for the same kind of object in case 3.
a=s.replace('        void* object;\n','')
a=region(a,'    } else if (req.f30 == 3)','        found = fn_80158598','object','(void*)controller').replace('(void*)controller = fn_80156DA0','controller = (s32)fn_80156DA0')
trial('split_found_unify_controller_object',a,'Use the existing callback controller scalar in both controller-creation branches.')
# Move late handle to pointer-typed controller variable prior to its final call use.
a=s
start=a.index('    } else if (req.f30 == 3)');stop=a.index('        fn_801568C8(object',start)
a=a[:start]+a[start:stop].replace('handle = fn_80201BC8(view);','controller = (s32)fn_80201BC8(view);').replace('fn_8011FA8C(handle','fn_8011FA8C((void*)controller').replace('fn_801261F4(handle','fn_801261F4((void*)controller').replace('fn_8011FCB0(handle','fn_8011FCB0((void*)controller')+a[stop:]
trial('split_found_controller_for_late_handle',a,'Reuse dead controller scalar for late handle lookup, changing allocation web without merging position or mode.')
# Equivalent expression order, avoid temporary object definition until callback condition argument consumes handle.
a=s.replace('        object = fn_80156DA0(3, 0);\n        if (fn_8011FCB0(handle) != 0) {','        if ((object = fn_80156DA0(3, 0), fn_8011FCB0(handle)) != 0) {')
trial('split_found_object_comma',a,'Put object creation and handle test in one sequenced expression; retain call order, alter temporary live-range construction.')
# Sequential blocks restrict the old handle name to the last read, then assign object.
a=s.replace('        object = fn_80156DA0(3, 0);\n        if (fn_8011FCB0(handle) != 0) {','        object = fn_80156DA0(3, 0);\n        if (fn_8011FCB0(handle) ? 1 : 0) {')
trial('split_found_boolean_condition',a,'Canonicalize callback predicate through conditional expression to test scheduler/web lowering.')
# Share same typed scalar for mode and late attachment rather than found result.
a=s.replace('    void* attachment;\n','').replace('attachment = fn_80201C2C','mode = (s32)fn_80201C2C').replace('attachment = fn_80204C2C','mode = (s32)fn_80204C2C').replace('if (attachment == 0)','if (mode == 0)').replace('fn_80204CE4(view, attachment)','fn_80204CE4(view, (void*)mode)')
trial('attachment_mode_reuse',a,'Join mode and attachment scalar webs, while preserving split owner search.')
