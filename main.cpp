#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Player.h"
#include "Meteroite.h"
#include "missile.h"
#include "Entity.h"
#include <vector>

using namespace std;

template <class Container>
typename Container::iterator to_mutable_iterator(Container& c, typename Container::const_iterator it)
{
    return c.begin() + (it - c.begin());
}

int main()
{
    int counter;
    int counter2;
    sf::Clock clockMissile;
    sf::Clock clockMeteorite;

    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(400, 600), "SFML works!");
    window.setFramerateLimit(60);

    Player player;

    vector<Meteroite>::const_iterator iterMeteorite;
    vector<Meteroite> meteoriteArray;

    Meteroite meteorite1;

    vector<missile>::const_iterator iterMissile;
    vector<missile> missileArray;

    missile missile1;

    bool canShoot = true;
    float tempsEcoule;
    float tempsRecharge;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
            case(sf::Event::Closed):
                window.close();
                break;
            case(sf::Event::KeyPressed):
                switch(event.key.code){
                case(sf::Keyboard::Escape):
                    window.close();
                    break;
                default:
                    break;
                }
            }
        }
        window.clear();

        //Gestion du temps
        tempsEcoule = clockMeteorite.getElapsedTime().asSeconds();
        tempsRecharge = clockMissile.getElapsedTime().asSeconds();

        //COLLISION
        counter =0;
        for(iterMissile = missileArray.begin(); iterMissile != missileArray.end(); iterMissile++){
            counter2=0;
            for(iterMeteorite = meteoriteArray.begin(); iterMeteorite != meteoriteArray.end(); iterMeteorite++){

                if(missileArray[counter].rect.getGlobalBounds().intersects(meteoriteArray[counter2].circ.getGlobalBounds())){
                    cout << "TOUCHE" << endl;
                    meteoriteArray[counter2].hp -= 5;
                    missileArray[counter].isDestroyed = true;
                }

                if(meteoriteArray[counter2].hp<=0){
                    meteoriteArray[counter2].isAlive = false;
                }
                counter2++;
            }
            counter++;
        }

        //Supprimer météorite détruites
        counter=0;
        for (iterMeteorite = meteoriteArray.begin(); iterMeteorite != meteoriteArray.end(); iterMeteorite++)
        {
            if (meteoriteArray[counter].isAlive == false)
            {
                cout << "Enemy has been obliterated! lawlz" << endl;
                iterMeteorite=meteoriteArray.erase(to_mutable_iterator(meteoriteArray,iterMeteorite));
                break;
            }

            counter++;
        }

        //Supprimer missiles
        counter =0;
        for(iterMissile = missileArray.begin(); iterMissile != missileArray.end(); iterMissile++)
        {
             if (missileArray[counter].isDestroyed == true)
            {
                iterMissile=missileArray.erase(to_mutable_iterator(missileArray,iterMissile));
                cout << "MISSILE DESTROYED" << endl;
                break;
            }
            counter++;
        }

        //Créer missiles
        if(tempsRecharge>=0.25){
            clockMissile.restart();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            missile1.rect.setPosition(player.rect.getPosition().x + 10,540);
            missileArray.push_back(missile1);
        }
        }


        //Dessiner missiles
        counter =0;
        for(iterMissile = missileArray.begin(); iterMissile != missileArray.end(); iterMissile++){
                    missileArray[counter].updatePosition();
                    window.draw(missileArray[counter].rect);
                    counter++;
        }

        //Créer météorites
        if(tempsEcoule >= 2){
            meteorite1.circ.setPosition(rand()%390-10,-20);
            meteoriteArray.push_back(meteorite1);
            clockMeteorite.restart();
        }

        //Dessiner météorites
        counter =0;
        for(iterMeteorite = meteoriteArray.begin(); iterMeteorite != meteoriteArray.end(); iterMeteorite++){
                if(counter <= 5){ //pas plus de 5 météorites en même temps
                    meteoriteArray[counter].updatePosition();
                    window.draw(meteoriteArray[counter].circ);
                    counter++;
                }
        }

        player.movement(); //Player movement

        window.draw(player.rect);
        window.display();
    }

    return 0;
}
