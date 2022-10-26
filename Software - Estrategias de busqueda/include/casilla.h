#include <iostream>
#include <cstdlib>
#include <vector>
#include <cfloat>
#include <algorithm> // find
#include <cmath>
#include <iomanip> // ceros a la izquierda

#define BLACK_GRND "\033[1;40m"
#define WHITE_GRND "\033[1;47m"
#define RED_GRND "\033[41m"
#define BLUE_GRND "\033[1;44m"
#define GREEN_GRND "\033[1;42m"
#define MAGENT_GRND "\033[1;45m"
#define RESET "\033[0m"

std::ostream& kBoldOff(std::ostream& os) {return os << "\e[0m";}
std::ostream& kBoldOn (std::ostream& os) {return os << "\e[1m";}
std::ostream& kWhite  (std::ostream& os) {return os << "\033[0;37m";}
std::ostream& kCyan   (std::ostream& os) {return os << "\033[0;36m";}
std::ostream& kGreen  (std::ostream& os) {return os << "\033[0;32m";}
std::ostream& kRed    (std::ostream& os) {return os << "\033[0;31m";}
std::ostream& kYellow (std::ostream& os) {return os << "\033[0;33m";}
std::ostream& kPurple (std::ostream& os) {return os << "\033[0;35m";}

#pragma once

class entorno;
class casilla {
  public:
    casilla(size_t, size_t);
    ~casilla(){};

    size_t get_i();
    size_t get_j();
    size_t get_state();
    size_t get_camefrom();
    double get_gScore();  //costo de nodo inicial a este nodo
    double get_fScore(); // costo estimado de nodo inicial a nodo objetivo

    void set_fScore(double);
    void set_gScore(double);
    void set_camefrom(size_t);
    void set_i(size_t);
    void set_j(size_t);
    void set_state(size_t);

    std::ostream& mostrar(std::ostream&);

  private:
    size_t pos_i, pos_j, state=0, camefrom_;
    double gScore_, fScore_;
};