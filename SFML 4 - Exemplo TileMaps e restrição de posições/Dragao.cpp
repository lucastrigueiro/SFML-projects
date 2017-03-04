#include "Dragao.h"

Dragao::Dragao(){
    dimensoes = Vector2u(105, 106);
    texture = Texture();
    texture.loadFromFile("dragon.png");
    rectSourceSprite = IntRect(0, 0, dimensoes.x, dimensoes.y);
    sprite = Sprite(texture, rectSourceSprite);
    flag = 0;
};

void Dragao::mover(Vector2f movimento, int passo){

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
        if(flag == 5){
            rectSourceSprite.left = (rectSourceSprite.left >= dimensoes.x*2) ? (0) : (rectSourceSprite.left += dimensoes.x);
            flag=0;
        }
        sprite.setTextureRect(rectSourceSprite);
        sprite.move(movimento);
    }

};

void Dragao::setPosition(Vector2f posicao){
    sprite.setPosition(posicao);
}

Sprite Dragao::getSprite(){
    return sprite;
}

int Dragao::getAltura(){
    return dimensoes.y;
}

int Dragao::getLargura(){
    return dimensoes.x;
}
Dragao::~Dragao() { };
