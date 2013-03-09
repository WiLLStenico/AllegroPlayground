//============================================================================
// Name        : AllegroEclipseTest01.cpp
// Author      : WiLLStenico
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <signal.h>


#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>



using namespace std;

int main() {

	ALLEGRO_DISPLAY *display = NULL;

	if(!al_init()){
		al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
	}


	display= al_create_display(1024,768);

	if(!display){
		al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
		return -1;
	}

	al_clear_to_color(al_map_rgb(0,0,255)); //coloring back buffer
	al_flip_display();//swap buffers to prevent flicker
	al_rest(5.0); //Timer de n segundos

	//=============================== Fonts ==================================
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font24 = al_load_font("Resources//cactus.ttf", 24, 0);
	ALLEGRO_FONT *font36 = al_load_font("Resources//cactus.ttf", 36, 0);
	ALLEGRO_FONT *font18 = al_load_font("Resources//cactus.ttf", 18, 0);

	al_clear_to_color(al_map_rgb(0,0,0));

	al_draw_text(font24, al_map_rgb(255, 0, 255), 50, 50, 0, "Hello World, this is 24 point");
	al_draw_text(font36, al_map_rgb(255, 127, 127), 640 / 2, 480 / 2, ALLEGRO_ALIGN_CENTRE, "This is Centered and 36 point");
	al_draw_text(font18, al_map_rgb(15, 240, 18), 620, 350, ALLEGRO_ALIGN_RIGHT, "This is right aligned and 18 point");

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	al_draw_textf(font18, al_map_rgb(255, 255, 255), screen_w/2, 400, ALLEGRO_ALIGN_CENTRE,
			"TEXT with variable output (textf): Screen width and height = %i / %i" , screen_w, screen_h);

	al_flip_display();

	al_rest(5.0);

	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_display(display);



	return 0;
}
