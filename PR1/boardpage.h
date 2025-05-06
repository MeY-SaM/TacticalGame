#ifndef BOARDPAGE_H
#define BOARDPAGE_H

#include <QMainWindow>

namespace Ui {
class boardpage;
}

class boardpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit boardpage(QWidget *parent = nullptr);
    ~boardpage();

private:
    Ui::boardpage *ui;
};

#endif // BOARDPAGE_H
