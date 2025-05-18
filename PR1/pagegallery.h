#ifndef PAGEGALLERY_H
#define PAGEGALLERY_H

#include <QMainWindow>

namespace Ui {
class pageGallery;
}

class pageGallery : public QMainWindow
{
    Q_OBJECT

public:
    explicit pageGallery(QWidget *parent = nullptr);
    ~pageGallery();

private slots:
    void on_pushButton_clicked();

private:
    Ui::pageGallery *ui;
    void makeTransparent(QWidget* widget);

};

#endif // PAGEGALLERY_H
