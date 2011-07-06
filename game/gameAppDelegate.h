//
//  gameAppDelegate.h
//  game
//
//  Created by Darshan Sanghani on 6/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
/*
#import <Cocoa/Cocoa.h>

@interface gameAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class player{
private:
    ALLEGRO_BITMAP *bmp;
    ALLEGRO_BITMAP *bmp_array[8][5];
    float animationwidth;
    float animationheight;
    
public:
    player();
    void draw(int animation, float* x, float* y);
    void move_up(float *x, float *y);
    void move_left(float* x, float* y);
    void move_right(float *x, float* y);
    void move_down(float *x, float* y);
};

class tile{
    private:
    ALLEGRO_BITMAP *tiles;
    ALLEGRO_BITMAP *tiles_array[256];
    int map_h;
    int map_w;
    int offset_w;
    int offset_h;
    
    public:
    tile();
    void draw_map(int x, int y);    
};

int map1[2][20] ={{72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72}
    ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 3, 0, 0, 0, 0}};
/*
    ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 2, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 4, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 4, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 4, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 4, 6, 5, 0, 0, 0, 2, 3, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 4, 6, 5, 0, 0, 0, 4, 5, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 4, 6, 5, 0, 0, 0, 4, 5, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 4, 6, 5, 0, 0, 0, 4, 5, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{0, 4, 6, 5, 0, 0, 0, 4, 5, 0, 0, 0, 4, 6, 6, 5, 0, 0, 0, 0}
    ,{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}};
*/
