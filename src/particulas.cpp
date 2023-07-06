#include "particulas.h"

//Partícula é definida por um vetor de posição, vetor de velocidade e massa
particula::particula(Vec2 xi, Vec2 vi, float massp):mass(massp){
    for(int i=0;i<2; i++){
        x.u[i]=xi.u[i];
        v.u[i]=vi.u[i];
    }
}

//Operações vetoriais comuns

float dotProd(Vec2 a,Vec2 b){
    return (a.u[0]*b.u[0]) + (a.u[1]*b.u[1]);
};

Vec2 difVec(Vec2 a,Vec2 b){
    Vec2 dif;
    dif.u[0] = a.u[0]-b.u[0];
    dif.u[1] = a.u[1]-b.u[1];
    return dif;
};

Vec2 normalize(Vec2 a){
    Vec2 aunit;
    aunit.u[0] = a.u[0]/magVec(a); aunit.u[1] = a.u[1]/magVec(a);
    return aunit;
};

float magVec(Vec2 a){
    return sqrt(a.u[0]*a.u[0] + a.u[1]*a.u[1]);
};

float distVec(Vec2 a,Vec2 b){
    return sqrt(pow(a.u[0]-b.u[0],2) + pow(a.u[1]-b.u[1],2));
};

Vec2 dirVec(Vec2 to, Vec2 from){
    Vec2 dir = normalize(difVec(to,from));
    return dir;
};

//Função auxiliadora para "prender" valores

float clamp(float x,float lo,float hi){
    if(x<lo){
        x=lo;
    }else if(x>hi){
        x=hi;
    }
}

/*

Vec2 particula::pegaPos(){
    return x;
}

Vec2 particula::pegaVel(){
    return v;
}

float particula::pegaMass(){
    return mass;
}
*/

//Integrando valores usando método de Euler

void particula::aplicafor(Vec2 force,float dt){
    //std::cout<<"("<<force.u[0]<<","<<force.u[1]<<")"<<std::endl;
    for(int i=0;i<2; i++){
        v.u[i] = v.u[i] + force.u[i] * dt/mass;
        x.u[i] = x.u[i] + v.u[i]*dt;
    }
}
