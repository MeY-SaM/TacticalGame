#include "boardpage.h"
#include "ui_boardpage.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
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

// ناحیه مجاز رهاسازی برای برد اصلی
const int BOARD_LEFT = 100;
const int BOARD_RIGHT = 700;

class DraggableHexItem : public QGraphicsPolygonItem {
public:
    DraggableHexItem(const QPolygonF& polygon, QGraphicsItem* parent = nullptr)
        : QGraphicsPolygonItem(polygon, parent) {
        setFlags(ItemIsMovable | ItemIsSelectable);
        setCursor(Qt::OpenHandCursor);
        setZValue(10); // جلوتر از آیتم‌های دیگر باشد
    }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemPositionChange && scene()) {
            QPointF newPos = value.toPointF();
            if (newPos.x() < BOARD_LEFT || newPos.x() > BOARD_RIGHT) {
                return pos(); // جلوگیری از خروج از محدوده برد
            }
        }
        return QGraphicsItem::itemChange(change, value);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    view.setFixedSize(800, 600);
    scene.setSceneRect(0, 0, 800, 600);

    // نوارهای سفید چپ و راست
    scene.addRect(0, 0, 100, 600, QPen(Qt::NoPen), QBrush(Qt::white));
    scene.addRect(700, 0, 100, 600, QPen(Qt::NoPen), QBrush(Qt::white));

    int randomIndex = QRandomGenerator::global()->bounded(1, 9); // عددی بین 1 تا 8
    QString filePath = QString(":/new/prefix1/grid%1.txt").arg(randomIndex);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file: " << file.errorString().toStdString() << std::endl;
        return -1;
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

    // مرکز برد را از لحاظ افقی به‌گونه‌ای تنظیم کنیم که شش‌ضلعی‌ها به‌طور متقارن قرار گیرند
    qreal boardStartX = BOARD_LEFT + (BOARD_RIGHT - BOARD_LEFT - charW * lines[0].length()) / 2.0;

    for (int row = 0; row < lines.size(); ++row) {
        const QString &line = lines[row];
        for (int col = 0; col < line.length(); ++col) {
            QChar ch = line[col];
            qreal x = boardStartX + col * charW; // مرکز برد
            qreal y = row * charH;

            switch (ch.unicode()) {
            case '/':{
                scene.addItem(new QGraphicsLineItem(x, y + charH, x + charW, y));
                break;
            }
            case '\\': {
                scene.addItem(new QGraphicsLineItem(x, y, x + charW, y + charH));
                break;
            }
            case '_': {
                scene.addItem(new QGraphicsLineItem(x, y + charH, x + charW, y + charH));
                break;
            }
            case ' ': {
                break;
            }
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
                scene.addItem(hexItem);

                auto text = new QGraphicsSimpleTextItem(QString(ch));
                text->setFont(mono);
                qreal tx = x + (charW - fm.horizontalAdvance(ch)) / 2.0;
                qreal ty = y + (charH - fm.ascent() - fm.descent()) / 2.0;
                text->setPos(tx, ty);
                scene.addItem(text);
                break;
            }
            }
        }
    }

    // ایجاد دو شش‌ضلعی در نوار چپ
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
        scene.addItem(item);
    }

    // ایجاد دو شش‌ضلعی در نوار راست
    for (int i = 0; i < 2; ++i) {
        auto item = new DraggableHexItem(hex);
        item->setBrush(QColor("red"));
        item->setPos(750, 100 + i * 100);
        scene.addItem(item);
    }

    view.setScene(&scene);
    view.show();
    view.setFixedSize(800,300);
    return app.exec();
}
