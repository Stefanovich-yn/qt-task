/**
 * @file numstr.h
 * @brief Описание структуры NumStr для компактного хранения входных чисел.
 */

#ifndef NUMSTR_H
#define NUMSTR_H

#include <stdint.h>

/**
 * @struct NumStr
 * @brief Структура с битовыми полями минимального размера для чисел A, B, C, D (40 бит).
 */
struct __attribute__((gcc_struct, packed)) NumStr
{
    /** @brief Число A (от 0 до 256, 9 бит). */
    uint16_t A : 9;

    /** @brief Число B (от 0 до 1, 1 бит). */
    uint8_t B : 1;

    /** @brief Число C (от -3 до 60, 6 бит). */
    uint8_t C : 6;

    /** @brief Число D (от 10 до 12345678, 24 бита). */
    uint32_t D : 24;
};

static_assert(sizeof(NumStr) == 5, "Размер структуры NumStr должен составлять ровно 5 байт (40 бит)");

#endif // NUMSTR_H