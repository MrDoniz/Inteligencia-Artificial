#include "../src/casilla.cpp"

class entorno {
  public:
    entorno (size_t filas, size_t columnas, char funct);
    ~entorno ();

    size_t get_filas();
    size_t get_columnas();

    void set_filas   (size_t aux);
    void set_columnas(size_t aux);

    bool comprobar  (size_t i, size_t j);
    bool isObstaculo(size_t nodoId);

    void obstaculo(size_t, size_t);
    void coche    (size_t, size_t);
    void meta     (size_t, size_t);
    void write    (std::ostream &os);

    std::ostream& WhiteLine(std::ostream &os);

    void BuscaCamino();
    void prepare_start();
    double heuristicCost(size_t from, size_t to);
    std::vector<size_t> get_vecinos(size_t nodoId);

  private: 
    size_t M, N, meta_, inicio_;
    char heuristicflag_;
    casilla **mapa_;
    bool flag_path;
    std::vector<size_t> _closedSet, _openSet, _path;
};
