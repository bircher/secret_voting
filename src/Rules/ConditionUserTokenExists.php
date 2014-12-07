<?php

/**
 * @file
 * Contains class ConditionUserTokenExists.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Provides condition for Rules to check if a token exists.
 */
class ConditionUserTokenExists extends \RulesConditionHandlerBase {

  /**
   * Provides information for Rules.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_user_token_exists',
      'label' => t('A Token for a user exists'),
      'help' => t('Checks if a token for a voting user exists.'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'vote' => array(
          'label' => t('Vote node'),
          'type' => 'node',
          // 'wrapped' => TRUE,
          'description' => t('The secret vote node to be checked.'),
        ),
        'user' => array(
          'label' => t('Voting user'),
          'type' => 'user',
          // 'wrapped' => TRUE,
          'description' => t('The user who is voting.'),
        ),
      ),
    );
  }
  
  /**
   * Callback that executes the condition.
   */
  public function execute($vote, $user) {
    if ($vote->type != 'vote') {
      // We only check the right kind of node and terms.
      return FALSE;
    }
    return secret_voting_user_token_exists($vote, $user);
  }

}