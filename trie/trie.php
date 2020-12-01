<?php

function insert(&$tree, $word, $start=0){
    while($start < strlen($word)){
        if(!isset($tree[1][$word[$start]])){
            $tree[1][$word[$start]] = array(false, array());
        }
        $tree = &$tree[1][$word[$start]];
        $start++;
    }
    $tree[0] = true;
}

function search(&$tree, $word, $start=0){
    while($start < strlen($word)){
        if(!isset($tree[1][$word[$start]])){
            return false;
        }else{
            $tree = &$tree[1][$word[$start]];
            $start++;
        }
    }
    return $tree[0];
}


function test(&$inserts, &$searches){
    $tree = array(False, array());
    foreach($inserts as $w){
        insert($tree, $w);
    }
    $count = 0;
    foreach($searches as $w){
        $count += search($tree, $w);
    }
    return $count;
}

$inserts = file($argv[1], FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
$searches = file($argv[2], FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

for($i = 0; $i < 20; $i++){
    test($inserts, $searches);
}
?>
