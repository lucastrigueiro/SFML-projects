#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<windows.h>

//#include<iostrean.h>


using namespace sf;
using namespace std;


class Bomb{
public:
	Bomb();
    Sprite getSprite();
    int getAltura();
    int getLargura();
    void disparar(Vector2f pos_bomba);
	void explodir();
    void setPosition(Vector2f posicao);
	bool getAtiva();
    ~Bomb();

private:
    int flag;
    Sprite sprite;
    IntRect rectSourceSprite;
    Texture texture;
    Vector2u dimensoes;
	bool ativa;
	sf::SoundBuffer som_bomba;
	sf::Sound sound;
};
