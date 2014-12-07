<?php

/**
 * @file
 * Contains class ActionMakeTokenHash.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Action: Export a Commerce order.
 */
class ActionMakeTokenHash extends \RulesActionHandlerBase {

  /**
   * Defines the action.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_make_token_hash',
      'label' => t('Get the hash for a token'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'token' => array(
          'label' => t('Secret token'),
          'type' => 'text',
          'description' => t('The secret token.'),
        ),
        'vote_token' => array(
          'label' => t('Voting token entity'),
          'type' => 'vote_token',
          'wrapped' => TRUE,
          'description' => t('The voting node.'),
        ),
      ),
      'provides' => array(
        'token_hash' => array(
          'label' => t('Token hash'),
          'type' => 'text',
        ),
      ),
      'help' => t('Generate a random secret token.'),
    );
  }

  /**
   * Executes the action.
   */
  public function execute($token, $vote_token) {
    // We use the global function here.
    if ($vote_token->value()->type == 'taxonomy_token') {
      return array('token_hash' => secret_voting_hash($token, $vote_token->field_token_term->value()->tid, FALSE));
    }
    elseif ($vote_token->value()->type == 'user_token') {
      return array('token_hash' => secret_voting_hash($token, $vote_token->field_token_user->value()->uid, FALSE));
    }
  }

}