#include "entorno.cpp"

int main() {
  int M, N;
  char funct;
  // Tamaño grid
  std::cout << "Introduzca las dimensiones Lado M x Lado N" << std::endl;
  std::cout << "¿Cuantas filas?: ";
  std::cin >> M;
  std::cout << "¿Cuantas columnas?: ";
  std::cin >> N;
  std::cout << "¿Desea utiliza la función heurística euclidean o Manhatan?:     (e/m)" << std::endl;
  do{
    std::cin >> funct;
    if( funct != 'e' && funct != 'm')
      std::cout << "Ha ocurrido un error, introduzca (e/m)\n";
  } while(funct != 'e' && funct != 'm');


  entorno mapa(M,N, funct);

  // Número de obstaculos
  int n_obs = 0;
  std::cout << "Introduzca el numero de obstaculos: ";
  do{
    std::cin >> n_obs;
    if (n_obs > (M * N - 2))
      std::cout << "Introduce menos obstaculos: ";
  } while (n_obs > (M * N - 2));

  // ¿Todo manual?
  int pos_i, pos_j;
  char value;
  bool retornar;
  std::cout << "¿Quieres introducir los datos manualmente?:     (s/n)" << std::endl;
  do{
    std::cin >> value;
    if( value != 's' && value != 'n')
      std::cout << "Ha ocurrido un error, introduzca (s/n)\n";
  } while(value != 's' && value != 'n');
  switch (value){
    case 'n':
      for(int i = 0; i < n_obs; i++) {
        do {
          retornar = false;
          pos_i = rand() % M;
          pos_j = rand() % N;
          if (pos_i > M-1 || pos_j > N-1)
            retornar = true;
        } while(retornar == true || mapa.comprobar(pos_i, pos_j));
        mapa.obstaculo(pos_i, pos_j );
      }
        do {
          retornar = false;
          pos_i = rand() % M;
          pos_j = rand() % N;
          if (pos_i > M-1 || pos_j > N-1)
            retornar = true;
        } while(retornar == true || mapa.comprobar(pos_i, pos_j));
      mapa.coche(pos_i, pos_j );
        do {
          retornar = false;
          pos_i = rand() % M;
          pos_j = rand() % N;
          if (pos_i > M-1 || pos_j > N-1)
            retornar = true;
        } while(retornar == true || mapa.comprobar(pos_i, pos_j));
      mapa.meta(pos_i, pos_j );
      break;
    case 's':
      mapa.write(std::cout);
      std::cout << "\nIndica las posiciones de los obstaculos\n";
      for(int i = 0; i < n_obs; i++) {
        do {
          retornar = false;
          std::cout << "Indica el número de la fila: ";
          std::cin >> pos_i;
          std::cout << "Indica el número de la columna: ";
          std::cin >> pos_j;
          if (pos_i > M-1 || pos_j > N-1){
            std::cout << "El rango de valores es\n Fila de 0 - " << M-1 << " y Columna de 0 - " << N-1 << "\n";
            retornar = true;
          }
          if (retornar == false && mapa.comprobar(pos_i, pos_j)){
            std::cout << "Esta posición está ocupada.\n";
            retornar = true;
          }
        } while(retornar == true);
        mapa.obstaculo(pos_i, pos_j );
      }
      std::cout << "\nIndica la posición del coche\n";
        do {
          retornar = false;
          std::cout << "Indica el número de la fila: ";
          std::cin >> pos_i;
          std::cout << "Indica el número de la columna: ";
          std::cin >> pos_j;
            if (pos_i > M-1 || pos_j > N-1){
            std::cout << "El rango de valores es\n Fila de 0 - " << M-1 << " y Columna de 0 - " << N-1 << "\n";
            retornar = true;
          }
          if (retornar == false && mapa.comprobar(pos_i, pos_j)){
            std::cout << "Esta posición está ocupada.\n";
            retornar = true;
          }
        } while(retornar == true);
      mapa.coche(pos_i, pos_j );
      std::cout << "\nIndica la posición de destino\n";
        do {
          retornar = false;
          std::cout << "Indica el número de la fila: ";
          std::cin >> pos_i;
          std::cout << "Indica el número de la columna: ";
          std::cin >> pos_j;
          if (pos_i > M-1 || pos_j > N-1){
            std::cout << "El rango de valores es\n Fila de 0 - " << M-1 << " y Columna de 0 - " << N-1 << "\n";
            retornar = true;
          }
          if (retornar == false && mapa.comprobar(pos_i, pos_j)){
            std::cout << "Esta posición está ocupada.\n";
            retornar = true;
          }
        } while(retornar == true);
      mapa.meta(pos_i, pos_j );
      break;
  }
  mapa.BuscaCamino();
  mapa.write(std::cout);
  std::cout << "Leyenda: " << kRed <<"Coche"<< kCyan <<" Obstaculo" << kGreen <<" Destino" << kPurple <<" Camino\n" << kWhite;
  return 0;
}