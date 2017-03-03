#include "Caixa.h"

Caixa::Caixa(){
    escala = Vector2f(0.5, 0.5);
    dimensoes = Vector2u(82, 82);
    texture = Texture();
    texture.loadFromFile("box.png");
    rectSourceSprite = IntRect(0, 0, dimensoes.x, dimensoes.y);
    sprite = Sprite(texture, rectSourceSprite);
    sprite.setScale(escala);
    flag = 0;
};

void Caixa::mover(Vector2f movimento, float passo){

    if((movimento.y!=0)  ||  (movimento.x!=0)){


        //sprite.setTextureRect(rectSourceSprite);
        sprite.move(movimento);
    }

};

void Caixa::setPosition(Vector2f posicao){
    sprite.setPosition(posicao);
}

Sprite Caixa::getSprite(){
    return sprite;
}

int Caixa::getAltura(){
    return dimensoes.y * escala.y;
}

int Caixa::getLargura(){
    return dimensoes.x * escala.x;
}

Caixa::~Caixa() { };
