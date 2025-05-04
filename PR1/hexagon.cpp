#include "hexagon.h"
#include <QString>
#include <string>


Hexagon::Hexagon(const std::string& val) : value(val), up(nullptr), up_right(nullptr),
    down_right(nullptr), down(nullptr), down_left(nullptr), up_left(nullptr)
{}

Hexagon::~Hexagon() {}
