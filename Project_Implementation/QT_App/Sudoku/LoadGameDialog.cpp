#include "LoadGameDialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

LoadGameDialog::LoadGameDialog(std::vector<std::string>& fileNames, QWidget* parent) : QDialog(parent) {
    QVBoxLayout* loadLayout = new QVBoxLayout();
    QLabel* loadTitle = new QLabel("Please Select the file containing the game:", this);

    loadGameSelectBox = new QComboBox(this);
    for(int index = 0; index < fileNames.size(); index++) {
        loadGameSelectBox -> addItem(QString(fileNames[index].c_str()));
    }

    QPushButton* OkButton = new QPushButton("OK", this);
    connect(OkButton, &QPushButton::clicked, this, &QDialog::accept);

    loadLayout -> addWidget(loadTitle);
    loadLayout -> addWidget(loadGameSelectBox);
    loadLayout -> addWidget(OkButton);
    setLayout(loadLayout);
}

QString LoadGameDialog::getSelectedFileName() const {
    return loadGameSelectBox -> currentText();
}
