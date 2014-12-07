<?php

/**
 * @file
 * Contains class ActionMakeNodeHash.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Action: Export a Commerce order.
 */
class ActionMakeNodeHash extends \RulesActionHandlerBase {

  /**
   * Defines the action.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_make_node_hash',
      'label' => t('Get the hash for a vote'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'token' => array(
          'label' => t('Secret token'),
          'type' => 'text',
          'description' => t('The secret token.'),
        ),
        'vote' => array(
          'label' => t('Voting node'),
          'type' => 'node',
          'description' => t('The voting node.'),
        ),
      ),
      'provides' => array(
        'node_hash' => array(
          'label' => t('Node hash'),
          'type' => 'text',
        ),
      ),
      'help' => t('Generate a random secret token.'),
    );
  }

  /**
   * Executes the action.
   */
  public function execute($token, $vote) {
    // We use the global function here.
    return array('node_hash' => secret_voting_hash($token, $vote->nid, TRUE));
  }

}