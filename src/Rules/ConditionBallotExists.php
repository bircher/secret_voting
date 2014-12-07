<?php

/**
 * @file
 * Contains class ConditionBallotExists.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Provides condition for Rules to check if a token exists.
 */
class ConditionBallotExists extends \RulesConditionHandlerBase {

  /**
   * Provides information for Rules.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_ballot_exists',
      'label' => t('A ballot exists'),
      'help' => t('Checks if a ballot for a secret token exists.'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'vote' => array(
          'label' => t('Vote node'),
          'type' => 'node',
          // 'wrapped' => TRUE,
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
    if ($vote->type != 'vote') {
      // We only check the right kind of node.
      return FALSE;
    }
    $hash = secret_voting_hash($secret_token, $vote->nid, TRUE);
    $query = new \EntityFieldQuery();
    $query->entityCondition('entity_type', 'vote_ballot')
      ->entityCondition('bundle', 'vote_ballot')
      ->fieldCondition('field_token_vote', 'target_id', $vote->nid)
      ->fieldCondition('field_token_hash', 'value', $hash);
    $result = $query->execute();
    return !empty($result['vote_ballot']);
  }

}