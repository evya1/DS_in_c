#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"
#include "test.h"
#include "avl_tests.h"

int main(void)
{
    run_test(delete_test_two, "delete_test_two");
    run_test(delete_test_three, "delete_test_three");
    run_test(delete_third_test, "delete_third_test");
    run_test(delete_third_test2, "delete_third_test2");
    run_test(delete_third_test3, "delete_third_test3");

    return 0;
}
