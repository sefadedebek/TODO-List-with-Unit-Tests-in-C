#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "todo.h"

static void test_addTask(void **state) {
    (void) state;  // Unused

    assert_int_equal(getTaskCount(), 0);
    addTask("Test Task 1");
    assert_string_equal(getTask(1)->task, "Test Task 1");
    assert_int_equal(getTask(1)->completed, 0);
    assert_int_equal(getTaskCount(), 1);
}

static void test_deleteTask(void **state) {
    (void) state;  // Unused

    addTask("Test Task 2");
    addTask("Test Task 3");
    assert_int_equal(getTaskCount(), 3);
    assert_int_equal(deleteTask(2), 0);
    assert_string_equal(getTask(2)->task, "Test Task 3");
    assert_int_equal(getTaskCount(), 2);
}

static void test_completeTask(void **state) {
    (void) state;  // Unused

    assert_int_equal(completeTask(2), 0);
    assert_int_equal(getTask(2)->completed, 1);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_addTask),
        cmocka_unit_test(test_deleteTask),
        cmocka_unit_test(test_completeTask),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
