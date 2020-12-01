

const insert = (tree, word, start=0)=>{
    while(start < word.length){
        if(tree['children'][word[start]] === undefined){
            tree['children'][word[start]] = {'has_word': false, 'children': new Map()}
        }
        tree = tree['children'][word[start]]
        start++
    }
    tree['has_word'] = true
}

const search = (tree, word, start=0)=>{
    while(start < word.length){
        if(tree['children'][word[start]] === undefined){
            return false;
        }else{
            tree = tree['children'][word[start]]
            start++
        }
    }
    return tree['has_word']
}

const test = (inserts, searches)=>{
    let tree = {'has_word': false, 'children': new Map()}
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
