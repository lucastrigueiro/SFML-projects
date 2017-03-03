#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>


using namespace sf;
using namespace std;


class BtnSprite{
public:
    BtnSprite();
    Sprite getSprite();
    bool verificaPosicao(Vector2i position);
    void atualiza(Event event, Vector2i mousePosition);
    ~BtnSprite();

private:
    int flag;
    Sprite sprite;
    IntRect rectSourceSprite;
    Texture myTexture;
};
