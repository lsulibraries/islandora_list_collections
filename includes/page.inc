<?php


function all_collections(){
  $tuque = islandora_get_tuque_connection();
  $query = <<<EOL
SELECT ?pid ?title FROM <#ri>
WHERE {
?pid <fedora-rels-ext:isMemberOfCollection> <info:fedora/islandora:root>.

?pid dc:title ?title .}
EOL;
  $collections = $tuque->repository->ri->sparqlQuery($query, 'unlimited');

  return $collections;
}

function links_from_query($query){
  $links = [];
  foreach($query as $q){
    islandora_object_load($q);
    $links[] = l(t($obj->label), 'islandora/object/'.$q);
}
  return $links;
}


function create_page($links){
  $values = array(
    'type' => 'PAGE',
    'status' => 1,
    'comment' => 0,
  );
  $entity = entity_create('node', $values);
  $ewrapper = entity_metadata_wrapper('node', $entity);
  $ewrapper->title->set('Collections');
  $ewrapper->body->set(array('value' => $links));
  $ewrapper->save(); 
}
