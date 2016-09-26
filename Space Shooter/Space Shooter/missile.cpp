#include "missile.h"

missile::missile()
{
    rect.setSize(sf::Vector2f(5,10));
    rect.setFillColor(sf::Color::Red);
    isDestroyed = false;
}

void missile::updatePosition(){
    if(rect.getPosition().y >=-9){
            rect.move(0,-moveSpeed);
    }else{
        isDestroyed = true;
    }
}
