
#include "s21_tetris.h"

// Mock functions for getch
int mock_getch_value;
int getch() {
    return mock_getch_value;
}

// Setup function to initialize game status
void setup(GameInfo_t *status) {
    status->high_score = 0;
    status->score = 0;
    status->level = 0;
    status->speed = 0;
    status->action = Start;
    status->field = allocate_field(FIELD_WIDTH, FIELD_LENGTH);
    status->current_figure = allocate_figure();
    status->next = allocate_figure();
}

// Teardown function to clean up
void teardown(GameInfo_t *status) {
    free_fields(status->field, FIELD_LENGTH);
    free_figure(status->current_figure);
    free_figure(status->next);
}

START_TEST(test_high_score) {
    GameInfo_t status;
    setup(&status);

    // Simulate a high score and save it
    status.high_score = 5000;
    save_high_score(status.high_score);

    // Check if the high score is correctly saved
    get_Current_high_score(&status);
    ck_assert_int_eq(status.high_score, 5000);

    teardown(&status);
}
END_TEST

START_TEST(test_updateCurrentState) {
    GameInfo_t status;
    setup(&status);

    // Simulate key press 'q' for Terminate
    mock_getch_value = 'q';
    updateCurrentState(&status);
    ck_assert_int_eq(status.action, Terminate);

    // Simulate key press KEY_LEFT for Left
    mock_getch_value = KEY_LEFT;
    updateCurrentState(&status);
    ck_assert_int_eq(status.action, Left);

    teardown(&status);
}
END_TEST

START_TEST(test_moveFigureLeft) {
    GameInfo_t status;
    setup(&status);

    // Initialize a simple figure at the middle of the field
    status.figure_position_x = FIELD_WIDTH / 2;
    status.figure_position_y = 1;
    status.current_figure[1][1] = 1;

    // Move figure left
    moveFigureLeft(&status);
    ck_assert_int_eq(status.figure_position_x, (FIELD_WIDTH / 2) - 1);

    teardown(&status);
}
END_TEST

START_TEST(test_moveFigureRight) {
    GameInfo_t status;
    setup(&status);

    // Initialize a simple figure at the middle of the field
    status.figure_position_x = FIELD_WIDTH / 2;
    status.figure_position_y = 1;
    status.current_figure[1][1] = 1;

    // Move figure right
    moveFigureRight(&status);
    ck_assert_int_eq(status.figure_position_x, (FIELD_WIDTH / 2) + 1);

    teardown(&status);
}
END_TEST

START_TEST(test_rotateFigureClockwise) {
    GameInfo_t status;
    setup(&status);

    // Initialize a simple figure
    status.figure_position_x = FIELD_WIDTH / 2;
    status.figure_position_y = 1;
    status.current_figure[0][1] = 1;
    status.current_figure[1][1] = 1;
    status.current_figure[2][1] = 1;

    // Rotate figure
    rotateFigureClockwise(&status);
    ck_assert_int_eq(status.current_figure[1][0], 1);
    ck_assert_int_eq(status.current_figure[1][1], 1);
    ck_assert_int_eq(status.current_figure[1][2], 1);

    teardown(&status);
}
END_TEST

Suite *tetris_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Tetris");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_high_score);
    tcase_add_test(tc_core, test_updateCurrentState);
    tcase_add_test(tc_core, test_moveFigureLeft);
    tcase_add_test(tc_core, test_moveFigureRight);
    tcase_add_test(tc_core, test_rotateFigureClockwise);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = tetris_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
