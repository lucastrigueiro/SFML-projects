#include "BtnSprite.h"

BtnSprite::BtnSprite()
{

    myTexture = Texture();

    if (!myTexture.loadFromFile("mapaObjetos.png"))
        cout << "Erro de carregamento de arquivo";
    myTexture.setSmooth(true);
    rectSourceSprite = IntRect(0, 0, 201, 71);
    sprite = Sprite(myTexture, rectSourceSprite);
    sprite.setPosition(Vector2f(80.0f, 150.0f));

    flag = 0;
};


bool BtnSprite::verificaPosicao(Vector2i position)
{

    int width = sprite.getGlobalBounds().width;
    int height = sprite.getGlobalBounds().height;

    if (position.x>sprite.getPosition().x && position.x<(sprite.getPosition().x + width))
    {
        if (position.y>sprite.getPosition().y && position.y<(sprite.getPosition().y +height))
        {
            return true;
        }
    }
    return false;
}

void BtnSprite::atualiza(Event event, Vector2i mousePosition)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            if(verificaPosicao(mousePosition)){
                rectSourceSprite.top = 142;
                flag=1;
            }

        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            flag = 0;
            if(verificaPosicao(mousePosition))
                rectSourceSprite.top = 71;
            else
                rectSourceSprite.top = 0;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        if(flag == 0)
        {
            if(verificaPosicao(mousePosition))
                rectSourceSprite.top = 71;
            else
                rectSourceSprite.top = 0;
        }
    }
    sprite.setTextureRect(rectSourceSprite);
};

Sprite BtnSprite::getSprite()
{
    return sprite;
}

BtnSprite::~BtnSprite() { };
