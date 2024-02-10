#ifndef TEST_H
#define TEST_H

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
    FAILED,
    PASSED
} TestResult;

void run_test(TestResult (*test_function)(), const char *test_name);
void print_result(TestResult result);

#endif // TEST_H
