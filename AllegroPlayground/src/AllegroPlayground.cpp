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
#include <allegro5/joystick.h>



using namespace std;

enum KEYS{ UP, DOWN, LEFT, RIGHT};

/*All inits here*/
void inits(){
	if(!al_init()){
		al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
	}

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_install_keyboard();
	al_install_mouse();
	al_install_joystick();
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

	int width = 1024;
	int height = 768;

	inits();

	display= al_create_display(width,height);

	if(!display){
		al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
		return -1;
	}

	al_clear_to_color(al_map_rgb(0,0,0)); //coloring back buffer


	//=============================== Fonts ==================================


	ALLEGRO_FONT *font24 = al_load_font("Resources//fonts//cactus.ttf", 24, 0);
	ALLEGRO_FONT *font36 = al_load_font("Resources//fonts//cactus.ttf", 36, 0);
	ALLEGRO_FONT *font18 = al_load_font("Resources//fonts//arial.ttf", 18, 0);

	al_draw_text(font24, al_map_rgb(255, 0, 255), 50, 50, 0, "Hello World, this is 24 point");
	al_draw_text(font36, al_map_rgb(255, 127, 127), 640 / 2, 480 / 2, ALLEGRO_ALIGN_CENTRE, "This is Centered and 36 point");
	al_draw_text(font18, al_map_rgb(15, 240, 18), 620, 350, ALLEGRO_ALIGN_RIGHT, "This is right aligned and 18 point");

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	al_draw_textf(font18, al_map_rgb(255, 255, 255), screen_w/2, 400, ALLEGRO_ALIGN_CENTRE,
			"TEXT with variable output (textf): Screen width and height = %i / %i" , screen_w, screen_h);


	//============================== Display ================================

	al_flip_display();//swap buffers to prevent flicker
	al_rest(2.0); //Timer de n segundos

	//=============================== Primitives =============================



	al_clear_to_color(al_map_rgb(50,50,50)); //coloring back buffer
	lines(width);
	al_draw_triangle(10, 200, 100, 10, 190, 200, al_map_rgb(255, 0, 255), 5);
	al_draw_filled_triangle(300, 400, 400, 200, 500, 400, al_map_rgb(0, 0, 255));

	al_draw_rectangle(20, 10, 250, 250, al_map_rgb(255, 0, 255), 5);
	al_draw_rounded_rectangle(width - 200, 10, width - 10, 50, 5, 5, al_map_rgb(0, 0, 255), 15);
	al_draw_filled_rectangle(30, 280, 250, height - 10, al_map_rgb(255, 255, 255));
	al_draw_filled_rounded_rectangle(width - 200, 180, width - 10, height - 10, 10, 10,  al_map_rgb(0, 255, 0));

	al_draw_circle(100, 100, 50, al_map_rgb(255, 255, 0), 7);
	al_draw_filled_circle(400, 400, 70, al_map_rgb(255, 255, 255));

	al_draw_ellipse(150, 100, 100, 50, al_map_rgb(127, 3, 34), 7);
	al_draw_filled_ellipse(400, 250, 100, 200, al_map_rgb(0, 255, 255));

	float points[] = {0, 20, 400, 100, 50, 200, width, height};
	al_draw_spline(points, al_map_rgb(255, 0, 255), 0);

	float points2[] = {100, height, 200, 100, 400, 200, width, height};
	al_draw_spline(points2, al_map_rgb(0, 0, 255), 3);

	al_flip_display();//swap buffers to prevent flicker
	al_rest(2.0); //Timer de n segundos

	//========================= Inputs ======================================

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();//swap buffers to prevent flicker

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	bool keys[4] = {false, false, false, false};

	bool done = false;
	bool draw = true;
	//bool redraw = true;

	ALLEGRO_COLOR color = al_map_rgb(255,0,255);

	int pos_x = width / 2;
	int pos_y = height / 2;

	int FPS = 60;
	int count = 0;

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//Pega os eventos do display, por exemplo o click do botao X do display
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_joystick_event_source());


	//================ Timer ================
	al_register_event_source(event_queue, al_get_mouse_event_source());
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);


	al_hide_mouse_cursor(display);
	//al_show_mouse_cursor(display);

	ALLEGRO_JOYSTICK *joy = al_get_joystick(0);

	ALLEGRO_JOYSTICK_STATE joyState;

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		al_get_joystick_state(joy, &joyState);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			}


		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1) //Botão esquerdo
				draw = !draw;
			else if (ev.mouse.button & 2) //Botão direito
				done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
		}
		else  if (ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS)
		{
			if (ev.joystick.axis == 0) //x
			{
				//pos_x += ev.joystick.pos* 10;
				keys[LEFT] = ev.joystick.pos < 0;
				keys[RIGHT] = ev.joystick.pos > 0;

			}
			else if (ev.joystick.axis == 1)//y
			{
				keys[UP] = ev.joystick.pos < 0;
				keys[DOWN] = ev.joystick.pos > 0;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
		{
			switch (ev.joystick.button)
			{
			case 1:
				color = al_map_rgb(255, 0, 0);
				break;
			case 2:
				color = al_map_rgb(0, 0, 255);
				break;
			case 3:
				color = al_map_rgb(0, 255, 0);
				break;
			case 0:
				color = al_map_rgb(255, 0, 255);
				break;
			default:
				color = al_map_rgb(255, 255, 255);
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			pos_y -= keys[UP] * 10;
			pos_y += keys[DOWN] * 10;
			pos_x -= keys[LEFT] * 10;
			pos_x += keys[RIGHT] * 10;

			//redraw = true;
		}

		/*if(draw)
			al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 255));
		 */
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, color);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));

		count++;

		al_draw_textf(font18, al_map_rgb(255, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE,
				"Frames: %i", count);

	}


	//========================= Destroys ====================================
	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}




