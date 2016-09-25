#include "Player.h"

Player::Player()
{
    rect.setSize(sf::Vector2f(20,50));
    rect.setPosition(190, 540);
    rect.setFillColor(sf::Color::Red);

}

void Player::movement(){
        int x = rect.getPosition().x;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x <= 380){
            rect.move(moveSpeed,0);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x >= 0){
            rect.move(-moveSpeed,0);
        }
}
