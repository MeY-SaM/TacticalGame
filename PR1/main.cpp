#include "page.h"
#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QAudioOutput>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMediaPlayer* player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/new/prefix1/soundgame.mp3"));
    audioOutput->setVolume(0.5);
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            player->play();
        }
    });
    player->play();

    Page w;

    w.show();

    return a.exec();
}
