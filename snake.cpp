#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <chrono>

using namespace std;

int score = 0;
int timeLimit = 500;

struct Position
{
    int x;
    int y;
};

void iniz(bool grid[10][10], Position *pos, char *ori, vector<Position> &positions)
{
    pos->x = 0;
    pos->y = 0;
    positions.push_back(*pos);
    *ori = 'W';
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            grid[i][j] = false;
        }
    }
    grid[0][0] = true;
}

void printGrid(bool grid[10][10], Position treat, Position pos, char ori)
{
    for(int i = 9; i >= 0; i--)
    {
        for(int j = 0; j < 10; j++)
        {
            if(i == treat.x && j == treat.y)
            {
                cout << "O";
            }
            else if(i == pos.x && j == pos.y)
            {
                switch(ori)
                {
                    case 'W':
                    cout << "^";
                    break;
                    case 'A':
                    cout << "<";
                    break;
                    case 'S':
                    cout << "v";
                    break;
                    case 'D':
                    cout << ">";
                    break;
                }
            }
            else if(grid[i][j])
            {
                cout << "X";
            }
            else
            {
                cout << "-";
            }
            cout << "\t";
        }
        cout << "\n";
    }
}

char timeChecker(char ori)
{
    auto start = chrono::steady_clock::now();
    while(!kbhit())
    {
        if(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() > timeLimit)
        {
            return -1;
        }
    }
    return getch();
}

int getinput(char *ori)
{
    auto start = chrono::steady_clock::now();
    char input;
    char isOverTime = timeChecker(*ori);
    if(isOverTime == -1)
    {
        return 0;
    }
    input = isOverTime;

    if(input == 'w' && *ori != 'S')
    {
        *ori = 'W';
    }
    else if(input == 'a' && *ori != 'D')
    {
        *ori = 'A';
    }
    else if(input == 's' && *ori != 'W')
    {
        *ori = 'S';
    }
    else if(input == 'd' && *ori != 'A')
    {
        *ori = 'D';
    }
    return 0;
}

void gridSetter(bool grid[10][10], vector<Position> &positions)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            grid[i][j] = false;
        }
    }
    for(int i = 0; i < positions.size(); i++)
    {
        grid[positions.at(i).x][positions.at(i).y] = true;
    }
}

Position treatPlace(bool grid[10][10])
{
    srand(time(0));
    Position validTreatPlace;
    validTreatPlace.x = rand()%10;
    validTreatPlace.y = rand()%10;
    while(grid[validTreatPlace.x][validTreatPlace.y])
    {
        validTreatPlace.x = rand()%10;
        validTreatPlace.y = rand()%10;
    }
 
    return validTreatPlace;
}

void movement(bool grid[10][10], char *ori, Position *pos, Position *treat, vector<Position> &positions)
{
    if(*ori == 'W')
    {
        (pos->x)++;
    }
    else if(*ori == 'A')
    {
        (pos->y)--;
    }
    else if(*ori == 'S')
    {
        (pos->x)--;
    }
    else if(*ori == 'D')
    {
        (pos->y)++;
    }
    if(!grid[pos->x][pos->y])
    {
        grid[pos->x][pos->y] = true;
    }
    else
    {
        pos->x = -1;
    }

    if(pos->x == treat->x && pos->y == treat->y)
    {
        *treat = treatPlace(grid);
        positions.push_back(*pos);
        score++;
    }
    else
    {
        positions.erase(positions.begin());
        positions.push_back(*pos);
    }
    gridSetter(grid, positions);
}

void game(bool grid[10][10], char *ori, Position *pos, vector<Position> &positions)
{
    iniz(grid, pos, ori, positions);
    int startTime = time(0);
    Position treat;
    treat = treatPlace(grid);
    while(pos->x > -1 && pos->x < 10 && pos->y > -1 && pos->y < 10)
    {
        if(score == 10 && timeLimit == 500)
        {
            timeLimit-=100;
        }
        if((score == 20 && timeLimit == 400))
        {
            timeLimit-=50;
        }
        if(score == 30 && timeLimit == 350)
        {
            timeLimit-=50;
        }
        cout << "Score: " << score << "\n";
        printGrid(grid, treat, *pos, *ori);
        getinput(ori);
        movement(grid, ori, pos, &treat, positions);
        system("cls");
    }
    cout << "Game Over\nScore: " << score << "\n";
}

int gameMode()
{
    string lvl1 = "EASY\n";
    string lvl2 = "MEDIUM\n";
    string lvl3 = "DIFFICULT\n";
    int x = 0;
    char a;
   
    cout << "Choose the difficulty!\n\nO" << lvl1 << " " << lvl2 << " " << lvl3;
    a = getch();
    system("cls");
    
    do
    {
        if(a == 'w')
        {
            if(x == 0)
            {
                x = 2;
            }
            else
            {
                x--;
            }
        }
        if(a == 's')
        {
            x++;
        }
        if(x % 3 == 0)
        {
            cout << "Choose the difficulty!\n\nO" << lvl1 << " " <<lvl2 << " " << lvl3;
        }
        if(x % 3 == 1)
        {
            cout << "Choose the difficulty!\n\n " << lvl1 << "O" <<lvl2 << " " << lvl3;
        }
        if(x % 3 == 2)
        {
            cout << "Choose the difficulty!\n\n " << lvl1 << " " <<lvl2 << "O" << lvl3;
        }
        a = getch();
        system("cls");
    } while (a != 13);
    a = 0;
    system("cls");
    cout << "Press Enter to start\n";
    do
    {
        a = getch();
    } while (a != 13);
    if(x % 3 == 0)
    {
        return 500;
    }
    if(x % 3 == 1)
    {
        return 450;
    }
    return 400;
}

int main()
{
    timeLimit = gameMode();
    bool grid[10][10];
    vector<Position> positions;
    srand(time(0));
    Position pos;
    char ori;
    game(grid, &ori, &pos, positions);
    system("pause");
    return 0;
}