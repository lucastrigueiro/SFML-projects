#pragma once
#include <SFML/Graphics.hpp>
#include "Dragao.h"
#include "Careca.h"
#include "TileMap.h"

using namespace sf;
using namespace std;

class Game{
public:
    Game();
    Game (string Title, Uint32 Style);
    ~Game();
    void run();

private:
    void handlePlayerInput(Keyboard::Key key, bool isPressed);
    void processEvents();
    void update();
    void render();
    // define the level with an array of tile indices
    const int level[128] =
    {
         00,  00,  00,  00,  00,  00,  00,  00,  00,  96,  97,  98,  00,  00,  00,  00,
         00,   8,  00,  00,  00,  00,  00,  00,  00, 112, 113, 114,  00,  00,  00,  00,
         03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,
         35,  35,  35,  35,  35,  35,  35,  19,  19,  35,  35,  35,  35,  35,  35,  35,
         00,  00,  00,  00,  00,  00,  24,  18,  20,  00,  00,  00,  00,  00,  00,  00,
         33,  33,  33,  33,  33,  00,  00,  18,  20,  00,  00,  33,  33,  33,  33,  33,
        128, 129, 130, 131,  33,  00,  00,  18,  20,  00,  00,  33, 128, 129, 130, 131,
        144, 145, 146, 147,  33,  00,  00,  18,  20,  00,  00,  33, 144, 145, 146, 147,
    };

    bool validaPosicao(Vector2i pos1, Vector2i pos2);

    RenderWindow mWindow;
    Careca personagem;
    TileMap mapa;
    Vector2u unidadeMapa;
    Vector2u dimensaoMapa;
    Game game();

protected:
    bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
};
