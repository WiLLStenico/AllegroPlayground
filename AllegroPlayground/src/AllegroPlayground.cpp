//============================================================================
// Name        : AllegroEclipseTest01.cpp
// Author      : WiLLStenico
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro5.h>


int main() {



	al_init();




  al_show_native_message_box(NULL,                    //ALLEGRO_DISPLAY* pode ser NULL
                             "Primeiro Programa",     //Título
							 "Atencao",               //Cabeçalho
							 "Welcome to Allegro!!!!",   //Texto
							 NULL,                    //Botões, pode ser NULL
							 0);                      //flags ALLEGRO_MESSAGEBOX_WARN
							                          //ALLEGRO_MESSAGEBOX_ERROR
													  //ALLEGRO_MESSAGEBOX_QUESTION
													  //ALLEGRO_MESSAGEBOX_OK_CANCEL
													  //ALLEGRO_MESSAGEBOX_YES_NO
													  //Retorna 0 se fechar a janela
													  //Retorna 1 se OK
													  //Retorna 2 se Cancel ou nenhum botão pressionado

	al_show_native_message_box(NULL,
                             "Primeiro Programa",
							 "Atencao",
							 "Welcome to Allegro!",
							 "acao",
							 ALLEGRO_MESSAGEBOX_WARN);

	al_show_native_message_box(NULL,
                             "Primeiro Programa",
							 "Atencao",
							 "Welcome to Allegro!",
							 "A | acao",
							 ALLEGRO_MESSAGEBOX_YES_NO);

  return 0;
}
