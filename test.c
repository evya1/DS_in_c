#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "avl.h"

/**
 * Run a test function and measure its execution time.
 *
 * @param test_function The test function to be executed.
 *                      It should return a TestResult and take no parameters.
 * @param test_name     A string representing the name of the test.
 *                      Used for displaying results with the test name.
 *
 * @return              The result of the test (FAILED or PASSED).
 *
 * Example Usage:
 *
 *     // Define a test function with the signature: TestResult my_test_function();
 *     TestResult my_test_function() {
 *         // ... implementation of the test ...
 *     }
 *
 *     // In main or another testing function:
 *     run_test(my_test_function, "My Test Function");
 */
void run_test(TestResult (*test_function)(), const char *test_name)
{
    clock_t start, end;
    double cpu_time_used;

    // Record the starting time
    start = clock();

    // Run the test
    TestResult result = test_function();

    // Record the ending time
    end = clock();

    // Calculate the time taken in seconds
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Display the result and execution time
    printf("Test: %s\n", test_name);
    printf("Result: %s\n", (result == PASSED) ? "PASSED" : "FAILED");
    printf("Time taken: %f seconds\n", cpu_time_used);
    printf("\n");
}

void print_result(TestResult result)
{
    if (result == PASSED)
        printf("PASSED.\n");
    else
        printf("FAILED.\n");
}
