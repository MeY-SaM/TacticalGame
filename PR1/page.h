#ifndef PAGE_H
#define PAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Page;
}
QT_END_NAMESPACE

class Page : public QMainWindow
{
    Q_OBJECT

public:
    Page(QWidget *parent = nullptr);
    ~Page();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Page *ui;
};
#endif // PAGE_H
