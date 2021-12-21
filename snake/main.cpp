#include <iostream>
#include <conio.h>
#include <Windows.h>

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum direction { STOP = 0, NORTH, SOUTH, WEST, EAST };
direction dir;
int tailX[100], tailY[100];
int length;

void setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                std::cout << "#";
            if (i == y && j == x)
                std::cout << "o";
            else if (i == fruitY && j == fruitX)
                std::cout << "F";
            else
            {
                bool print = false;
                for (int k =0; k < length; k++)
                {
                   
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << "o";
                        print = true;
                    }
                }
                if(!print)
                    std::cout << " ";
               
            }
                


            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
    std::cout << "score: " << score << std::endl;
}

void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                dir = WEST;
                break;
            case 'w':
                dir = NORTH;
                break;
            case 'd':
                dir = EAST;
                break;
            case 's':
                dir = SOUTH;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X,  prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i =1; i <length; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir)
    {
        case WEST:
            x--;
            break;
        case NORTH:
            y--;
            break;
        case EAST:
            x++;
            break;
        case SOUTH:
            y++;
            break;
    }

        if (x> width)
        {
            x =0;
            dir = EAST;
        }
        if (x < 0)
        {
            x = width;
            dir = WEST;
        }
        if (y > height)
        {
            y= 0;
            dir = SOUTH;
        }
        if (y < 0)
        {
            y= width;
            dir = NORTH;
        }
    for (int i =0;i < length; i++)
    {
        if(tailX[i] ==x && tailY[i] == y)
            gameOver = true;
    }
    if (x == fruitX && y == fruitY)
    {
        length++;
        score+=1; 
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main()
{
    setup();
    while (!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(10);
    }
    if (gameOver == true)
    {
        exit(0);
    }
    
}