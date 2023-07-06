#ifndef BARNESHUT_H_INCLUDED
#define BARNESHUT_H_INCLUDED

#include "particulas.h"
#include "quadtree.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <stdlib.h>

class barneshut{
public:
    //Função construtora
    barneshut(std::vector<particula> ps,float iwidth);

    void atualiza(float theta,float dt);
    std::vector<quadtree> pegaForcas(particula pt,float theta,quadtree* nd);

    quadtree* pai;
    float time=0.0f;

};

#endif // BARNESHUT_H_INCLUDED
