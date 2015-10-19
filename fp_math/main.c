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


