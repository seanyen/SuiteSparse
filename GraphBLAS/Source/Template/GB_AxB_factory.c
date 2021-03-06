//------------------------------------------------------------------------------
// GB_AxB_factory: switch factory for C=A*B
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2021, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

// This is used by GB_AxB_saxpy3.c and GB_AxB_dot[234].c to create the
// built-in versions of sparse matrix-matrix multiplication.  The #include'ing
// file defines the GB_AxB_WORKER macro, and mult_opcode, add_opcode, xcode,
// ycode, and zcode.

// Three 2nd level switch factories are used:

//      GB_AxB_type_factory: handles all semirings where the multiply operator
//          is TxT->T (as is the monoid).

//      GB_AxB_compare_factory: handles all semirings where the multiply
//          operator is TxT -> bool (for the comparison operators, LT, GT,
//          etc), and where the monoid is bool x bool -> bool.

//      GB_AxB_bitwise_factory: handles all semirings for bitwise operators.

//      GxB_AxB_positional_factory: handles all semirings for positional
//          multiply operators.  Those operators are of the for XxX -> int64,
//          where "X" denotes any type.  No typecasting is needed from the
//          types of A and B.

// If the multiplicative operator is ANY, then it has already been renamed to
// SECOND, prior to using this factory, since that is faster for the
// saxpy-based methods (y is the value of B(k,j), which is loaded less
// frequently from memory than A(i,k)).

ASSERT (mult_opcode != GB_ANY_opcode) ;

{
    //--------------------------------------------------------------------------
    // launch the switch factory
    //--------------------------------------------------------------------------

    switch (mult_opcode)
    {

        //----------------------------------------------------------------------
        case GB_FIRST_opcode   :    // z = x
        //----------------------------------------------------------------------

            // 61 semirings with FIRST:
            // 50: (min,max,plus,times,any) for 10 non-boolean real
            // 5: (or,and,xor,eq,any) for boolean
            // 6: (plus,times,any) for 2 complex
            #define GB_MNAME _first
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_SECOND_opcode  :    // z = y
        //----------------------------------------------------------------------

            // 61 semirings with SECOND:
            // 50: (min,max,plus,times,any) for 10 real non-boolean
            // 5: (or,and,xor,eq,any) for boolean
            // 6: (plus,times,any) for 2 complex
            #define GB_MNAME _second
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_PAIR_opcode   :    // z = 1
        //----------------------------------------------------------------------

            // 26 semirings with PAIR:
            // 20: (plus,any) for 10 real non-boolean
            // 2: (xor,any) for boolean
            // 4: (plus,any) for 2 complex
            // land_pair, lor_pair, max_pair, min_pair, times_pair, eq_pair
            // all become any_pair.
            #define GB_MULT_IS_PAIR_OPERATOR
            #define GB_MNAME _pair
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            #undef  GB_MULT_IS_PAIR_OPERATOR
            break ;

        //----------------------------------------------------------------------
        case GB_MIN_opcode     :    // z = min(x,y)
        //----------------------------------------------------------------------

            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // MIN == TIMES == AND for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _min
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_MAX_opcode     :    // z = max(x,y)
        //----------------------------------------------------------------------

            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // MAX == PLUS == OR for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _max
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_PLUS_opcode    :    // z = x + y
        //----------------------------------------------------------------------

            // 56 semirings:
            // 50: (min,max,plus,times,any) for 10 real non-boolean
            // 6: (plus,times,any) for 2 complex types
            // MAX == PLUS == OR for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _plus
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_MINUS_opcode   :    // z = x - y
        //----------------------------------------------------------------------

            // 56 semirings:
            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // 6: (plus,times,any) for 2 complex types
            // MINUS == RMINUS == NE == ISNE == XOR for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _minus
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_RMINUS_opcode   :    // z = y - x (reverse minus)
        //----------------------------------------------------------------------

            // 56 semirings:
            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // 6: (plus,times,any) for 2 complex types
            #define GB_NO_BOOLEAN
            #define GB_MNAME _rminus
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_TIMES_opcode   :    // z = x * y
        //----------------------------------------------------------------------

            // 56 semirings:
            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // 6: (plus,times,any) for 2 complex types
            #define GB_NO_BOOLEAN
            #define GB_MNAME _times
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_DIV_opcode   :      // z = x / y
        //----------------------------------------------------------------------

            // 56 semirings:
            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // 6: (plus,times,any) for 2 complex types
            // FIRST == DIV for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _div
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_RDIV_opcode   :     // z = y / x (reverse division)
        //----------------------------------------------------------------------

            // 56 semirings:
            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // 6: (plus,times,any) for 2 complex types
            // SECOND == RDIV for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _rdiv
            #define GB_COMPLEX
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_ISEQ_opcode    :    // z = (x == y)
        //----------------------------------------------------------------------

            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // ISEQ == EQ for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _iseq
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_ISNE_opcode    :    // z = (x != y)
        //----------------------------------------------------------------------

            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // MINUS == RMINUS == NE == ISNE == XOR for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _isne
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_ISGT_opcode    :    // z = (x >  y)
        //----------------------------------------------------------------------

            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // ISGT == GT for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _isgt
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_ISLT_opcode    :    // z = (x <  y)
        //----------------------------------------------------------------------

            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // ISLT == LT for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _islt
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_ISGE_opcode    :    // z = (x >= y)
        //----------------------------------------------------------------------

            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // ISGE == GE for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _isge
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_ISLE_opcode     :    // z = (x <= y)
        //----------------------------------------------------------------------

            // 50 semirings: (min,max,plus,times,any) for 10 real non-boolean
            // ISLE == LE for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _isle
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_EQ_opcode      :    // z = (x == y)
        //----------------------------------------------------------------------

            // 55 semirings: (and,or,xor,eq,any) * 11 types (all but complex)
            #define GB_MNAME _eq
            #include "GB_AxB_compare_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_NE_opcode      :    // z = (x != y)
        //----------------------------------------------------------------------

            // 50 semirings: (and,or,xor,eq,any) * (10 real non-boolean types)
            // MINUS == RMINUS == NE == ISNE == XOR for boolean
            #define GB_NO_BOOLEAN
            #define GB_MNAME _ne
            #include "GB_AxB_compare_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_GT_opcode      :    // z = (x >  y)
        //----------------------------------------------------------------------

            // 55 semirings: (and,or,xor,eq,any) * 11 types (all but complex)
            #define GB_MNAME _gt
            #include "GB_AxB_compare_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_LT_opcode      :    // z = (x <  y)
        //----------------------------------------------------------------------

            // 55 semirings: (and,or,xor,eq,any) * 11 types (all but complex)
            #define GB_MNAME _lt
            #include "GB_AxB_compare_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_GE_opcode      :    // z = (x >= y)
        //----------------------------------------------------------------------

            // 55 semirings: (and,or,xor,eq,any) * 11 types (all but complex)
            #define GB_MNAME _ge
            #include "GB_AxB_compare_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_LE_opcode      :    // z = (x <= y)
        //----------------------------------------------------------------------

            // 55 semirings: (and,or,xor,eq,any) * 11 types (all but complex)
            #define GB_MNAME _le
            #include "GB_AxB_compare_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_LOR_opcode     :    // z = x || y
        //----------------------------------------------------------------------

            // 55 semirings: (and,or,xor,eq,any) * 11 types (all but complex)
            #define GB_MNAME _lor
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_LAND_opcode    :    // z = x && y
        //----------------------------------------------------------------------

            // 55 semirings: (and,or,xor,eq,any) * 11 types (all but complex)
            #define GB_MNAME _land
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_LXOR_opcode    :    // z = x != y
        //----------------------------------------------------------------------

            // 55 semirings: (and,or,xor,eq,any) * 11 types (all but complex)
            #define GB_MNAME _lxor
            #include "GB_AxB_type_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_BOR_opcode :     // z = (x | y), bitwise or
        //----------------------------------------------------------------------

            // 16 semirings: (bor,band,bxor,bxnor) * (uint8,16,32,64)
            #define GB_MNAME _bor
            #include "GB_AxB_bitwise_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_BAND_opcode :    // z = (x & y), bitwise and
        //----------------------------------------------------------------------

            // 16 semirings: (bor,band,bxor,bxnor) * (uint8,16,32,64)
            #define GB_MNAME _band
            #include "GB_AxB_bitwise_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_BXOR_opcode :    // z = (x ^ y), bitwise xor
        //----------------------------------------------------------------------

            // 16 semirings: (bor,band,bxor,bxnor) * (uint8,16,32,64)
            #define GB_MNAME _bxor
            #include "GB_AxB_bitwise_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_BXNOR_opcode :   // z = ~(x ^ y), bitwise xnor
        //----------------------------------------------------------------------

            // 16 semirings: (bor,band,bxor,bxnor) * (uint8,16,32,64)
            #define GB_MNAME _bxnor
            #include "GB_AxB_bitwise_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_FIRSTI_opcode   :   // z = first_i(A(i,k),y) == i
        //----------------------------------------------------------------------

            // 10 semirings: (min,max,times,plus,any) * (int32,int64)
            #define GB_MNAME _firsti
            #include "GB_AxB_positional_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_FIRSTI1_opcode  :   // z = first_i1(A(i,k),y) == i+1
        //----------------------------------------------------------------------

            // 10 semirings: (min,max,times,plus,any) * (int32,int64)
            #define GB_MNAME _firsti1
            #include "GB_AxB_positional_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_FIRSTJ_opcode   :   // z = first_j(A(i,k),y) == k
        case GB_SECONDI_opcode  :   // z = second_i(x,B(k,j)) == k
        //----------------------------------------------------------------------

            // 10 semirings: (min,max,times,plus,any) * (int32,int64)
            // FIRSTJ and SECONDI are identical when used in a semiring
            #define GB_MNAME _firstj
            #include "GB_AxB_positional_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_FIRSTJ1_opcode  :   // z = first_j1(A(i,k),y) == k+1
        case GB_SECONDI1_opcode :   // z = second_i1(x,B(k,j)) == k+1
        //----------------------------------------------------------------------

            // 10 semirings: (min,max,times,plus,any) * (int32,int64)
            // FIRSTJ1 and SECONDI1 are identical when used in a semiring
            #define GB_MNAME _firstj1
            #include "GB_AxB_positional_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_SECONDJ_opcode  :   // z = second_j(x,B(i,j)) == j
        //----------------------------------------------------------------------

            // 10 semirings: (min,max,times,plus,any) * (int32,int64)
            #define GB_MNAME _secondj
            #include "GB_AxB_positional_factory.c"
            break ;

        //----------------------------------------------------------------------
        case GB_SECONDJ1_opcode :   // z = second_j1(x,B(i,j)) == j+1
        //----------------------------------------------------------------------

            // 10 semirings: (min,max,times,plus,any) * (int32,int64)
            #define GB_MNAME _secondj1
            #include "GB_AxB_positional_factory.c"
            break ;

        default: ;
    }
}

