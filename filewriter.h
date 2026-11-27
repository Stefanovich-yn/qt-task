/**
 * @file filewriter.h
 * @brief Описание класса FileWriter для сохранения данных в файл.
 */

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <stdint.h>
#include <string>
#include <vector>

/**
 * @class FileWriter
 * @brief Класс, отвечающий за запись результатов в текстовый файл.
 */
class FileWriter
{
public:
    /**
     * @brief Записывает набор битов (0 или 1) в файл, по одному значению на строку.
     * @param bits Вектор битов (значения 0 или 1).
     * @param filePath Путь к файлу для сохранения.
     * @return 1 при успешной записи, 0 при ошибке открытия или записи файла.
     */
    uint8_t saveBitsToFile(const std::vector<uint8_t> &bits, const std::string &filePath);
};

#endif // FILEWRITER_H