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
#define MAX_ADDRESS 8
#define MAX_DATA 8
#define MAX_DATA_MAIN 2048
#define OFFSET 3

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
    Block() { }

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

    const int getRangeInf() {

        return stoi( (blockAddress + "000").c_str(), 0, 2);

    }

    const int getRangeSup() {

      return  stoi( (blockAddress + "111").c_str(), 0, 2);

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
     string q = setQueue[setQueue.size() - 1];
     auto position  = find(setQueue.begin(), setQueue.end(), q);
     if ( position != setQueue.end())  {
       setQueue.erase(position);
     }
     return q;

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

   void write( const int pos, vector<string>  data, string blockAddress) {

     this->blocks[pos]->v = 1;
     this->blocks[pos]->address = blockAddress;
     this->blocks[pos]->data = data;
     this->setLeasRecentlyUsed(blockAddress);

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

        for (int i = x; i <= y; i++)
          information.push_back(data[i]);
      }

      return information;
    }

    void write(const int x, const int y, vector<string> data) {

      string linea;
      int i, k;
      vector<string> tmp;
      std::ifstream file("MemoryMain.txt");

      while (!file.eof()) {

        file >> linea;
        tmp.push_back(linea);

      }
      file.close();

      for (k = 0, i = x; i <= y; i++, k++)
        tmp[i] = data[k];

      std::ofstream fileWrite("MemoryMain.txt");

       for (i = 0; i < tmp.size(); i++)
        fileWrite << tmp[i] << endl;

       fileWrite.close();
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

    void updateOutput(string address, string data) {

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

    for (int i = 0; i < MAX_ADDRESS; i++) {
        int n = rand() % 2;
        aux+=to_string(n);
    }
    direccion.blockAddress = aux;
    for (int i = 0; i < OFFSET; i++) {
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

vector<string> openInput(string nameFile) {

  string aux;
  vector<string> data;
  std::ifstream file(nameFile);

  for (int i = 0; i <= MAX_DATA ; i++) {
    file >> aux;
    data.push_back(aux);
  }

  file.close();

  return data;

}

void writeMemory(Cache & memoryCache, MemoryMain & memoryMain) {

  string input = "input1.txt";
  vector<string> temp, data;
  temp = openInput(input);

  string address = temp[0];

  int pos, x, y, i;

  for (int i = 1; i < temp.size(); i++)
    data.push_back(temp[i]);

  pos = memoryCache.getPosAddress(address);

  /* Escritura en cache */

  if (pos == -1 && memoryCache.pos < 16)
    pos = memoryCache.pos++;

  else if (pos == -1 && memoryCache.pos == 16)
      pos = memoryCache.getPosAddress(memoryCache.getLeasRecentlyUsed());

  memoryCache.write(pos, data, address);

  PhysicalAddress phyAddress(address, "000");
  x = phyAddress.getRangeInf();
  y = phyAddress.getRangeSup();

  memoryMain.write(x, y, data);

  cout <<"\nData Cache [0]\n";

  cout << "V: " << memoryCache.blocks[0]->v << endl;
  cout << "Address: " << memoryCache.blocks[0]->address << endl;
  for (i = 0; i <  memoryCache.blocks[0]->data.size(); i++) {
    cout <<  memoryCache.blocks[0]->data[i] << " ";
  }
  cout << endl;
  /* Escritura en memoria principal */


}


void  inicio(Cache & memoryCache, MemoryMain & memoryMain, Output & salida ){

    leerDataMemoryMain( memoryMain );
    PhysicalAddress Direccion;
    Gen(Direccion);
    int x = memoryCache.getPosAddress(Direccion.blockAddress); // si esta la direccion en la Cache

    if (memoryCache.isHit(x)) {

        salida.updateOutput(Direccion.blockAddress, memoryCache.blocks[x]->data[stoi(Direccion.offset.c_str(), 0, 2) ] ); // *** - 1
        memoryCache.setLeasRecentlyUsed(Direccion.blockAddress);
    }

    else {


      if (memoryCache.pos < 16)
        memoryCache.write(memoryCache.pos++, memoryMain.getData( Direccion.getRangeInf(), Direccion.getRangeSup()), Direccion.blockAddress);

      else{

          int z = memoryCache.getPosAddress(memoryCache.getLeasRecentlyUsed()) ;
          memoryCache.write(z, memoryMain.getData( Direccion.getRangeInf(), Direccion.getRangeSup()), Direccion.blockAddress);

      }
      salida.miss++;
    }

}


int main( int argc, char const *argv[] ) { // menu infinito

  srand(time(NULL));

  /* Creando instancia de estructura Cache */
  Cache memoryCache;
  MemoryMain memoryMain;
  Output salida;
  string input = "";
  int N = 100;

  writeMemory(memoryCache, memoryMain);

  return 0;

  /*while (N-- > 0) {

    //inicio(memoryCache, memoryMain, salida);
  }*/

  /*
  while ( input != "E" ) {

    cout << "\nMemoria cache\n";
    cout << "[G] Generar direccion\n";
    cout << "[W] Escrbir"
    cout << "[E] Salir\n> ";
    cin >> input;

    if (input == "G")
      inicio(memoryCache, memoryMain, salida);

  }*/

  cout << "Taza" << '\n';
  cout << "Hits: " << salida.hits << '\n';
  cout << "Miss: " << salida.miss << '\n';


  return 0;
}
