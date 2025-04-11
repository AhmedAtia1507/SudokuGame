#include "SaveGameDialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

SaveGameDialog::SaveGameDialog(QWidget* parent) : QDialog(parent) {
    saveGameLineEdit = new QLineEdit(this);
    saveGameLineEdit -> setPlaceholderText("ex. 'game.txt'");

    QVBoxLayout* saveLayout = new QVBoxLayout(this);

    QLabel* saveLabel = new QLabel("Enter the file name to save the game to: ", this);
    saveLayout ->addWidget(saveLabel);
    saveLayout ->addWidget(saveGameLineEdit);

    QPushButton* OkButton = new QPushButton("OK", this);
    saveLayout -> addWidget(OkButton);
    connect(OkButton, &QPushButton::clicked, this, &QDialog::accept);
    setLayout(saveLayout);
}

QString SaveGameDialog::getSaveGameName() const {
    return saveGameLineEdit -> text();
}
