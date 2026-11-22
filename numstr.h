/**
 * @file numstr.h
 * @brief Описание структуры NumStr для хранения входных чисел.
 */

#ifndef NUMSTR_H
#define NUMSTR_H

#include <stdint.h>

/**
 * @struct NumStr
 * @brief Структура с битовыми полями минимального размера для чисел A, B, C, D.
 */
struct __attribute__((gcc_struct, packed)) NumStr
{
    /** @brief Число A (от 0 до 256, 9 бит). */
    uint16_t A : 9;

    /** @brief Число B (от 0 до 1, 1 бит). */
    uint8_t B : 1;

    /** @brief Число C (от -3 до 60, 7 бит). */
    int8_t C : 7;

    /** @brief Число D (от 10 до 12345678, 24 бита). */
    uint32_t D : 24;
};

// Проверка, что структура занимает ровно 6 байт (41 бит с округлением вверх до байта)
static_assert(sizeof(NumStr) == 6, "Размер структуры NumStr должен быть 6 байт");

#endif // NUMSTR_H