#pragma once
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class RenameUserCommandDIalog; }
QT_END_NAMESPACE

class RenameUserCommandDIalog : public QDialog {
    Q_OBJECT

public:
    explicit RenameUserCommandDIalog(QWidget *parent = nullptr);
    ~RenameUserCommandDIalog() override;

signals:
    void textChanged(const QString &text);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::RenameUserCommandDIalog *ui;
    void setupUIForHome();
    void setupUIForCommands();
};
