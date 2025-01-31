#include "mp3.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

typedef struct {
    int x, y;
    int width, height;
} Paddle;

typedef struct {
    int x, y;
    int size;
    f32 speedX, speedY;
} Ball;

Paddle player1 = {0};
Paddle player2 = {0};
Ball ball = {0};

// Declare the controller input structure
typedef struct Custom0 {
    u16 type;                  /* Controller Type */
    u8 status;                 /* Controller status */
    u8 errno;
} Custom0;

typedef struct Custom1 {
    u16 button;
    s8 stick_x;
    s8 stick_y;
} Custom1;

typedef struct CombinedCont {
    Custom0 status;
    Custom1 pad;
} CombinedCont;

extern u8 ciImage[];
extern u16 palette[];
extern u8 bluePaddle[];
extern u8 redPaddle[];
Gfx* gfx_draw_textured_rectangle(Gfx* gfx, int x, int y, int width, int height, u8* texture);
Gfx* gfx_draw_rectangle(Gfx* gfx, int x, int y, int width, int height, u32 color);

#define PADDLE_SPEED 3

extern CombinedCont D_800CC3F0_CCFF0[4];

// Function to control paddles based on input
void control_paddles(void) {
    CombinedCont *controller1 = &D_800CC3F0_CCFF0[0];
    CombinedCont *controller2 = &D_800CC3F0_CCFF0[1];

    // Update player 1's paddle position based on input
    if (!(controller1->status.status & 0x80)) {
        if (controller1->pad.stick_y > 0) {
            player1.y -= PADDLE_SPEED; // Move up
        } else if (controller1->pad.stick_y < 0) {
            player1.y += PADDLE_SPEED; // Move down
        }
    }

    // Keep player 1's paddle within screen bounds
    if (player1.y < 0) player1.y = 0;
    if (player1.y > SCREEN_HEIGHT - player1.height) player1.y = SCREEN_HEIGHT - player1.height;

    // Update player 2's paddle position based on input
    if (!(controller1->status.status & 0x80)) {
        if (controller1->pad.stick_y > 0) {
            player2.y -= PADDLE_SPEED; // Move up
        } else if (controller1->pad.stick_y < 0) {
            player2.y += PADDLE_SPEED; // Move down
        }
    }

    // Keep player 2's paddle within screen bounds
    if (player2.y < 0) player2.y = 0;
    if (player2.y > SCREEN_HEIGHT - player2.height) player2.y = SCREEN_HEIGHT - player2.height;
}

// Initialize the game state
void init_game() {
    player1.x = 10;              // Player 1 position
    player1.y = (SCREEN_HEIGHT - 60) / 2; // Centered vertically
    player1.width = 16;          // Paddle width
    player1.height = 48;         // Paddle height

    player2.x = SCREEN_WIDTH - 20; // Player 2 position
    player2.y = (SCREEN_HEIGHT - 60) / 2; // Centered vertically
    player2.width = 16;          // Paddle width
    player2.height = 48;         // Paddle height

    ball.x = (SCREEN_WIDTH - 20) / 2; // Centered horizontally
    ball.y = (SCREEN_HEIGHT - 20) / 2; // Centered vertically
    ball.size = 12;               // Ball size
    ball.speedX = 2;              // Ball speed in X direction
    ball.speedY = 2;              // Ball speed in Y direction
}

// Draw the game objects
Gfx* draw_game(Gfx* gfx) {
    gfx = gfx_draw_textured_rectangle(gfx, player1.x, player1.y, player1.width, player1.height, redPaddle);
    gfx = gfx_draw_textured_rectangle(gfx, player2.x, player2.y, player2.width, player2.height, bluePaddle);
    gfx = gfx_draw_rectangle(gfx, ball.x, ball.y, ball.size, ball.size, 0xFFFFFFFF); // Draw the ball
    return gfx;
}

// Update the game state
void update_game() {
    char buffer[32];

    control_paddles();

    // Update ball position
    ball.x += ball.speedX;
    ball.y += ball.speedY;

    // Ball collision with top and bottom
    if (ball.y <= 0) {
        ball.y = 0;                  // Correct ball position
        ball.speedY = -ball.speedY;  // Reverse direction
    } else if (ball.y >= SCREEN_HEIGHT - ball.size) {
        ball.y = SCREEN_HEIGHT - ball.size; // Correct ball position
        ball.speedY = -ball.speedY;  // Reverse direction
    }

    // Ball collision with paddles
    // Player 1 collision
    if (ball.x <= player1.x + player1.width && 
        ball.y + ball.size >= player1.y && 
        ball.y <= player1.y + player1.height) {
        ball.x = player1.x + player1.width; // Place ball to the right of paddle
        ball.speedX -= 0.20f;
        ball.speedX = -ball.speedX; // Reverse direction
        
    }

    // Player 2 collision
    else if (ball.x + ball.size >= player2.x && 
             ball.y + ball.size >= player2.y && 
             ball.y <= player2.y + player2.height) {
        ball.x = player2.x - ball.size; // Place ball to the left of paddle
        ball.speedX += 0.20f;
        ball.speedX = -ball.speedX; // Reverse direction
    }

    // Reset ball if it goes out of bounds
    if (ball.x < 0 || ball.x > SCREEN_WIDTH) {
        ball.x = (SCREEN_WIDTH - ball.size) / 2; // Reset position
        ball.y = (SCREEN_HEIGHT - ball.size) / 2; // Reset position
        ball.speedX = 2; // Reset speed
        ball.speedY = 2;
    }
    mp3_sprintf(buffer, "SPX:%.2f, SPY:%.2f", ball.speedX, ball.speedX);
    mp3_DrawDebugText(30, 3, buffer);
}


// Main loop
Gfx* game_loop(Gfx* gfx) {
    if (player1.x == 0) {
        init_game(); // Initialize the game if not already done
    }

    // Update the game state
    update_game();
    gfx = draw_game(gfx);

    return gfx; // Return the graphics context
}