<?php

function islandora_list_collections_preprocess(&$variables, $hook){
  if($hook == 'page'){
    echo 'hello';
  }
}


function template_preprocess_islandora_list_collections(&$variables){
  $variables['test'] = 'test';
}
