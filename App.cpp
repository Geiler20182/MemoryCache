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
    int pos;
   /* Contructor */
   Cache() {

     pos = 0;
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

   bool isHit( int x ){
     if( x >= 0 ){
       if( this->blocks[x]-> v == 1 ) return  true;
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

/*
 * Estructura output:
   Estructura escargada de almacenar la cantidad de hit y miss que
   ocurren en la ejecución, también atualiza el archivo Output.txt
*/
class Output {

  public:

    unsigned int hits;
    unsigned int miss;

    Output() {

      hits = 0;
      miss = 0;

    }

    updateOutput(string address, string data) {

      ofstream file;
      file.open("Output.txt", std::ofstream::app);
      file << "| " << address << " | " << data << " |" << endl;
      file.close();
      hits++;

    }


};

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

void leerDataMemoryMain( MemoryMain & memoryMain ) {

  string linea;
  std::ifstream file("MemoryMain.txt");

  while (!file.eof()) {

    file >> linea;
    memoryMain.data.push_back(linea);

  }
  file.close();
}

int inicio(Cache & memoryCache, MemoryMain & memoryMain, Output & salida ){

    leerDataMemoryMain( memoryMain );
    PhysicalAddress Direccion;
    Gen(Direccion);

    //cout << "\nDireccion generada: " << Direccion.blockAddress << " dec: " << stoi(Direccion.offset.c_str(), 0, 2) << '\n';
    int x = memoryCache.getPosAddress(Direccion.blockAddress); // si esta la direccion en la Cache
    if (memoryCache.isHit(x)) {

        cout << "Hit: " << x << endl;
        cout << "Cantidad data: " <<  memoryCache.blocks[x]->data.size() << endl;
        cout << "offset: " << stoi(Direccion.offset.c_str(), 0, 2) << endl;
        salida.updateOutput(Direccion.blockAddress, memoryCache.blocks[x]->data[stoi(Direccion.offset.c_str(), 0, 2) ] ); // *** - 1
        cout << "----------------\n";
    }

    else {

      //cout << "pos: " << memoryCache.pos << endl;
      if (memoryCache.pos < 15) {
        cout << "Miss - Pos: " << memoryCache.pos << endl;
        memoryCache.blocks[memoryCache.pos]->v = 1;
        memoryCache.blocks[memoryCache.pos]->address = Direccion.blockAddress;
        memoryCache.blocks[memoryCache.pos++]->data = memoryMain.getData(3, 10);
        salida.miss++;


      }
    }

}

int main( int argc, char const *argv[] ) { // menu infinito

  /* Creando instancia de estructura Cache */
  Cache memoryCache;
  MemoryMain memoryMain;
  Output salida;
  string input = "";

  int N = 1000;
  while (N-- > 0) {
    inicio(memoryCache, memoryMain, salida);
  }
  /*
  while ( input != "E" ) {

    cout << "\nMemoria cache\n";
    cout << "[G] Generar direccion\n";
    cout << "[E] Salir\n> ";
    cin >> input;

    if (input == "G")
      inicio(memoryCache, memoryMain, salida);

  }*/

  cout << "Taza" << '\n';
  cout << "Hits: " << salida.hits << '\n';
  cout << "Miss: " << salida.miss << '\n';

  srand(time(NULL));

  return 0;
}
