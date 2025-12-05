#include "SearchEngine.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;
namespace fs = std::filesystem;

// Constructor que itera por los archivos del directorio y las palabras de los archivos
// Y llena el inverted index
SearchEngine::SearchEngine(const string& directory) {

    // Interates through all the files in directory
    // Forma parte de template.cpp
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            ifstream file(entry.path());
            if (!file.is_open()) {
                std::cerr << "No se pudo abrir el archivo: " << entry.path() << '\n';
                continue;
            }
    // Forma parte de template.cpp
            
            // Implementación de llenar el inverted directory
            string word;
            string filename = entry.path().filename().string();
            while(file >> word) {
                // Inserta la palabra, cantidad: 1 y nombre del archivo
                // si no está en el inverted index
                if (inv_index.find(word) == inv_index.end())
                    inv_index[word].push_back({1, filename});
                else {
                    bool txtFileFound = false;
                    list<pair<int, string>>::iterator itr;

                    // Itera por el inverted index para ver si el archivo abierto está en el inverted index
                    // y si está, incrementa por 1 la cantidad de veces que la palabra aparece en el archivo
                    for (itr = inv_index[word].begin(); itr != inv_index[word].end(); itr++) {
                        if (itr->second == filename) {
                            txtFileFound = true;
                            break;
                        }
                    }
                    if (txtFileFound) {
                        itr->first++;
                        listSort(inv_index[word], itr);
                    }
                    // Si no está, se le añade a la lista la cantidad: 1 y el nombre de archivo
                    else inv_index[word].push_back({1, filename});
                }
            }
        }
    }
}

vector<string> SearchEngine::inputSeparator(const string& input) const {
    vector<string> res;
    string word = "";

    // Va contruyendo la palabra con chars hasta que llegue a un
    // espacio en blanco y se le hace push al vector y devolverlo
    for (char i : input) {
        if (i != ' ')
            word += i;
        else {
            res.push_back(word);
            word = "";
        }
    }
    res.push_back(std::move(word));
    return res;
}

void SearchEngine::listSort(list<pair<int, string>> &lst, list<pair<int, string>>::iterator &itr) {
    list<pair<int, string>>::iterator itr2 = itr;
    itr2--;

    // Se le va haciendo swap del pair del iterador a uno previo hasta
    // que la lista esté de orden descendiente
    for (; itr != lst.begin(); itr2--, itr--) {
        if (itr->first > itr2->first) {
            swap(itr->first, itr2->first);
            swap(itr->second, itr2->second);
        }
        else break;
    }
}

vector<string> SearchEngine::search(const string& query, int &menorCantidad) {
    vector<string> res, palabras = inputSeparator(query);

    // Iteradores donde apuntan a las listas donde aparece en los archivos
    auto itr1 = inv_index.find(palabras[0]);
    auto itr2 = inv_index.find(palabras[1]);

    // Devuelve -1 al vector si no se encontró en el inverted index
    if (itr1 == inv_index.end() && itr2 == inv_index.end()) {
        res.push_back("-1");
        return res;
    }

    // Caso donde el usuario hizo input una sola palabra
    else if (itr2 == inv_index.end()) {
        // Si la lista es menor que 3, hacer push_back a todo el contenido al vector
        // e incrementar menorCantidad para llevar cuenta para la notificación
        if (itr1->second.size() < 3) {
            for (auto i : itr1->second) {
                res.push_back(i.second);
                menorCantidad++;
            }
        }
        // Si la lista >= 3, push_back a los primero 3 elementos de la lista
        else {
            int counter = 0;
            for (auto lst_itr = itr1->second.begin(); counter < 3; counter++, lst_itr++) {
                res.push_back(lst_itr->second);
            }
        }
    }
    else {
        // Se combina la lista de ambas palabras en una sola lista para buscar el archivo de mayor frecuencia.
        // Comienza con copiando la lista de la primera palabra
        list<pair<int, string>> combinedFreq = itr1->second;

        // Luego itera por la lista y la segunda lista para ver si ambas palabras están en un mismo archivo
        // si están, se le suma la frecuencia a la lista final
        for (auto combine_itr = combinedFreq.begin(); combine_itr != combinedFreq.end(); combine_itr++) {
            for (auto lst_itr = itr2->second.begin(); lst_itr != itr2->second.end(); lst_itr++) {
                if (combine_itr->second == lst_itr->second) {
                    combine_itr->first += lst_itr->first;
                    listSort(combinedFreq, combine_itr);
                    break;
                }
                // Si no, se le añade como push_back a la lista final
                // y se le llama listSort para ordenar la lista final
                combinedFreq.push_back(*lst_itr);
                auto end_itr = combinedFreq.end();
                end_itr--;
                listSort(combinedFreq, end_itr);
            }
        }

        // Si la lista es menor que 3, hacer exactamente como el procedimiento de arriba
        if (combinedFreq.size() < 3) {
            for (auto i : combinedFreq) {
                res.push_back(i.second);
                menorCantidad++;
            }
        }
        // Si la lista >= 3, hacer exactamente como el procedimiento de arriba
        else {
            int counter = 0;
            for (auto lst_itr = combinedFreq.begin(); counter < 3; counter++, lst_itr++) {
                res.push_back(lst_itr->second);
            }
        }
    }
    return res;
}