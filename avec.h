/*
 * Copyright (c) 2026 almrk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __AVEC_H
#define __AVEC_H

#include <math.h>

/* avec2 */
#define __AVEC2_NEW_VARIANT(T, S) \
    typedef struct { \
        T x; \
        T y; \
    } avec2##S;
#define __AVEC2_ARITH_OP(T, S, N, O) \
    static avec2##S avec2##S##_##N(avec2##S v0, avec2##S v1) { \
        return (avec2##S){v0.x O v1.x, v0.y O v1.y}; \
    }
#define __AVEC2_SCALAR_ARITH_OP(T, S, N, O) \
    static avec2##S avec2##S##_##N##_scalar(avec2##S v, T s) { \
        return (avec2##S){v.x O s, v.y O s}; \
    }
#define __AVEC2_NEG_OP(T, S) \
    static avec2##S avec2##S##_neg(avec2##S v) { \
        return (avec2##S){-v.x, -v.y}; \
    }
#define __AVEC2_DOT_OP(T, S) \
    static T avec2##S##_dot(avec2##S v0, avec2##S v1) { \
        return v0.x * v1.x + v0.y * v1.y; \
    }
#define __AVEC2_LEN_OP(T, S) \
    static T avec2##S##_len(avec2##S v) { \
        return sqrt(v.x * v.x + v.y * v.y); \
    }
#define __AVEC2_NORM_OP(T, S) \
    static avec2##S##_norm(avec2##S v) { \
        float l = sqrt(v.x * v.x + v.y * v.y); \
        if (l < 1e-6f) \
            return (avec2##S){0}; \
        return (avec2##S){v.x / l, v.y / l}; \
    }

/* avec3 */
#define __AVEC3_NEW_VARIANT(T, S) \
    typedef struct { \
        T x; \
        T y; \
        T z; \
    } avec3##S;
#define __AVEC3_ARITH_OP(T, S, N, O) \
    static avec3##S avec3##S##_##N(avec3##S v0, avec3##S v1) { \
        return (avec3##S){v0.x O v1.x, v0.y O v1.y, v0.z O v1.z}; \
    }
#define __AVEC3_SCALAR_ARITH_OP(T, S, N, O) \
    static avec3##S avec3##S##_##N##_scalar(avec3##S v, T s) { \
        return (avec3##S){v.x O s, v.y O s, v.z O s}; \
    }
#define __AVEC3_NEG_OP(T, S) \
    static avec3##S avec3##S##_neg(avec3##S v) { \
        return (avec3##S){-v.x, -v.y, -v.z}; \
    }
#define __AVEC3_CROSS_OP(T, S) \
    static avec3##S avec3##S##_cross(avec3##S v0, avec3##S v1) { \
        return (avec3##S){ \
            v0.y * v1.z - v0.z * v1.y, \
            v0.z * v1.x - v0.x * v1.z, \
            v0.z * v1.y - v0.y * v1.x \
        }; \
    }
#define __AVEC3_DOT_OP(T, S) \
    static T avec3##S##_dot(avec3##S v0, avec3##S v1) { \
        return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z; \
    }
#define __AVEC3_LEN_OP(T, S) \
    static T avec3##S##_len(avec3##S v) { \
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); \
    }
#define __AVEC3_NORM_OP(T, S) \
    static avec3##S avec3##S##_norm(avec3##S v) { \
        float l = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); \
        if (l < 1e-6f) \
            return (avec3##S){0}; \
        return (avec3##S){v.x / l, v.y / l, v.z / l}; \
    }

/* avec2 variants and functions */
__AVEC2_NEW_VARIANT(int, i)
__AVEC2_ARITH_OP(int, i, add, +)
__AVEC2_ARITH_OP(int, i, sub, -)
__AVEC2_ARITH_OP(int, i, mul, *)
__AVEC2_ARITH_OP(int, i, div, /)
__AVEC2_SCALAR_ARITH_OP(int, i, mul, *)
__AVEC2_SCALAR_ARITH_OP(int, i, div, /)
__AVEC2_NEG_OP(int, i)
__AVEC2_DOT_OP(int, i)
__AVEC2_LEN_OP(int, i)
__AVEC2_NORM_OP(int, i)

__AVEC2_NEW_VARIANT(unsigned, u)
__AVEC2_ARITH_OP(unsigned, u, add, +)
__AVEC2_ARITH_OP(unsigned, u, sub, -)
__AVEC2_ARITH_OP(unsigned, u, mul, *)
__AVEC2_ARITH_OP(unsigned, u, div, /)
__AVEC2_SCALAR_ARITH_OP(unsigned, u, mul, *)
__AVEC2_SCALAR_ARITH_OP(unsigned, u, div, /)
__AVEC2_NEG_OP(unsigned, u)
__AVEC2_DOT_OP(unsigned, u)
__AVEC2_LEN_OP(unsigned, u)
__AVEC2_NORM_OP(unsigned, u)

__AVEC2_NEW_VARIANT(float, f)
__AVEC2_ARITH_OP(float, f, add, +)
__AVEC2_ARITH_OP(float, f, sub, -)
__AVEC2_ARITH_OP(float, f, mul, *)
__AVEC2_ARITH_OP(float, f, div, /)
__AVEC2_SCALAR_ARITH_OP(float, f, mul, *)
__AVEC2_SCALAR_ARITH_OP(float, f, div, /)
__AVEC2_NEG_OP(float, f)
__AVEC2_DOT_OP(float, f)
__AVEC2_LEN_OP(float, f)
__AVEC2_NORM_OP(float, f)

__AVEC2_NEW_VARIANT(double, d)
__AVEC2_ARITH_OP(double, d, add, +)
__AVEC2_ARITH_OP(double, d, sub, -)
__AVEC2_ARITH_OP(double, d, mul, *)
__AVEC2_ARITH_OP(double, d, div, /)
__AVEC2_SCALAR_ARITH_OP(double, d, mul, *)
__AVEC2_SCALAR_ARITH_OP(double, d, div, /)
__AVEC2_NEG_OP(double, d)
__AVEC2_DOT_OP(double, d)
__AVEC2_LEN_OP(double, d)
__AVEC2_NORM_OP(double, d)

/* avec3 variants and functions */
__AVEC3_NEW_VARIANT(int, i)
__AVEC3_ARITH_OP(int, i, add, +)
__AVEC3_ARITH_OP(int, i, sub, -)
__AVEC3_ARITH_OP(int, i, mul, *)
__AVEC3_ARITH_OP(int, i, div, /)
__AVEC3_SCALAR_ARITH_OP(int, i, mul, *)
__AVEC3_SCALAR_ARITH_OP(int, i, div, /)
__AVEC3_NEG_OP(int, i)
__AVEC3_CROSS_OP(int, i)
__AVEC3_DOT_OP(int, i)
__AVEC3_LEN_OP(int, i)
__AVEC3_NORM_OP(int, i)

__AVEC3_NEW_VARIANT(unsigned, u)
__AVEC3_ARITH_OP(unsigned, u, add, +)
__AVEC3_ARITH_OP(unsigned, u, sub, -)
__AVEC3_ARITH_OP(unsigned, u, mul, *)
__AVEC3_ARITH_OP(unsigned, u, div, /)
__AVEC3_SCALAR_ARITH_OP(unsigned, u, mul, *)
__AVEC3_SCALAR_ARITH_OP(unsigned, u, div, /)
__AVEC3_NEG_OP(unsigned, u)
__AVEC3_CROSS_OP(unsigned, u)
__AVEC3_DOT_OP(unsigned, u)
__AVEC3_LEN_OP(unsigned, u)
__AVEC3_NORM_OP(unsigned, u)

__AVEC3_NEW_VARIANT(float, f)
__AVEC3_ARITH_OP(float, f, add, +)
__AVEC3_ARITH_OP(float, f, sub, -)
__AVEC3_ARITH_OP(float, f, mul, *)
__AVEC3_ARITH_OP(float, f, div, /)
__AVEC3_SCALAR_ARITH_OP(float, f, mul, *)
__AVEC3_SCALAR_ARITH_OP(float, f, div, /)
__AVEC3_NEG_OP(float, f)
__AVEC3_CROSS_OP(float, f)
__AVEC3_DOT_OP(float, f)
__AVEC3_LEN_OP(float, f)
__AVEC3_NORM_OP(float, f)

__AVEC3_NEW_VARIANT(double, d)
__AVEC3_ARITH_OP(double, d, add, +)
__AVEC3_ARITH_OP(double, d, sub, -)
__AVEC3_ARITH_OP(double, d, mul, *)
__AVEC3_ARITH_OP(double, d, div, /)
__AVEC3_SCALAR_ARITH_OP(double, d, mul, *)
__AVEC3_SCALAR_ARITH_OP(double, d, div, /)
__AVEC3_NEG_OP(double, d)
__AVEC3_CROSS_OP(double, d)
__AVEC3_DOT_OP(double, d)
__AVEC3_LEN_OP(double, d)
__AVEC3_NORM_OP(double, d)

#endif /* __AVEC_H */
