#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Personagem.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	char connectionType;
	sf::Packet packet;
	float passo = 0.25;
	cout << "Enter (s) for Server, Enter (c) for client" << endl;
	cin >> connectionType;
	string st;
	if (connectionType == 's') {
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		st = "Servidor";
	}
	else {
		socket.connect(ip, 2000);
		st = "Cliente";
	}
	sf::RenderWindow window(sf::VideoMode(600, 400, 32), st);

	Personagem personagem1(connectionType == 's');
	Personagem personagem2(connectionType != 's');
	
	if (connectionType == 's') {
		personagem1.setPosition(sf::Vector2f(0, 0));
		personagem2.setPosition(sf::Vector2f(350, 0));
	}
	else {
		personagem1.setPosition(sf::Vector2f(350, 0));
		personagem2.setPosition(sf::Vector2f(0, 0));
	}

	sf::Vector2f prevPosition, p2Position;

	socket.setBlocking(false);

	bool update = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				window.close();
			else if (event.type == sf::Event::GainedFocus)
				update = true;
			else if (event.type == sf::Event::LostFocus)
				update = false;
		}

		if (update) {

			prevPosition = personagem1.getSprite().getPosition();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				personagem1.mover(sf::Vector2f(1.0f, 0.0f), passo);
				packet << 1.0f << 0.0f;
				socket.send(packet);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				personagem1.mover(sf::Vector2f(-1.0f, 0.0f), passo);
				packet << -1.0f << 0.0f;
				socket.send(packet);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				personagem1.mover(sf::Vector2f(0.0f, -1.0f), passo);
				packet << 0.0f << -1.0f;
				socket.send(packet);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				personagem1.mover(sf::Vector2f(0.0f, 1.0f), passo);
				packet << 0.0f << 1.0f;
				socket.send(packet);
			}
		}

		//if(prevPosition.x != personagem1.getSprite().getPosition().x  || prevPosition.y != personagem1.getSprite().getPosition().y){
			//packet << personagem1.getSprite().getPosition().x << personagem1.getSprite().getPosition().y;
			//socket.send(packet);
		//}
		socket.receive(packet);
		if (packet >> p2Position.x >> p2Position.y) {
			personagem2.mover(p2Position, passo);
			//cout << "(" << p2Position.x << "," << p2Position.y << ")" << endl;
		}

		window.clear();
		window.draw(personagem1.getSprite());
		window.draw(personagem2.getSprite());

		window.display();

	}
	system("pause");
	return 0;
}
