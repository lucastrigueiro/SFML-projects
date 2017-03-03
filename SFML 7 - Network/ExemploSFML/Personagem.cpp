#include "Personagem.h"

Personagem::Personagem(int n) {
	if (n) {
		dimensoes = Vector2u(105, 106);
		texture = Texture();
		texture.loadFromFile("dragon.png");
		nformas=2;
	}else{
		dimensoes = Vector2u(52, 70);
		texture = Texture();
		texture.loadFromFile("careca.png");
		nformas = 7;
	}
	rectSourceSprite = IntRect(0, 0, dimensoes.x, dimensoes.y);
	sprite = Sprite(texture, rectSourceSprite);
	flag = 0;
};

void Personagem::mover(Vector2f movimento, float passo){

    if((movimento.y!=0)  ||  (movimento.x!=0)){
		
		movimento.x *= passo;
		movimento.y *= passo;

        if(movimento.y==passo)
            rectSourceSprite.top = 0;
        else if(movimento.x==-passo)
            rectSourceSprite.top = dimensoes.y;
        else if(movimento.x==passo)
            rectSourceSprite.top = dimensoes.y*2;
        else if(movimento.y==-passo)
            rectSourceSprite.top = dimensoes.y*3;

        flag++;
        if(flag == 100){
            rectSourceSprite.left = (rectSourceSprite.left >= dimensoes.x*nformas) ? (0) : (rectSourceSprite.left += dimensoes.x);
            flag=0;
        }
        sprite.setTextureRect(rectSourceSprite);
        sprite.move(movimento);
    }

};

void Personagem::setPosition(Vector2f posicao){
    sprite.setPosition(posicao);
}

Sprite Personagem::getSprite(){
    return sprite;
}

int Personagem::getAltura(){
    return dimensoes.y;
}

int Personagem::getLargura(){
    return dimensoes.x;
}
Personagem::~Personagem() { };
