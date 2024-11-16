#ifndef RENAMEUSERCOMMANDDIALOG_H
#define RENAMEUSERCOMMANDDIALOG_H

#include <QDialog>

namespace Ui {
class RenameUserCommandDIalog;
}

class RenameUserCommandDIalog : public QDialog
{
    Q_OBJECT

public:
    explicit RenameUserCommandDIalog(QWidget *parent = nullptr);
    ~RenameUserCommandDIalog();

signals:
    void textChanged(const QString &text);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::RenameUserCommandDIalog *ui;
};

#endif // RENAMEUSERCOMMANDDIALOG_H
