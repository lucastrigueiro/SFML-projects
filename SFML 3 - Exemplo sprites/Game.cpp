#include "Game.h"

Game::Game(){
    mWindow.create(VideoMode(640, 480), "");
};

Game::Game(string Title, Uint32 Style){
    mWindow.create(VideoMode(640,480), Title, Style);
    //palhaco();

    linha1 = RectangleShape(sf::Vector2f(560, 1.5));
    linha1.rotate(55);
    linha1.setPosition(320.f, 0.f);

    linha2 = RectangleShape(sf::Vector2f(560, 1.5));
    linha2.rotate(125);
    linha2.setPosition(320.f, 0.f);


    mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = true;
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
            handlePlayerInput(event.key.code,false);
            break;
        case Event::KeyReleased:
            handlePlayerInput(event.key.code,true);
            break;
        case Event::Closed:
            mWindow.close();
            break;
        }
        if(event.type == Event::Closed)
            mWindow.close();
    };
}

void Game::update(){
    Vector2f movement(0.f, 0.f);
    if(mIsMovingUp)
        movement.y += 3.f;
    if(mIsMovingDown)
        movement.y -= 3.f;
    if(mIsMovingLeft)
        movement.x += 3.f;
    if(mIsMovingRight)
        movement.x -= 3.f;

    dragao.mover(movement);
    mWindow.display();
};

void Game::render(){
    mWindow.clear();
    mWindow.draw(dragao.getSprite());
    mWindow.display();

};

Game::~Game() { };
