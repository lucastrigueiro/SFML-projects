#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <list>
using namespace sf;
using namespace std;

int main() {
	int num_conexoes = 0;
	TcpSocket socket;
	IpAddress ip = IpAddress().getLocalAddress();
	int usuario;
	std::string msg = "Connectado em ...";
	char connType;
	int porta = 53000;
	char buffer[255] = "";
	size_t received;

	cout << "Servidor funcionando"<<endl;

	// Create a socket to listen to new connections
	sf::TcpListener listener;
	listener.listen(porta);
	// Create a list to store the future clients
	std::list<sf::TcpSocket*> clients;
	// Create a selector
	sf::SocketSelector selector;
	// Add the listener to the selector
	selector.add(listener);
	
	// Endless loop that waits for new connections
	while (true)
	{
		// Make the selector wait for data on any socket
		if (selector.wait())
		{
			// Test the listener
			if (selector.isReady(listener))
			{
				// The listener is ready: there is a pending connection
				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
					num_conexoes++;
					//Envia o id para o cliente
					sf::Packet packet;
					packet << num_conexoes;
					client->send(packet);
					// Add the new client to the clients list
					clients.push_back(client);
					// Add the new client to the selector so that we will
					// be notified when he sends something
					selector.add(*client);
					cout << "Cliente adicionado: Player" << num_conexoes << endl;
				}
				else
				{
					// Error, we won't get a new connection, delete the socket
					delete client;
				}
			}
			else
			{	
				// The listener socket is not ready, test all other sockets (the clients)
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
				{
					sf::TcpSocket& client = **it;	
					
					if (selector.isReady(client))
					{
						// The client has sent some data, we can receive it
						sf::Packet packet;
						if (client.receive(packet) == sf::Socket::Done)
						{

							//if (packet >> usuario >> msg) {
								//cout << "Recebido >> " << usuario << " >> " << msg << endl;
								//usuario *= usuario;
								
							//}
							for (std::list<sf::TcpSocket*>::iterator itPack = clients.begin(); itPack != clients.end(); ++itPack)
							{
								sf::TcpSocket& clientPack = **itPack;
								//packet << usuario << "Bao";
								clientPack.send(packet);
							}
							packet.clear();
						}
					}
				}
			}
		}
	}
	//*/
}
