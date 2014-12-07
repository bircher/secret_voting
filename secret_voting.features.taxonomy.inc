<?php
/**
 * @file
 * secret_voting.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function secret_voting_taxonomy_default_vocabularies() {
  return array(
    'voting_terms' => array(
      'name' => 'Voting terms',
      'machine_name' => 'voting_terms',
      'description' => 'Voting terms may be countries or sections, if a vote includes voting terms, a vote for each term may be cast',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
