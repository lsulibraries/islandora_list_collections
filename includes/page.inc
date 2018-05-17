<?php

function all_collections(){
  $tuque = islandora_get_tuque_connection();
  $query = <<<EOL
SELECT ?pid FROM <#ri>
WHERE {
?pid <fedora-rels-ext:isMemberOfCollection> <info:fedora/islandora:root>}
EOL;
  $collections = $tuque->repository->ri->sparqlQuery($query, 'unlimited');

  return $collections;
}

function links_from_query($query){
  $links = [];
  foreach($query as $q){
   foreach($q as $thing){
    var_dump($thing);
   }
    explode('/',$q);
    $obj = islandora_object_load($q[1]);
    $links[] = l(t($obj->label), 'islandora/object/'.$q);
}
  return $links;
}


function callback(){
  echo 'hello world';
}

function collection_list(){
  $query_return = all_collections();
  $links = links_from_query($query_return);
  return $links;
}

function create_page(){
 $links =  collection_list();
 foreach($links as $link){
 }
}

