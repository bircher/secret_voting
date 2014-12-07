<?php

/**
 * @file
 * Contains class ConditionTermBallotExists.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Provides condition for Rules to check if a token exists.
 */
class ConditionTermBallotExists extends \RulesConditionHandlerBase {

  /**
   * Provides information for Rules.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_term_ballot_exists',
      'label' => t('A ballot exists (term)'),
      'help' => t('Checks if a ballot for a secret token exists.'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'vote' => array(
          'label' => t('Vote node'),
          'type' => 'node',
          // 'wrapped' => TRUE,
          'description' => t('The secret vote node to be checked.'),
        ),
        'term' => array(
          'label' => t('term'),
          'type' => 'taxonomy_term',
          'description' => t('The term used for voting.'),
        ),
      ),
    );
  }
  
  /**
   * Callback that executes the condition.
   */
  public function execute($vote, $term) {
    if ($vote->type != 'vote') {
      // We only check the right kind of node.
      return FALSE;
    }
    $query = new \EntityFieldQuery();
    $query->entityCondition('entity_type', 'vote_ballot')
      ->entityCondition('bundle', 'vote_ballot')
      ->fieldCondition('field_token_vote', 'target_id', $vote->nid)
      ->fieldCondition('field_token_term', 'tid', $term->tid);
    $result = $query->execute();
    return !empty($result['vote_ballot']);
  }

}