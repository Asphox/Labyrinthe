#include "Labyrinthe.h"

using namespace Laby;

Cell::Cell(unsigned int id,unsigned int posX,unsigned posY){
    this->id = id;
    this->posX = posX;
    this->posY = posY;
}

void Cell::changeId(unsigned int id, Cell* source){
  this->id = id;
  for( auto it : linked )
  {
    if(it != source)
    {
      it->changeId(id,this);
    }
  }
}

void Cell::openWallTo(Cell* target){
    if( sqrDistanceTo(target) == 1 )
    {

      if( posX > target->posX ){ walls[W] = false; target->walls[E] = false; }
      else if( posX < target->posX ){ walls[E] = false; target->walls[W] = false; }
      else if( posY > target->posY ){ walls[N] = false; target->walls[S] = false; }
      else if( posY < target->posY ){ walls[S] = false; target->walls[N] = false; }

      linked.insert(target);
      target->linked.insert(this);
      target->changeId(id,this);
    }
}

Labyrinthe::Labyrinthe(unsigned int  sizeX , unsigned int sizeY ){
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    nbrWallMax = sizeX*sizeY-1;

    generator = std::default_random_engine( (unsigned int)time(0) );
    distribX = std::uniform_int_distribution<unsigned int>(0,sizeX-1);
    distribY = std::uniform_int_distribution<unsigned int>(0,sizeY-1);
    distribCard = std::uniform_int_distribution<unsigned int>(N,W);


    for( unsigned int x=0 ; x<sizeX ; x++ )
    {
      cells_array.push_back( std::vector< Cell* >() );
      for( unsigned int y=0 ; y<sizeY ; y++ )
      {
        Cell* cell = new Cell(y*sizeX + x , x , y);
        cells_array[x].push_back( cell );
      }
    }

}

Cell* Labyrinthe::getCellAt(unsigned int x , unsigned int y){
    if( x > sizeX-1 || y > sizeY-1)return nullptr;
    return cells_array[x][y];
}

Cell* Labyrinthe::getRandomCellCard(Cell* source){
    Cell* target = source;
    unsigned int exc1,exc2,card=0;

    if( source->getX() == 0 && source->getY() == 0 ){exc1=N;exc2=W;}
    else if( source->getX() == 0 && source->getY() == sizeY-1){exc1=S;exc2=W;}
    else if( source->getX() == 0 ){exc1=W;exc2=NONE;}
    else if( source->getX() == sizeX-1 && source->getY() == 0){exc1=N;exc2=E;}
    else if( source->getX() == sizeX-1 && source->getY() == sizeY-1){exc1=E;exc2=S;}
    else if( source->getX() == sizeX-1 ){exc1=E;exc2=NONE;}
    else if( source->getY() == 0 ){exc1=N;exc2=NONE;}
    else if( source->getY() == sizeY-1){exc1=S;exc2=NONE;}
    else { exc1=NONE;exc2=NONE; }

    do {
      card = distribCard(generator);
      switch(card)
      {
        case N : if(source->getY() > 0) target = cells_array[source->getX()][source->getY()-1]; break;
        case E : if(source->getX() < sizeX-1) target = cells_array[source->getX()+1][source->getY()]; break;
        case S : if(source->getY() < sizeY-1) target = cells_array[source->getX()][source->getY()+1]; break;
        case W : if(source->getX() > 0) target = cells_array[source->getX()-1][source->getY()]; break;
      }

    } while(card == exc1 || card == exc2 );

    if( source->getId() == target->getId() )return source;

    return target;
}

void Labyrinthe::generate(){
    Cell* source = nullptr;
    Cell* target = nullptr;
    for(unsigned int i=0 ; i<nbrWallMax ; i++)
    {
      do {
        source = getRandomCell();
        target = getRandomCellCard(source);
      } while(target == source);
      source->openWallTo(target);
    }
}

Labyrinthe::~Labyrinthe()
{
    for( unsigned int x=0 ; x<sizeX ; x++ )
    {
      for( unsigned int y=0 ; y<sizeY ; y++ )
      {
        delete cells_array[x][y];
      }
    }
}
