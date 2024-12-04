//Position.h
#ifndef POSITION_H
#define POSITION_H

#include <cmath>

class Position {
private:
    int x;
    int y;

public:
    Position(int x = 0, int y = 0);

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    int distance(const Position& other) const;
    void moveTowards(const Position& target);
};

#endif
//Position.cpp
#include "Position.h"

Position::Position(int x, int y) : x(x), y(y) {}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

void Position::setX(int x) {
    this->x = x;
}

void Position::setY(int y) {
    this->y = y;
}

int Position::distance(const Position& other) const {
    int dx = other.x - x;
    int dy = other.y - y;
    return static_cast<int>(std::sqrt(dx * dx + dy * dy));
}

void Position::moveTowards(const Position& target) {
    if (x < target.x) x++;
    else if (x > target.x) x--;

    if (y < target.y) y++;
    else if (y > target.y) y--;
}
//Unit.h
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include "Position.h"

class Unit {
private:
    std::string name;
    int health;
    Position position;

public:
    Unit(const std::string& name, int health, int x, int y);

    std::string getName() const;
    int getHealth() const;
    Position getPosition() const;

    void setName(const std::string& name);
    void setHealth(int health);
    void setPosition(int x, int y);

    void move(int dx, int dy);
    void moveTowards(const Unit& target);
    int distanceTo(const Unit& other) const;
};

#endif
//Unit.cpp
#include "Unit.h"

Unit::Unit(const std::string& name, int health, int x, int y)
    : name(name), health(health), position(x, y) {}

std::string Unit::getName() const {
    return name;
}

int Unit::getHealth() const {
    return health;
}

Position Unit::getPosition() const {
    return position;
}

void Unit::setName(const std::string& name) {
    this->name = name;
}

void Unit::setHealth(int health) {
    this->health = health;
}

void Unit::setPosition(int x, int y) {
    position.setX(x);
    position.setY(y);
}

void Unit::move(int dx, int dy) {
    position.setX(position.getX() + dx);
    position.setY(position.getY() + dy);
}

void Unit::moveTowards(const Unit& target) {
    position.moveTowards(target.getPosition());
}

int Unit::distanceTo(const Unit& other) const {
    return position.distance(other.getPosition());
}
//main.cpp
#include "Unit.h"
#include "Team.h"
#include <iostream>

int main() {
    Unit u1("Warrior", 100, 0, 0);
    Unit u2("Mage", 80, 5, 5);

    std::cout << "Distance between Warrior and Mage: " << u1.distanceTo(u2) << "\n";

    while (u1.distanceTo(u2) > 0) {
        u1.moveTowards(u2);
        std::cout << "Warrior moved to ("
            << u1.getPosition().getX() << ", "
            << u1.getPosition().getY() << ")\n";
    }

    std::cout << "Warrior reached Mage's position.\n";

    return 0;
}
