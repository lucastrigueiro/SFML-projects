#include "Game.h"

Game::Game(string Title, Uint32 Style){
    mWindow.create(VideoMode(1024, 512), Title,Style::Close);

    // define the level with an array of tile indices

    unidadeMapa = Vector2u(64,64);
    dimensaoMapa = Vector2u(16,8);

    // Arquivo_Imagem, pixels(largura, altura), array, largura_array, altura_array
    if (!mapa.load("tilemaps64.png", unidadeMapa,level, dimensaoMapa)){
        mWindow.close();//Sair
    }



    //Posicao inicial
    personagem.setPosition(Vector2f(448,128));

    mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = false;
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

bool verificaValor(int val){
if(val != 3 && val != 35 && val != 19 && val != 18 && val != 20)
        return true;
    return false;
}

bool Game::validaPosicao(Vector2i pos1, Vector2i pos2){
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

    return true;
}

void Game::update(){
    int passo = 3;
    Vector2f movement(0.f, 0.f);
    Vector2i pos1, pos2;

    if(mIsMovingUp){
        pos1.x = 0;
        pos1.y = -passo;
        pos2.x = personagem.getLargura();
        pos2.y = -passo;
        if(validaPosicao(pos1, pos2))
            movement.y -= passo;
    }
    if(mIsMovingDown){
        pos1.x = 0;
        pos1.y = personagem.getAltura() + passo;
        pos2.x = personagem.getLargura();
        pos2.y = personagem.getAltura() + passo;
        if(validaPosicao(pos1, pos2))
            movement.y += passo;
    }
    if(mIsMovingLeft){
        pos1.x = -passo;
        pos1.y = 0;
        pos2.x = -passo;
        pos2.y = personagem.getAltura();;
        if(validaPosicao(pos1, pos2))
            movement.x -= passo;
    }
    if(mIsMovingRight){
        pos1.x = personagem.getLargura() + passo;
        pos1.y = 0;
        pos2.x = personagem.getLargura() + passo;
        pos2.y = personagem.getAltura();
        if(validaPosicao(pos1, pos2))
            movement.x += passo;
    }

    personagem.mover(movement, passo);
    mWindow.display();
};

void Game::render(){
    mWindow.clear();
    mWindow.draw(mapa);
    mWindow.draw(personagem.getSprite());
    mWindow.display();

};

Game::~Game() { };
