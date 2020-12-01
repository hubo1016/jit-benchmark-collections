
class Trie {
    constructor(){
        this.has_word = false;
        this.children = {};
    }

    insert(word, start=0){
        let tree = this
        while(start < word.length){
            if(tree.children[word[start]] === undefined){
                tree.children[word[start]] = new Trie()
            }
            tree = tree.children[word[start]]
            start++
        }
        tree.has_word = true
    }

    search(word, start=0){
        let tree = this
        while(start < word.length){
            if(tree.children[word[start]] === undefined){
                return false;
            }else{
                tree = tree.children[word[start]]
                start++
            }
        }
        return tree.has_word
    }
}

const test = (inserts, searches)=>{
    let tree = new Trie()
    for(let w of inserts){
        tree.insert(w)
    }
    let count = 0
    for(let w of searches){
        count += tree.search(w)
    }
    return count
}
let fs = require('fs')
let inserts = fs.readFileSync(process.argv[2], 'utf-8')
                .split('\n')
                .filter(Boolean)
let searches = fs.readFileSync(process.argv[3], 'utf-8')
                 .split('\n')
                 .filter(Boolean)
console.log(test(inserts, searches))
for(let i = 0; i < 20; i++){
    test(inserts, searches)
}
