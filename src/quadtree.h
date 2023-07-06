#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include "particulas.h"
#include <vector>


//Axis-Aligned Bounding-Box, inutilizado
/*
class aabb{
public:
    //Fun��o construtora
    aabb(float x[2], float width);

    //"Getters"


    //testes de pertencimento e de intersec��es

    //TODO

private:
    //Vari�veis
    float x[2];
    float width;
};
*/

class quadtree{
public:
    //Fun��o construtora
    quadtree(std::vector <particula> plist,float iwidth);
    quadtree(float iwidth);
    quadtree(quadtree *pai);
    void inserepart(particula p);
    void subdivide();
    bool contains(particula pt);

    quadtree* raiz;
    quadtree* nw;
    quadtree* ne;
    quadtree* sw;
    quadtree* se;
    //aabb caixa;
    float massatot=0.0f;
    Vec2 cent;
    float hwidth=0.0f;
    Vec2 centmassa;
    std::vector<particula> ps;
    bool folha=true;
    //vari�vel para analisar altura da �rvore
    int bleeps=0;

private:

};

#endif // QUADTREE_H_INCLUDED
