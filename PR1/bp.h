#ifndef BP_H
#define BP_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class bp : public QWidget {
    Q_OBJECT
public:
    explicit bp(QWidget *parent = nullptr);
    ~bp();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif
