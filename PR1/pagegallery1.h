#ifndef PAGEGALLERY1_H
#define PAGEGALLERY1_H

#include <QMainWindow>

#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include <QScrollArea>

namespace Ui {
class pageGallery1;
}

class pageGallery1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit pageGallery1(QWidget *parent = nullptr);
    ~pageGallery1();

private slots:
    void handlePlayButtonClick();


private:
    Ui::pageGallery1 *ui;
    QScrollArea* leftScrollArea;
    QScrollArea* rightScrollArea;
    QList<QPushButton*> leftButtons;
    QList<QPushButton*> rightButtons;
    QList<QPushButton*> selectedLeftButtons;
    QList<QPushButton*> selectedRightButtons;

    void setupSection(QWidget* container, bool isLeft);
    void handleButtonClick(QPushButton* button, int index, bool isLeft);
    void executeButtonAction(int index);
};

#endif // PAGEGALLERY1_H
