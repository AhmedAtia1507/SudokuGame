#ifndef SAVEGAMEDIALOG_H
#define SAVEGAMEDIALOG_H

#include <QDialog>
#include <QLineEdit>

class SaveGameDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit* saveGameLineEdit;
public:
    explicit SaveGameDialog(QWidget* parent = nullptr);
    QString getSaveGameName() const;
};

#endif // SAVEGAMEDIALOG_H
