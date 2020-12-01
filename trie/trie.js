

const insert = (tree, word, start=0)=>{
    while(start < word.length){
        if(tree[1][word[start]] === undefined){
            tree[1][word[start]] = [false, {}]
        }
        tree = tree[1][word[start]]
        start++
    }
    tree[0] = true
}

const search = (tree, word, start=0)=>{
    while(start < word.length){
        if(tree[1][word[start]] === undefined){
            return false;
        }else{
            tree = tree[1][word[start]]
            start++
        }
    }
    return tree[0]
}

const test = (inserts, searches)=>{
    let tree = [false, {}]
    for(let w of inserts){
        insert(tree, w)
    }
    let count = 0
    for(let w of searches){
        count += search(tree, w)
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
