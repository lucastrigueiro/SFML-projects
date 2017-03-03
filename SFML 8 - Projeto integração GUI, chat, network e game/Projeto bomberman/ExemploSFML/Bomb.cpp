#include "Bomb.h"

Bomb::Bomb(){
    dimensoes = Vector2u(128, 128);
	ativa = false;
    texture = Texture();
    texture.loadFromFile("imagem/Bomb.png");
    rectSourceSprite = IntRect(0, 0, dimensoes.x, dimensoes.y);
    sprite = Sprite(texture, rectSourceSprite);
	sprite.setScale(Vector2f(0.5,0.5));
    flag = 0;
	if (!som_bomba.loadFromFile("audio/bomba.ogg")) {
		cout << "Falha ao carregar o som da bomba" << endl;
	}
};

void Bomb::disparar(Vector2f pos_bomba){
	if (flag == 0) {
		ativa = true;
		this->setPosition(pos_bomba);
	}
};

void Bomb::explodir() {
	if (ativa) {
		flag++;
		if (flag % 200 == 0) {
			rectSourceSprite.left = (rectSourceSprite.left >= dimensoes.x * 2) ? (0) : (rectSourceSprite.left += dimensoes.x);
			if (flag == 1200) {
				ativa = false;
				flag = 0;
				sound.setBuffer(som_bomba);
				sound.play();
			}
			sprite.setTextureRect(rectSourceSprite);
		}
	}
}

void Bomb::setPosition(Vector2f posicao){
    sprite.setPosition(posicao);
}

Sprite Bomb::getSprite(){
    return sprite;
}

int Bomb::getAltura(){
    return dimensoes.y*0.5;
}

int Bomb::getLargura(){
    return dimensoes.x*0.5;
}

bool Bomb::getAtiva() {
	return ativa;
}

Bomb::~Bomb() { };
