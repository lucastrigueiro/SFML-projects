#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


class Button
{
public:
    Button(String normalTex, String clickedTex, Vector2f location);
    void checkClick(Vector2f mousePos);
    void atualiza(Event event);
    void setState(bool);
    bool getSate()
    {
        return current;
    };
    Sprite getDrawButton()
    {
        return currentSpr;
    };

private:
    Sprite normal;
    Sprite clicked;
    Sprite currentSpr;
    bool current;
    Texture aux;
    Texture aux2;
};
