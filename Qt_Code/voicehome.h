#ifndef VOICEHOME_H
#define VOICEHOME_H

#include <QMainWindow>
#include "voicehomemainwindow.h"
#include <voicehomemainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class VoiceHome; }
QT_END_NAMESPACE

class VoiceHome : public QMainWindow
{
    Q_OBJECT

public:
    VoiceHome(QWidget *parent = nullptr);
    ~VoiceHome();

private slots:
    bool isconnectpossible();
    void loadinterface();

public slots:
    void checkconnection();

private:
    Ui::VoiceHome *ui;
    VoiceHomeMainWindow *mainapp;
};
#endif // VOICEHOME_H
