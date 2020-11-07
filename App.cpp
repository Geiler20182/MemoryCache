/*

 * Arquitetura del Computador
 * Pontificia Universidad Javeriana Cali
 * Memoria Cache
 * Por : Angelo Lozano y Geiler Hipia Mejía
 * Version : 1.0

*/

/* Librerias necesarias */
#include <iostream>
#include <vector>
#include <string.h>

/* Constantes en mi sistema de memoria */
#define MAX_BLOCKS 16
#define MAX_ADDRESS 11
#define MAX_DATA 8

using namespace std;

/* Estructuras */

/*
 * Estructura bloque
    Estructura encargada de simular cada bloque de la memoria cache, teniendo
    consigo 3 atributos, el primero (v) de tipo int para representar el bit de validez, el
    segundo (address) de tipo string para representar la direccion, y por ultimo
    el (data) de tipo string para representar el dato en la memoria cache
*/
class Block {

  public:

    /* Atributos */
    int v;
    string address;
    string data;

    /* Contructor */
    Block() {}

    Block(int v, string address, string data) {

      this.v = v;
      this.address = address;
      this.data = data;

    }
};

/*
 * Estructura cache:
    Estructura encargada de simular la memoria cache
    teniendo consigo un atributo de tipo vector que contiene
    punteros a bloques.
*/
class Cache {

  public:

    /* Atributos */
    vector< Block* > blocks;

   /* Contructor */
   Cache() {

     this->blocks =  vector<Block*>(MAX_BLOCKS);
     for (int i = 0; i < MAX_BLOCKS; i++)
       this->blocks[i] = new Block;
   }

};

// +++ Manejar todas los paramteros de las funciones como referencia +++ //

/* Firmas de funciones */

void modificarValor( Cache & );

/* Definición de funciones */

void modificarValor( Cache & memoryCache ) {

  memoryCache.blocks[0]->v = 0;

}

int main( int argc, char const *argv[] ) {

  std::cout << "Be happy!" << '\n';

  /* Creando instancia de estructura Cache */
  Cache memoryCache;

  /* Ejemplo de asignacion y modificacion */

  memoryCache.blocks[0]->v = 1;

  modificarValor( memoryCache );

  memoryCache.blocks[0]->address = "010101001";
  memoryCache.blocks[0]->data = "111111111";

  cout << memoryCache.blocks[0]->v << '\n';
  cout << memoryCache.blocks[0]->address << '\n';
  cout << memoryCache.blocks[0]->data << '\n';

  /* Fin de ejemplo */

  return 0;
}
