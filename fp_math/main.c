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
Fixed point library test frame
*/

#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

#include "fixed_point_inst.h"

#define UNITTEST

int tests_run = 0;

static char * test_float_to_Q()
{
    mu_assert("error in float_to_Q16_16(1) != 0x00010000", float_to_Q16_16(1) == 0x00010000);
    mu_assert("error in float_to_Q16_16(1.5) != 0x00018000", float_to_Q16_16(1.5) == 0x00018000);
    mu_assert("error in float_to_Q16_16(-1) == 0xFFFF0000", float_to_Q16_16(-1) == 0xFFFF0000);
    mu_assert("error in float_to_Q16_16(-1.5) == 0xFFFF8000", float_to_Q16_16(-1.5) == 0xFFFE8000);
    return 0;
}

static char * test_Q_to_int32()
{
    mu_assert("error in Q16_16_to_int32(0x00010000) == 1", Q16_16_to_int32(0x00010000) == 1);
    mu_assert("error in Q16_16_to_int32(0x00018000) == 1", Q16_16_to_int32(0x00018000) == 1);
    mu_assert("error in Q16_16_to_int32(0xFFFF0000) == -1", Q16_16_to_int32(0xFFFF0000) == -1);
    mu_assert("error in Q16_16_to_int32(0xFFFF8000) == -1", Q16_16_to_int32(0xFFFF8000) == -1);
    mu_assert("error in Q16_16_to_int32(0xFFFFFFFF) == -1", Q16_16_to_int32(0xFFFFFFFF) == -1);
    mu_assert("error in Q16_16_to_int32(0xFFFEFFFF) == -2", Q16_16_to_int32(0xFFFEFFFF) == -2);
    return 0;
}

static char * test_Q_add()
{
    mu_assert("error in Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(1))) == 2",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(1))) == 2);
    mu_assert("Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(1))) == 0",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(1))) == 0);
    mu_assert("Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(-1))) == 0",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(-1))) == 0);
    mu_assert("Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(-1))) == 0",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(-1))) == 0);
    mu_assert("Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.5), float_to_Q16_16(0.5))) == 1",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.5), float_to_Q16_16(0.5))) == 1);
    mu_assert("Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.5), float_to_Q16_16(1.5))) == 2",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.5), float_to_Q16_16(1.5))) == 2);
    mu_assert("Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.5), float_to_Q16_16(-0.5))) == 0",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.5), float_to_Q16_16(-0.5))) == 0);
    mu_assert("Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.5), float_to_Q16_16(-1.5))) == -1",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.5), float_to_Q16_16(-1.5))) == -1);
    mu_assert("Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.4999999), float_to_Q16_16(-1.5))) == -2",
        Q16_16_to_int32(Q16_16_add_Q16_16_to_Q16_16(float_to_Q16_16(0.4999999), float_to_Q16_16(-1.5))) == -2);
    return 0;
}

static char * test_Q_sub()
{
    mu_assert("Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(1))) == 0",
        Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(1))) == 0);
    mu_assert("Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(-1))) == 2",
        Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(-1))) == 2);
    mu_assert("Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(1))) == -2",
        Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(1))) == -2);
    mu_assert("Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(-1))) == 0",
        Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(-1))) == 0);
    mu_assert("Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(-1.5))) == 0",
        Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(-1.5))) == 0);
    mu_assert("Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(1.5), float_to_Q16_16(-1))) == 2",
        Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(1.5), float_to_Q16_16(-1))) == 2);
    mu_assert("Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(0), float_to_Q16_16(-1))) == 1",
        Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(0), float_to_Q16_16(-1))) == 1);
    mu_assert("Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(0))) == -1",
        Q16_16_to_int32(Q16_16_sub_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(0))) == -1);

    return 0;
}

static char * test_Q_mul()
{
    mu_assert("Q16_16_to_int32(Q16_16_mul_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(1))) == 1",
        Q16_16_to_int32(Q16_16_mul_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(1))) == 1);
    mu_assert("Q16_16_to_int32(Q16_16_mul_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(1))) == -1",
        Q16_16_to_int32(Q16_16_mul_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(1))) == -1);
    mu_assert("Q16_16_to_int32(Q16_16_mul_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(-1))) == -1",
        Q16_16_to_int32(Q16_16_mul_Q16_16_to_Q16_16(float_to_Q16_16(1), float_to_Q16_16(-1))) == -1);
    mu_assert("Q16_16_to_int32(Q16_16_mul_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(-1))) == 1",
        Q16_16_to_int32(Q16_16_mul_Q16_16_to_Q16_16(float_to_Q16_16(-1), float_to_Q16_16(-1))) == 1);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_float_to_Q);
    mu_run_test(test_Q_to_int32);
    mu_run_test(test_Q_add);
    mu_run_test(test_Q_sub);
    mu_run_test(test_Q_mul);
    return 0;
}


#ifdef UNITTEST

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

#else

int main()
{
    Q16_16 a = float_to_Q16_16(0);
    Q16_16 b = float_to_Q16_16(-1);
    Q16_16 result = Q16_16_sub_Q16_16_to_Q16_16(a,b);
    printf("FP result %X, a %X, b %X\n", result, a, b);
    int32_t intresult = Q16_16_to_int32(result);
    printf("Result %d\n", intresult);

    return 0;
}

#endif // UNITTEST


