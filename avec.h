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
#ifndef AVEC_H
#define AVEC_H

#include <math.h>

/* avec2 */
#define AVEC2_NEW_VARIANT(T, S) \
    typedef struct { \
        T x; \
        T y; \
    } avec2##S;
#define AVEC2_ARITH_OP(T, S, N, O) \
    static avec2##S avec2##S##_##N(avec2##S v0, avec2##S v1) { \
        return (avec2##S){v0.x O v1.x, v0.y O v1.y}; \
    }
#define AVEC2_SCALAR_ARITH_OP(T, S, N, O) \
    static avec2##S avec2##S##_##N##_scalar(avec2##S v, T s) { \
        return (avec2##S){v.x O s, v.y O s}; \
    }
#define AVEC2_NEG_OP(T, S) \
    static avec2##S avec2##S##_neg(avec2##S v) { \
        return (avec2##S){-v.x, -v.y}; \
    }
#define AVEC2_DOT_OP(T, S) \
    static T avec2##S##_dot(avec2##S v0, avec2##S v1) { \
        return v0.x * v1.x + v0.y * v1.y; \
    }
#define AVEC2_LEN_OP(T, S) \
    static T avec2##S##_len(avec2##S v) { \
        return sqrt(v.x * v.x + v.y * v.y); \
    }
#define AVEC2_NORM_OP(T, S) \
    static avec2##S avec2##S##_norm(avec2##S v) { \
        float l = sqrt(v.x * v.x + v.y * v.y); \
        if (l < 1e-6f) \
            return (avec2##S){0}; \
        return (avec2##S){v.x / l, v.y / l}; \
    }

/* avec3 */
#define AVEC3_NEW_VARIANT(T, S) \
    typedef struct { \
        T x; \
        T y; \
        T z; \
    } avec3##S;
#define AVEC3_ARITH_OP(T, S, N, O) \
    static avec3##S avec3##S##_##N(avec3##S v0, avec3##S v1) { \
        return (avec3##S){v0.x O v1.x, v0.y O v1.y, v0.z O v1.z}; \
    }
#define AVEC3_SCALAR_ARITH_OP(T, S, N, O) \
    static avec3##S avec3##S##_##N##_scalar(avec3##S v, T s) { \
        return (avec3##S){v.x O s, v.y O s, v.z O s}; \
    }
#define AVEC3_NEG_OP(T, S) \
    static avec3##S avec3##S##_neg(avec3##S v) { \
        return (avec3##S){-v.x, -v.y, -v.z}; \
    }
#define AVEC3_CROSS_OP(T, S) \
    static avec3##S avec3##S##_cross(avec3##S v0, avec3##S v1) { \
        return (avec3##S){ \
            v0.y * v1.z - v0.z * v1.y, \
            v0.z * v1.x - v0.x * v1.z, \
            v0.z * v1.y - v0.y * v1.x \
        }; \
    }
#define AVEC3_DOT_OP(T, S) \
    static T avec3##S##_dot(avec3##S v0, avec3##S v1) { \
        return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z; \
    }
#define AVEC3_LEN_OP(T, S) \
    static T avec3##S##_len(avec3##S v) { \
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); \
    }
#define AVEC3_NORM_OP(T, S) \
    static avec3##S avec3##S##_norm(avec3##S v) { \
        float l = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); \
        if (l < 1e-6f) \
            return (avec3##S){0}; \
        return (avec3##S){v.x / l, v.y / l, v.z / l}; \
    }

/* avec2 variants and functions */
AVEC2_NEW_VARIANT(int, i)
AVEC2_ARITH_OP(int, i, add, +)
AVEC2_ARITH_OP(int, i, sub, -)
AVEC2_ARITH_OP(int, i, mul, *)
AVEC2_ARITH_OP(int, i, div, /)
AVEC2_SCALAR_ARITH_OP(int, i, mul, *)
AVEC2_SCALAR_ARITH_OP(int, i, div, /)
AVEC2_NEG_OP(int, i)
AVEC2_DOT_OP(int, i)
AVEC2_LEN_OP(int, i)
AVEC2_NORM_OP(int, i)

AVEC2_NEW_VARIANT(unsigned, u)
AVEC2_ARITH_OP(unsigned, u, add, +)
AVEC2_ARITH_OP(unsigned, u, sub, -)
AVEC2_ARITH_OP(unsigned, u, mul, *)
AVEC2_ARITH_OP(unsigned, u, div, /)
AVEC2_SCALAR_ARITH_OP(unsigned, u, mul, *)
AVEC2_SCALAR_ARITH_OP(unsigned, u, div, /)
AVEC2_NEG_OP(unsigned, u)
AVEC2_DOT_OP(unsigned, u)
AVEC2_LEN_OP(unsigned, u)
AVEC2_NORM_OP(unsigned, u)

AVEC2_NEW_VARIANT(float, f)
AVEC2_ARITH_OP(float, f, add, +)
AVEC2_ARITH_OP(float, f, sub, -)
AVEC2_ARITH_OP(float, f, mul, *)
AVEC2_ARITH_OP(float, f, div, /)
AVEC2_SCALAR_ARITH_OP(float, f, mul, *)
AVEC2_SCALAR_ARITH_OP(float, f, div, /)
AVEC2_NEG_OP(float, f)
AVEC2_DOT_OP(float, f)
AVEC2_LEN_OP(float, f)
AVEC2_NORM_OP(float, f)

AVEC2_NEW_VARIANT(double, d)
AVEC2_ARITH_OP(double, d, add, +)
AVEC2_ARITH_OP(double, d, sub, -)
AVEC2_ARITH_OP(double, d, mul, *)
AVEC2_ARITH_OP(double, d, div, /)
AVEC2_SCALAR_ARITH_OP(double, d, mul, *)
AVEC2_SCALAR_ARITH_OP(double, d, div, /)
AVEC2_NEG_OP(double, d)
AVEC2_DOT_OP(double, d)
AVEC2_LEN_OP(double, d)
AVEC2_NORM_OP(double, d)

/* avec3 variants and functions */
AVEC3_NEW_VARIANT(int, i)
AVEC3_ARITH_OP(int, i, add, +)
AVEC3_ARITH_OP(int, i, sub, -)
AVEC3_ARITH_OP(int, i, mul, *)
AVEC3_ARITH_OP(int, i, div, /)
AVEC3_SCALAR_ARITH_OP(int, i, mul, *)
AVEC3_SCALAR_ARITH_OP(int, i, div, /)
AVEC3_NEG_OP(int, i)
AVEC3_CROSS_OP(int, i)
AVEC3_DOT_OP(int, i)
AVEC3_LEN_OP(int, i)
AVEC3_NORM_OP(int, i)

AVEC3_NEW_VARIANT(unsigned, u)
AVEC3_ARITH_OP(unsigned, u, add, +)
AVEC3_ARITH_OP(unsigned, u, sub, -)
AVEC3_ARITH_OP(unsigned, u, mul, *)
AVEC3_ARITH_OP(unsigned, u, div, /)
AVEC3_SCALAR_ARITH_OP(unsigned, u, mul, *)
AVEC3_SCALAR_ARITH_OP(unsigned, u, div, /)
AVEC3_NEG_OP(unsigned, u)
AVEC3_CROSS_OP(unsigned, u)
AVEC3_DOT_OP(unsigned, u)
AVEC3_LEN_OP(unsigned, u)
AVEC3_NORM_OP(unsigned, u)

AVEC3_NEW_VARIANT(float, f)
AVEC3_ARITH_OP(float, f, add, +)
AVEC3_ARITH_OP(float, f, sub, -)
AVEC3_ARITH_OP(float, f, mul, *)
AVEC3_ARITH_OP(float, f, div, /)
AVEC3_SCALAR_ARITH_OP(float, f, mul, *)
AVEC3_SCALAR_ARITH_OP(float, f, div, /)
AVEC3_NEG_OP(float, f)
AVEC3_CROSS_OP(float, f)
AVEC3_DOT_OP(float, f)
AVEC3_LEN_OP(float, f)
AVEC3_NORM_OP(float, f)

AVEC3_NEW_VARIANT(double, d)
AVEC3_ARITH_OP(double, d, add, +)
AVEC3_ARITH_OP(double, d, sub, -)
AVEC3_ARITH_OP(double, d, mul, *)
AVEC3_ARITH_OP(double, d, div, /)
AVEC3_SCALAR_ARITH_OP(double, d, mul, *)
AVEC3_SCALAR_ARITH_OP(double, d, div, /)
AVEC3_NEG_OP(double, d)
AVEC3_CROSS_OP(double, d)
AVEC3_DOT_OP(double, d)
AVEC3_LEN_OP(double, d)
AVEC3_NORM_OP(double, d)

#endif /* AVEC_H */
