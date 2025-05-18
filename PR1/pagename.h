#ifndef PAGENAME_H
#define PAGENAME_H

#include <QMainWindow>

namespace Ui {
class pageName;
}

class pageName : public QMainWindow
{
    Q_OBJECT

public:
    explicit pageName(QWidget *parent = nullptr);
    ~pageName();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::pageName *ui;
};

#endif // PAGENAME_H
