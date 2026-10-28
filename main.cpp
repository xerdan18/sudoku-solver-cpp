#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

    //Comprobamos si se paso un archivo de texto
   if (argc < 2) {
        cout << "Uso: " << argv[0] << " <nombre_del_archivo>" << endl;
        return 1;
    }    
    
    //Vemos el nombre
    char* nombreArchivo = argv[1];
    cout << "El nombrre del arrchivo recibido es: " << nombreArchivo << endl;


    //Abrimos el archivo
    ifstream archivo(nombreArchivo);

    //Compruebo si se abrio bien
    if(!archivo){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    //Leemos las lineas
    string linea;
    for(int i = 0; i < 9 ; i++){
        getline(archivo, linea);
        if(linea.size() != 9){
            cout<< "Error: la linea " << i+1 << " tiene " << linea.size() << " caracteres (se esperaban 9)" << endl;
            return 1;
        }
        cout << linea << endl;
    }

    return 0;
}