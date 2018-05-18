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

function links_from_query($query_results){
  $links = [];
  foreach($query_results as $query){
    foreach($query as $result){
      $obj = islandora_object_load($result['value']);
      $links[] = l(t($obj->label), 'islandora/object/'.$result['value']);
    }
  }
  return $links;
}

function collection_list(){
  $links = &drupal_static(__FUNCTION__);
  if(!isset($links)){
    if($cache = cache_get('collection_list_data')){
      $links = $cache->data;
    }
    else{
      $query_return = all_collections();      
      $links = links_from_query($query_return);
    }
  }
  return $links;
}

