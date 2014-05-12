#ifndef  __Z_H__
#define __Z_H__

/*! Now, we open a new programming !*/
#ifndef UNUSED
#define UNUSED(x)   ((void)x)
#endif

#define choose_expr __builtin_choose_expr
#define types_p     __builtin_types_compatible_p
#define is_const    __builtin_constant_p

#define build_buf_on(e)         (sizeof(char[1 - 2 * !!(e)]))
#define build_bug_on_zero(e)    (sizeof(char[1 - 2 * !!(e)]) - 1)
#define __must_be_array(a)  build_bug_on_zero(types_p(__typeof__(a),__typeof__(&a[0])))

#define test(a)   (a)
#define $(ret,expr)    ({ ret $$ expr;&$$;})
#define lambda  $
#define STRING(x)   _STRING(x)
#define _STRING(x)  #x

/*! ~~~~~~~~~~~~~~~~~~~~~~~ excoption ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ !*/
#define try(expr,code,...) ({\
        __typeof__(code) _v = code;\
        if(test(expr _v)){\
            eprint("Exception : " #code "\nUnfold    : "STRING(code));\
            __VA_ARGS__;\
        }_v;})

#define throw    goto

#define foreach(index,start,end) for(__typeof__(end) index = start;index < end;index++)
#define ARRAY_SIZE(v)  (sizeof(v) / sizeof(__typeof__(v[0])) + __must_be_array(v))


/*! ~~~~~~~~~~~~~~~~~~~~  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ !*/
#define PP_NARG(...) \
    PP_NARG_(__VA_ARGS__,PP_RSEQ_N())

#define PP_NARG_(...) \
    PP_ARG_N(__VA_ARGS__)

#define PP_ARG_N( \
         _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
        _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
        _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
        _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
        _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
        _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
        _61,_62,_63,_64,_65,_66,_67,_68,_69,N,...) N

#define _NR_N(n) n ## 9,n ## 8,n ## 7,n ## 6,n ## 5,n ## 4,n ## 3,n ## 2,n ## 1,n ## 0
#define NR_N(n) _NR_N(n)
#define PP_RSEQ_N() \
    NR_N(6), NR_N(5), NR_N(4), NR_N(3), NR_N(2), NR_N(1), NR_N(),


#define TOKEN(x,y)  _TOKEN(x,y)
#define _TOKEN(x,y) x ## y

#define EXPR0(expr,arg)            (expr arg)
#define EXPR1(expr,link,arg,...)   EXPR0(expr,arg) 
#define EXPR2(expr,link,arg,...)   EXPR0(expr,arg) link EXPR1(expr,link,__VA_ARGS__)
#define EXPR3(expr,link,arg,...)   EXPR0(expr,arg) link EXPR2(expr,link,__VA_ARGS__)
#define EXPR4(expr,link,arg,...)   EXPR0(expr,arg) link EXPR3(expr,link,__VA_ARGS__)
#define EXPR5(expr,link,arg,...)   EXPR0(expr,arg) link EXPR4(expr,link,__VA_ARGS__)
#define EXPR6(expr,link,arg,...)   EXPR0(expr,arg) link EXPR5(expr,link,__VA_ARGS__)
#define EXPR7(expr,link,arg,...)   EXPR0(expr,arg) link EXPR6(expr,link,__VA_ARGS__)
#define EXPR8(expr,link,arg,...)   EXPR0(expr,arg) link EXPR7(expr,link,__VA_ARGS__)
#define EXPR9(expr,link,arg,...)   EXPR0(expr,arg) link EXPR8(expr,link,__VA_ARGS__)
#define EXPR(expr,link,...)        TOKEN(EXPR,PP_NARG(__VA_ARGS__))(expr,link,__VA_ARGS__)
#define and(expr,...)      EXPR(expr,&&,__VA_ARGS__)
#define or(expr,...)       EXPR(expr,||,__VA_ARGS__)

#define APPLY0(fn,arg)            fn(arg)
#define APPLY1(fn,link,arg,...)   APPLY0(fn,arg) 
#define APPLY2(fn,link,arg,...)   APPLY0(fn,arg) link APPLY1(fn,link,__VA_ARGS__)
#define APPLY3(fn,link,arg,...)   APPLY0(fn,arg) link APPLY2(fn,link,__VA_ARGS__)
#define APPLY4(fn,link,arg,...)   APPLY0(fn,arg) link APPLY3(fn,link,__VA_ARGS__)
#define APPLY5(fn,link,arg,...)   APPLY0(fn,arg) link APPLY4(fn,link,__VA_ARGS__)
#define APPLY6(fn,link,arg,...)   APPLY0(fn,arg) link APPLY5(fn,link,__VA_ARGS__)
#define APPLY7(fn,link,arg,...)   APPLY0(fn,arg) link APPLY6(fn,link,__VA_ARGS__)
#define APPLY8(fn,link,arg,...)   APPLY0(fn,arg) link APPLY7(fn,link,__VA_ARGS__)
#define APPLY9(fn,link,arg,...)   APPLY0(fn,arg) link APPLY8(fn,link,__VA_ARGS__)
#define APPLY(fn,link,...)        TOKEN(APPLY,PP_NARG(__VA_ARGS__))(fn,link,__VA_ARGS__)
#define _CATCH(x)    x:
#define catch(...)  APPLY(_CATCH,,__VA_ARGS__)
#define unused(...) APPLY(UNUSED,;,__VA_ARGS__)

#endif
