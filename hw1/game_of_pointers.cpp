#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
		      int rows, int columns, int &reserves, ofstream &output){

    //check to see if skirmish_row is in bounds
    if (skirmish_row < 0 || skirmish_row > (columns-1)) {
      cout << "out of bounds" << endl;
      return false;
    }

    for (int i = 0; i < rows; i++) {
      Warrior* protector = protectors[i][skirmish_row];
      Warrior* invader = invaders[skirmish_row][i];

      //check if invader or protector is not there (null)
      if(!protector) {
        //invaders win
        return true;
      }
      if(!invader) {
        output << "No assault" << endl;
        break;
      }

        if ((protector -> power > invader -> power) ||
        (protector -> weapon == "axe" && invader -> weapon == "sword")) {
        //case where protector wins
        delete invaders[skirmish_row][i];
        invaders[skirmish_row][i] = NULL;
        output << "Invader killed" << endl;

      } else if ((protector -> power < invader -> power) ||
        (protector -> weapon == "sword" && invader -> weapon == "axe")) {
        //case where invader wins

        //check for open positions in invader army
        bool emptySpotFound = false;
        for (int j = 0; j < columns; j++) {
          if (emptySpotFound == false) {
            for (int k = 0; k < rows; k++) {
              if (invaders[j][k] == NULL) {
                invaders[j][k] = protector;
                emptySpotFound = true;
                output << "Protector defected" << endl;
                protectors[i][skirmish_row] = NULL;
                break;
              }
            }
          }
        }
        //if there was no empty spot, kill the protector
        if (emptySpotFound == false) {
          output << "Protector killed" << endl;
          delete protectors[i][skirmish_row];
          protectors[i][skirmish_row] = NULL;
        }

        //check to see if protectors have reserve
        if (reserves > 0) {
          //if they do, replace fallen protector and decrement reserves
          protectors[i][skirmish_row] = new Warrior();
          protectors[i][skirmish_row] -> power = 100;
          protectors[i][skirmish_row] -> weapon = "axe";
          reserves = reserves - 1;
        }
      } else if (protector -> power == invader -> power) {
       //draw
       output << "Duel ends in draw" << endl;
     }
    }
    return false;
}

//this is just for debugging
void printWarriors(Warrior*** warriors,int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << warriors[i][j] -> power << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserve;
    int skirmishes;

    //read the input file and initialize the values here.

    input >> rows >> cols >> reserve >> skirmishes;

    Warrior ***protectors;
    Warrior ***invaders;

    //initialize the protectors and invaders here.
    protectors = new Warrior**[rows];

    for (int i = 0; i < rows; i++) {
      protectors[i] = new Warrior*[cols];
      for (int j = 0; j < cols; j++) {
        protectors[i][j] = new Warrior();
        protectors[i][j] -> power = i*10+(j+1)*10;
        if (i%2 == 0) {
          protectors[i][j] -> weapon = "axe";
        } else {
          protectors[i][j] -> weapon = "sword";
        }
      }
    }

    invaders = new Warrior**[cols];
    for (int i = 0; i < cols; i++) {
      invaders[i] = new Warrior*[rows];
      for (int j = 0; j < rows; j++) {
        invaders[i][j] = new Warrior();
        invaders[i][j] -> power = i*10+(j+1)*10;
        if (i%2 == 1) {
          invaders[i][j] -> weapon = "axe";
        } else {
          invaders[i][j] -> weapon = "sword";
        }
      }
    }

    bool end;
    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;

        //read the input file to find the value for skirmish row
        input >> skirmish_row;
        //In general, it is bad style to throw everything into your main function
        end = skirmish(protectors, invaders, skirmish_row, rows, cols, reserve, output);
        if (end == true) {
          output << "Winner: invaders" << endl;
          break;
        }
    }
    if (end == false) {
      output << "Winner: protectors" << endl;
    }
    //deallocate your memory.
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if(protectors[i][j]) {
        delete protectors[i][j];
      }
      }
      delete [] protectors[i];
    }

    delete [] protectors;

    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        if(invaders[i][j]) {
        delete invaders[i][j];
      }
      }
      delete [] invaders[i];
    }

    delete [] invaders;

    return 0;
}
