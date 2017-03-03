#include "Careca.h"

Careca::Careca(){
    dimensoes = Vector2u(52, 70);

    texture = Texture();
    texture.loadFromFile("imagem/careca.png");
    rectSourceSprite = IntRect(0, 0, dimensoes.x, dimensoes.y);
    sprite = Sprite(texture, rectSourceSprite);
	sprite.setScale(Vector2f(0.8,0.8));
    flag = 0;
};

void Careca::mover(Vector2f movimento, float passo){

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
        if(flag == 30){
            rectSourceSprite.left = (rectSourceSprite.left >= dimensoes.x*7) ? (0) : (rectSourceSprite.left += dimensoes.x);
            flag=0;
        }
        sprite.setTextureRect(rectSourceSprite);
        sprite.move(movimento);
    }

};

void Careca::setPosition(Vector2f posicao){
    sprite.setPosition(posicao);
}

Sprite Careca::getSprite(){
    return sprite;
}

int Careca::getAltura(){
    return dimensoes.y*0.8;
}

int Careca::getLargura(){
    return dimensoes.x*0.8;
}

Careca::~Careca() { };
