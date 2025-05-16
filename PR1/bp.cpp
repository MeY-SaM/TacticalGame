#include "bp.h"
#include <QPainter>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPolygonItem>
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QFontMetrics>
#include <QStringList>
#include <QPolygonF>
#include <iostream>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPointF>
#include <cmath>

const int BOARD_LEFT = 100;
const int BOARD_RIGHT = 700;

class DraggableHexItem : public QGraphicsPolygonItem {
public:
    DraggableHexItem(const QPolygonF& polygon, QGraphicsItem* parent = nullptr)
        : QGraphicsPolygonItem(polygon, parent) {
        setFlags(ItemIsMovable | ItemIsSelectable);
        setCursor(Qt::OpenHandCursor);
        setZValue(10);
        originalPos = pos();
    }

    void setSnapGrid(qreal cellWidth, qreal cellHeight, qreal boardStartX) {
        this->cellWidth = cellWidth;
        this->cellHeight = cellHeight;
        this->boardStartX = boardStartX;
    }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemPositionChange && scene()) {
            QPointF newPos = value.toPointF();
            if (newPos.x() < BOARD_LEFT || newPos.x() > BOARD_RIGHT) {
                return pos();
            }
            return newPos;
        } else if (change == ItemPositionHasChanged) {
            snapToGrid();
        }
        return QGraphicsItem::itemChange(change, value);
    }

private:
    void snapToGrid() {
        qreal x = pos().x();
        qreal y = pos().y();
        qreal col = floor((x - boardStartX) / cellWidth + 0.5);
        qreal row = floor(y / cellHeight + 0.5);
        qreal newX = boardStartX + col * cellWidth;
        qreal newY = row * cellHeight;
        setPos(newX, newY);
    }

    QPointF originalPos;
    qreal cellWidth = 0;
    qreal cellHeight = 0;
    qreal boardStartX = 0;
};

bp::bp(QWidget *parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);

    view->setFixedSize(800, 300);
    scene->setSceneRect(0, 0, 800, 300);
    setFixedSize(800, 300);

    scene->addRect(0, 0, 100, 300, QPen(Qt::NoPen), QBrush(Qt::gray));
    scene->addRect(700, 0, 100, 300, QPen(Qt::NoPen), QBrush(Qt::gray));

    int randomIndex = QRandomGenerator::global()->bounded(1, 9);
    QString filePath = QString(":/new/prefix1/grid%1.txt").arg(randomIndex);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file: " << file.errorString().toStdString() << std::endl;
        return;
    }
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty())
            lines.append(line);
    }
    file.close();

    QFont mono("Courier New");
    mono.setStyleHint(QFont::Monospace);
    mono.setPointSize(12);
    QFontMetrics fm(mono);
    const int charW = fm.horizontalAdvance('X');
    const int charH = fm.height();

    qreal boardStartX = BOARD_LEFT + (BOARD_RIGHT - BOARD_LEFT - charW * lines[0].length()) / 2.0;

    for (int row = 0; row < lines.size(); ++row) {
        const QString &line = lines[row];
        for (int col = 0; col < line.length(); ++col) {
            QChar ch = line[col];
            qreal x = boardStartX + col * charW;
            qreal y = row * charH;
            switch (ch.unicode()) {
            case '/':
                scene->addItem(new QGraphicsLineItem(x, y + charH, x + charW, y));
                break;
            case '\\':
                scene->addItem(new QGraphicsLineItem(x, y, x + charW, y + charH));
                break;
            case '_':
                scene->addItem(new QGraphicsLineItem(x, y + charH, x + charW, y + charH));
                break;
            case ' ':
                break;
            default: {
                QPolygonF hexagon;
                qreal cx = x + charW;
                qreal cy = y + charH;
                qreal radius = qMin(charW, charH) * 2.0;
                for (int i = 0; i < 6; ++i) {
                    qreal angle = M_PI / 3.0 * i;
                    hexagon << QPointF(cx + radius * cos(angle), cy + radius * sin(angle));
                }
                auto hexItem = new QGraphicsPolygonItem(hexagon);
                if (ch == '1') {
                    hexItem->setBrush(QBrush(Qt::yellow));
                } else if (ch == '2') {
                    hexItem->setBrush(QBrush(Qt::red));
                } else if (ch == '*') {
                    hexItem->setBrush(QBrush(Qt::cyan));
                } else if (ch == '#') {
                    hexItem->setBrush(QBrush(Qt::gray));
                } else {
                    hexItem->setBrush(QBrush(Qt::cyan));
                }
                hexItem->setPen(Qt::NoPen);
                hexItem->setZValue(0);
                scene->addItem(hexItem);

                auto text = new QGraphicsSimpleTextItem(QString(ch));
                text->setFont(mono);
                qreal tx = x + (charW - fm.horizontalAdvance(ch)) / 2.0;
                qreal ty = y + (charH - fm.ascent() - fm.descent()) / 2.0;
                text->setPos(tx, ty);
                text->setZValue(1);
                scene->addItem(text);
                break;
            }
            }
        }
    }

    qreal cellWidth = charW;
    qreal cellHeight = charH;

    QPolygonF hex;
    qreal r = 20.0;
    for (int i = 0; i < 6; ++i) {
        qreal angle = M_PI / 3.0 * i;
        hex << QPointF(r * cos(angle), r * sin(angle));
    }
    for (int i = 0; i < 2; ++i) {
        auto item = new DraggableHexItem(hex);
        item->setBrush(QColor("yellow"));
        item->setPos(50, 100 + i * 100);
        item->setSnapGrid(cellWidth, cellHeight, boardStartX);
        scene->addItem(item);
    }

    for (int i = 0; i < 2; ++i) {
        auto item = new DraggableHexItem(hex);
        item->setBrush(QColor("red"));
        item->setPos(750, 100 + i * 100);
        item->setSnapGrid(cellWidth, cellHeight, boardStartX);
        scene->addItem(item);
    }
    view->show();
}

bp::~bp() {
    delete scene;
    delete view;
}
