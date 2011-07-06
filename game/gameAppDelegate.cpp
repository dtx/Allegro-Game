#include <stdio.h>
#include "gameAppDelegate.h"


enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int tilesize =32;

tile::tile(){
    tiles = al_load_bitmap("blocks1.png");
    al_convert_mask_to_alpha(tiles, al_map_rgb(0, 0, 0));
    map_h = al_get_bitmap_height(tiles);
    map_w = (al_get_bitmap_width(tiles))-26;
    offset_w=0; 
    offset_h=0;
    int i1=0;
    for (int i=0; i<22; i++) {
        offset_w = 0;
        if(i%2 == 0){
            offset_h +=2;
            continue;
        }
        else{
            offset_h+=32;
        }
        for (int j=0; j<36; j++) {
            if(j%2 == 0){
                offset_w +=2;
                continue;
            }
            else{
                offset_w+=32;
                printf("%d,%d\n", offset_w,offset_h);
                tiles_array[i1]=al_create_sub_bitmap(tiles, offset_w, offset_h, 32, 32);
                i1++;
            }
        }
    }
}

void tile::draw_map(){
    int i,j;
    //base level blitting
    for (i=0; i<15; i++) {
        for (j=0; j<20; j++) {
            //draw the tile using the tile set in .h file
            printf("\nbobo lasha %d %d %d\n\n", map1[i][j], al_get_bitmap_height(tiles_array[map1[i][j]]), al_get_bitmap_width(tiles_array[map1[i][j]]));
            al_draw_bitmap(tiles_array[map1[i][j]], i*tilesize, j*tilesize, 0);
        }
    }
}

player::player(){
    bmp = al_load_bitmap("player.png");
    animationwidth = al_get_bitmap_width(bmp)/5;
    animationheight = al_get_bitmap_height(bmp)/8;
    al_convert_mask_to_alpha(bmp, al_map_rgb(255, 0, 255));
    for (int x=0; x<8; x++) {
        for (int y=0; y<5; y++) {
            bmp_array[x][y] = al_create_sub_bitmap(bmp, 32*x, 32*y, 32, 32);
        }
    }
}

void player::move_up(float* x, float* y){
    static int animation_state=0;
    printf("animation state in the function : %d\n", animation_state);
    animation_state++;
    al_draw_bitmap(bmp_array[animation_state][2], *x, *y, 0);
    *y = *y -3;
    if (animation_state == 4) {
        animation_state = 0; 
    }
}

void player::move_left(float* x, float* y){
    static int animation_state=0;
    printf("animation state in the function : %d\n", animation_state);
    animation_state++;
    al_draw_bitmap(bmp_array[animation_state][0], *x, *y, 0);
    *x = *x -3;
    if (animation_state == 4) {
        animation_state = 0;
    }
}

void player::move_right(float* x, float* y){
    static int animation_state=0;
    printf("animation state in the function : %d\n", animation_state);
    animation_state++;
    al_draw_bitmap(bmp_array[animation_state][1], *x, *y, 0);
    *x = *x +3;
    if (animation_state == 4) {
        animation_state = 0;
    }
}

void player::move_down(float* x, float* y){
    static int animation_state=0;
    printf("animation state in the function : %d\n", animation_state);
    animation_state++;
    al_draw_bitmap(bmp_array[animation_state][3], *x, *y, 0);
    *y = *y +3;
    if (animation_state == 4) {
        animation_state = 0;
    }
}

void player::draw(int animation, float * x, float* y){
    //printf("%f %f\n", animationheight, animationwidth);
    switch (animation) {
        case 0:
            al_draw_bitmap(bmp_array[0][1], *x, *y, 0);
            break;
        case 1:
            printf("animation number %d\n", animation);
            move_up(x, y);
            break;
        case 2:
            move_down(x, y);
            break;
        case 3:
            move_left(x, y);
            break;
        case 4:
            move_right(x, y);
            break;
        default:
            break;
    }
    //al_draw_bitmap(bmp_array[0][1], x, y, 0);
}


const float FPS = 10;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    //ALLEGRO_BITMAP *bouncer = NULL;
    bool redraw = true;
    float center_w = SCREEN_W/2;
    float center_h = SCREEN_H/2;
    bool key[4] = { false, false, false, false };
    bool doexit = false;
    int animation_code;
    
    al_init_image_addon();

    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    
    player man;
    tile titi;
    
    if(!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }
    
    //al_convert_mask_to_alpha(bouncer, al_map_rgb(255, 0, 255));
    //al_set_target_bitmap(bouncer);
    
    //al_clear_to_color(al_map_rgb(255, 0, 255));
    
    //al_set_target_bitmap(al_get_backbuffer(display));
    
    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        //al_destroy_bitmap(bouncer);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    
    al_clear_to_color(al_map_rgb(0,0,0));
    
    al_flip_display();
    
    al_start_timer(timer);
    
    while (!doexit) {
        printf("here!!!");
        titi.draw_map();
    while(!doexit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(key[KEY_UP]) {
                animation_code=1;
            }
            
            if(key[KEY_DOWN]) {
                animation_code  =2;
            }
            
            if(key[KEY_LEFT]) {
                animation_code = 3;
            }
            
            if(key[KEY_RIGHT]) {
                animation_code= 4;
            }
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    printf("HERE!!!!!!!!!!!!!!!!!!!!!!!");
                    break;
                    
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
                    
                case ALLEGRO_KEY_LEFT: 
                    key[KEY_LEFT] = true;
                    break;
                    
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
        }
        
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    printf("FALSE!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                    break;
                    
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                    
                case ALLEGRO_KEY_LEFT: 
                    key[KEY_LEFT] = false;
                    break;
                    
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
                    
                case ALLEGRO_KEY_ESCAPE:
                    doexit = true;
                    break;
            }
        }
        
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            //al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
            man.draw(animation_code, &center_w, &center_h);
            al_flip_display();
            animation_code = 0;
        }
    }
}
    
    //al_destroy_bitmap(bouncer);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    
    return 0;
}