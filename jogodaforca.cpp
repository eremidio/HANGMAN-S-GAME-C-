//VAMOS CRIAR UM JOGO DA FORCA EM C++

/*
COMPILAR ESTE PROGRAMA EM LINUX USANDO A SEGFUINTE LINHA DE COMANDO
g++ -o jogodaforca jogodaforca.cpp `pkg-config gtkmm-3.0 --cflags --libs`
EM WINDOWS ADICIONAR A FLAG `pkg-config gtkmm-3.0 --cflags --libs` AO COMPILADOR SE O PKG-CONFIG ESTIVER INSTALADO 
*/ 

/*CABEÇALHO*/
#include"jogodaforca_metodos.h"
#include<gtkmm/application.h>
using namespace std;
using namespace Glib;
using namespace Gtk;

int main(int argc, char* argv[]){
//Ponteiro smart
RefPtr<Application> app =Application::create(argc, argv);

//Instanciando o objeto da classe do aplicativo e executando o mesmo
Game hangman;
hangman.set_default_size(1000, 800);
hangman.set_border_width(0);
return app->run(hangman);

}
