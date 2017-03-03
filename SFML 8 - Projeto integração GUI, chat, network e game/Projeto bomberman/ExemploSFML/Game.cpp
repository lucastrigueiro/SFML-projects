#include "Game.h"

Game::Game(string Title, Uint32 Style){
	mWindow.create(VideoMode(611, 662), Title);// , Style::Close);

    if (!music.openFromFile("audio/sonic.ogg"))
        mWindow.close();//Sair

    view = View(sf::FloatRect(0, 0, 832, 578));
    //view = mWindow.getDefaultView();
	view.setViewport(sf::FloatRect(0.0f, 0.0, 1.f, 0.64f));

    unidadeMapa = Vector2u(64,64);
    dimensaoMapa = Vector2u(13,9);

    // Arquivo_Imagem, pixels(largura, altura), array, largura_array, altura_array
    if (!mapa.load("imagem/tilemaps64.png", unidadeMapa,level, dimensaoMapa)){
        mWindow.close();//Sair
    }

	msg = "";
    mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = mKeySpace = false;
};

void Game::run(){
	//Inicia widgets
	tgui::Gui gui(mWindow);
	try
	{
		// Carrega widgets
		loadWidgets(gui);
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
		cout << "Falha ao carregar widgets" << endl;
		mWindow.close();
	}

	//Aguarda o usuario conectar ao servidor
	flagConectar = false;//Inicia flag de status da conexao
	while (!flagConectar) {
		Event event;
		while (mWindow.pollEvent(event)) {
			if (event.type == Event::Closed)
				mWindow.close();
			gui.handleEvent(event);
		};
		gui.draw();
		mWindow.display();
	}

	//Conecta ao servidor
	IpAddress ip = IpAddress().getLocalAddress();
	if (client.connect(ip, 53000) != sf::Socket::Done)
	{
		// Erro
		cout << "Falha ao conectar ao servidor" << endl;
		mWindow.close();
	}
	sf::Packet packet;
	client.receive(packet);
	packet >> id;
	cout << "Player "<< id<< endl;
	
	bomba.setPosition(Vector2f(500, 256));
	//Posicao inicial
	if (id == 1) {
		personagem.setPosition(Vector2f(400, 256));
		personagem2.setPosition(Vector2f(450, 256));
	}else {
		personagem2.setPosition(Vector2f(400, 256));
		personagem.setPosition(Vector2f(450, 256));
	}
	explosao.setPosition(Vector2f(256, 256));
	// create a thread with func() as entry point
	sf::Thread thread(&Game::leitura_servidor,this);

	// run it
	thread.launch();

	//Inicia o jogo
	//music.play();
    while(mWindow.isOpen()){
        processEvents(gui);
        update();
        render(gui);
    }
};

void Game::leitura_servidor()
{
	sf::Packet packet;
	// thread que recebe valores do servidor
	int recebido_id;
	Vector2f recebido_movi;
	string recebido_msg;
	Vector2f pos_bomba(0.f, 0.f);
	flag_explosao = false;
	flag_explosao2 = false;
	int cont, cont2;
	cont = 0;
	cont2 = 0;
	while (true) {
		packet.clear();
		client.receive(packet);
		packet >> recebido_id >> recebido_movi.x >> recebido_movi.y >> recebido_msg >> pos_bomba.x >> pos_bomba.y;
		if (id != recebido_id) {
			personagem2.mover(recebido_movi, 0.25f);
			if (recebido_msg != "") {
				chatbox->addLine("Oponente: "+recebido_msg, sf::Color::Magenta);
			}
			if (pos_bomba.x != -1.f) {
				bomba2.disparar(pos_bomba);
				explosao2.setPosition(pos_bomba);
				flag_explosao2 = true;
			}
		}
		bomba.explodir();
		bomba2.explodir();
		if (flag_explosao && !bomba.getAtiva()) {
			cont++;
			if (cont == 150) {
				cont = 0;
				flag_explosao = false;
			}
		}
		if (flag_explosao2 && !bomba2.getAtiva()) {
			cont2++;
			if (cont2 == 150) {
				cont2 = 0;
				flag_explosao2 = false;
			}
		}
	}
}

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

void Game::processEvents(tgui::Gui& gui){
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
		gui.handleEvent(event);
    };
}

bool Game::verificaValor(int val){
if(val != 2 && val != 3 && val != 4 && val != 19 && val != 18 && val != 20 && val != 34 && val != 35 && val != 36)
        return true;
    return false;
}

bool Game::validaPosicao(Vector2f pos1, Vector2f pos2){
    int val;
    Vector2i posicao;
	Vector2f posicao_personagem;
	posicao_personagem.x = personagem.getSprite().getPosition().x;
	posicao_personagem.y = personagem.getSprite().getPosition().y;

	if (pos1.x+ posicao_personagem.x < 0 || pos1.x+ posicao_personagem.x > dimensaoMapa.x * unidadeMapa.x || 
		pos1.y+ posicao_personagem.y < 0 || pos1.y+ posicao_personagem.y > dimensaoMapa.y * unidadeMapa.y)
		return false;

    posicao.x = (pos1.x + posicao_personagem.x)/unidadeMapa.x;
    posicao.y = (pos1.y + posicao_personagem.y)/unidadeMapa.y;
	val = level[posicao.x + posicao.y * dimensaoMapa.x];

    if(verificaValor(val))
        return false;

    posicao.x = (pos2.x + posicao_personagem.x)/unidadeMapa.x;
    posicao.y = (pos2.y + posicao_personagem.y)/unidadeMapa.y;
	val = level[posicao.x + posicao.y * dimensaoMapa.x];

    if(verificaValor(val))
        return false;

    return true;
}

void Game::update() {
	Vector2f pos_bomba(-1.f, -1.f);
	if (mKeySpace && !bomba.getAtiva()) {
		pos_bomba.x = (personagem.getSprite().getPosition().x + personagem.getLargura() / 2);
		pos_bomba.x -= (int)pos_bomba.x % unidadeMapa.x;
		pos_bomba.y = (personagem.getSprite().getPosition().y + personagem.getAltura() / 2);
		pos_bomba.y -= (int)pos_bomba.y % unidadeMapa.y;
		bomba.disparar(pos_bomba);
		explosao.setPosition(pos_bomba);
		flag_explosao = true;
	}
    
	float passo = 0.25;
    Vector2f movement(0.f, 0.f);
    Vector2f pos1, pos2;

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
	sf::Packet packet;
	packet << id << movement.x << movement.y << msg << pos_bomba.x << pos_bomba.y;
	client.send(packet);
	msg = "";
};

void Game::render(tgui::Gui& gui) {
	mWindow.clear();
	mWindow.draw(mapa);
	if (bomba.getAtiva())
		mWindow.draw(bomba.getSprite());
	if (bomba2.getAtiva())
		mWindow.draw(bomba2.getSprite());
	if (flag_explosao && !bomba.getAtiva())
		drawExplosao(explosao);
	if (flag_explosao2 && !bomba2.getAtiva())
		drawExplosao(explosao2);
    mWindow.draw(personagem.getSprite());
	mWindow.draw(personagem2.getSprite());
    mWindow.setView(view);
	gui.draw();
	mWindow.display();

};

void Game::drawExplosao(Explosao e) {
	mWindow.draw(e.getSprite(0));
	if ((int)(e.getSprite(0).getPosition().x / unidadeMapa.x) % 2 == 0) {
		mWindow.draw(e.getSprite(1));
		mWindow.draw(e.getSprite(2));
	}
	if ((int)(e.getSprite(0).getPosition().y / unidadeMapa.y) % 2 == 0) {
		mWindow.draw(e.getSprite(3));
		mWindow.draw(e.getSprite(4));
	}
}

void conectar(bool *flag)
{
	//Seta flag que permite conexao
	*flag = true;
}

void enviar(tgui::EditBox::Ptr mensagem, tgui::ChatBox::Ptr chatbox, bool *flag, string *msg)
{
	if (mensagem->getText().toAnsiString() != "" && *flag==true) {
		//add a mensagem ao chat
		chatbox->addLine("Você: " + mensagem->getText().toAnsiString(), sf::Color::White);
		//prepara a variavel de envio
		*msg = mensagem->getText().toAnsiString();
		//limpa o campo de texto
		mensagem->setText("");
	}
}

void Game::loadWidgets(tgui::Gui& gui)
{
	// Carrega o black theme
	auto theme = std::make_shared<tgui::Theme>("imagem/Black.txt");

	// Pega a largura e a altura atual da janela
	// Para passar os valores em proporcao e assim adequar ao redimensionamento
	auto windowWidth = tgui::bindWidth(gui);
	auto windowHeight = tgui::bindHeight(gui);

	// Cria a label mensagem
	tgui::Label::Ptr lblMensagem = theme->load("Label");
	lblMensagem->setText("Mensagem");
	lblMensagem->setPosition(windowWidth * 3 / 10, windowHeight * 4.05 / 6);
	lblMensagem->setTextColor(sf::Color(190, 190, 190));
	lblMensagem->setTextSize(22);
	gui.add(lblMensagem);

	// Cria o campo de mensagem
	tgui::EditBox::Ptr editMensagem = theme->load("EditBox");
	editMensagem->setSize(windowWidth * 6.7 / 10, windowHeight / 20);
	editMensagem->setPosition(windowWidth * 3 / 10, windowHeight * 4.4 / 6);
	editMensagem->setDefaultText("Digite seu mensagem aqui");
	gui.add(editMensagem, "Mensagem");

	// Cria o botao enviar
	tgui::Button::Ptr btnEnviar = theme->load("Button");
	btnEnviar->setSize(windowWidth * 5 / 20, windowHeight / 20);
	btnEnviar->setPosition(windowWidth / 34, windowHeight * 4.4 / 6);
	btnEnviar->setText("Enviar");
	gui.add(btnEnviar);

	// Cria o botao conectar
	tgui::Button::Ptr btnConectar = theme->load("Button");
	btnConectar->setSize(windowWidth * 5 / 20, windowHeight / 20);
	btnConectar->setPosition(windowWidth / 34, windowHeight * 3.95 / 6);
	btnConectar->setText("Conectar");
	gui.add(btnConectar);

	// Cria a label historico
	tgui::Label::Ptr lblHistorico = theme->load("Label");
	lblHistorico->setText("Histórico");
	lblHistorico->setPosition(windowWidth / 34, windowHeight * 4.75 / 6);
	lblHistorico->setTextColor(sf::Color(190, 190, 190));
	lblHistorico->setTextSize(22);
	gui.add(lblHistorico);

	//Cria o campo do historico do chat
	chatbox = theme->load("ChatBox");
	chatbox->setSize(windowWidth * 9.4 / 10, windowHeight / 6.6);
	chatbox->setTextSize(20);
	chatbox->setPosition(windowWidth / 34, windowHeight * 5 / 6);
	gui.add(chatbox);

	// Chama a funcao enviar mensagem quando for pressionado
	btnEnviar->connect("pressed", enviar, editMensagem, chatbox, &flagConectar, &msg);


	// Chama a funcao de conectar quando for pressionado
	btnConectar->connect("pressed", conectar, &flagConectar);
}

Game::~Game() { };
