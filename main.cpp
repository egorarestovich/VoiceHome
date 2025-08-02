#include "voicehome.h"
#include <QApplication>
#include <QTimer>
#include "styles.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyleSheet(Styles::darkTheme());  // Теперь Styles доступен

    VoiceHome w;
    QTimer::singleShot(3000, &w, &VoiceHome::checkConnection);  // Теперь QTimer доступен
    w.show();

    return a.exec();
}
