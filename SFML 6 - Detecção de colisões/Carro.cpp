#include "Carro.h"

Carro::Carro(){
    escala = Vector2f(0.5, 0.5);
    dimensoes = Vector2u(128, 96);
    texture = Texture();
    texture.loadFromFile("carro1.png");
    rectSourceSprite = IntRect(0, 0, dimensoes.x, dimensoes.y);
    sprite = Sprite(texture, rectSourceSprite);
    sprite.setScale(0.5, 0.5);
    flag = 0;
};

void Carro::mover(Vector2f movimento, float passo){

    if((movimento.y!=0)  ||  (movimento.x!=0)){


        if(movimento.y==passo)
            rectSourceSprite.top = 0;
        else if(movimento.x==-passo)
            rectSourceSprite.top = dimensoes.y;
        else if(movimento.x==passo)
            rectSourceSprite.top = dimensoes.y*2;
        else if(movimento.y==-passo)
            rectSourceSprite.top = dimensoes.y*3;

        flag++;
        if(flag == 3){
            rectSourceSprite.left = (rectSourceSprite.left >= dimensoes.x*3) ? (0) : (rectSourceSprite.left += dimensoes.x);
            flag=0;
        }
        sprite.setTextureRect(rectSourceSprite);
        sprite.move(movimento);
    }

};

void Carro::setPosition(Vector2f posicao){
    sprite.setPosition(posicao);
}

Sprite Carro::getSprite(){
    return sprite;
}

int Carro::getAltura(){
    return dimensoes.y * escala.y;
}

int Carro::getLargura(){
    return dimensoes.x * escala.x;
}

Carro::~Carro() { };
