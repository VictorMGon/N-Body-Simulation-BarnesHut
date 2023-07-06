#include "quadtree.h"
#include <iostream>
#include <stdio.h>
#include <string>


//Inicializando árvore com um nodo pai
quadtree::quadtree(quadtree *pai){
    raiz = pai;
    hwidth=pai->hwidth/2;

}

//Inicializando árvore com uma lista de partículas e tamanho espacial
quadtree::quadtree(std::vector<particula> plist,float iwidth){
    //std::cout<<ps.size();
    hwidth=iwidth;
    cent.u[0]=hwidth; cent.u[1]=hwidth;
    for(int i=0;i<plist.size();i++){
        //Ignorar nodos que ultrapassam os limites espaciais da árvore
        if(plist.at(i).x.u[0]<0 || plist.at(i).x.u[0]>hwidth*2 || plist.at(i).x.u[1]<0 || plist.at(i).x.u[1]>hwidth*2){
            continue;
        }
        inserepart(plist.at(i));
    }
}

//Inserindo e calculando centros de massas
void quadtree::inserepart(particula p){
    if(ps.size()>0){
        if(folha){
            subdivide();
        }
        if(p.x.u[0]<=cent.u[0]){
            if(p.x.u[1]<=cent.u[1]){
                sw->inserepart(p);
            }else{
                nw->inserepart(p);
            }
        }else{
            if(p.x.u[1]<=cent.u[1]){
                se->inserepart(p);
            }else{
                ne->inserepart(p);
            }
        }
        ps.push_back(p);
        centmassa.u[0]=(centmassa.u[0]*massatot+p.x.u[0]*p.mass)/(massatot+p.mass);
        centmassa.u[1]=(centmassa.u[1]*massatot+p.x.u[1]*p.mass)/(massatot+p.mass);

        massatot=massatot+p.mass;
    }else{
        massatot=p.mass;
        centmassa=p.x;
        ps.push_back(p);
    }
}

//Subdivisão da árvore
void quadtree::subdivide(void){
    std::vector<particula> tmp;
    nw = new quadtree(this);
    nw->cent.u[0]=cent.u[0]-hwidth/2;
    nw->cent.u[1]=cent.u[1]+hwidth/2;
    nw->bleeps = bleeps+1;
    //std::cout<<nw->bleeps<<std::endl;

    ne = new quadtree(this);
    ne->cent.u[0]=cent.u[0]+hwidth/2;
    ne->cent.u[1]=cent.u[1]+hwidth/2;
    ne->bleeps = bleeps+1;

    sw = new quadtree(this);
    sw->cent.u[0]=cent.u[0]-hwidth/2;
    sw->cent.u[1]=cent.u[1]-hwidth/2;
    sw->bleeps = bleeps+1;

    se = new quadtree(this);
    se->cent.u[0]=cent.u[0]+hwidth/2;
    se->cent.u[1]=cent.u[1]-hwidth/2;
    se->bleeps = bleeps+1;

    tmp = ps;
    ps.clear();
    //reinserir pontos que já estavam na árvore caso tenha mais de um
    for(int i=0;i<tmp.size();i++){
        if(tmp.at(i).x.u[0]<=cent.u[0]){
            if(tmp.at(i).x.u[1]<=cent.u[1]){
                sw->inserepart(tmp.at(i));
            }else{
                nw->inserepart(tmp.at(i));
            }
        }else{
            if(tmp.at(i).x.u[1]<=cent.u[1]){
                se->inserepart(tmp.at(i));
            }else{
                ne->inserepart(tmp.at(i));
            }
        }
        ps.push_back(tmp.at(i));
    }
    folha = false;
}
//Verificar se o nodo possui uma partícula
bool quadtree::contains(particula pt){
    for(int i=0;i<ps.size();i++){
        if(ps.at(i).x.u[0]==pt.x.u[0] && ps.at(i).x.u[1]==pt.x.u[1]){
            return true;
        }
    }
    return false;
}
