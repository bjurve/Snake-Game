#include "raylib.h"
#include <deque>
#include <cstdlib>

const int screenWidth = 800;
const int screenHeight = 600;
const int gridSize = 20;
const int gridWidth = screenWidth / gridSize;
const int gridHeight = screenHeight / gridSize;

//snake directions

enum snakeDirections{UP, DOWN, RIGHT, LEFT};

// Objects
struct SnakeSegment{
    int x,y;
};

struct Snake{
    std::deque<SnakeSegment> snakeBody;
    snakeDirections direction;
};

struct Fruit{
    int x,y;
};   

//Function to generate random fruit position

Fruit GenerateFruit(){
    Fruit fruit;
    fruit.x = rand() % gridWidth;
    fruit.y = rand() % gridHeight;
    return fruit;
}

//function to check collision between snake head and body

bool CollisionCheckItself(const Snake& snake){
    for(size_t i = 1; i < snake.snakeBody.size(); i++){
        if ( snake.snakeBody[0].x == snake.snakeBody[i].x && snake.snakeBody[0].y == snake.snakeBody[i].y){
            return true;
        }
    }
    return false;
}


int main(){
    InitWindow(screenWidth, screenHeight,"Snake Game");
    SetTargetFPS(10); // sets fps of the game

    //initiate snake
    Snake snake;
    snake.snakeBody.push_back({gridWidth  / 2, gridHeight / 2});
    snake.direction = RIGHT;

    //initiate first fruit
    Fruit fruit = GenerateFruit();

    bool gameOver = false;

 
    while(!WindowShouldClose()){

        //Handelr for snakeMovement
        if (IsKeyPressed(KEY_UP) && snake.direction != DOWN) snake.direction = UP;
        if (IsKeyPressed(KEY_DOWN) && snake.direction != UP) snake.direction = DOWN;
        if (IsKeyPressed(KEY_LEFT) && snake.direction != RIGHT) snake.direction = LEFT;
        if (IsKeyPressed(KEY_RIGHT) && snake.direction != LEFT) snake.direction = RIGHT;

        if(!gameOver){
           //Move snake according to Direction
           SnakeSegment newHead = snake.snakeBody.front();
           if(snake.direction == UP) {newHead.y--;}
           if(snake.direction == DOWN) {newHead.y++;}
           if(snake.direction == LEFT) {newHead.x--;}
           if(snake.direction == RIGHT) {newHead.x++;}


           //Check if snake eat fruit
           if(newHead.x == fruit.x && newHead.y == fruit.y){

            // grow snake by adding segmen to the head
            fruit = GenerateFruit();
           }
           else{
            //remove the last segment, aka tail
            snake.snakeBody.pop_back();
           }
           //add new head to the front
           snake.snakeBody.push_front(newHead);
            
           // check for collision with itself or screen boundaries
           if(newHead.x < 0 || newHead.x >= gridWidth || newHead.y < 0 || newHead.y >= gridHeight || CollisionCheckItself(snake)){
              gameOver = true;
           }
        }

        //DRAWING
        BeginDrawing();
        ClearBackground(BLACK);

        //drawing the snake
        for(const SnakeSegment& segment : snake.snakeBody){

            DrawRectangle(segment.x * gridSize, segment.y * gridSize, gridSize, gridSize, GREEN);
        }

        //drawing the fruit
        DrawRectangle(fruit.x * gridSize, fruit.y * gridSize, gridSize, gridSize,RED);
        
        if (gameOver){

            DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 -20, 40, WHITE );
        }

        EndDrawing();

    }


    CloseWindow();
    return 0;
}