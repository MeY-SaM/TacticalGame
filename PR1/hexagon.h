#ifndef HEXAGON_H
#define HEXAGON_H

#include <string>
#include <QString>
class Hexagon {
public:
    std::string value;
    Hexagon* up;
    Hexagon* up_right;
    Hexagon* down_right;
    Hexagon* down;
    Hexagon* down_left;
    Hexagon* up_left;

    Hexagon(const std::string& val = "");
    ~Hexagon();
};

#endif // HEXAGON_H
