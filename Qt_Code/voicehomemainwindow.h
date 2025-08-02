#pragma once
#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class VoiceHomeMainWindow; }
QT_END_NAMESPACE

class SerialPortManager;

class VoiceHomeMainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit VoiceHomeMainWindow(QWidget *parent = nullptr);
    ~VoiceHomeMainWindow() override;

private slots:
    void openConnect();
    void voicehomeprep();
    void on_HomeButton_clicked();
    void on_CommandsButton_clicked();
    void on_CheckBoxSvet_stateChanged(int state);
    void on_CheckBoxFan_stateChanged(int state);
    void on_CheckBoxChainik_stateChanged(int state);
    void on_CheckBoxUserCommand_stateChanged(int state);
    void on_UserCommandButton_clicked();
    void WriteOnUserButton(const QString &text);

    void handleSerialData(const QString &data);
    void handleSerialError(const QString &error);

private:
    std::unique_ptr<Ui::VoiceHomeMainWindow> ui;
    std::unique_ptr<SerialPortManager> m_serialManager;
    QString m_userCommand;
    const QString m_commandsFile = "C:/vcres/commands.txt";

    void loadUserCommand();
    void saveUserCommand(const QString &command);
    void setupUIForHome();
    void setupUIForCommands();
};
