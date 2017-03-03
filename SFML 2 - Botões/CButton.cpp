#include "CButton.h"

Button::Button(String normalTex, String clickedTex, Vector2f location)
{
    try
    {
        if (! aux.loadFromFile(normalTex) )
            cout << "Erro de carregamento de arquivo";
        this->normal.setTexture(aux);

        if (!aux2.loadFromFile(clickedTex))
            cout << "Erro de carregamento de arquivo";

        this->clicked.setTexture(aux2);

        this->normal.setPosition(location);
        this->clicked.setPosition(location);

        setState(false);

    }
    catch (int e)
    {
        cout << "Error";
    };


};

void Button::checkClick(Vector2f mousePos)
{
    int width = currentSpr.getGlobalBounds().width;
    int height = currentSpr.getGlobalBounds().height;

    if (mousePos.x>currentSpr.getPosition().x && mousePos.x<(currentSpr.getPosition().x + width))
    {
        if (mousePos.y>currentSpr.getPosition().y && mousePos.y<(currentSpr.getPosition().y +height))
        {
            setState(!current);
        }
    }
};

void Button::atualiza(Event event){
    if (event.type == sf::Event::MouseButtonPressed)
        if (event.mouseButton.button == sf::Mouse::Right)
            checkClick(Vector2f(event.mouseButton.x, event.mouseButton.y));
}

void Button::setState(bool which)
{
    current = which;
    if (current)
    {
        currentSpr = clicked;
        return;
    }
    currentSpr = normal;
};
