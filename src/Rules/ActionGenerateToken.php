<?php

/**
 * @file
 * Contains class ActionGenerateToken.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Action: Export a Commerce order.
 */
class ActionGenerateToken extends \RulesActionHandlerBase {

  /**
   * Defines the action.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_generate_token',
      'label' => t('Generate a secret token'),
      'group' => t('Secret Voting'),
      'provides' => array(
        'secret_token' => array(
          'label' => t('Secret token'),
          'type' => 'text',
        ),
      ),
      'help' => t('Generate a random secret token.'),
    );
  }

  /**
   * Executes the action.
   */
  public function execute() {
    return array('secret_token' => secret_voting_create_secret_token());
  }

}