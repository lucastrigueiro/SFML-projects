#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>
#include "Dragao.h"
#include "Careca.h"
#include "Bomb.h"
#include "Explosao.h"
#include "TileMap.h"

using namespace sf;
using namespace std;

class Game{
public:
    Game (string Title, Uint32 Style);
    ~Game();
    void run();

private:
    void handlePlayerInput(Keyboard::Key key, bool isPressed);
	void processEvents(tgui::Gui& gui);
    void update();
    void render(tgui::Gui& gui);
    
	// define o level com os valores para os tilemaps
    const int level[117] =
    {
         02,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  03,  04,
         18,  52,  19,  52,  19,  52,  19,  52,  19,  52,  19,  52,  20,
         18,  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,  20,
		 18,  52,  19,  52,  19,  52,  19,  52,  19,  52,  19,  52,  20,
		 18,  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,  20,
		 18,  52,  19,  52,  19,  52,  19,  52,  19,  52,  19,  52,  20,
		 18,  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,  20,
		 18,  52,  19,  52,  19,  52,  19,  52,  19,  52,  19,  52,  20,
		 34,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  36,
    };

    bool validaPosicao(Vector2f pos1, Vector2f pos2); //Controla se o personagem tentar acessar uma posicao nao permitida
    RenderWindow mWindow;	//Janela
    View view;				//Visao do jogo
    Careca personagem;		//Personagem utilizado
	Careca personagem2;		//Personagem oponente
    TileMap mapa;			//Mapa do jogo
    Vector2u unidadeMapa;	//Quantidade de pixels de uma unidade do tilemap (x,y)
    Vector2u dimensaoMapa;	//Quantidade de tilemaps nas dimensoes (x,y)
    bool verificaValor(int val);		//Verifica se a posição atual do personagem deve acionar algum evento
    sf::Music music;		//Musica do jogo
	void loadWidgets(tgui::Gui& gui);	//Carrega os widgets
	tgui::ChatBox::Ptr chatbox;			//Variavel globo do chatbox
	bool flagConectar;		//Flag que aguarda conexao para iniciar o jogo
	string msg;				//Variavel que guarda a mensagem a ser enviada no chat
	sf::TcpSocket client;
	void Game::leitura_servidor();
	int id;					// id do usuario no servidor
	Bomb bomba, bomba2;
	Explosao explosao, explosao2;
	bool flag_explosao, flag_explosao2;
	void Game::drawExplosao(Explosao e);

protected:
    bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight, mKeySpace;
};
