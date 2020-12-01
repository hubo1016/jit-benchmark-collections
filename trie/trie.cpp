#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;


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
    unordered_map<string, unique_ptr<Trie>> children;
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

