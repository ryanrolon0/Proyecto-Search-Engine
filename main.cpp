#include "SearchEngine.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    SearchEngine motor("./moviesdb");

    while (true) {
        string palabra;
        cout << "Entre la palabra o frase (2 palabra máximo) para buscar el archivo: ";
        getline(cin, palabra);

        while (!motor.checkInput(palabra)) {
            cout << "Trata otra vez: ";
            getline(cin, palabra);
        }

        vector<string> resultados = motor.search(palabra);
        cout << "Los archivos más relevantes de acuerdo con tu búsqueda son:\n\n";

        for (string e : resultados) {
            cout << e << "\n";
        }

        int decision;
        cout << "Quieres hacer otra búsqueda? (Entre 1 para sí o 0 para no): ";
        cin >> decision;

        if (decision == 1) break;
        else cout << "\n";
    }
    return 0;
}
