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
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <iterator>
#include <string.h>
#include <fstream>
#include <iostream>
#include <algorithm>

/* Constantes en mi sistema de memoria */
#define MAX_BLOCKS 16
#define MAX_ADDRESS 11
#define MAX_DATA 8
#define MAX_DATA_MAIN 2048

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
    vector<string> data;

    /* Contructor */
    Block() {
      data = std::vector<string> (8); // cada linea esta bits
    }
/*
>>>>>>> 5c3252fdc50fbfb4d6c9eed87931b2d153462833
    Block(int newV, string newAddress) {

      v = newV;
      address = newAddress;

    }*/
};

/*
 * Estructura direccion fisica
    Estructura encargada de simular cada instruccion fisica, teniendo
    consigo 2 atributos, el primero (blockAddress) de tipo string para representar la direccion del bloque, el
    segundo (offset) de tipo string para representar el block offset.
*/
class PhysicalAddress {

  public:

    /* Atributos */

    string blockAddress;
    string offset;

    /* Contructor */
    PhysicalAddress() {}
    PhysicalAddress( string newBlockAddress, string newOffset) {

      blockAddress = newBlockAddress;
      offset = newOffset;

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
    vector< string > setQueue;

   /* Contructor */
   Cache() {

     this->blocks =  vector<Block*>(MAX_BLOCKS);
     for (int i = 0; i < MAX_BLOCKS; i++)
       this->blocks[i] = new Block;
   }

   /* metodos */

   string getLeasRecentlyUsed() {

     return setQueue[setQueue.size() - 1];

   }

   void setLeasRecentlyUsed(string address) {

     auto position  = find(setQueue.begin(), setQueue.end(), address);
     if ( position != setQueue.end())  {
       setQueue.erase(position);
     }
     setQueue.insert(setQueue.begin(), address);

   }

   int getPosAddress (string direccion ){
     for (int i = 0; i < MAX_BLOCKS; i++)
       if(this->blocks[i]->address == direccion) return i;
       return -1;
   }

   bool isHit( int pos ){
     if( pos != -1){
       if( this->blocks[pos]-> v == 1 ) return  true;
       else return false;
     }
     else return false;
   }

};


/*
 * Estructura generador de direcciones:
    Estructura encargada de generar de manera aleatoria direcciones fisicas.

*/


class MemoryMain {

  public:

    /* Atributo */
    vector<string> data;

    /* Construtor */
    MemoryMain() {};


    vector<string> getData( const int x, const int y ) {

      /* Vector tipo string para almacenar la informacion
        que hay en la memoria principal, dado un rango [x - y] */
      vector<string> information;

      if (x >= 0 && y < data.size()) {

        for (int i = x; i < y; i++)
          information.push_back(data[i]);
      }

      return information;
    }



};


class Output {

  public:

    int hit;
    int mips;

    Output() {

      hit = 0;
      mips = 0;

    }

    updateOutPut(string address, string data) {

      string linea;
      std::ifstream file("Output.txt");
      file << address << " " << data << " " << endl;
      file.close();

    }


}
// +++ Manejar todas los paramteros de las funciones como referencia +++ //

/* Firmas de funciones */

void modificarValor( Cache & );
void leerDataMemoryMain( MemoryMain & );
void Gen( PhysicalAddress & );

/* Definición de funciones */

void Gen( PhysicalAddress & direccion ) {
    string aux="";
    string aux2="";

    for (int i = 0; i < 11; i++) {
        int n = rand() % 2;
        aux+=to_string(n);
    }
    direccion.blockAddress = aux;
    for (int i = 0; i < 3; i++) {
        int n = rand() % 2;
        aux2+=to_string(n);
    }
    direccion.offset = aux2;
}

void modificarValor( Cache & memoryCache ) {

  memoryCache.blocks[0]->v = 0;

}

void leerDataMemoryMain( MemoryMain & memoryMain ) {

  string linea;
  std::ifstream file("MemoryMain.txt");

  while (!file.eof()) {

    file >> linea;
    memoryMain.data.push_back(linea);

  }
  file.close();
}

int main( int argc, char const *argv[] ) {

  std::cout << "Be happy!" << '\n';

  /* Creando instancia de estructura Cache */
  Cache memoryCache;
  MemoryMain memoryMain;

  leerDataMemoryMain( memoryMain );



  return 0;
}
