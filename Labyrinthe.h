#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <set>
#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>
#include <cstdlib>

namespace Laby
{


/* points cardinaux */
constexpr uint8_t N = 0;
constexpr uint8_t E = 1;
constexpr uint8_t S = 2;
constexpr uint8_t W = 3;
constexpr uint8_t NONE = 4;

class Cell
{
private:
  unsigned int id,posX,posY;
  bool walls[4] = {true,true,true,true}; //tableau representant l'etat des murs d'une cellule entre 'ouvert'(false) ou 'fermé'(true)
  std::set< Cell* > linked;  //tableau des cellules ayant la meme id que la cellule courante ( utile pour le changement d'identifiant )

public:
  bool checked = false;

 /*constructeur*/
  Cell(unsigned int id,unsigned int posX,unsigned posY);

  /*remplace l'id de la cellule courante ( et des cellules voisines reliées ) par l'id de la cellule source*/
  void changeId(unsigned int id, Cell* source);

  inline uint16_t getId(){ return id; } const

  inline void setId( uint16_t id ){ this->id = id; }

  inline unsigned int getX(){ return posX; } const
  inline unsigned int getY(){ return posY; } const

  /*renvoi si un mur existe suivant la direction voulue*/
  inline bool isWall(uint8_t card){ return walls[card]; } const

  /*renvoi la distance au carré avec une autre cellule ( pour verifier si les  cellules selectionnées pour l'ouverture sont bien adjacentes )*/
  inline unsigned int sqrDistanceTo(Cell* target) const {
    return  (target->posX - posX)*(target->posX - posX) + (target->posY - posY)*(target->posY - posY) ;
  }

  /* creé une ouverture entre la cellule courante et la cellule target*/
  void openWallTo(Cell* target);

};


class Labyrinthe
{
private:
  unsigned int sizeX,sizeY,nbrWallMax;
  std::vector< std::vector< Cell* > > cells_array;

  std::default_random_engine generator;  //generateur peseudo-aleatoire C++11
  std::uniform_int_distribution<unsigned int> distribX; //distribution uniforme pour la coord x d'une cellule
  std::uniform_int_distribution<unsigned int> distribY; //distribution uniforme pour la coord y d'une cellule
  std::uniform_int_distribution<unsigned int> distribCard; //distribution uniforme pour le point cardinal

  inline Cell* getRandomCell(){
    return cells_array[distribX(generator)][distribY(generator)];
  }

    /*renvoi une cellule adjacente à source au hasard ( en verifiant si le mur entre les deux peut etre ouvert )*/
  Cell* getRandomCellCard(Cell* source);

public:

    /*constructeur*/
  Labyrinthe(unsigned int  sizeX , unsigned int sizeY );

    /*genere le labyrinthe*/
  void generate();

  inline unsigned int getSizeX() const { return sizeX; }
  inline unsigned int getSizeY() const { return sizeY; }
  Cell* getCellAt(unsigned int x , unsigned int y);

  ~Labyrinthe();


};

}

#endif //LABYRINTHE_H
