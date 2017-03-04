#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    const int level[357] =
    {
         00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,
         00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  96,  97,  98,  00,  00,  00,  00,  00,  00,  00,  00,
         00,  00,  00,  00,  00,  00,  00,  00,  00,  00, 112, 113, 114,  00,   8,  00,  00,  00,  00,  00,  00,
         00,  00,  00,  00,  00,  00,  00,  00,  02,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,
         00,  00,  00,  00,  00,  00,  00,  00,  18,  19,  35,  35,  35,  35, 153,  35,  35,  35,  35,  35,  35,
         00,  00,  00,  00,  00,  00,  00,  00,  18,  20,  24,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,
         33,  33,  33,  33,  33,  00,  00,  00,  18,  20,  00,  00,  00,  00, 00,  00,  00,  00,  00,  00,  00,
        128, 129, 130, 131,  33,  00,  00,  00,  18,  20,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00, 154,  20,  00,  00,  83,  83,  83,  83,  83,  83,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00,  18,  20,  00,  00,  99,  99,  99,  99,  99,  99,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00,  18,  20,  00,  00, 115, 115, 115, 115, 115, 115,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00,  18,  19,  03,  03,  03, 155,  03,  03,  03,  04,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00,  34,  35,  35,  35,  35,  35,  35,  35,  35,  36,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,
        144, 145, 146, 147,  33,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,  00,
    };

    bool validaPosicao(Vector2i pos1, Vector2i pos2);

    RenderWindow mWindow;
    View view, minimapView;
    Careca personagem;
    TileMap mapa;
    Vector2u unidadeMapa;
    Vector2u dimensaoMapa;
    Game game();
    bool verificaValor(int val);
    int flag_som;
    sf::SoundBuffer som_pato;
    sf::SoundBuffer som_boi;
    sf::SoundBuffer som_cabra;
    sf::Sound sound;
    sf::Music music;

protected:
    bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mKeySpace;
};
