#ifndef PARTICULAS_H_INCLUDED
#define PARTICULAS_H_INCLUDED

#include <math.h>
#include <iostream>
#include <GL/glut.h>

struct Vec2{
    float u[2]={0,0};
};

float dotProd(Vec2 a,Vec2 b);
float magVec(Vec2 a);
float distVec(Vec2 a,Vec2 b);
Vec2 dirVec(Vec2 to, Vec2 from);
Vec2 difVec(Vec2 a,Vec2 b);
Vec2 normalize(Vec2 a);
float clamp(float x,float lo,float hi);

class particula{
public:
    //Função construtora
    particula(Vec2 xi, Vec2 vi, float massp);

    //"Getters"
    /*
    void pegaPos(float (&xr)[2]);
    Vec2 pegaPos();
    void pegaVel(float (&vr)[2]);
    Vec2 pegaVel();
    void pegaMass(float &ms);
    float pegaMass();
    */
    float mass=0.0f;
    Vec2 x;
    Vec2 v;
    GLfloat cor[3];

    //Aplicação de impulsos/forças em um tempo dt
    void aplicafor(Vec2 force,float dt);
    /*
private:
    //Variáveis
    float mass;
    Vec2 x;
    Vec2 v;
    */
};

#endif // PARTICULAS_H_INCLUDED
