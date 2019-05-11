#ifndef SNAKE_HPP_INCLUDED
#define SNAKE_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <cstdlib>
#include "global_constants.hpp"
#include "segment.hpp"

class Snake {

public:
    Snake(int startx, int starty, char dir);
    ~Snake();
    void addSegment(int x, int y);
    void move();
    void setDirection(char dir);
    void checkCollision();
    bool isAlive() { return alive; }
    bool checkAndEatFood(Segment* food);
    std::vector<Segment *> getBody();
    char getDirection();
    //void checkAndEatFood();

private:
    std::vector<Segment *> body;
    char direction;
    bool alive;
};


#endif // SNAKE_HPP_INCLUDED
