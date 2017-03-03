#include "Explosao.h"

Explosao::Explosao(){
    dimensoes = Vector2u(32, 32);

    texture = Texture();
    texture.loadFromFile("imagem/explosao.png");
    rectSourceSprite = IntRect(0, 0, dimensoes.x, dimensoes.y);
	
	rectSourceSprite.top = dimensoes.y * 3;
	sprite[0] = Sprite(texture, rectSourceSprite);
	sprite[0].setScale(Vector2f(2,2));
	
	rectSourceSprite.left = dimensoes.x * 3;
	sprite[1] = Sprite(texture, rectSourceSprite);
	sprite[1].setScale(Vector2f(2, 2));

	rectSourceSprite.left = dimensoes.x * 4;
	sprite[2] = Sprite(texture, rectSourceSprite);
	sprite[2].setScale(Vector2f(2, 2));

	rectSourceSprite.left = dimensoes.x * 5;
	sprite[3] = Sprite(texture, rectSourceSprite);
	sprite[3].setScale(Vector2f(2, 2));

	rectSourceSprite.left = dimensoes.x * 6;
	sprite[4] = Sprite(texture, rectSourceSprite);
	sprite[4].setScale(Vector2f(2, 2));

    flag = 0;
};

void Explosao::mover(Vector2f movimento, float passo){

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
        //sprite.setTextureRect(rectSourceSprite);
        //sprite.move(movimento);
    }

};

void Explosao::setPosition(Vector2f p){
	sprite[0].setPosition(p);
	sprite[1].setPosition(p.x, p.y - 64);
	sprite[2].setPosition(p.x, p.y + 64);
	sprite[3].setPosition(p.x + 64, p.y);
	sprite[4].setPosition(p.x - 64, p.y);
}

Sprite Explosao::getSprite(int n){
    return sprite[n];
}

int Explosao::getAltura(){
    return dimensoes.y*2;
}

int Explosao::getLargura(){
    return dimensoes.x*2;
}

Explosao::~Explosao() { };
