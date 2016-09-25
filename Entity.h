#ifndef ENTITY_H
#define ENTITY_H


#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <tgmath.h>
#include <deque>
#include <list>
#include <vector>
#include <unistd.h>
using namespace std;
//#include "randomFunction.h"

class Entity
{
public:
    sf::RectangleShape rect;
    sf::CircleShape circ;
    sf::Sprite sprite;
    sf::Text text;

private:
protected:
};
#endif // ENTITY_H
