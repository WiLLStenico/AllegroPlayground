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
#include <allegro5/allegro_primitives.h>



using namespace std;


/*All inits here*/
void inits(){
	if(!al_init()){
		al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
	}

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
}

/*draw some lines*/
void lines(int width){

	al_draw_line(100, 100, width - 100, 100, al_map_rgb(255, 0, 0), 1);
	al_draw_line(50, 200, width - 50, 200, al_map_rgb(0, 0, 255), 5);
	al_draw_line(0, 300, width, 300, al_map_rgb(255, 0, 255), 10);
	al_draw_line(50, 50, 50, 400, al_map_rgb(0, 255, 0), 3);
	al_draw_line(50, 200, width - 50, 400, al_map_rgb(0, 0, 255), 5);

}


int main() {

	ALLEGRO_DISPLAY *display = NULL;

	inits();

	display= al_create_display(1024,768);

	if(!display){
		al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
		return -1;
	}

	al_clear_to_color(al_map_rgb(0,0,0)); //coloring back buffer


	//=============================== Fonts ==================================


	ALLEGRO_FONT *font24 = al_load_font("Resources//cactus.ttf", 24, 0);
	ALLEGRO_FONT *font36 = al_load_font("Resources//cactus.ttf", 36, 0);
	ALLEGRO_FONT *font18 = al_load_font("Resources//cactus.ttf", 18, 0);

	al_draw_text(font24, al_map_rgb(255, 0, 255), 50, 50, 0, "Hello World, this is 24 point");
	al_draw_text(font36, al_map_rgb(255, 127, 127), 640 / 2, 480 / 2, ALLEGRO_ALIGN_CENTRE, "This is Centered and 36 point");
	al_draw_text(font18, al_map_rgb(15, 240, 18), 620, 350, ALLEGRO_ALIGN_RIGHT, "This is right aligned and 18 point");

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	al_draw_textf(font18, al_map_rgb(255, 255, 255), screen_w/2, 400, ALLEGRO_ALIGN_CENTRE,
			"TEXT with variable output (textf): Screen width and height = %i / %i" , screen_w, screen_h);


	//============================== Display ================================

	al_flip_display();//swap buffers to prevent flicker
	al_rest(5.0); //Timer de n segundos

	//=============================== Primitives =============================

	int width = 640;
	int height = 480;

	al_clear_to_color(al_map_rgb(50,50,50)); //coloring back buffer
	lines(width);
	al_draw_triangle(10, 200, 100, 10, 190, 200, al_map_rgb(255, 0, 255), 5);
	al_draw_filled_triangle(300, 400, 400, 200, 500, 400, al_map_rgb(0, 0, 255));

	al_draw_rectangle(10, 10, 250, 250, al_map_rgb(255, 0, 255), 5);
	al_draw_rounded_rectangle(width - 200, 10, width - 10, 50, 5, 5, al_map_rgb(0, 0, 255), 15);
	al_draw_filled_rectangle(10, 280, 250, height - 10, al_map_rgb(255, 255, 255));
	al_draw_filled_rounded_rectangle(width - 200, 180, width - 10, height - 10, 10, 10,  al_map_rgb(0, 255, 0));

	al_draw_circle(100, 100, 50, al_map_rgb(255, 255, 0), 7);
	al_draw_filled_circle(400, 400, 70, al_map_rgb(255, 255, 255));

	al_draw_ellipse(150, 100, 100, 50, al_map_rgb(127, 3, 34), 7);
	al_draw_filled_ellipse(400, 250, 100, 200, al_map_rgb(0, 255, 255));

	float points[] = {0, 0, 400, 100, 50, 200, width, height};
	al_draw_spline(points, al_map_rgb(255, 0, 255), 0);

	float points2[] = {100, height, 200, 100, 400, 200, width, height};
	al_draw_spline(points2, al_map_rgb(0, 0, 255), 3);

	al_flip_display();//swap buffers to prevent flicker
	al_rest(5.0); //Timer de n segundos


	//========================= Destroys ====================================
	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_display(display);

	return 0;
}




