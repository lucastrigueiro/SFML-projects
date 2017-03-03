#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>


using namespace sf;
using namespace std;


class Personagem {
public:
	Personagem(int n);
    Sprite getSprite();
    int getAltura();
    int getLargura();
    void mover(Vector2f movimento, float passo);
    void setPosition(Vector2f posicao);
    ~Personagem();

private:
	int nformas;
    int flag;
    Sprite sprite;
    IntRect rectSourceSprite;
    Texture texture;
    Vector2u dimensoes;
};
