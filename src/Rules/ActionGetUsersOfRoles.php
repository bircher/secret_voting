<?php

/**
 * @file
 * Contains class ActionGetUsersOfRoles.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Action: Export a Commerce order.
 */
class ActionGetUsersOfRoles extends \RulesActionHandlerBase {

  /**
   * Defines the action.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_get_users_of_roles',
      'label' => t('Get the users of given roles'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'role' => array(
          'label' => t('role ids'),
          'type' => 'list<integer>',
          'description' => t('The role IDs.'),
        ),
      ),
      'provides' => array(
        'users' => array(
          'label' => t('Users'),
          'type' => 'list<user>',
        ),
      ),
      'help' => t('Retrieve all users with a certain role.'),
    );
  }

  /**
   * Executes the action.
   */
  public function execute($roles) {
    $query = 'SELECT DISTINCT(ur.uid) 
      FROM {users_roles} AS ur
      WHERE ur.rid IN (:rids)';
    $result = db_query($query, array(':rids' => $roles));
    $uids = $result->fetchCol();
    $users = user_load_multiple($uids);
    return array('users' => $users);
  }

}