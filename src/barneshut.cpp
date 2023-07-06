#include "barneshut.h"

//Constante gravitacional com um valor grande para não ter que criar partículas de massas planetárias
float G = 1e6;
//Epsilon para evitar divisões por 0
float eps=1e-2;

//o sistema Barnes-Hut é inicializado por uma árvore
barneshut::barneshut(std::vector<particula> ps,float iwidth){
    pai = new quadtree(ps,iwidth);
}

//Loop central para do sistema físico
//O(n*f(n,theta))
//se theta=0.0, O(n^2)
//se theta=1.0, ~O(n*log(n))
void barneshut::atualiza(float theta,float dt){
    std::vector<quadtree> corpos;
    float force;
    Vec2 forceres,dir;
    for(int i=0;i<pai->ps.size();i++){
        forceres.u[0] = 0.0f; forceres.u[1] = 0.0f;
        //std::cout<<i<<":"<<std::endl;
        particula pt = pai->ps.at(i);
        corpos = pegaForcas(pt,theta,pai);
        //std::cout<<corpos.size()<<std::endl;
        for(int j=0;j<corpos.size();j++){
            quadtree corpo = corpos.at(j);
            force = (G*pt.mass*corpo.massatot)/pow(distVec(corpo.centmassa,pt.x)+eps,2);
            if(std::isnan(force) || force>1000){
                force = 1000;
            }
            dir = dirVec(corpo.centmassa,pt.x);
            forceres.u[0] = forceres.u[0]+dir.u[0]*force;
            forceres.u[1] = forceres.u[1]+dir.u[1]*force;
            //std::cout<<corpo.centmassa.u[0]<<std::endl;
            //std::cout<<"("<<dir.u[0]<<","<<dir.u[1]<<")"<<std::endl;
            //std::cout<<magVec(forceres)<<std::endl;
        }
        //std::cout<<"("<<pt.x.u[0]<<","<<pt.x.u[1]<<")"<<std::endl;
        //std::cout<<magVec(forceres)<<std::endl;
        pai->ps.at(i).aplicafor(forceres,dt);

        //std::cout<<"("<<pt.x.u[0]<<","<<pt.x.u[1]<<")"<<std::endl;

    }
    pai = new quadtree(pai->ps,pai->hwidth);
}

//Função que analisa nodos do quadtree que satisfazem um criterio e retornando-os
std::vector<quadtree> barneshut::pegaForcas(particula pt,float theta,quadtree* nd){
    std::vector<quadtree> lista,resto;
    if((nd->ps.empty() == false)){
        if(nd->folha){
            if(!(nd->contains(pt))){
                lista.push_back(*nd);
            }
        }else{
            if((2*(nd->hwidth))/(distVec(pt.x,nd->cent)+eps)<=theta){
                lista.push_back(*nd);
            }else{
                resto = pegaForcas(pt,theta,nd->nw);
                lista.insert(lista.end(),resto.begin(),resto.end());
                resto = pegaForcas(pt,theta,nd->ne);
                lista.insert(lista.end(),resto.begin(),resto.end());
                resto = pegaForcas(pt,theta,nd->sw);
                lista.insert(lista.end(),resto.begin(),resto.end());
                resto = pegaForcas(pt,theta,nd->se);
                lista.insert(lista.end(),resto.begin(),resto.end());
            }
        }
    }
    return lista;
}
