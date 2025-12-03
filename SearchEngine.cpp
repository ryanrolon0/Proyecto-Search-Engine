#include "SearchEngine.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;
namespace fs = std::filesystem;

// Function to read all files that are inside the directory that receives
SearchEngine::SearchEngine(const string& directory) {

    // Interates through all the files in directory
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            ifstream file(entry.path());
            if (!file.is_open()) {
                std::cerr << "No se pudo abrir el archivo: " << entry.path() << '\n';
                continue;
            }
            
            // Implementación de llenar el inverted directory
            string word;
            string filename = entry.path().filename().string();
            while(file >> word) {
                if (inv_directory.find(word) == inv_directory.end()) {
                    vector<pair<int, string>> temp = {{1, filename}};
                    inv_directory[word] = std::move(temp);
                }
                else {
                    bool txtFileFound = false;
                    int i;

                    for (i = 0; i < inv_directory[word].size(); i++) {
                        if (inv_directory[word][i].second == filename) {
                            txtFileFound = true;
                            break;
                        }
                    }

                    if (txtFileFound) inv_directory[word][i].first++;
                    else inv_directory[word].push_back({1, filename});
                }
            }
        }
    }
}

bool SearchEngine::checkInput(const string& input) {
    int spaceCount = 0;
    for (char i : input) {
        if (i == ' ') spaceCount++;
        if (spaceCount > 1) return false;
    }
    return true;
}

vector<string> SearchEngine::search(const string& query) const {
    vector<string> res;
    auto itr = inv_directory.find(query);

    if (itr == inv_directory.end()) {
        res.push_back("-1");
        return res;
    }


}