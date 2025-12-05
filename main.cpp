#include "SearchEngine.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Objeto de la clase, se pasa el directorio para el motor
    SearchEngine motor("./testDir2");

    // Ciclo que se repite hasta que el usuario lo diga
    while (true) {
        // Pide input la palabra o frase para buscar
        string palabra;
        cout << "Entre la palabra o frase (2 palabra máximo) para buscar el archivo: ";
        getline(cin, palabra);

        // Se ejecuta el search y el menorCantidad es por si el resultado es menor que 3
        int menorCantidad = 0;
        vector<string> resultados = motor.search(palabra, menorCantidad);
        
        // Imprime los resultados de la busqueda. Si los resultados < 3, se imprime la notificación
        if (resultados[0] != "-1") {
            if (menorCantidad > 0)
                cout << "Note que la palabra que buscaste aparece en " << menorCantidad << " archivos.\n";

            cout << "Los archivos más relevantes de acuerdo con tu búsqueda son:\n\n";

            for (string e : resultados) {
                cout << e << "\n";
            }
        }
        else 
            cout << "No se encontró la palabra que tú buscaste.\n";

        // Le pregunta al usuario si quiere hacer otra búsqueda
        int decision;
        cout << "\nQuieres hacer otra búsqueda? (Entre 1 para sí o 0 para no): ";
        cin >> decision;
        cin.ignore();

        if (!decision) break;
        else {
            cout << "\n";
            continue;
        }
    }
    return 0;
}
