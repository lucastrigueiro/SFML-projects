#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>


using namespace sf;
using namespace std;


class Explosao{
public:
	Explosao();
    Sprite getSprite(int n);
    int getAltura();
    int getLargura();
    void mover(Vector2f movimento, float passo);
    void setPosition(Vector2f posicao);
    ~Explosao();

private:
    int flag;
    Sprite sprite[5];
    IntRect rectSourceSprite;
    Texture texture;
    Vector2u dimensoes;
};
