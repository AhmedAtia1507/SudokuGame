#ifndef LOADGAMEDIALOG_H
#define LOADGAMEDIALOG_H

#include <QDialog>
#include <QComboBox>

class LoadGameDialog: public QDialog
{
    Q_OBJECT
private:
    QComboBox* loadGameSelectBox;
public:
    explicit LoadGameDialog(std::vector<std::string>& fileNames, QWidget* parent = nullptr);
    QString getSelectedFileName() const;
};

#endif // LOADGAMEDIALOG_H
