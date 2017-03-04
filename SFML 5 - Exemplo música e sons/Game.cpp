#include "Game.h"

Game::Game(string Title, Uint32 Style){
    mWindow.create(VideoMode(1024, 512), Title,Style::Close);

    if (!som_pato.loadFromFile("audio/pato_divertido.ogg")){
        mWindow.close();//Sair
    }
    if (!som_boi.loadFromFile("audio/som_de_boi.ogg")){
        mWindow.close();//Sair
    }
    if (!som_cabra.loadFromFile("audio/cabra_gritando.ogg")){
        mWindow.close();//Sair
    }
    flag_som=0;

    if (!music.openFromFile("audio/sonic.ogg"))
        mWindow.close();//Sair
    music.play();

    //view = View(sf::FloatRect(0, 0, 1024, 512));
    view = mWindow.getDefaultView();

    unidadeMapa = Vector2u(64,64);
    dimensaoMapa = Vector2u(21,17);

    // Arquivo_Imagem, pixels(largura, altura), array, largura_array, altura_array
    if (!mapa.load("tilemaps64.png", unidadeMapa,level, dimensaoMapa)){
        mWindow.close();//Sair
    }



    //Posicao inicial
    personagem.setPosition(Vector2f(486,221));

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
&& val != 153 && val != 154 && val != 155)
        return true;
    if(val == 153 && flag_som!=1){
        sound.setBuffer(som_pato);
        sound.play();
        flag_som=1;
    }else if(val == 155 && flag_som!=2){
        sound.setBuffer(som_boi);
        sound.play();
        flag_som=2;
    }else if(val == 154 && flag_som!=3){
        sound.setBuffer(som_cabra);
        sound.play();
        flag_som=3;
    }else{
        flag_som=0;
    }
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
    int passo;
    if(mKeySpace)
        passo = 7;
    else
        passo = 3;
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

    //cout<<personagem.getSprite().getPosition().x<<","<<personagem.getSprite().getPosition().y<<endl;
    personagem.mover(movement, passo);
    view.move(movement);
    mWindow.display();
};

void Game::render(){
    mWindow.clear();
    mWindow.draw(mapa);
    mWindow.draw(personagem.getSprite());
    mWindow.setView(view);
    mWindow.display();

};

Game::~Game() { };
