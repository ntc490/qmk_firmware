/*
Copyright 2018 Nathan Crapo <nathan_crapo@yahoo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "led.h"
#include "config.h"
#include "keyboard.ioh"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;
static uint8_t matrix_row[MATRIX_ROWS];
static uint8_t matrix_row_debounce[MATRIX_ROWS];

static uint8_t read_row(uint8_t row);
static void select_row(uint8_t row);

void matrix_scan_kb(void) {
    matrix_scan_user();
}

void matrix_init(void)
{
    ports_init();

    /* debug_enable = true; */
    /* dprint("matrix_init"); dprintln(); */

    // initialize matrix state: all keys off
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row[row] = 0;
        matrix_row_debounce[row] = 0;
    }

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        uint8_t column_bits = read_row(row);
        if (matrix_row_debounce[row] != column_bits) {
            matrix_row_debounce[row] = column_bits;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                matrix_row[row] = matrix_row_debounce[row];
            }
        }
    }
    matrix_scan_quantum();
    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix_row[row] & (1 << col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix_row[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        count += bitpop16(matrix_row[row]);
    }
    return count;
}

static matrix_row_t read_row(uint8_t row)
{
    if (row == 12) {
        /* TODO: Read special function keys */
        return 0;
    }
    select_row(row);
    _delay_us(30);  // without this wait read unstable value.

    return ~bitrev(columns_read());
}

static void select_row(uint8_t row)
{
    if (row & 1) row_sel0_on(); else row_sel0_off();
    if (row & 2) row_sel1_on(); else row_sel1_off();
    if (row & 4) row_sel2_on(); else row_sel2_off();
    if (row & 8) row_sel3_on(); else row_sel3_off();
}
