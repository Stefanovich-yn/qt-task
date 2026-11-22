/**
 * @file mainwindow.h
 * @brief Описание класса главного окна MainWindow.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Главное окно программы с полями ввода A, B, C, D и кнопкой «Выполнить».
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
    /** @brief Указатель на интерфейс формы. */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H