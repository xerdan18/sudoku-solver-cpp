#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void imprimirTablero(int tablero[9][9]) {
    for(int i = 0; i<9;i++){
        for(int j = 0; j<9;j++){
            if(tablero[i][j] == 0)cout << ". ";
            else cout << tablero[i][j] << " ";
            
            if(j == 2  || j == 5)cout << "| ";
        }
        
        if(i == 2 || i == 5){
            cout<< endl;
            cout<< "------+-------+------";
        }
        cout<< endl;
    }
}


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
    int tablero[9][9];
    for(int i = 0; i < 9 ; i++){
        //Obtengo la lienea y veo si esta bien el formato
        getline(archivo, linea);
        if(linea.size() != 9){
            cout<< "Error: la linea " << i+1 << " tiene " << linea.size() << " caracteres (se esperaban 9)" << endl;
            return 1;
        }

        //Relleno el tablero segun el .txt
        for(int j = 0; j < 9; j++){
            char c = linea[j];

            if(c == '0'|| c == '.') tablero[i][j] = 0;
            else if(c >= '1' && c <= '9')tablero[i][j] = c - '0';
            else{
                cout << "Caracter no valido: " << c << " en la columnna "<< j+1 << "  y fila " << i+1 << endl;
                return 1;
            }
        }
        
    }

  imprimirTablero(tablero);


    return 0;
}

