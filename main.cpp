#include <iostream>
#include <ctime>
#include "Labyrinthe.h"

using namespace Laby;

void display(Labyrinthe& lab)
{
    for(unsigned int y=0; y < lab.getSizeY() ; y++)
    {
      for(unsigned int x=0 ; x < lab.getSizeX() ; x++)
      {
        if ( x==0 )std::cout << " ";
        if( lab.getCellAt(x,y)->isWall(N) ) std::cout << "_ ";
        else std::cout << "  ";
      }
      std::cout << std::endl;
      bool eastBefore = false;
      for(unsigned int x=0 ; x < lab.getSizeX() ; x++)
      {
        if( lab.getCellAt(x,y)->isWall(W) && !eastBefore )std::cout << "|";
        else if( lab.getCellAt(x,y)->isWall(W) && eastBefore ) std::cout << "";
        else std::cout << "";
        eastBefore = false;
        std::cout << " ";
        if( lab.getCellAt(x,y)->isWall(E) ){std::cout << "|";eastBefore=true;}
        else std::cout << " ";
      }
      std::cout << std::endl;
    }
    for( unsigned int x=0; x < lab.getSizeX() ; x++)
    {
      if ( x==0 )std::cout << " ";
      if( lab.getCellAt(x,lab.getSizeY()-1)->isWall(S) ) std::cout << "_ ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
  Labyrinthe lab(10,10);
  lab.generate();
  display(lab);
  return 0;
}
