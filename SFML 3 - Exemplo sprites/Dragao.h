#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>


using namespace sf;
using namespace std;


class Dragao{
public:
    Dragao();
    Sprite getSprite();
    void mover(Vector2f movimento);
    ~Dragao();

private:
    int flag;
    Sprite sprite;
    IntRect rectSourceSprite;
    Texture texture;
};
