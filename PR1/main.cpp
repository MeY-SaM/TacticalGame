//#include "page.h"
#include "pagename.h"
#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include "hexagon.h"

void parseFile(const std::string& filename, Hexagon* hexagons[], size_t count) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> values;
    while (std::getline(file, line)) {
        std::string currentValue = "";
        bool afterSlash = false;
        for (char c : line) {
            if (c == '/') {
                afterSlash = true;
                currentValue = "";
            } else if (afterSlash) {
                currentValue += c;
                values.push_back(currentValue);
                afterSlash = false;
            }
        }
    }
    file.close();

    // تخصیص مقادیر به اشیاء Hexagon
    for (size_t i = 0; i < count && i < values.size(); ++i) {
        hexagons[i]->value = values[i];
    }

    // چاپ برای تست
    for (size_t i = 0; i < count; ++i) {
        std::cout << "Hexagon " << i + 1 << ": " << hexagons[i]->value << std::endl;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Page w;
    //w.show();
    pageName w;
    w.show();
    return a.exec();
}
