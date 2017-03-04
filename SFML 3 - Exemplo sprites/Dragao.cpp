#include "Dragao.h"

Dragao::Dragao(){
    texture = Texture();
    texture.loadFromFile("dragon.png");
    rectSourceSprite = IntRect(0, 0, 105, 106);
    sprite = Sprite(texture, rectSourceSprite);
    flag = 0;
};

void Dragao::mover(Vector2f movimento){

    if((movimento.y!=0)  ||  (movimento.x!=0)){


        if(movimento.y==3)
            rectSourceSprite.top = 0;
        else if(movimento.x==-3)
            rectSourceSprite.top = 106;
        else if(movimento.x==3)
            rectSourceSprite.top = 212;
        else if(movimento.y==-3)
            rectSourceSprite.top = 318;

        flag++;
        if(flag == 5){
            rectSourceSprite.left = (rectSourceSprite.left >= 210) ? (0) : (rectSourceSprite.left += 105);
            flag=0;
        }
        sprite.setTextureRect(rectSourceSprite);
        sprite.move(movimento);
    }

};

Sprite Dragao::getSprite(){
    return sprite;
}

Dragao::~Dragao() { };
