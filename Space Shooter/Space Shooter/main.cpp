#include <cstdlib>
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include <ctime>
#include "Player.h"
#include "Meteroite.h"
#include "missile.h"
#include "Entity.h"
#include <fstream>
#include <vector>

using namespace std;

string lvl;

template <class Container>
typename Container::iterator to_mutable_iterator(Container& c, typename Container::const_iterator it)
{
    return c.begin() + (it - c.begin());
}

void ecrireFichier() {
	ofstream file("res/data.txt", ios::out | ios::trunc);
	if (file) {
		cout << "HELLO" << endl;
		file << lvl;
		file.close();
	}
}

int main()
{

	sf::Font font;

	if (!font.loadFromFile("res/Arial.ttf"))
	{
	}

	ifstream file("res/data.txt", ios::in);
	if (file) {

			getline(file,lvl);

			cout << "open" << endl ;
			cout << "level = " + lvl << endl;

			file.close();
	}


    int counter;
    int counter2;

    int scoreint=0;
        
    sf::Clock clockMissile;
    sf::Clock clockMeteorite;
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(400, 800), "SFML works!");
    window.setFramerateLimit(60);

    Player player;

	int lvlint = atoi(lvl.c_str());
	sf::Text level;
	level.setFont(font);
	level.setPosition(10,740);

    sf::Text Score;
	Score.setFont(font);
	Score.setPosition(10,700);


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
				ecrireFichier();
                window.close();
                break;
            case(sf::Event::KeyPressed):
                switch(event.key.code){
                default:
                    break;
                }
            }
        }
        window.clear();

        //Gestion du temps
        tempsEcoule = clockMeteorite.getElapsedTime().asSeconds();
        tempsRecharge = clockMissile.getElapsedTime().asSeconds();

		//GestionScore
		string scorestr = to_string(scoreint);
		Score.setString("Score " + scorestr);

		lvl = to_string(lvlint);
		level.setString("Level" + lvl);

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

        //Supprimer m�t�orite d�truites
        counter=0;
        for (iterMeteorite = meteoriteArray.begin(); iterMeteorite != meteoriteArray.end(); iterMeteorite++)
        {
            if (meteoriteArray[counter].isAlive == false)
            {
                cout << "Meteorite broken" << endl;
                iterMeteorite=meteoriteArray.erase(to_mutable_iterator(meteoriteArray,iterMeteorite));
				scoreint++;
				lvlint++;
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

        //Cr�er missiles
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

        //Cr�er m�t�orites
        if(tempsEcoule >= 2){
            meteorite1.circ.setPosition(rand()%390-10,-20);
            meteoriteArray.push_back(meteorite1);
            clockMeteorite.restart();
        }

        //Dessiner m�t�orites
        counter =0;
        for(iterMeteorite = meteoriteArray.begin(); iterMeteorite != meteoriteArray.end(); iterMeteorite++){
                if(counter <= 5){ //pas plus de 5 m�t�orites en m�me temps
                    meteoriteArray[counter].updatePosition();
                    window.draw(meteoriteArray[counter].circ);
                    counter++;
                }
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			ecrireFichier();
			window.close();
		}

        player.movement(); //Player movement

		window.draw(Score);
		window.draw(level);
        window.draw(player.rect);
        window.display();
    }

    return 0;
}
