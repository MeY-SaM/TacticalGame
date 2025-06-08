#ifndef HEXAGON_H
#define HEXAGON_H

#include <QPolygonF>
#include <QPointF>
#include <QChar>

class Hexagon {
public:
    explicit Hexagon(qreal x, qreal y, QChar value = ' ', int index = -1)
        : posX_(x), posY_(y), value_(value), index_(index),
        neighbor0_(nullptr), neighbor1_(nullptr), neighbor2_(nullptr),
        neighbor3_(nullptr), neighbor4_(nullptr), neighbor5_(nullptr) {
        polygon_ << QPointF(17.5, 0) << QPointF(52.5, 0)
        << QPointF(70, 35) << QPointF(52.5, 70)
        << QPointF(17.5, 70) << QPointF(0, 35);
    }

    void setValue(QChar value) { value_ = value; }
    QChar getValue() const { return value_; }
    QPointF getCenter() const { return QPointF(posX_ + 35, posY_ + 35); }
    QPolygonF getPolygon() const { return polygon_; }
    int getIndex() const { return index_; }

    void setNeighbor(int index, Hexagon* neighbor) {
        if (index == 0) neighbor0_ = neighbor;
        else if (index == 1) neighbor1_ = neighbor;
        else if (index == 2) neighbor2_ = neighbor;
        else if (index == 3) neighbor3_ = neighbor;
        else if (index == 4) neighbor4_ = neighbor;
        else if (index == 5) neighbor5_ = neighbor;
    }

    Hexagon* getNeighbor(int index) const {
        if (index == 0) return neighbor0_;
        if (index == 1) return neighbor1_;
        if (index == 2) return neighbor2_;
        if (index == 3) return neighbor3_;
        if (index == 4) return neighbor4_;
        if (index == 5) return neighbor5_;
        return nullptr;
    }

private:
    QPolygonF polygon_;

    QChar value_;
    qreal posX_, posY_;
    int index_;

    Hexagon* neighbor0_;
    Hexagon* neighbor1_;
    Hexagon* neighbor2_;
    Hexagon* neighbor3_;
    Hexagon* neighbor4_;
    Hexagon* neighbor5_;
};

#endif // HEXAGON_H
