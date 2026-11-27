/**
 * @file mainwindow.h
 * @brief Описание класса главного окна MainWindow.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>
#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Главное окно приложения с полями ввода A, B, C, D, проверкой ввода и кнопкой «Выполнить».
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор главного окна.
     * @param parent Родительский виджет.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор главного окна.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Обработчик нажатия на кнопку «Выполнить».
     */
    void onRunClicked();

private:
    /**
     * @brief Настраивает валидаторы, значения по умолчанию и всплывающие подсказки для полей ввода.
     */
    void setupInputFields();

    /**
     * @brief Проверяет и преобразует строку в целое число в заданном диапазоне.
     * @param text Текст из поля ввода.
     * @param minVal Минимально допустимое значение.
     * @param maxVal Максимально допустимое значение.
     * @param outValue Ссылка для записи корректного числа.
     * @return 1 если число корректно и входит в диапазон, 0 при ошибке.
     */
    uint8_t tryParseInRange(const QString &text, int32_t minVal, int32_t maxVal, int32_t &outValue);

    /** @brief Указатель на интерфейс формы. */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H