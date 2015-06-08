#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "time.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

int playerPosition = 0;
bool playing = true;
int FIELD_SIZE = 0;

vector<vector<char>> field(FIELD_SIZE);

void createField() {
    srand(time(NULL));
    for(int i = 0; i < FIELD_SIZE; i++) {
        // define special chars in field
        int characterPosition = rand() % FIELD_SIZE + 1;
        char typeChar = '0';
        if(i != 0 && i != (FIELD_SIZE - 1)) {
            if(rand() % 2 + 1 == 1) {
                typeChar = 'T';
            }
        } else if(i == 0) {
            typeChar = 'G';
            playerPosition = (characterPosition + 1);
        } else if(i == (FIELD_SIZE - 1)) {
            typeChar = 'X';
        }

        // loop through row and add characters
        for(int j = 0; j < FIELD_SIZE; j++) {
            if(typeChar != '0' && characterPosition == j) { field[i].push_back(typeChar); }
            else { field[i].push_back('.'); }
        }
    }
}

void printField() {
    system("cls");
    for(int i = 0; i < FIELD_SIZE; i++) {
        for(int j = 0; j < FIELD_SIZE; j++) {
            cout << field[i][j];
            if(j == (FIELD_SIZE - 1)) { cout << endl; }
        }
    }
}

void changeCharacterOnPosition(int, char);
int checkCollision(int);
void movePlayer() {
    int c = 0;
    switch(c = getch()) {
        case KEY_UP :
            if(playerPosition > FIELD_SIZE) {
                changeCharacterOnPosition(playerPosition, '.');
                playerPosition -= FIELD_SIZE;
            }
            break;
        case KEY_DOWN :
            if(playerPosition < (FIELD_SIZE * FIELD_SIZE) - 10) {
                changeCharacterOnPosition(playerPosition, '.');
                playerPosition += FIELD_SIZE;
            }
            break;
        case KEY_RIGHT :
            if(playerPosition < (FIELD_SIZE * FIELD_SIZE)) {
                changeCharacterOnPosition(playerPosition, '.');
                playerPosition += 1;
            }
            break;
        case KEY_LEFT :
            if(playerPosition > 1) {
                changeCharacterOnPosition(playerPosition, '.');
                playerPosition -= 1;
            }
            break;
    }

    //check new position for collision, after that move the player
    int status = checkCollision(playerPosition);
    changeCharacterOnPosition(playerPosition, 'G');
    printField();

    if(status != 0) {
        playing = false;
        if(status == 1) {
            cout << "You win!" << endl;
        }
        if(status == -1) {
            cout << "You lose!" << endl;
        }
    }
}

void changeCharacterOnPosition(int position, char character) {
    int counter = 0;
    for(int i = 0; i < FIELD_SIZE; i++) {
        for(int j = 0; j < FIELD_SIZE; j++) {
            counter++;
            if(counter == position) {
                field[i][j] = character;
            }
        }
    }
}

int checkCollision(int position) {
    int counter = 0;
    for(int i = 0; i < FIELD_SIZE; i++) {
        for(int j = 0; j < FIELD_SIZE; j++) {
            counter++;
            if(counter == position) {
                if(field[i][j] == 'X') {
                    return 1;
                }
                if(field[i][j] == 'T') {
                    return -1;
                }
            }
        }
    }

    return 0;
}

void initGame() {
    startInit :
    playerPosition = 0;
    playing = true;
    cout << "Enter the size of the dungeon: " << endl;
    int dungeonSize = 0;
    cin >> dungeonSize;
    if(dungeonSize < 5) {
        cout << "Minimal size is 5" << endl;
        goto startInit;
    }

    FIELD_SIZE = dungeonSize;
    field.clear();
    field.resize(FIELD_SIZE * FIELD_SIZE);

    createField();
    printField();
}

int main()
{
    startOver:
    initGame();

    do{
        movePlayer();
    } while(playing);

    cout << "Press 1 to start again" << endl;
    int input;
    cin >> input;
    if(input == 1) {
        goto startOver;
    }

    return 0;
}
