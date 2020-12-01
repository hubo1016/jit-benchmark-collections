#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
using namespace std;


template<class U, class V>
class VectorMap{
public:
    using vector_type = vector<pair<const U,V>>;
    using iterator = typename vector_type::iterator;
    using const_iterator = typename vector_type::const_iterator;
    iterator begin() {
        return _maps.begin();
    }
    iterator end() {
        return _maps.end();
    }
    const_iterator begin() const {
        return _maps.begin();
    }
    const_iterator end() const {
        return _maps.end();
    }
    iterator find(const U &key) {
        return std::find_if(begin(), end(), [&](const auto &x)->bool{return x.first == key;});
    } 
    const_iterator find(const U &key) const {
        return std::find_if(begin(), end(), [&](const auto &x)->bool{return x.first == key;});
    } 
    V &operator[](const U &key) {
        auto i = find(key);
        if(i == end()){
            _maps.emplace_back(key, V());
            i = end();
            --i;
        }
        return i->second;
    }
private:
    vector_type _maps;
};


class Trie {
public:
    Trie(): has_word(false) {}
    void insert(const string &word, int start=0){
        auto tree = this;
        while(start < word.length()){
            auto c = word.substr(start, 1);
            if(tree->children.find(c) == tree->children.end()){
                tree->children[c] = make_unique<Trie>();
            }
            tree = tree->children[c].get();
            start++;
        }
        tree->has_word = true;
    }
    bool search(const string &word, int start=0) const{
        auto tree = this;
        while(start < word.length()){
            auto c = word.substr(start, 1);
            if(tree->children.find(c) == tree->children.end()){
                return false;
            }else{
                tree = tree->children.find(c)->second.get();
                start++;
            }
        }
        return tree->has_word;
    }
private:
    bool has_word;
    VectorMap<string, unique_ptr<Trie>> children;
};


int test(const vector<string> &inserts, const vector<string> &searches){
    auto tree = make_unique<Trie>();
    for(auto &&w: inserts){
        tree->insert(w);
    }
    int count = 0;
    for(auto &&w: searches){
        count += tree->search(w);
    }
    return count;
}

vector<string> read_all(const char *path){
    ifstream f(path);
    vector<string> result;
    while(!f.eof()){
        string buff;
        getline(f, buff);
        if(!buff.empty()){
            result.emplace_back(move(buff));
        }
    }
    return result;
}


int main(int argc, const char *argv[]){
    auto inserts = read_all(argv[1]);
    auto searches = read_all(argv[2]);
    cout<<test(inserts, searches)<<endl;
    for(int i = 0; i < 20; i++){
        test(inserts, searches);
    }
    return 0;
}

