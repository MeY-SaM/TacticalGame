#ifndef CHARACTERDIALOG_H
#define CHARACTERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

#include <QTabWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QTabWidget>


struct CharacterInfo {
    QString name;
    int hp;
    int mobility;
    int damage;
    float attackRange;
};

CharacterInfo waterwalkingcharacterData[] = {
    {"Angus", 400, 2, 100 , 1},
    {"Billy", 320, 3, 90, 1},
    {"Bunka", 320, 3, 100, 1},
    {"Colonel Baba", 400 , 2, 100, 1},
    {"Duraham", 320, 2, 100, 2},
    {"Medusa", 320, 2, 90, 2},
    {"Reketon", 320, 2, 80, 2},
    {"Sanka", 320, 3, 100, 1}
};
CharacterInfo groundedCharacterData[] = {
    {"Boi", 400, 2, 100, 1},
    {"Eloi", 240, 2, 100, 2.3},
    {"Elsa", 320, 2, 140, 2},
    {"Frost", 260, 2, 80, 2},
    {"Kabu", 400 , 2, 120, 1},
    {"Kanar", 160, 2, 100, 2},
    {"Karissa", 280, 2, 80, 2},
    {"Khan", 320, 2, 90, 1},
    {"Rajakal", 320, 2, 130, 1},
    {"Salih",400, 2,80, 1},
    {"Sir Lamorak", 320, 3, 110, 1},
    {"Sir Philip", 400, 2, 100, 1},
    {"Tusk", 400, 2, 100, 1}
};

class CharacterDialog : public QDialog {
public:
    CharacterDialog(const QString& name, int hp, int mobility, int damage, float attackRange, const QString& imagePath, QWidget* parent = nullptr)
        : QDialog(parent) {
        setWindowTitle(name);

        QVBoxLayout* layout = new QVBoxLayout(this);
        //layout->setAlignment(Qt::AlignCenter);


        QLabel* imageLabel = new QLabel(this);
        QPixmap pixmap(imagePath);
        imageLabel->setPixmap(pixmap.scaled(250, 350, Qt::KeepAspectRatio));
        imageLabel->setAlignment(Qt::AlignCenter);

        QLabel* nameLabel = new QLabel("Name : " + name, this);
        nameLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
        nameLabel->setAlignment(Qt::AlignCenter);

        QLabel* hpLabel = new QLabel(QString("HP : %1").arg(hp), this);
        hpLabel->setStyleSheet("font-size: 16px;");
        hpLabel->setAlignment(Qt::AlignCenter);

        QLabel* mobilityLabel = new QLabel(QString("Mobility : %1").arg(mobility), this);
        mobilityLabel->setStyleSheet("font-size: 16px;");
        mobilityLabel->setAlignment(Qt::AlignCenter);

        QLabel* damageLabel = new QLabel(QString("Damage : %1").arg(damage), this);
        damageLabel->setStyleSheet("font-size: 16px;");
        damageLabel->setAlignment(Qt::AlignCenter);

        QLabel* attackRangeLabel = new QLabel(QString("Attack Range : %1").arg(attackRange), this);
        attackRangeLabel->setStyleSheet("font-size: 16px;");
        attackRangeLabel->setAlignment(Qt::AlignCenter);

        layout->addWidget(imageLabel);
        layout->addWidget(nameLabel);
        layout->addWidget(hpLabel);
        layout->addWidget(mobilityLabel);
        layout->addWidget(damageLabel);
        layout->addWidget(attackRangeLabel);

        QPushButton* closeButton = new QPushButton("Close", this);
        connect(closeButton, &QPushButton::clicked, this, &QDialog::close);
        layout->addWidget(closeButton);

        setLayout(layout);
        setFixedSize(400, 600);

        // move(176, 46);

    }
};
#endif // CHARACTERDIALOG_H
