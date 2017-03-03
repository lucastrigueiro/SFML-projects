#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>


using namespace sf;
using namespace std;


class Palhaco{
public:
    Palhaco();
    CircleShape cabeca;
    RectangleShape tronco;
    CircleShape chapeu;
    RectangleShape bracoE;
    RectangleShape bracoD;
    CircleShape peE;
    CircleShape peD;
    void mover(Vector2f movimento);
    void mudarTamanho();
    ~Palhaco();

private:
    float tamanho;
    float tamanhoRef = 200;
};
