#pragma once
#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class VoiceHome; }
QT_END_NAMESPACE

class VoiceHomeMainWindow;

class VoiceHome : public QMainWindow {
    Q_OBJECT

public:
    explicit VoiceHome(QWidget *parent = nullptr);
    ~VoiceHome() override;

public slots:
    void checkConnection();

private:
    std::unique_ptr<Ui::VoiceHome> ui;
    std::unique_ptr<VoiceHomeMainWindow> mainapp;

    bool isPortAvailable(const QString &portName);
    void loadInterface();
};
