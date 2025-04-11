#include "NewGameDialog.h"
#include <QVBoxLayout>
#include <QGroupBox>

NewGameDialog::NewGameDialog(QWidget* parent) : QDialog(parent) {
    EasyLevel = new QRadioButton("Easy", this);
    MediumLevel = new QRadioButton("Medium", this);
    HardLevel = new QRadioButton("Hard", this);
    ExpertLevel = new QRadioButton("Expert", this);

    EasyLevel -> setChecked(true);

    QVBoxLayout* DialogLayout = new QVBoxLayout(this);
    QGroupBox* buttonBox = new QGroupBox("Select Difficulty:");
    QVBoxLayout* buttonLayout = new QVBoxLayout();
    buttonLayout -> addWidget(EasyLevel);
    buttonLayout -> addWidget(MediumLevel);
    buttonLayout -> addWidget(HardLevel);
    buttonLayout -> addWidget(ExpertLevel);
    buttonBox -> setLayout(buttonLayout);

    DialogLayout -> addWidget(buttonBox);

    OkButton = new QPushButton("OK", this);
    connect(OkButton, &QPushButton::clicked, this, &QDialog::accept);
    DialogLayout -> addWidget(OkButton);

    setWindowTitle("New Game");
    setMinimumWidth(200);
}

NewGameDialog::DialogResults NewGameDialog::getSelectedDifficulty() const {
    if(EasyLevel ->isChecked()) return NewGameDialog::DialogResults::EASY;
    else if(MediumLevel ->isChecked()) return NewGameDialog::DialogResults::MEDIUM;
    else if(HardLevel -> isChecked()) return NewGameDialog::DialogResults::HARD;
    else if(ExpertLevel -> isChecked()) return NewGameDialog::DialogResults::EXPERT;
    else return NewGameDialog::DialogResults::MEDIUM;
}
