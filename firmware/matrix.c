#include <stdint.h>
#include <stdbool.h>
#include "gpio_api.h"
#include "timer.h"
#include "wait.h"
#include "matrix.h"


#ifndef DEBOUNCE
#define DEBOUNCE    5
#endif

/*
 * Switchblade Pinusage:
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PTB0, PTB1, PTB2, PTB3, PTB7, PTD0, PTD1, PTD2,
 *       PTF0, PTF1, PTF4, PTF5, PTF6, PTF7, PTB6, PTB5, PTB4, PTD7
 *     row: { PTD3, PTC6, PTC7, PTD6, PTD4 }
 */
static gpio_t col[MATRIX_COLS];
static gpio_t row[MATRIX_ROWS];

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;


void matrix_init(void)
{
    /* Column(sense) */
    gpio_init_in_ex(&col[0],  Pb0, PullDown);
    gpio_init_in_ex(&col[1],  Pb1, PullDown);
    gpio_init_in_ex(&col[2],  Pb2, PullDown);
    gpio_init_in_ex(&col[3],  Pb3, PullDown);
    gpio_init_in_ex(&col[4],  Pb7, PullDown);
    gpio_init_in_ex(&col[5],  Pd0, PullDown);
    gpio_init_in_ex(&col[6],  Pd1, PullDown);
    gpio_init_in_ex(&col[7],  Pd2, PullDown);
    gpio_init_in_ex(&col[8],  Pf0, PullDown);
    gpio_init_in_ex(&col[9],  Pf1, PullDown);
    gpio_init_in_ex(&col[10], Pf4, PullDown);
    gpio_init_in_ex(&col[11], Pf5, PullDown);
    gpio_init_in_ex(&col[12], Pf6, PullDown);
    gpio_init_in_ex(&col[13], Pf7, PullDown);
    gpio_init_in_ex(&col[14], Pb6, PullDown);
    gpio_init_in_ex(&col[15], Pb5, PullDown);
    gpio_init_in_ex(&col[16], Pb4, PullDown);
    gpio_init_in_ex(&col[17], Pd7, PullDown);

    /* Row(strobe) */
    gpio_init_out_ex(&row[0], PTD3, 0);
    gpio_init_out_ex(&row[1], PTC6, 0);
    gpio_init_out_ex(&row[2], PTC7, 0);
    gpio_init_out_ex(&row[3], PTD6, 0);
    gpio_init_out_ex(&row[4], PTD4, 0);
}

uint8_t matrix_scan(void)
{
    for (int i = 0; i < MATRIX_ROWS; i++) {
        matrix_row_t r = 0;

        gpio_write(&row[i], 1);
        wait_us(1); // need wait to settle pin state
        for (int j = 0; j < MATRIX_COLS; j++) {
            if (gpio_read(&col[j])) {
                r |= (1<<j);
            }
        }
        gpio_write(&row[i], 0);

        if (matrix_debouncing[i] != r) {
            matrix_debouncing[i] = r;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int i = 0; i < MATRIX_ROWS; i++) {
            matrix[i] = matrix_debouncing[i];
        }
        debouncing = false;
    }
/*
    if (debouncing) {
        if (--debouncing) {
            return 0;
        } else {
            for (int i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
*/
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
}
