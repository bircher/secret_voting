<?php

/**
 * @file
 * Contains class ConditionTermTokenExists.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Provides condition for Rules to check if a token exists.
 */
class ConditionTermTokenExists extends \RulesConditionHandlerBase {

  /**
   * Provides information for Rules.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_term_token_exists',
      'label' => t('A Token for a term exists'),
      'help' => t('Checks if a token for a voting term exists.'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'vote' => array(
          'label' => t('Vote node'),
          'type' => 'node',
          // 'wrapped' => TRUE,
          'description' => t('The secret vote node to be checked.'),
        ),
        'term' => array(
          'label' => t('Voting term'),
          'type' => 'taxonomy_term',
          // 'wrapped' => TRUE,
          'description' => t('The voting term to be checked.'),
        ),
      ),
    );
  }
  
  /**
   * Callback that executes the condition.
   */
  public function execute($vote, $term) {
    if ($vote->type != 'vote' || $term->vocabulary_machine_name != 'voting_terms') {
      // We only check the right kind of node and terms.
      return FALSE;
    }
    return secret_voting_term_token_exists($vote, $term);
  }

}