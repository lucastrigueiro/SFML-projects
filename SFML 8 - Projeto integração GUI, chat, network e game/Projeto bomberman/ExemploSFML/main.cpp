#include "Game.h"

int main(int ArgC, char** ArgV)
{
    Game game("Jogo com TGUI", Style::Default);
    game.run();
    return 0;
}
