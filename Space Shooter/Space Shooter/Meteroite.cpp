#include "Meteroite.h"

Meteroite::Meteroite()
{
    circ.setRadius(20);
    circ.setFillColor(sf::Color::Red);
    circ.setPosition(rand()%390-10,-20);
    hp=10;
    isAlive = true;
}

void Meteroite::updatePosition(){
    if(circ.getPosition().y <600){
            circ.move(0,3);
    }else{
            circ.setPosition(rand()%390-10,0);
    }

}
