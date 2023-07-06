#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "barneshut.h"

#define M_PI 3.14159

#define width 800

static int ortho = 1;

float dt = 0.01667;
barneshut* sist;

float oldT = 0;
int frames = 0;

float th = 1.0;
int N = 100;

std::vector<particula>* pl;

void circle(float x, float y, float r, GLfloat cor[3],int segments){
    //Gerando pontos para desenhar o nosso círculo
    glColor3f(cor[0],cor[1],cor[2]);
    glBegin( GL_TRIANGLE_FAN );
        glVertex2f(x, y);
        for( int n = 0; n <= segments; ++n ) {
            float const t = 2 * M_PI * (float)n / (float)segments;
            glVertex2f(x + sin(t) * r, y + cos(t) * r);
        }
    glEnd();
}

static void timer(int value){
    //Atualizar estado
    float startT = glutGet(GLUT_ELAPSED_TIME);
    float deltaT = startT - oldT;
    frames++;
    if(deltaT>=5000){
        std::cout<<"FPS:"<<frames*1000.0/deltaT<<std::endl;
        oldT = startT;
        frames = 0;
    }
    glutPostRedisplay();
    /*
    for(int i=0;i<sist->pai->ps.size();i++){
        std::cout<<"("<<sist->pai->ps.at(i).x.u[0]<<","<<sist->pai->ps.at(i).x.u[1]<<")"<<std::endl;
    }
    */

    sist->atualiza(th,dt);
    pl=&(sist->pai->ps);

    /*
    for(int i=0;i<sist->pai->ps.size();i++){
        std::cout<<"("<<sist->pai->ps.at(i).x.u[0]<<","<<sist->pai->ps.at(i).x.u[1]<<")"<<std::endl;
    }
    */

    glutTimerFunc(dt*1000, timer, 0);
}

static void display(void) {
    //Função gráfica de renderização
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if (ortho) {
    } else {
        gluLookAt(0.0, 0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i=0;i<pl->size();i++){
        float x,y;
        x=pl->at(i).x.u[0];
        y=pl->at(i).x.u[1];
        circle(x-400.0,y-400.0,5.0+pow(pl->at(i).mass*2-1.0,2),pl->at(i).cor,20);
    }
    glFlush();
}

static void reshape(int w, int h) {
    //Função gráfica para ajustamento da janela, por enquanto não é ajustado a proporção de tela
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (ortho) {
        glOrtho(-400.0, 400.0, -400.0, 400.0, -1.5, 1.5);
    } else {
        glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    //Gerando as partículas com posições aleatórias
    srand(time(NULL));
    std::cout<<"Exercicio Computacional: N-Corpos"<<std::endl;
    std::cout<<"Objetivo: Comparar tempo simulando de forca bruta e com quadtree"<<std::endl;
    std::cout<<"Objetivo-extra: Representacao grafica da simulacao"<<std::endl;
    std::cout<<"-------------------------------------------"<<std::endl;
    std::cout<<"Entrada 1: Numero de particulas"<<std::endl;
    std::cout<<"Entrada 2: Parametro theta: parametro utilizado na determinacao das forcas(ler: Algoritmo de Barnes-Hut)"<<std::endl;
    std::cout<<"-------------------------------------------"<<std::endl;
    std::cout<<"Tempo Gasto: 1.5~ semanas"<<std::endl;
    std::cout<<"Dificuldade: Muito dificil; +Primeira vez utilizando OpenGL puro +Revisitagem a uma linguagem com pouca experiencia"<<std::endl;
    std::cout<<"Valeu a pena?: Sim"<<std::endl;
    std::cout<<"-------------------------------------------"<<std::endl;
    std::cout<<"MAT01093 - ALGORITMOS E PROGRAMACAO II"<<std::endl;
    std::cout<<"Professor: Rudnei"<<std::endl;
    std::cout<<"Feito por: Victor Machado Goncalves(no 00313930)"<<std::endl;
    std::cout<<"-------------------------------------------"<<std::endl<<std::endl;
    std::cout<<"Numero de particulas(1-500):"<<std::endl;
    std::cin>>N;
    while(N<=0 || N>500){
        std::cout<<"Numero de particulas invalido"<<std::endl;
        std::cout<<"Numero de particulas(1-500):"<<std::endl;
        std::cin>>N;
    }
    std::cout<<"Parametro Theta(0.0-10.0):"<<std::endl;
    std::cin>>th;
    while(th<0.0 || th>10.0){
        std::cout<<"Parametro theta invalido"<<std::endl;
        std::cout<<"Parametro Theta(0.0-10.0):"<<std::endl;
        std::cin>>th;
    }

    Vec2 xp1;
    Vec2 vp1;
    float mass;
    pl = new std::vector<particula>;
    for(int i=0;i<N;i++){
        xp1.u[0]=static_cast <float>(rand())/static_cast <float>(RAND_MAX)*800.0f;xp1.u[1]=static_cast <float>(rand())/static_cast <float>(RAND_MAX)*800.0f;
        mass = 1.0+(static_cast <float>(rand())/static_cast <float>(RAND_MAX)*1-0.5);
        //mass = 1.0;
        GLfloat cores[6][3]={{0.5,0.5,1.0},{0.5,1.0,0.5},{1.0,0.5,0.5},{1.0,1.0,0.5},{1.0,0.75,0.5},{1.0,0.5,1.0}};
        //GLfloat cores[1][3]={{1.0,1.0,1.0}};
        int randint = rand() % (sizeof(cores)/sizeof(float[3]));
        particula a(xp1,vp1,mass);
        a.cor[0]=cores[randint][0];a.cor[1]=cores[randint][1];a.cor[2]=cores[randint][2];
        pl->push_back(a);
    }

    //Inicializando sistema Barnes-Hut com o vetor de n-partículas e o tamanho do plano computacional
    std::cout<<"Inicializando Sistema Barnes-Hut"<<std::endl;
    sist = new barneshut(*pl,400.0f);
    pl=&(sist->pai->ps);

    //Checagem do centro de massa do nodo raiz

    std::cout<<"Centro de massa(raiz): ("<<sist->pai->centmassa.u[0]<<","<<sist->pai->centmassa.u[1]<<")"<<std::endl;
    std::cout<<"Massa total: "<<sist->pai->massatot<<std::endl<<std::endl;


    //Configurações gráficas

    glutInit(&argc, argv);
    ortho =1;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutSetWindowTitle("N-Corpos");
    glutSetIconTitle("N-Corpos");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return EXIT_SUCCESS;
}
