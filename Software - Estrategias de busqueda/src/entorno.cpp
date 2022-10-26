#include "../include/entorno.h"

entorno::entorno(size_t filas, size_t columnas, char funct) {
  heuristicflag_ = funct;
  set_filas(filas);
  set_columnas(columnas);
  mapa_ = new casilla *[ filas * columnas ];
  for(size_t i = 0; i < filas; i++)
    for(size_t j=0; j<columnas;j++)
      mapa_[i * columnas + j] = new casilla(i, j);
}

entorno::~entorno() {
  for (size_t i = 0; i < get_filas(); i++)
    for(size_t j = 0; j < get_columnas(); j++)
      delete mapa_[i* get_columnas() +j];
  delete[] mapa_;
}

void entorno::obstaculo(size_t i, size_t j) {
  mapa_[i * get_columnas() + j]->set_state(1);
}

bool entorno::comprobar(size_t i, size_t j){
  unsigned prueba;
  prueba = mapa_[i * get_columnas() + j]->get_state() ;
  if (prueba != 0) {
    return true;
  } else {
    return false;
    std::cout << "Ha ocurrido un errror.\n";
  }
}

void entorno::coche(size_t i, size_t j) {
  inicio_ = i * get_columnas() + j;
  mapa_[i * get_columnas() + j]->set_state(2);
}

void entorno::meta(size_t i, size_t j) {
  meta_ = i * get_columnas() + j;
  mapa_[i * get_columnas() + j]->set_state(3);
}

void entorno::write(std::ostream &os) {
  os << "   "; 
  for (unsigned a = 0; a < get_columnas(); a++){
    os << "    " << std::setfill('0') << std::setw(2) << a;
  }
  for (size_t i = 0; i < get_filas(); i++) {
    WhiteLine(os);
    os << std::setfill('0') << std::setw(3) << i << " " << WHITE_GRND << " " << RESET;
    for (size_t j = 0; j < get_columnas(); j++) {
      mapa_[i * get_columnas() + j]->mostrar(os);
    }
   os << WHITE_GRND << " " << RESET;
  }
 WhiteLine(os);
}

size_t entorno::get_filas() {  return M;  }
size_t entorno::get_columnas() {  return N;  }
void entorno::set_filas(size_t aux) {  M = aux;  }
void entorno::set_columnas(size_t aux) {  N = aux;  }

bool entorno::isObstaculo(size_t nodoId) {
  if (mapa_[nodoId]->get_state() == 1)
    return true;
  else 
    return false;
}

std::vector<size_t> entorno::get_vecinos(size_t nodoId) {
  std::vector<size_t> vecinos;
  //si no está a la izq del todo  comprueba oeste 
  if (mapa_[nodoId]->get_j() > 0 && !isObstaculo(nodoId - 1)) 
    vecinos.push_back(nodoId - 1); 
  //si no está a la dcha del todo comprueba este
  if (mapa_[nodoId]->get_j() < (get_columnas() - 1) && !isObstaculo(nodoId + 1)) 
    vecinos.push_back(nodoId + 1); 
  //si no esta arriba del todo comprueba norte
  if (mapa_[nodoId]->get_i() > 0 && !isObstaculo(nodoId - get_columnas())) 
    vecinos.push_back(nodoId - get_columnas()); 
  //si no está abajo del todo comprueba sur
  if (mapa_[nodoId]->get_i() < (get_filas() - 1) && !isObstaculo(nodoId + get_columnas())) 
    vecinos.push_back(nodoId + get_columnas());

  return vecinos;
}

void entorno::BuscaCamino() {
  unsigned t0, t1;
  t0=clock();
  int logintud_camino_minimo = 0;
  int nodos_expandidos = 0;
  prepare_start();
  flag_path = false;
  while (!_openSet.empty()) {
    double lowestF = DBL_MAX;
    size_t cur;
    for (auto it = _openSet.begin(); it != _openSet.end(); it++) {
      if (mapa_[*it]->get_fScore() < lowestF) {
        lowestF = mapa_[*it]->get_fScore();
        cur = *it;
      }
    }
    if (cur == meta_) {
      flag_path = true;
      break;
    } else {
      auto it = std::find(_openSet.begin(), _openSet.end(), cur);
      _openSet.erase(it);
      _closedSet.push_back(cur);
      std::vector<size_t> vecinos = get_vecinos(cur);
      for (size_t i = 0; i < vecinos.size(); i++) {
        auto it = std::find(_closedSet.begin(), _closedSet.end(), vecinos[i]);
        if (it == _closedSet.end()) {
          double tentativeGScore = mapa_[cur]->get_gScore() + heuristicCost(cur, vecinos[i]);
          auto it = std::find(_openSet.begin(), _openSet.end(), vecinos[i]);
          if (it == _openSet.end()) {
            nodos_expandidos++;
            _openSet.push_back(vecinos[i]);
          } else if (tentativeGScore >= mapa_[vecinos[i]]->get_gScore()) {
            continue;
          }
          mapa_[vecinos[i]]->set_camefrom(cur);
          mapa_[vecinos[i]]->set_gScore(tentativeGScore);
          mapa_[vecinos[i]]->set_fScore(tentativeGScore + heuristicCost(vecinos[i], meta_));
        }
      }
    }
  }
  if (flag_path) {
    _path.push_back(meta_);
    size_t cur = mapa_[meta_]->get_camefrom();
    while (cur != inicio_) {
      logintud_camino_minimo++;
      _path.push_back(cur);
      size_t previous = mapa_[cur]->get_camefrom();
      mapa_[cur]->set_state(4);
      cur = previous;
    }
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    std::cout << "\n\nHay una camino al destino.";
    std::cout << "\nLongitud del camino mínomo: " << logintud_camino_minimo;
    std::cout << "\nNodos expandidos          : " << nodos_expandidos;
    std::cout << "\nTiempo de ejecución " << time << " segundos." << std::endl;
  } else {
    std::cout << "¡No hay camino hacia el destino!" << std::endl;
  }
  return;
}

std::ostream& entorno::WhiteLine(std::ostream &os) {
  size_t count=0;
  os << "\n" << "    " << WHITE_GRND << " ";
  while(count<get_columnas()){
    os << "      ";
    count++;
  }
  os << " " << RESET << "\n";

  return os;
}

void entorno::prepare_start() { 
  mapa_[inicio_]->set_gScore(0); 
  mapa_[inicio_]->set_fScore(heuristicCost(inicio_, meta_)); 
  _path.push_back(inicio_);
  _openSet.push_back(inicio_);
  flag_path = false;
}

double entorno::heuristicCost(size_t from, size_t to){
  double cost;
  if (heuristicflag_ == 'e') {
    cost = sqrt(((mapa_[from]->get_i() - mapa_[to]->get_i()) * (mapa_[from]->get_i() - mapa_[to]->get_i())) + ((mapa_[from]->get_j() - mapa_[to]->get_j())*(mapa_[from]->get_j() - mapa_[to]->get_j())));
  }
    if (heuristicflag_ == 'm') {
    int aux1 = mapa_[from]->get_i() - mapa_[to]->get_i(), aux2 = mapa_[from]->get_j() - mapa_[to]->get_j(); 
    cost = std::abs(aux1) + std::abs(aux2);
  }
  return cost;
}
