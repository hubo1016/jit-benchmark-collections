<?php

class Trie {
    private $has_word = false;
    private $children = array();
    public function insert($word, $start=0){
        $tree = $this;
        while($start < strlen($word)){
            if(!isset($tree->children[$word[$start]])){
                $tree->children[$word[$start]] = new Trie();
            }
            $tree = $tree->children[$word[$start]];
            $start++;
        }
        $tree->has_word = true;
    }

    public function search($word, $start=0){
        $tree = $this;
        while($start < strlen($word)){
            if(!isset($tree->children[$word[$start]])){
                return false;
            }else{
                $tree = $tree->children[$word[$start]];
                $start++;
            }
        }
        return $tree->has_word;
    }
}

function test(&$inserts, &$searches){
    $tree = new Trie();
    foreach($inserts as $w){
        $tree->insert($w);
    }
    $count = 0;
    foreach($searches as $w){
        $count += $tree->search($w);
    }
    return $count;
}

$inserts = file($argv[1], FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
$searches = file($argv[2], FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

echo(test($inserts, $searches));
for($i = 0; $i < 20; $i++){
    test($inserts, $searches);
}
?>
