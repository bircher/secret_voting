<?php

/**
 * @file
 * Contains class ConditionSecretValid.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Provides condition for Rules to check if a token exists.
 */
class ConditionSecretValid extends \RulesConditionHandlerBase {

  /**
   * Provides information for Rules.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_secret_valid',
      'label' => t('Secret is valid'),
      'help' => t('Checks if a secret token is valid for the vote.'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'vote' => array(
          'label' => t('Vote node'),
          'type' => 'node',
          'wrapped' => TRUE,
          'description' => t('The secret vote node to be checked.'),
        ),
        'secret_token' => array(
          'label' => t('Secret token'),
          'type' => 'text',
          'description' => t('The secret token used for voting.'),
        ),
      ),
    );
  }
  
  /**
   * Callback that executes the condition.
   */
  public function execute($vote, $secret_token) {
    if(secret_voting_secret_lookup($secret_token, $vote)) {
      return TRUE;
    }
    return FALSE;
  }

}