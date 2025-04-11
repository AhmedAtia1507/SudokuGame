#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QRadioButton>
#include <QPushButton>

class NewGameDialog : public QDialog
{
    Q_OBJECT
private:
    QRadioButton* EasyLevel;
    QRadioButton* MediumLevel;
    QRadioButton* HardLevel;
    QRadioButton* ExpertLevel;
    QPushButton* OkButton;
public:
    enum DialogResults {
        EASY,
        MEDIUM,
        HARD,
        EXPERT
    };
    explicit NewGameDialog(QWidget* parent = nullptr);
    DialogResults getSelectedDifficulty() const;
};

#endif // NEWGAMEDIALOG_H
