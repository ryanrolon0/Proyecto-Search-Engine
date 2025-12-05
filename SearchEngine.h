#include <unordered_map>
#include <vector>
#include <list>
using namespace std;

class SearchEngine {
private:
    // Inverted index del programa
    unordered_map<string, list<pair<int, string>>> inv_index;

    // Método que toma el input del usuario y separa las palabras por los espacios en blancos
    vector<string> inputSeparator(const string& input) const;
    
    // Toma una lista y un iterator a un pair y lo ordena en orden decendiente
    void listSort(list<pair<int, string>> &lst, list<pair<int, string>>::iterator &itr);

public:
    // Constructor de la clase
    SearchEngine(const string& directory);
    // Motor de búsqueda
    vector<string> search(const string& query, int &menorCantidad);
};