
//
//  game.cpp
//
//  Created by Mahsa on 2/2/23.
//

/* notes:
if u have another map u have to enter it and also define the correct map height and width
and also make sure to use capital words
U=UP
D=DOWN
L=LEFT
R=RIGHT
X=DESIRED SPOTS
B=BOX
@=WORKER
#=WALL
U CAN CHANGE'EM IF U WANT :)
HOPE U ENJOY THE GAME PROFESSOR.
*/
//IF U HAVE DEVC++ ADD #include<windows.h> and check line 224
#include<iostream>
#include <string>
using namespace std;

//if u wanna change the map u have to delete from here down to line 40
/*
#define MAPWIDTH 13
#define MAPHEIGHT 5
#define PLAYERPOSITION pos_y * MAPWIDTH + pos_x


char map[] = {                                              //I stored the map in an array with the type of char

    "#############\n"
    "##x#### ## ##\n"
    "#  B  # @ ###\n"
    "#           #\n"
    "#############\n"
   
};
*/
//I've got some samples to use:

#define PLAYERPOSITION pos_y * MAPWIDTH + pos_x
#define MAPWIDTH 14
#define MAPHEIGHT 10

char map[] = {

    "##############\n"
    "#        xB  #\n"
    "#  x         #\n"
    "#   B        #\n"
    "#            #\n"
    "#     @      #\n"
    "#            #\n"
    "#    B       #\n"
    "#     x      #\n"
    "##############\n"

};
 
 /*
#define MAPWIDTH 14
#define MAPHEIGHT 10
#define PLAYERPOSITION pos_y * MAPWIDTH + pos_x

char map[] = {

    "##############\n"
    "#      # xB  #\n"
    "#  x   # xB  #\n"
    "#   B  # xB  #\n"
    "#      ####  #\n"
    "#     @   #  #\n"
    "#         #  #\n"
    "#    B    #  #\n"
    "#     x      #\n"
    "##############\n"

};

*/

int dest_squares[100];                                                // array to store max cell indexes for 'x' cells

int GetDestSquares()                                                    // init 'x' cells indexes
{
    int count, cell;                                                    // 'x' cell number, current cell index

    for(int row = 0; row < MAPHEIGHT; row++)
    {
        for(int col = 0; col < MAPWIDTH; col++)
        {
            cell = row*MAPWIDTH + col;                               // init current cell index
        
            if(map[cell] == 'x' || map[cell] == 'O')                    // if 'x' cell is empty or with box on it
                dest_squares[count++] = cell;                           // store it in an array
        }
    }

    return count-1;                                                   // return number of 'x' cells
}

void GetPosition(int *pos_x, int *pos_y)                                //gets position of the worker
{
    int cell;                                                           // current cell index

    for(int row = 0; row < MAPHEIGHT; row++)                           // loop ower map rows
    {
        for(int col = 0; col < MAPWIDTH; col++)                        // loop ower map columns
        {
            cell = row * MAPWIDTH + col;                               // init current cell index
        
            if(map[cell] == '@')                                        // if current cell on the map contains player
            {
                *pos_x = col;                                           // store player's x coordinate
                *pos_y = row;                                           // store player's y coordinate
            }
        }
    }
}

void MoveCharacter(int pos_x, int pos_y, int offset)
{
    if(map[PLAYERPOSITION + offset] != '#')                            // if player doesn't hit the wall
    {
        if(((map[PLAYERPOSITION + offset] == 'B') ||                   // if player hits the box
            (map[PLAYERPOSITION + offset] == 'O')) &&                  // or the box was at the right place
            (map[PLAYERPOSITION + offset * 2] != '#' ||                // and box doesn't hit a wall
             map[PLAYERPOSITION + offset * 2] != 'B' ||                // or another box
             map[PLAYERPOSITION + offset * 2] != 'O'))                 // or box on 'x' cell
        {
            map[PLAYERPOSITION] = ' ';                                 // clear previous player's position
            pos_x += offset;                                            // update player's coordinate

            if(map[PLAYERPOSITION + offset] == ' ')                    // if the square next to the box is empty
                map[PLAYERPOSITION + offset] = 'B';                    // push the box

            else if(map[PLAYERPOSITION + offset] == 'x')               // if the square next to the box is 'x'
                map[PLAYERPOSITION + offset] = 'O';                    // mark the box is on it's place

            else
            {
                map[PLAYERPOSITION - offset] = '@';                    // if box hits the wall or another box
                return;                                                 // don't push it any further
            }

            map[PLAYERPOSITION] = '@';                                 // draw the player in the new position
        }

        else                                                            // if the square next to the player is empty
        {
            map[PLAYERPOSITION] = ' ';                                 // clear previous player position
            pos_x += offset;                                            // update player's coordinate
            map[PLAYERPOSITION] = '@';                                 // draw the player in the new position
        }
    }
}

int main()
{
    int key;                                                            // user input key
    int pos_x, pos_y;                                                   //  player's coordinates
    int dest_count;                                                     //  'x' cells counter
    int dest_num = GetDestSquares()+1;                                    // get number of 'x' cells

    printf("%s\n", map);                                                // print map

    while(key != 27)                                                    // till it's not escape button
    {
        GetPosition(&pos_x, &pos_y);                                    // get player's coordinates
        
        key = getchar();                                                // get user input

        switch(key)
        {
            // move character up
            case 'U':
                MoveCharacter(pos_x, pos_y, -MAPWIDTH-1 );
                break;

            // move character down
            case 'D':
                MoveCharacter(pos_x, pos_y, MAPWIDTH+1 );
                break;

            // move character left
            case 'L':
                MoveCharacter(pos_x, pos_y, -1);
                break;

            // move character right
            case 'R':
                MoveCharacter(pos_x, pos_y, 1);
                break;

        }
       
        
            dest_count = 0;                                                 // reset 'x' cells counter
            
            for(int i = 1; i <= 3 ; i++)                                     // for all destination squares
            {
                if(map[dest_squares[i]] == 'O')
                    dest_count++;               // increase 'x' cells counter if box is on 'x' cell
                
                if(map[dest_squares[i]] == ' ')                             // if 'x' cell has been erased
                    map[dest_squares[i]] = 'x';                             // restore it
            }
        
        printf("%s\n", map);                                            // print map
              // if all boxes are on it's places break out of game loop
        if(dest_num == dest_count)
        {
            char arr[8]={'Y','O' , 'U',' ','W','O','N','!'};
            for (int i=0 ; i<7 ; i++){
                cout<<arr[i]<<'\a';
                
                //if u've added <windows.h> also add here:
                //sleep(500);
                //system("color 4");
            }
            break;
        }
       
    }
        
    return 0;
}

