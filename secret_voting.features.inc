<?php
/**
 * @file
 * secret_voting.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function secret_voting_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function secret_voting_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function secret_voting_eck_bundle_info() {
  $items = array(
    'vote_ballot_term_ballot' => array(
      'machine_name' => 'vote_ballot_term_ballot',
      'entity_type' => 'vote_ballot',
      'name' => 'term_ballot',
      'label' => 'term ballot',
    ),
    'vote_ballot_user_ballot' => array(
      'machine_name' => 'vote_ballot_user_ballot',
      'entity_type' => 'vote_ballot',
      'name' => 'user_ballot',
      'label' => 'user ballot',
    ),
    'vote_ballot_vote_ballot' => array(
      'machine_name' => 'vote_ballot_vote_ballot',
      'entity_type' => 'vote_ballot',
      'name' => 'vote_ballot',
      'label' => 'vote ballot',
    ),
    'vote_token_taxonomy_token' => array(
      'machine_name' => 'vote_token_taxonomy_token',
      'entity_type' => 'vote_token',
      'name' => 'taxonomy_token',
      'label' => 'taxonomy token',
    ),
    'vote_token_user_token' => array(
      'machine_name' => 'vote_token_user_token',
      'entity_type' => 'vote_token',
      'name' => 'user_token',
      'label' => 'user token',
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function secret_voting_eck_entity_type_info() {
  $items = array(
    'vote_ballot' => array(
      'name' => 'vote_ballot',
      'label' => 'vote ballot',
      'properties' => array(),
    ),
    'vote_token' => array(
      'name' => 'vote_token',
      'label' => 'vote token',
      'properties' => array(
        'created' => array(
          'label' => 'Created',
          'type' => 'integer',
          'behavior' => 'created',
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_node_info().
 */
function secret_voting_node_info() {
  $items = array(
    'vote' => array(
      'name' => t('Vote'),
      'base' => 'node_content',
      'description' => t('A vote can be set up and will allow people to cast votes. When chosen to be secret it will save the results not keeping a record of who voted for what.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
