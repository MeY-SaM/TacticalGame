#ifndef PAGE1_H
#define PAGE1_H

#include <QMainWindow>

namespace Ui {
class page1;
}

class page1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit page1(QWidget *parent = nullptr);
    ~page1();

private slots:
    void on_pushButtonGallery_clicked();

    void on_pushButtonStart_clicked();

private:
    Ui::page1 *ui;
};

#endif // PAGE1_H
