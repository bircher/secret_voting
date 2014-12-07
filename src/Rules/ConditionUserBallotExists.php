<?php

/**
 * @file
 * Contains class ConditionUserBallotExists.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Provides condition for Rules to check if a token exists.
 */
class ConditionUserBallotExists extends \RulesConditionHandlerBase {

  /**
   * Provides information for Rules.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_user_ballot_exists',
      'label' => t('A ballot exists (user)'),
      'help' => t('Checks if a ballot for a secret token exists.'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'vote' => array(
          'label' => t('Vote node'),
          'type' => 'node',
          // 'wrapped' => TRUE,
          'description' => t('The secret vote node to be checked.'),
        ),
        'user' => array(
          'label' => t('User'),
          'type' => 'user',
          'description' => t('The user voting.'),
        ),
      ),
    );
  }
  
  /**
   * Callback that executes the condition.
   */
  public function execute($vote, $user) {
    if ($vote->type != 'vote') {
      // We only check the right kind of node.
      return FALSE;
    }
    $query = new \EntityFieldQuery();
    $query->entityCondition('entity_type', 'vote_ballot')
      ->entityCondition('bundle', 'user_ballot')
      ->fieldCondition('field_token_vote', 'target_id', $vote->nid)
      ->fieldCondition('field_token_user', 'target_id', $user->uid);
    $result = $query->execute();
    return !empty($result['vote_ballot']);
  }

}