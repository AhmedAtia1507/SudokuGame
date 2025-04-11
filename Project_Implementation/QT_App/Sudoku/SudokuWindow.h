#ifndef SUDOKU_WINDOW_H
#define SUDOKU_WINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "../../SudokuGame/include/SudokuBoard.hpp"


class SudokuWindow : public QMainWindow
{
    Q_OBJECT

public:
    SudokuWindow(QWidget *parent = nullptr);
    ~SudokuWindow();

private:
    SudokuBoard* board;
    QLineEdit* SudokuCells[9][9];
    QLabel* validMoveLabel;
    QPushButton* autoSolveButton;
    void setInitBoard();
};
#endif // SUDOKU_WINDOW_H
