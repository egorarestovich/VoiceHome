#ifndef VOICEHOMEMAINWINDOW_H
#define VOICEHOMEMAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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

    void on_addcommand_clicked();


    void on_deletecommand_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

public slots:
    void voicehomeprep();

    void setcommand();

    void writecommand();

private:
    Ui::VoiceHomeMainWindow *ui;
};

#endif // VOICEHOMEMAINWINDOW_H
