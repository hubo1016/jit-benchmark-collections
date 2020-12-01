<?php

function insert(&$tree, $word, $start=0){
    while($start < strlen($word)){
        if(!isset($tree['children'][$word[$start]])){
            $tree['children'][$word[$start]] = array('has_word'=>false, 'children'=>array());
        }
        $tree = &$tree['children'][$word[$start]];
        $start++;
    }
    $tree['has_word'] = true;
}

function search(&$tree, $word, $start=0){
    while($start < strlen($word)){
        if(!isset($tree['children'][$word[$start]])){
            return false;
        }else{
            $tree = &$tree['children'][$word[$start]];
            $start++;
        }
    }
    return $tree['has_word'];
}


function test(&$inserts, &$searches){
    $tree = array('has_word'=>False, 'children'=>array());
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

echo(test($inserts, $searches));
for($i = 0; $i < 20; $i++){
    test($inserts, $searches);
}
?>
