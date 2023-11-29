#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>


// Tiffany Torres F. - 2241747 - tiffany.torre@correounivalle.edu.co
// Julian Rengifo J. - 2241016 - julian.david.rengifo@correounivalle.edu.co
// Pablo Becerra G. - 2243506 - pablo.becerra@correounivalle.edu.co

// Simulador de siclo basico de instrucciones - Sistemas Operativos


using namespace std;
void leerArchivo(); 


int main() {
  leerArchivo();
  return 0;
}

// se usa un diccionario para simular la memeoria, la clave del diccionario sera la direccion de la memoria D1, D2, D3, etc.


void leerArchivo(){
  string fileName;
  cout<<"Ingrese el nombre del archivo: ";
  cin>>fileName;
  ifstream archivo(fileName + ".txt");
  string line;
  int accumulator=0;
  int icr = 0;
  string mar = "";
  int mdr = 0;
  string uc = "";
  int mdr_ldr = 0;

  unordered_map<string, int> memoria;  

  if(archivo.is_open()){

    while(getline(archivo,line)){ 
      istringstream iss(line);
      vector <string> palabras;
      string palabra;
      while(iss>> palabra){ 
        palabras.push_back(palabra);

      }
      
      //funcion SET
      if (!palabras.empty() && palabras[0] == "SET" && palabras.size() >= 3) { 
        uc = palabras[0];
        string clave = palabras[1];
        mdr = stoi(palabras[2]);
        mar = palabras[1];
        memoria[mar] = mdr;
        icr++;
      }
      
      //funciones SHW
      if (!palabras.empty() && palabras[0] == "SHW" && palabras.size() >= 3) {
        if(palabras[2]=="NULL" && palabras[3]=="NULL"){
          uc = palabras[0];
          int value= memoria[palabras[1]] ;
          cout<<value<<endl;
          icr++;
        }
        if(palabras[1]=="ACC"){
          uc = palabras[0];
          cout<<"Acumulador: "<<accumulator<<endl;
          icr++;
        }
        if(palabras[1]=="MAR"){
          uc = palabras[0];
          cout<<"MAR: "<<mar<<endl;
          icr++;
        }
        if(palabras[1]=="ICR"){
          uc = palabras[0];
          cout<<"ICR: "<<icr<<endl;
          icr++;
        }
        if(palabras[1]=="MDR"){
          uc = palabras[0];
          cout<<"MDR: "<<mdr_ldr <<endl;
          icr++;
        }
        if(palabras[1]=="UC"){
          uc = palabras[0];
          cout<<"UC: "<<uc<<endl;
          icr++;
        }
      }
      
      //funciones ADD
      if (!palabras.empty() && palabras[0] == "ADD" && palabras.size() >= 3) {
        if(palabras[2]=="NULL" && palabras[3]=="NULL"){
            uc = palabras[0];
            mar = palabras[1];
            mdr = memoria[mar];
            accumulator = accumulator + mdr;
            icr++;            
        }
        if(palabras[2]!="NULL" && palabras[3]=="NULL"){
           uc = palabras[0];
            mar = palabras[1];
            mdr = memoria[mar];
            int value1 = mdr;
            mar =palabras[2];
            mdr = memoria[mar];
            int value2 = mdr;  
            accumulator =  value1 + value2;
            icr++;
        }
        if(palabras[2]!="NULL" && palabras[3]!="NULL"){
            uc = palabras[0];
            mar = palabras[1];
            mdr = memoria[mar];
            int value = mdr;
            mar = palabras[2];
            mdr = memoria[mar];
            int value2 = mdr;
            int suma = value + value2;
            memoria[palabras[3]] = suma;
            icr++;
        }
      }
      
      //funcion LDR
      if (!palabras.empty() && palabras[0] == "LDR" && palabras.size() >= 3) {
        uc = palabras[0];
        mar = palabras[1];
        mdr_ldr = memoria[mar];
        int value = mdr;
        accumulator = mdr_ldr;
        icr++;
       
      }
      

      //funcion INC
      if (!palabras.empty() && palabras[0] == "INC" && palabras.size() >= 3){
        uc = palabras[0];
        mar = palabras[1];
        mdr = memoria[mar];
        int value = mdr;
        int increment = value + 1;
        memoria[mar]=increment;
        icr++;
      
      }
      

      //funcion DEC
      if (!palabras.empty() && palabras[0] == "DEC" && palabras.size() >= 3){
        uc = palabras[0];
        mar = palabras[1];
        mdr = memoria[mar];
        int value = mdr;
        int decrement = value - 1;
        memoria[mar]=decrement;
        icr++;
        
      }
      
      //funcion STR
      if (!palabras.empty() && palabras[0] == "STR" && palabras.size() >= 3) {
        uc = palabras[0];
        mar = palabras[1];
        memoria[mar]=accumulator;
        accumulator=0;
        icr++;
      }
      

      //funcion PAUSE
      if (!palabras.empty() && palabras[0] == "PAUSE" && palabras.size() >= 3) {
        uc = palabras[0];
        cout<<"El simulador esta en pausa, estos son los valores actuales en memoria:"<<endl;
        for (const auto& entry : memoria) {
          cout << "Direccion: " << entry.first << ", Valor: " << entry.second << endl;
        } 
        string valorUsuario = "";
        cout<<"desea seguir con las instrucciones? (si o no) : ";
        cin>>valorUsuario;
        if (valorUsuario == "si"){
          cout<<"siguiendo con la simulacion."<<endl;
        }else if(valorUsuario == "no"){
          cout << "Saliendo del programa..." << endl;
          exit(0);
        }else{
          cout<<"Error critico, terminando programa...";
          exit(0);

        }
        icr++;
      }
      

      //funcion END
      if (!palabras.empty() && palabras[0] == "END" && palabras.size() >= 3) {
        uc = palabras[0];
        cout<<"Simulacion terminada";
        exit(0);
      }
    }
    archivo.close();
  }else{
    cout<<"No se encontro un archivo con ese nombre.";
  }
}
