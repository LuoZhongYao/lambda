#ifndef  __Z_H__
#define __Z_H__

/*! Now, we open a new programming !*/

#ifndef UNUSED
#define UNUSED(x)   (void)(x)
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

#define throw(excpt)    goto excpt
#define CATCH0(arg)      arg:
#define CATCH1(arg,...)  CATCH0(arg) 
#define CATCH2(arg,...)  CATCH0(arg) CATCH1(__VA_ARGS__)
#define CATCH3(arg,...)  CATCH0(arg) CATCH2(__VA_ARGS__)
#define CATCH4(arg,...)  CATCH0(arg) CATCH3(__VA_ARGS__)
#define CATCH5(arg,...)  CATCH0(arg) CATCH4(__VA_ARGS__)
#define CATCH6(arg,...)  CATCH0(arg) CATCH5(__VA_ARGS__)
#define CATCH7(arg,...)  CATCH0(arg) CATCH6(__VA_ARGS__)
#define CATCH8(arg,...)  CATCH0(arg) CATCH7(__VA_ARGS__)
#define CATCH9(arg,...)  CATCH0(arg) CATCH8(__VA_ARGS__)
#define catch(...)    TOKEN(CATCH,PP_NARG(__VA_ARGS__))(__VA_ARGS__)

#define foreach(start,end) for(__typeof__(end) i = start;i < end;i++)
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

#define LOGIC0(expr,arg)             (expr arg)
#define LOGIC1(logic,expr,arg,...)   LOGIC0(expr,arg) 
#define LOGIC2(logic,expr,arg,...)   LOGIC0(expr,arg) logic LOGIC1(logic,expr,__VA_ARGS__)
#define LOGIC3(logic,expr,arg,...)   LOGIC0(expr,arg) logic LOGIC2(logic,expr,__VA_ARGS__)
#define LOGIC4(logic,expr,arg,...)   LOGIC0(expr,arg) logic LOGIC3(logic,expr,__VA_ARGS__)
#define LOGIC5(logic,expr,arg,...)   LOGIC0(expr,arg) logic LOGIC4(logic,expr,__VA_ARGS__)
#define LOGIC6(logic,expr,arg,...)   LOGIC0(expr,arg) logic LOGIC5(logic,expr,__VA_ARGS__)
#define LOGIC7(logic,expr,arg,...)   LOGIC0(expr,arg) logic LOGIC6(logic,expr,__VA_ARGS__)
#define LOGIC8(logic,expr,arg,...)   LOGIC0(expr,arg) logic LOGIC7(logic,expr,__VA_ARGS__)
#define LOGIC9(logic,expr,arg,...)   LOGIC0(expr,arg) logic LOGIC8(logic,expr,__VA_ARGS__)
#define LOGIC(logic,expr,...)        TOKEN(LOGIC,PP_NARG(__VA_ARGS__))(logic,expr,__VA_ARGS__)
#define and(expr,...)   (LOGIC(&&,expr,__VA_ARGS__))
#define  or(expr,...)   (LOGIC(||,expr,__VA_ARGS__))

#endif
