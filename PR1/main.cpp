#include "page.h"
//#include "pagename.h"
#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <fstream>
//#include <vector>
//#include <iostream>
//#include <cmath>
//#include "hexagon.h"

/*void parseFile(const std::string& filename, Hexagon* hexagons[], size_t count) {
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

    for (size_t i = 0; i < count && i < values.size(); ++i) {
        hexagons[i]->value = values[i];
    }

    for (size_t i = 0; i < count; ++i) {
        std::cout << "Hexagon " << i + 1 << ": " << hexagons[i]->value << std::endl;
    }
}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Page w;
    w.show();
    //pageName w;
    // w.show();
    /*Hexagon o1;
    Hexagon o2;
    Hexagon o3;
    Hexagon o4;
    Hexagon o5;
    Hexagon o6;
    Hexagon o7;
    Hexagon o8;
    Hexagon o9;
    Hexagon o10;
    Hexagon o11;
    Hexagon o12;
    Hexagon o13;
    Hexagon o14;
    Hexagon o15;
    Hexagon o16;
    Hexagon o17;
    Hexagon o18;
    Hexagon o19;
    Hexagon o20;
    Hexagon o21;
    Hexagon o22;
    Hexagon o23;
    Hexagon o24;
    Hexagon o25;
    Hexagon o26;
    Hexagon o27;
    Hexagon o28;
    Hexagon o29;
    Hexagon o30;
    Hexagon o31;
    Hexagon o32;
    Hexagon o33;
    Hexagon o34;
    Hexagon o35;
    Hexagon o36;
    Hexagon o37;
    Hexagon o38;
    Hexagon o39;
    Hexagon o40;
    Hexagon o41;

    o1.down_right = &o6;
    o1.down = &o10;

    o2.down_left=&o6;
    o2.down=&o11;
    o2.down_right=&o7;

    o3.down_left=&o7;
    o3.down=&o12;
    o3.down_right=&o8;

    o4.down_left=&o8;
    o4.down=&o13;
    o4.down_right=&o9;

    o5.down_left = &o9;
    o5.down=&o14;

    o6.up_left=&o1;
    o6.up_right=&o2;
    o6.down_left = &o10;
    o6.down_right=&o11;
    o6.down = &o15;

    o7.up_left=&o2;
    o7.up_right=&o3;
    o7.down_left = &o11;
    o7.down_right=&o12;
    o7.down = &o16;

    o8.up_left=&o3;
    o8.up_right=&o4;
    o8.down_left = &o12;
    o8.down_right=&o13;
    o8.down = &o17;


    o9.up_left=&o4;
    o9.up_right=&o5;
    o9.down_left = &o13;
    o9.down_right=&o14;
    o9.down = &o18;

    o10.up=&o1;
    o10.up_right=&o6;
    o10.down_right=&o15;
    o10.down=&o19;

    o11.up=&o2;
    o11.up_right=&o7;
    o11.down_right=&o16;
    o11.down=&o20;
    o11.down_left=&o15;
    o11.up_left=&o6;

    o12.up=&o3;
    o12.up_right=&o8;
    o12.down_right=&o17;
    o12.down=&o21;
    o12.down_left=&o16;
    o12.up_left=&o7;

    o13.up=&o4;
    o13.up_right=&o9;
    o13.down_right=&o18;
    o13.down=&o22;
    o13.down_left=&o17;
    o13.up_left=&o8;

    o14.up=&o5;
    o14.down=&o23;
    o14.down_left=&o18;
    o14.up_left=&o9;

    o15.up=&o6;
    o15.up_right=&o11;
    o15.down_right=&o20;
    o15.down=&o24;
    o15.down_left=&o19;
    o15.up_left=&o10;

    o16.up=&o7;
    o16.up_right=&o12;
    o16.down_right=&o21;
    o16.down=&o25;
    o16.down_left=&o20;
    o16.up_left=&o11;

    o17.up=&o8;
    o17.up_right=&o13;
    o17.down_right=&o22;
    o17.down=&o26;
    o17.down_left=&o21;
    o17.up_left=&o12;

    o18.up=&o9;
    o18.up_right=&o14;
    o18.down_right=&o23;
    o18.down=&o27;
    o18.down_left=&o22;
    o18.up_left=&o13;

    o19.up=&o10;
    o19.up_right=&o15;
    o19.down_right=&o24;
    o19.down=&o28;


    o20.up=&o11;
    o20.up_right=&o16;
    o20.down_right=&o25;
    o20.down=&o29;
    o20.down_left=&o24;
    o20.up_left=&o15;

    o21.up=&o12;
    o21.up_right=&o17;
    o21.down_right=&o26;
    o21.down=&o30;
    o21.down_left=&o25;
    o21.up_left=&o16;

    o22.up=&o13;
    o22.up_right=&o18;
    o22.down_right=&o27;
    o22.down=&o31;
    o22.down_left=&o26;
    o22.up_left=&o17;

    o23.up=&o14;
    o23.down=&o32;
    o23.down_left=&o27;
    o23.up_left=&o18;

    o24.up=&o15;
    o24.up_right=&o20;
    o24.down_right=&o29;
    o24.down=&o33;
    o24.down_left=&o28;
    o24.up_left=&o19;

    o25.up=&o16;
    o25.up_right=&o21;
    o25.down_right=&o30;
    o25.down=&o34;
    o25.down_left=&o29;
    o25.up_left=&o20;

    o26.up=&o17;
    o26.up_right=&o22;
    o26.down_right=&o31;
    o26.down=&o35;
    o26.down_left=&o30;
    o26.up_left=&o21;

    o27.up=&o18;
    o27.up_right=&o23;
    o27.down_right=&o32;
    o27.down=&o36;
    o27.down_left=&o31;
    o27.up_left=&o22;

    o28.up=&o19;
    o28.up_right=&o24;
    o28.down_right=&o33;
    o28.down=&o37;

    o29.up=&o20;
    o29.up_right=&o25;
    o29.down_right=&o34;
    o29.down=&o38;
    o29.down_left=&o33;
    o29.up_left=&o24;

    o30.up=&o21;
    o30.up_right=&o26;
    o30.down_right=&o35;
    o30.down=&o39;
    o30.down_left=&o34;
    o30.up_left=&o25;

    o31.up=&o22;
    o31.up_right=&o27;
    o31.down_right=&o36;
    o31.down=&o40;
    o31.down_left=&o35;
    o31.up_left=&o26;

    o32.up=&o23;
    o32.down=&o41;
    o32.down_left=&o36;
    o32.up_left=&o27;

    o33.up=&o24;
    o33.up_right=&o29;
    o33.down_right=&o38;
    o33.down_left=&o37;
    o33.up_left=&o28;

    o34.up=&o25;
    o34.up_right=&o30;
    o34.down_right=&o39;
    o34.down_left=&o38;
    o34.up_left=&o29;

    o35.up=&o26;
    o35.up_right=&o31;
    o35.down_right=&o40;
    o35.down_left=&o39;
    o35.up_left=&o30;

    o36.up=&o27;
    o36.up_right=&o32;
    o36.down_right=&o41;
    o36.down_left=&o40;
    o36.up_left=&o31;

    o37.up=&o28;
    o37.up_right=&o38;

    o38.up=&o29;
    o38.up_right=&o34;
    o38.up_left=&o33;

    o39.up=&o30;
    o39.up_right=&o35;
    o39.up_left=&o34;

    o40.up=&o31;
    o40.up_right=&o36;
    o40.up_left=&o35;

    o41.up=&o32;
    o41.up_left=&o40;
    Hexagon* hexagons[] = {
        &o1, &o2, &o3, &o4, &o5, &o6, &o7, &o8, &o9, &o10,
        &o11, &o12, &o13, &o14, &o15, &o16, &o17, &o18, &o19, &o20,
        &o21, &o22, &o23, &o24, &o25, &o26, &o27, &o28, &o29, &o30,
        &o31, &o32, &o33, &o34, &o35, &o36, &o37, &o38, &o39, &o40, &o41
    };


    parseFile("grid1.txt", hexagons, 41);*/

    return a.exec();
}
