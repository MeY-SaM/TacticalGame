#ifndef PAGEGALLERY1_H
#define PAGEGALLERY1_H

#include <QMainWindow>

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
    void on_pushButton_clicked();

private:
    Ui::pageGallery1 *ui;
};

#endif // PAGEGALLERY1_H
