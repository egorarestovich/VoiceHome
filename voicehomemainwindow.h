#ifndef VOICEHOMEMAINWINDOW_H
#define VOICEHOMEMAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDir>
#include "renameusercommanddialog.h"

namespace Ui {
class VoiceHomeMainWindow;
}

class VoiceHomeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VoiceHomeMainWindow(QWidget *parent = nullptr);
    ~VoiceHomeMainWindow();

private slots:

    void on_CommandsButton_clicked();

    void on_HomeButton_clicked();

    void on_CheckBoxSvet_stateChanged(int arg1);

    void on_CheckBoxFan_stateChanged(int arg1);

    void on_CheckBoxChainik_stateChanged(int arg1);

    void on_CheckBoxUserCommand_stateChanged(int arg1);

    void on_UserCommandButton_clicked();

public slots:
    void voicehomeprep();

    void writebluetooth(int command);

    void WriteOnUserButton(QString text);
private:
    Ui::VoiceHomeMainWindow *ui;
};

#endif // VOICEHOMEMAINWINDOW_H
