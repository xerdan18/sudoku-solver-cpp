#include <iostream>
using namespace std;

int main(int argc, char* argv[]){

   if (argc < 2) {
        cout << "Uso: " << argv[0] << " <nombre_del_archivo>" << endl;
        return 1;
    }    
    
    char* nombreArchivo = argv[1];
    cout << "El nombrre del arrchivo recibido es: " << nombreArchivo << endl;

    return 0;
}