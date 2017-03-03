#include "Palhaco.h"

Palhaco::Palhaco(){
    //inicializa o tamanho
    tamanho = tamanhoRef;

    //Inicializa formas do palhaco
    chapeu = CircleShape(30,3);
    chapeu.setPosition(290.f, 155.f);
    chapeu.setFillColor(Color::Blue);

    cabeca.setRadius(30.f);
    cabeca.setPosition(290.f, 200.f);
    cabeca.setFillColor(Color::Red);

    tronco.setSize(Vector2f(40, 80));
    tronco.setPosition(300.f, 260.f);
    tronco.setFillColor(Color::Green);

    bracoD.setSize(Vector2f(25, 60));
    bracoD.setPosition(282.f, 250.f);
    bracoD.setFillColor(Color::Yellow);
    bracoD.rotate(45);

    bracoE.setSize(Vector2f(25, 60));
    bracoE.setPosition(341.f, 267.f);
    bracoE.setFillColor(Color::Yellow);
    bracoE.rotate(-45);

    peD.setRadius(14.f);
    peD.setPosition(290.f, 340.f);
    peD.setFillColor(Color::Cyan);

    peE.setRadius(14.f);
    peE.setPosition(324.f, 340.f);
    peE.setFillColor(Color::Cyan);

};

void Palhaco::mover(Vector2f movimento){
    //Verifica tamanho minimo e maximo
    if((movimento.y==-1 && tamanho==1) || (movimento.y==1 && tamanho==260))
        movimento.y=0;
    //Redimensiona caso haja movimento em Y
    if(movimento.y!=0){
        tamanho+= movimento.y;
        //Redimensiona formas
        mudarTamanho();

        //Realinha formas redimensionadas (X)
        //Usa a cabeca como referencia (Y)
        chapeu.move(Vector2f(-movimento.y*30/tamanhoRef,-movimento.y*45/tamanhoRef));
        cabeca.move(Vector2f(-movimento.y*30/tamanhoRef,0));
        tronco.move(Vector2f(-movimento.y*20/tamanhoRef,movimento.y*60/tamanhoRef));
        bracoD.move(Vector2f(-movimento.y*38/tamanhoRef,movimento.y*50/tamanhoRef));
        bracoE.move(Vector2f(movimento.y*21/tamanhoRef,movimento.y*67/tamanhoRef));
        peD.move(Vector2f(-movimento.y*30/tamanhoRef,movimento.y*140/tamanhoRef));
        peE.move(Vector2f(movimento.y*4/tamanhoRef,movimento.y*140/tamanhoRef));
    }
    //Move formas
    cabeca.move(movimento);
    tronco.move(movimento);
    chapeu.move(movimento);
    bracoD.move(movimento);
    bracoE.move(movimento);
    peD.move(movimento);
    peE.move(movimento);
};

void Palhaco::mudarTamanho(){
    cabeca.setRadius(30.f*tamanho/tamanhoRef);
    tronco.setSize(Vector2f(40*tamanho/tamanhoRef, 80*tamanho/tamanhoRef));
    chapeu.setRadius(30*tamanho/tamanhoRef);
    bracoD.setSize(Vector2f(25*tamanho/tamanhoRef, 60*tamanho/tamanhoRef));
    bracoE.setSize(Vector2f(25*tamanho/tamanhoRef, 60*tamanho/tamanhoRef));
    peD.setRadius(14.f*tamanho/tamanhoRef);
    peE.setRadius(14.f*tamanho/tamanhoRef);
};

Palhaco::~Palhaco() { };
