#include <unordered_map>
#include <vector>
using namespace std;

class SearchEngine {
private:
    unordered_map<string, vector<pair<int, string>>> inv_directory;
public:
    SearchEngine(const string& directory);

    bool checkInput(const string& input);
    vector<string> search(const string& query) const;
};