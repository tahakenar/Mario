#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// MAIN GAME SETTINGS
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024
#define GAME_SPEED 400


// PATHS ETC.
#define ASSET_PATH "../assets"
#define BRICK_ASSET_PATH ASSET_PATH  "/brick.png"
#define FLOOR_ASSET_PATH ASSET_PATH  "/floor.png"

#define PIPE_ASSET_PATH ASSET_PATH "/pipe.png"
#define PIPE_S_ASSET_PATH ASSET_PATH "/pipeS.png"

#define MARIO_ASSET_PREPATH ASSET_PATH "/mario"
#define MARIO_1 MARIO_ASSET_PREPATH "1.png"
#define MARIO_2 MARIO_ASSET_PREPATH "2.png"
#define MARIO_3 MARIO_ASSET_PREPATH "3.png"
#define MARIO_4 MARIO_ASSET_PREPATH "4.png"
#define MARIO_5 MARIO_ASSET_PREPATH "5.png"
#define MARIO_6 MARIO_ASSET_PREPATH "6.png"
#define MARIO_7 MARIO_ASSET_PREPATH "7.png"

#define TURTLE_ASSET_PREPATH ASSET_PATH "/turtle"
#define TURTLE_1 TURTLE_ASSET_PREPATH "1.png"
#define TURTLE_2 TURTLE_ASSET_PREPATH "2.png"
#define TURTLE_3 TURTLE_ASSET_PREPATH "3.png"
#define TURTLE_4 TURTLE_ASSET_PREPATH "4.png"
#define TURTLE_5 TURTLE_ASSET_PREPATH "5.png"

// SPRITE DIMENSIONS
#define FLOOR_WIDTH 1024
#define FLOOR_HEIGHT 62

#define BRICK_WIDTH 30
#define BRICK_HEIGHT 34

#define FIRST_FLOOR_BRICK_WIDTH BRICK_WIDTH*12
#define MIDDLE_BRICK_WIDTH BRICK_WIDTH*16
#define SHORT_BRICK_WIDTH BRICK_WIDTH*4
#define LAST_FLOOR_BRICK_WIDTH BRICK_WIDTH*14

#define PIPE_WIDTH 130
#define PIPE_HEIGHT 74

#define PIPE_S_WIDTH 194
#define PIPE_S_HEIGHT 122

#define MARIO_WIDTH 66
#define MARIO_HEIGHT 88


// BACKROUND POSITIONS
#define X_AXIS 0
#define Y_AXIS 1

#define FLOOR_X 0
#define FLOOR_Y WINDOW_HEIGHT - FLOOR_HEIGHT

#define FIRST_FLOOR_BRICK_X_LEFT 0
#define FIRTS_FLOOR_BRICK_X_RIGHT WINDOW_WIDTH - FIRST_FLOOR_BRICK_WIDTH
#define FIRST_FLOOR_BRICK_Y FLOOR_Y - 240

#define SHORT_BRICK_X_LEFT 0
#define SHORT_BRICK_X_RIGHT WINDOW_WIDTH - SHORT_BRICK_WIDTH
#define SHORT_BRICK_Y FIRST_FLOOR_BRICK_Y - 180

#define MIDDLE_BRICK_X (WINDOW_WIDTH/2) - (MIDDLE_BRICK_WIDTH/2)
#define MIDDLE_BRICK_Y SHORT_BRICK_Y - BRICK_HEIGHT

#define LAST_FLOOR_BRICK_X_LEFT 0
#define LAST_FLOOR_BRICK_X_RIGHT WINDOW_WIDTH - LAST_FLOOR_BRICK_WIDTH
#define LAST_FLOOR_Y MIDDLE_BRICK_Y - 180

#define PIPE_X_LEFT 0
#define PIPE_X_RIGHT WINDOW_WIDTH - PIPE_WIDTH
#define PIPE_Y FLOOR_Y - PIPE_HEIGHT

#define PIPE_S_X_LEFT 0
#define PIPE_S_X_RIGHT WINDOW_WIDTH - PIPE_S_WIDTH
#define PIPE_S_Y LAST_FLOOR_Y - PIPE_S_HEIGHT - 50

// CHARACTER RELATED DEFINITIONS
#define HEADING_LEFT 1
#define HEADING_RIGHT 2
#define FLOOR_INTERACTION_TRESHOLD 15
#define CEILING_INTERACTION_TRESHOLD 5
#define LATERAL_INTERACTION_TRESHOLD 5
#define GRAVITY_COEFFICIENT 2

// MARIO DYNAMICS
#define MARIO_STEP_SIZE 4
#define MARIO_JUMP_STEP_SIZE 1
#define MARIO_LATERAL_RIGHT_SPEED 3
#define MARIO_LATERAL_LEFT_SPEED -3
#define MARIO_JUMP_SPEED -32

// MARIO STATES

enum MarioStates
{
    STILL,
    RUN,
    JUMP,
    FALL,
    SLIDE
};

#endif