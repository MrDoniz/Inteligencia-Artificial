#include "../include/casilla.h"

casilla::casilla(size_t m, size_t n) {
  set_i(m);
  set_j(n);
  gScore_ = DBL_MAX;
  fScore_ = DBL_MAX;
}

size_t casilla::get_i()        {return pos_i;}
size_t casilla::get_j()        {return pos_j;}
size_t casilla::get_state()    {return state;}
double casilla::get_gScore()   {return gScore_;}
double casilla::get_fScore()   {return fScore_;}
size_t casilla::get_camefrom() {return camefrom_;}

void casilla::set_i(size_t value)      {pos_i = value;}
void casilla::set_j(size_t value)      {pos_j = value;}
void casilla::set_state(size_t value)  {state = value;}
void casilla::set_gScore(double aux)   {gScore_ = aux;}
void casilla::set_fScore(double aux)   {fScore_ = aux;}
void casilla::set_camefrom(size_t pos) {camefrom_ = pos;}

std::ostream& casilla::mostrar(std::ostream& os) {
  size_t aux = get_state();
  switch (aux) {
    case 0:
      os << WHITE_GRND << "  " << BLACK_GRND << "  " << WHITE_GRND << "  " << RESET;
      break;
    case 1:
      os << WHITE_GRND << "  " << BLUE_GRND << "  " << WHITE_GRND << "  " << RESET;
      break;
    case 2:
      os << WHITE_GRND << "  " << RED_GRND << "  " << WHITE_GRND << "  " << RESET;
      break;
    case 3:
      os << WHITE_GRND << "  " << GREEN_GRND << "  " << WHITE_GRND << "  " << RESET;
      break;
    case 4:
      os << WHITE_GRND << "  " << MAGENT_GRND << "  " << WHITE_GRND << "  " << RESET;
      break;
  }
  return os; 
}
