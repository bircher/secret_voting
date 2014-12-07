<?php
/**
 * @file
 * secret_voting.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function secret_voting_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'eck add vote_ballot term_ballot entities'.
  $permissions['eck add vote_ballot term_ballot entities'] = array(
    'name' => 'eck add vote_ballot term_ballot entities',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck add vote_ballot user_ballot entities'.
  $permissions['eck add vote_ballot user_ballot entities'] = array(
    'name' => 'eck add vote_ballot user_ballot entities',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck add vote_ballot vote_ballot entities'.
  $permissions['eck add vote_ballot vote_ballot entities'] = array(
    'name' => 'eck add vote_ballot vote_ballot entities',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck add vote_token taxonomy_token entities'.
  $permissions['eck add vote_token taxonomy_token entities'] = array(
    'name' => 'eck add vote_token taxonomy_token entities',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck add vote_token user_token entities'.
  $permissions['eck add vote_token user_token entities'] = array(
    'name' => 'eck add vote_token user_token entities',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'eck',
  );

  return $permissions;
}
