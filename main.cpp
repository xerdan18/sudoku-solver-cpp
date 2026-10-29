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

bool leerTablero(const string& nombreArchivo, int tablero[9][9]){
    //Abrimos el archivo
    ifstream archivo(nombreArchivo);

    //Compruebo si se abrio bien
    if(!archivo){
        cout << "Error al abrir el archivo" << endl;
        return false;
    }

    //Leemos las lineas
    string linea;
    for(int i = 0; i < 9 ; i++){
        //Obtengo la lienea y veo si esta bien el formato
        getline(archivo, linea);
        if(linea.size() != 9){
            cout<< "Error: la linea " << i+1 << " tiene " << linea.size() << " caracteres (se esperaban 9)" << endl;
            return false;
        }

        //Relleno el tablero segun el .txt
        for(int j = 0; j < 9; j++){
            char c = linea[j];

            if(c == '0'|| c == '.') tablero[i][j] = 0;
            else if(c >= '1' && c <= '9')tablero[i][j] = c - '0';
            else{
                cout << "Caracter no valido: " << c << " en la columnna "<< j+1 << "  y fila " << i+1 << endl;
                return false;
            }
        }
    }

    return true;
}

bool sePuedePoner(int tablero[9][9], int fila, int col, int num){
    //Recorro la fila
    for(int j = 0; j < 9; j++){
        if(j != col){
            if(tablero[fila][j] == num)return false;
        }
    }

    //Recorro columna
    for(int i = 0; i < 9; i++){
        if(i != fila){
            if(tablero[i][col] ==  num)return false;
        }
    }

    //Recorro caja
    //Primero tengo que ver en que cajaa  estoy  parado, hay  9 
    //y cada  una  empieza enn una celad distinta, con esto vemos donde arranca cada una
    int inicioFila = fila - fila % 3;
    int inicioCol = col - col % 3;

    for(int i = inicioFila; i < 3 + inicioFila ; i++){
        for(int j = inicioCol; j < 3 + inicioCol; j++){
            if(i != fila && j != col){
                if(tablero[i][j] == num)return false;
            }
        }
    }

    return true;
}

bool tableroValido(int tablero[9][9]){
    //Recorre toddas las celdas y salta las vacias (0)
    //Si no es 0, pregunta  sePuedePoner, si dda false termina

    for(int i = 0; i<9;i++){
        for (int j = 0; j <9; j++){
            if(tablero[i][j] != 0){
                if(!sePuedePoner(tablero, i, j, tablero[i][j])){
                    cout<< "Conflicto en fila " << i+1 << " y columnna "<< j+1 << " con el numeero "<< tablero[i][j]<< endl;
                    return false;
                }
            }
        }
    }

    return true;
}

bool resolver(int t[9][9]){
    int fila = -1;
    int col = -1;

    for(int i = 0; i < 9 ; i++){
        for(int j = 0; j<9;j++){
            if(t[i][j] == 0){
                fila = i;
                col = j;
                break;
            }
        }
        if(fila != -1)break;
    }

    if(fila == -1)return true; //Sudoku resuelto

    for(int val = 1; val <=9 ;val++){
        if(sePuedePoner(t, fila, col, val)){
            t[fila][col] = val;
            if(resolver(t))return true;
            else t[fila][col] = 0;
        }

    }

    return false;
}

int main(int argc, char* argv[]){

    //Comprobamos si se paso un archivo de texto
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <nombre_del_archivo>" << endl;
        return 1;
    }    

    int tablero[9][9];
    if(!leerTablero(argv[1],tablero))return 1;

    if(!tableroValido(tablero))return 1;

    imprimirTablero(tablero);

    cout<< endl;

    if(resolver(tablero)){
        cout << "Solucion: "<< endl;
        imprimirTablero(tablero);
    }else{
        cout <<"Sudoku sin solucion"<< endl;
        return 1;
    }
    return 0;
}

