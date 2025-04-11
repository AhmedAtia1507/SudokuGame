#include "SudokuWindow.h"
#include "NewGameDialog.h"
#include "SaveGameDialog.h"
#include "LoadGameDialog.h"
#include "../../SudokuGame/include/FileManager.hpp"

#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>


SudokuWindow::SudokuWindow(QWidget *parent)
    : QMainWindow(parent)
    , board(new SudokuBoard())
{
    /****************************************** File Menu Actions ******************************************/
    QAction* newGameAction = new QAction("New Game", this);
    QAction* saveGameAction = new QAction("Save Game", this);
    QAction* loadGameAction = new QAction("Load Game", this);
    QAction* deleteGameAction = new QAction("Delete Saved Game", this);

    saveGameAction -> setDisabled(true);
    QMenu* gameMenu = menuBar() -> addMenu("Game");
    gameMenu -> addAction (newGameAction);
    gameMenu -> addAction (saveGameAction);
    gameMenu -> addAction (loadGameAction);
    gameMenu -> addAction (deleteGameAction);

    /************************** Central Widget *****************************/
    QWidget* centralWidget = new QWidget(this);

    /****************************************** Initial Labels *****************************************/
    QLabel* WelcomeLabel = new QLabel("WELCOME TO SUDOKU!!!", centralWidget);
    WelcomeLabel -> setStyleSheet("font-size: 25px; color: green; font-weight: bold; font-family: 'Consolas'");
    WelcomeLabel ->setAlignment(Qt::AlignCenter);

    QLabel* JokeLabel = new QLabel("Sudoku. Because who needs a social life when you have numbers?", centralWidget);
    JokeLabel -> setStyleSheet("font-size: 18px; color: green; font-weight: bold; font-family: 'Consolas'");
    JokeLabel ->setAlignment(Qt::AlignCenter);

    QLabel* IntroductionLabel = new QLabel("My name is Ahmed Atia Said, and I will be your host today.", centralWidget);
    IntroductionLabel -> setStyleSheet("font-size: 18px; color: green; font-weight: bold; font-family: 'Consolas'");
    IntroductionLabel ->setAlignment(Qt::AlignCenter);


    /****************************************** Auto Solve Button *****************************************/
    autoSolveButton = new QPushButton("Solve Puzzle", centralWidget);
    autoSolveButton -> setDisabled(true);

    /****************************************** Valid Move Label *****************************************/
    validMoveLabel = new QLabel(centralWidget);
    validMoveLabel ->setStyleSheet("font-size: 16px; font-weight: bold; font-family: 'Consolas'");


    /****************************************** Sudoku Board *****************************************/
    QWidget* SudokuWidget = new QWidget(centralWidget);
    QGridLayout* SudokuLayout = new QGridLayout(SudokuWidget);
    QGridLayout* SudokuBoxLayout[3][3];
    for(int row = 0; row < 3; row++) {
        for(int column = 0; column < 3; column++) {
            SudokuBoxLayout[row][column] = new QGridLayout();
        }
    }
    for(int row = 0; row < 9; row++) {
        for(int column = 0; column < 9; column++) {
            SudokuCells[row][column] = new QLineEdit(SudokuWidget);
            SudokuCells[row][column] -> setMaximumWidth(40);
            SudokuCells[row][column] -> setMaxLength(1);
            SudokuCells[row][column] -> setAlignment(Qt::AlignCenter);
            SudokuCells[row][column] -> setReadOnly(true);

            connect(SudokuCells[row][column], &QLineEdit::textEdited, [=]() {
                if(board -> setMove(row, column, SudokuCells[row][column] -> text().toInt())) {
                    validMoveLabel -> setText("Valid Move!!");
                    validMoveLabel ->setStyleSheet("font-size: 16px; font-weight: bold; font-family: 'Consolas'; color: green;");
                }
                else {
                    SudokuCells[row][column] -> clear();
                    validMoveLabel -> setText("Invalid Move!!");
                    validMoveLabel -> setStyleSheet("font-size: 16px; font-weight: bold; font-family: 'Consolas'; color: red");
                }

                if(board -> isSolved()) {
                    QMessageBox::information(this, "Congratulations!!", "Congratulations! You've conquered the Sudoku challenge! Your Sudoku skills are truly impressive!");
                    autoSolveButton -> setDisabled(true);
                    validMoveLabel -> clear();
                    saveGameAction -> setDisabled(true);
                    for(int i = 0; i < 9; i++) {
                        for(int j = 0; j < 9; j++) {
                            SudokuCells[i][j] -> setReadOnly(true);
                        }
                    }
                }
            });

            SudokuBoxLayout[(row / 3)][(column / 3)] -> addWidget(SudokuCells[row][column], (row % 3), (column % 3), Qt::AlignCenter);
        }
    }
    for(int row = 0; row < 3; row++) {
        for(int column = 0; column < 3; column++) {
            QWidget* SudokuBox = new QWidget(SudokuWidget);
            SudokuBox -> setLayout(SudokuBoxLayout[row][column]);
            SudokuBox -> setStyleSheet("border: 1px solid gray");
            SudokuLayout -> addWidget(SudokuBox, row, column, Qt::AlignCenter);
        }
    }
    SudokuWidget->setLayout(SudokuLayout);

    /************************** Central Widget Layout **********************/
    QGridLayout* centralWidgetLayout = new QGridLayout(centralWidget);
    centralWidgetLayout -> addWidget(WelcomeLabel, 0, 0, 1, 2, Qt::AlignCenter);
    centralWidgetLayout -> addWidget(JokeLabel, 1, 0, 1, 2, Qt::AlignCenter);
    centralWidgetLayout -> addWidget(IntroductionLabel, 2, 0, 1, 2, Qt::AlignCenter);
    centralWidgetLayout -> addWidget(SudokuWidget, 3, 0, 2, 1, Qt::AlignCenter);
    centralWidgetLayout -> addWidget(autoSolveButton, 3, 1, Qt::AlignCenter);
    centralWidgetLayout -> addWidget(validMoveLabel, 4, 1, Qt::AlignCenter);
    centralWidget -> setLayout(centralWidgetLayout);
    setCentralWidget(centralWidget);


    connect(autoSolveButton, &QPushButton::clicked, [=](){
        if(board -> autoSolve()) {
            std::vector<std::vector<char>> boardCells = board -> getBoard();
            for(int row = 0; row < 9; row++) {
                for(int column = 0; column < 9; column++) {
                    SudokuCells[row][column] -> setReadOnly(true);
                    SudokuCells[row][column] -> setText(QString(boardCells[row][column]));
                }
            }
            QMessageBox::information(this, "Success", "Successfully Solved");
            autoSolveButton -> setDisabled(true);
            validMoveLabel -> clear();
            saveGameAction -> setDisabled(true);
        }
        else {
            QMessageBox::warning(this, "Warning", "Cannot Be Solved");
        }
    });

    connect(newGameAction, &QAction::triggered, [=]() {
        NewGameDialog gameDialog(this);
        if(gameDialog.exec() == QDialog::Accepted) {
            switch(gameDialog.getSelectedDifficulty()) {
                case NewGameDialog::DialogResults::EASY: {
                    board -> generateNewBoard(SudokuGenerator::Difficulty::EASY);
                    break;
                }
                case NewGameDialog::DialogResults::MEDIUM: {
                    board -> generateNewBoard(SudokuGenerator::Difficulty::MEDIUM);
                    break;
                }
                case NewGameDialog::DialogResults::HARD: {
                    board -> generateNewBoard(SudokuGenerator::Difficulty::HARD);
                    break;
                }
                case NewGameDialog::DialogResults::EXPERT: {
                    board -> generateNewBoard(SudokuGenerator::Difficulty::EXPERT);
                    break;
                }
            }
            setInitBoard();
            saveGameAction -> setDisabled(false);
        }
    });

    connect(loadGameAction, &QAction::triggered, [=]() {
        std::vector<std::string> fileNames = FileManager::getSavedGames();
        if(fileNames.size() == 0) {
            QMessageBox::information(this, "No Saved Games", "No Saved Games Found");
        }
        else {
            LoadGameDialog loadDialog(fileNames, this);
            if(loadDialog.exec() == QDialog::Accepted) {
                try {
                    board -> loadBoard(loadDialog.getSelectedFileName().toStdString());
                    setInitBoard();
                    saveGameAction -> setDisabled(false);
                }
                catch(const std::runtime_error& e) {
                    QMessageBox::critical(this, "Runtime Error", e.what());
                }
                catch(const std::invalid_argument& e) {
                    QMessageBox::critical(this, "Invalid File", e.what());
                }
            }
        }
    });

    connect(saveGameAction, &QAction::triggered, [=]() {
        SaveGameDialog saveDialog(this);
        if(saveDialog.exec() == QDialog::Accepted) {
            board -> saveBoard(saveDialog.getSaveGameName().toStdString());
            QMessageBox::information(this, "Success", "Successfully Saved");
        }
    });

    connect(deleteGameAction, &QAction::triggered, [=]() {
        std::vector<std::string> fileNames = FileManager::getSavedGames();
        if(fileNames.size() == 0) {
            QMessageBox::information(this, "No Saved Games", "No Saved Games Found");
        }
        else {
            LoadGameDialog deleteDialog(fileNames, this);
            if(deleteDialog.exec() == QDialog::Accepted) {
                board -> deleteBoard(deleteDialog.getSelectedFileName().toStdString());
                QMessageBox::information(this, "Success", "Successfully Deleted");
            }
        }
    });
}

void SudokuWindow::setInitBoard() {
    std::vector<std::vector<char>> boardCells = board -> getBoard();
    for(int row = 0; row < 9; row++) {
        for(int column = 0; column < 9; column++) {
            if(boardCells[row][column] == '.') {
                SudokuCells[row][column] -> clear();
                SudokuCells[row][column] -> setReadOnly(false);
                SudokuCells[row][column] -> setStyleSheet("background-color: black; color: white;");
            }
            else {
                SudokuCells[row][column] -> setText(QString(boardCells[row][column]));
                SudokuCells[row][column] -> setReadOnly(true);
                SudokuCells[row][column] -> setStyleSheet("background-color: green; color: black;");
            }
        }
    }
    QMessageBox::information(this, "Success", "Successfully Created");
    autoSolveButton -> setDisabled(false);
}
SudokuWindow::~SudokuWindow()
{
    delete board;
}
