#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>


using namespace std;
void leerArchivo(); 


int main() {
  leerArchivo();
  return 0;
}

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

  unordered_map<string, int> memory;  

  if(archivo.is_open()){

    while(getline(archivo,line)){ 
      istringstream iss(line);
      vector <string> palabras;
      string palabra;
      while(iss>> palabra){ 
        palabras.push_back(palabra);

      }
      
      if (!palabras.empty() && palabras[0] == "SET" && palabras.size() >= 3) { 
        uc = palabras[0];
        string clave = palabras[1];
        int mdr = stoi(palabras[2]);
        mar = palabras[1];
        memory[mar] = mdr;
        icr++;
      }
      
      if (!palabras.empty() && palabras[0] == "SHW" && palabras.size() >= 3) {
        if(palabras[2]=="NULL" && palabras[3]=="NULL"){
          uc = palabras[0];
          int value= memory[palabras[1]] ;
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
          cout<<"MDR: "<<mdr<<endl;
          icr++;
        }
        if(palabras[1]=="UC"){
          uc = palabras[0];
          cout<<"UC: "<<uc<<endl;
          icr++;
        }
      }
      
      if (!palabras.empty() && palabras[0] == "ADD" && palabras.size() >= 3) {
        if(palabras[2]=="NULL" && palabras[3]=="NULL"){
            uc = palabras[0];
            mar = palabras[1];
            int mdr = memory[mar];
            accumulator = accumulator + mdr;
            icr++;            
        }
        if(palabras[2]!="NULL" && palabras[3]=="NULL"){
           uc = palabras[0];
            mar = palabras[1];
            mdr = memory[mar];
            int value1 = mdr;
            mar =palabras[2];
            mdr = memory[mar];
            int value2 = mdr;  
            accumulator =  value1 + value2;
            icr++;
        }
        if(palabras[2]!="NULL" && palabras[3]!="NULL"){
            uc = palabras[0];
            mar = palabras[1];
            mdr = memory[mar];
            int value = mdr;
            mar = palabras[2];
            mdr = memory[mar];
            int value2 = mdr;
            int suma = value + value2;
            memory[palabras[3]] = suma;
            icr++;
        }
      }
      
      if (!palabras.empty() && palabras[0] == "LDR" && palabras.size() >= 3) {
        uc = palabras[0];
        mar = palabras[1];
        mdr = memory[mar];
        int value = mdr;
        accumulator=value;
        icr++;
       
      }
      
      if (!palabras.empty() && palabras[0] == "INC" && palabras.size() >= 3){
        uc = palabras[0];
        mar = palabras[1];
        mdr = memory[mar];
        int value = mdr;
        int increment = value + 1;
        memory[mar]=increment;
        icr++;
      
      }
      
      if (!palabras.empty() && palabras[0] == "DEC" && palabras.size() >= 3){
        uc = palabras[0];
        mar = palabras[1];
        mdr = memory[mar];
        int value = mdr;
        int decrement = value - 1;
        memory[mar]=decrement;
        icr++;
        
      }
      
      if (!palabras.empty() && palabras[0] == "STR" && palabras.size() >= 3) {
        uc = palabras[0];
        mar = palabras[1];
        memory[mar]=accumulator;
        accumulator=0;
        icr++;
      }
      
      if (!palabras.empty() && palabras[0] == "PAUSE" && palabras.size() >= 3) {
        uc = palabras[0];
        cout<<"El simulador esta en pausa, estos son los valores actuales en memoria:"<<endl;
        for (const auto& entry : memory) {
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
