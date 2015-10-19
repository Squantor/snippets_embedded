/*
Copyright (c) 2015 Anton Bilos
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
Fixed point library macro instantiations
*/

#include <stdint-gcc.h>
#include "fixed_point_template.h"

FIXED_POINT_TEMPLATE_INT32(Q16_16, 16, 16)

// maths
static inline Q16_16 Q16_16_add_Q16_16_to_Q16_16(Q16_16 a, Q16_16 b)
{
    return a + b;
}

// maths
static inline Q16_16 Q16_16_sub_Q16_16_to_Q16_16(Q16_16 a, Q16_16 b)
{
    return a - b;
}

// maths
static inline Q16_16 Q16_16_mul_Q16_16_to_Q16_16(Q16_16 a, Q16_16 b)
{
    int64_t product = (int64_t)a * b;
    return product >> Q16_16_Shift;
}
