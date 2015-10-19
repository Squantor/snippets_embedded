/*
The MIT License (MIT)

Copyright (c) 2015 Anton Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/*
Fixed point library macro instantiations
*/

#define FIXED_POINT_TEMPLATE_INT32(name, m, n)      \
                                                    \
/* constants */                                     \
const unsigned int name##_Shift = n;                \
const unsigned int name##_M = 0xFFFFFFFF << m;      \
const unsigned int name##_N = 0xFFFFFFFF >> n;      \
                                                    \
/* types */                                         \
typedef int32_t name;                               \
                                                    \
/* conversion functions */                          \
static inline name float_to_##name(float val)       \
{                                                   \
    return val * (1 << name##_Shift);               \
}                                                   \
                                                    \
static inline name int32_to_##name(int32_t val)     \
{                                                   \
    return val << name##_Shift;                     \
}                                                   \
                                                    \
static inline int32_t name##_to_int32(name val)     \
{                                                   \
    return val >> name##_Shift;                     \
}                                                   \


