#include "Game.h"

Game::Game(string Title, Uint32 Style){
    mWindow.create(VideoMode(1024, 704), Title,Style::Close);

    movement = Vector2f(0.f, 0.f);
    passo = 4;

    unidadeMapa = Vector2u(32,32);
    dimensaoMapa = Vector2u(32,22);

    // Arquivo_Imagem, pixels(largura, altura), array, largura_0.f, 0.f)array, altura_array
    if (!mapa.load("tilemaps32.png", unidadeMapa,level, dimensaoMapa)){
        mWindow.close();//Sair
    }



    //Posicao inicial
    personagem.setPosition(Vector2f(486,221));
    caixa.setPosition(Vector2f(586,421));

    mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = mKeySpace = false;
};

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
};

void Game::handlePlayerInput(Keyboard::Key key, bool isPressed){
    if(key == Keyboard::Up)
        mIsMovingUp = isPressed;
    else if(key == Keyboard::Down)
        mIsMovingDown = isPressed;
    else if(key == Keyboard::Left)
        mIsMovingLeft = isPressed;
    else if(key == Keyboard::Right)
        mIsMovingRight = isPressed;
    else if(key == Keyboard::Escape)
        mWindow.close();
    if(key == Keyboard::Space)
        mKeySpace = isPressed;
};

void Game::processEvents(){
    Event event;
    while(mWindow.pollEvent(event)){
        switch(event.type){
        case Event::KeyPressed:
            handlePlayerInput(event.key.code,true);
            break;
        case Event::KeyReleased:
            handlePlayerInput(event.key.code,false);
            break;
        case Event::Closed:
            mWindow.close();
            break;
        }
        if(event.type == Event::Closed)
            mWindow.close();
    };
}

bool Game::verificaValor(int val){
if(val != 2 && val != 3 && val != 4 && val != 19 && val != 18 && val != 20 && val != 34 && val != 35 && val != 36
&& val != 153 && val != 154 && val != 155){
        if(val == 52)
            passo = 1;

        return true;
    }
    return false;
}

bool Game::verificaCaixa(Vector2i pos1, Vector2i pos2, Vector2i pos3){
    int val;
    Vector2i posicao;

    posicao.x = (pos1.x + personagem.getSprite().getPosition().x);
    posicao.y = (pos1.y + personagem.getSprite().getPosition().y);
    if (posicao.x>=caixa.getSprite().getPosition().x &&
        posicao.x<=(caixa.getSprite().getPosition().x+caixa.getLargura()) &&
        posicao.y>=caixa.getSprite().getPosition().y &&
        posicao.y<=(caixa.getSprite().getPosition().y+caixa.getAltura())
        )
        return true;
        //cout<<posicao.x<<" , "<<caixa.getSprite().getPosition().x<<endl;

    posicao.x = (pos2.x + personagem.getSprite().getPosition().x);
    posicao.y = (pos2.y + personagem.getSprite().getPosition().y);
    if (posicao.x>=caixa.getSprite().getPosition().x &&
        posicao.x<=(caixa.getSprite().getPosition().x+caixa.getLargura()) &&
        posicao.y>=caixa.getSprite().getPosition().y &&
        posicao.y<=(caixa.getSprite().getPosition().y+caixa.getAltura()))
        return true;
        //cout<<posicao.x<<" , "<<caixa.getSprite().getPosition().x<<endl;

    posicao.x = (pos3.x + personagem.getSprite().getPosition().x);
    posicao.y = (pos3.y + personagem.getSprite().getPosition().y);
    if (posicao.x>=caixa.getSprite().getPosition().x &&
        posicao.x<=(caixa.getSprite().getPosition().x+caixa.getLargura()) &&
        posicao.y>=caixa.getSprite().getPosition().y &&
        posicao.y<=(caixa.getSprite().getPosition().y+caixa.getAltura()))
        return true;
        //cout<<posicao.x<<" , "<<caixa.getSprite().getPosition().x<<endl;

    return false;
}

bool Game::validaPosicao(Vector2i pos1, Vector2i pos2, Vector2i pos3){
    int val;
    Vector2i posicao;

    posicao.x = (pos1.x + personagem.getSprite().getPosition().x)/unidadeMapa.x;
    posicao.y = (pos1.y + personagem.getSprite().getPosition().y)/unidadeMapa.y;
    val = level[posicao.x + posicao.y * dimensaoMapa.x];

    if(verificaValor(val))
        return false;

    posicao.x = (pos2.x + personagem.getSprite().getPosition().x)/unidadeMapa.x;
    posicao.y = (pos2.y + personagem.getSprite().getPosition().y)/unidadeMapa.y;
    val = level[posicao.x + posicao.y * dimensaoMapa.x];

    if(verificaValor(val))
        return false;

    posicao.x = (pos3.x + personagem.getSprite().getPosition().x)/unidadeMapa.x;
    posicao.y = (pos3.y + personagem.getSprite().getPosition().y)/unidadeMapa.y;
    val = level[posicao.x + posicao.y * dimensaoMapa.x];

    if(verificaValor(val))
        return false;

    return true;
}

void Game::update(){
    if(passo<4)
        passo+=0.02;

    bool movecaixa =false;

    Vector2i pos1, pos2, pos3;

    if(mIsMovingUp){
        movement.y=-passo;
        movement.x=0;
    }else if(mIsMovingDown){
        movement.y=passo;
        movement.x=0;
    }else if(mIsMovingLeft){
        movement.y=0;
        movement.x=-passo;
    }else if(mIsMovingRight){
        movement.y=0;
        movement.x=passo;
    }

    if(movement.y<01){
        pos1.x = personagem.getLargura()*1/3;
        pos1.y = -passo;
        pos2.x = personagem.getLargura()*2/3;
        pos2.y = -passo;
        pos3.x = personagem.getLargura()/2;
        pos3.y = -passo;
        if(!validaPosicao(pos1, pos2, pos3))
            movement.y *= -1;
        else if(verificaCaixa(pos1, pos2, pos3))
            movecaixa = true;
    }
    if(movement.y>0){
        pos1.x = personagem.getLargura()*1/3;
        pos1.y = personagem.getAltura() + passo;
        pos2.x = personagem.getLargura()*2/3;
        pos2.y = personagem.getAltura() + passo;
        pos3.x = personagem.getLargura()/2;
        pos3.y = personagem.getAltura() + passo;
        if(!validaPosicao(pos1, pos2, pos3))
            movement.y *= -1;
        else if(verificaCaixa(pos1, pos2, pos3))
            movecaixa = true;
    }
    if(movement.x<0){
        pos1.x = -passo;
        pos1.y = personagem.getAltura()*1/3;
        pos2.x = -passo;
        pos2.y = personagem.getAltura()*2/3;
        pos3.x = -passo;
        pos3.y = personagem.getAltura()/2;
        if(!validaPosicao(pos1, pos2, pos3))
            movement.x *= -1;
        else if(verificaCaixa(pos1, pos2, pos3))
            movecaixa = true;
    }
    if(movement.x>0){
        pos1.x = personagem.getLargura() + passo;
        pos1.y = personagem.getAltura()*1/3;
        pos2.x = personagem.getLargura() + passo;
        pos2.y = personagem.getAltura()*2/3;
        pos3.x = personagem.getLargura() + passo;
        pos3.y = personagem.getAltura()/2;
        if(!validaPosicao(pos1, pos2, pos3))
            movement.x *= -1;
        else if(verificaCaixa(pos1, pos2, pos3))
            movecaixa = true;
    }

    if(movement.x!=0 && (movement.x!=passo||movement.x!=-passo))
        movement.x = (movement.x>0) ? (passo) : (-passo);
    if(movement.y!=0 && (movement.y!=passo||movement.y!=-passo))
        movement.y = (movement.y>0) ? (passo) : (-passo);

    //cout<<personagem.getSprite().getPosition().x<<","<<personagem.getSprite().getPosition().y<<endl;
    personagem.mover(movement, passo);
    if(movecaixa)
        caixa.mover(movement, passo);
    //view.move(movement);
};

void Game::render(){
    mWindow.clear();
    mWindow.draw(mapa);
    mWindow.draw(personagem.getSprite());
    mWindow.draw(caixa.getSprite());
    //mWindow.setView(view);
    mWindow.display();

};

Game::~Game() { };
