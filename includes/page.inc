<?php

function all_collections(){
  $tuque = islandora_get_tuque_connection();
  $query = <<<EOL
SELECT ?pid ?title FROM <#ri>
WHERE {
?pid <fedora-rels-ext:isMemberOfCollection> <info:fedora/islandora:root>.
?pid <info:fedora/fedora-system:def/model#label> ?title}
ORDER BY ?title
EOL;
  $collections = $tuque->repository->ri->sparqlQuery($query, 'unlimited');

  return $collections;
}

function links_from_query($query_results){
  $links = [];
  foreach($query_results as $query){
    $links[] = l(t($query['title']['value']), 'islandora/object/'.$query['pid']['value']);
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

