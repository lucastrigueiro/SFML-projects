#include<iostream>
#include<SFML/Graphics.hpp>
#include "CButton.h"
#include "BtnSprite.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Exemplo de Textura");

    Button *btnSair = new Button("btn2.png", "btn1.png", Vector2f(400.0f, 100.0f));
    BtnSprite btnSprite;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if ((event.type == Event::KeyPressed) && (event.key.code = Keyboard::Escape))
                window.close();

            btnSprite.atualiza(event, sf::Mouse::getPosition(window));
            btnSair->atualiza(event);

        }
        window.clear(Color(0, 0, 0));
        window.draw(btnSprite.getSprite());
        window.draw(btnSair->getDrawButton());
        window.display();
    }
    return 0;
};
