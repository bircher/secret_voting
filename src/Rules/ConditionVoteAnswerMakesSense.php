<?php

/**
 * @file
 * Contains class ConditionVoteAnswerMakesSense.
 */

namespace Drupal\secret_voting\Rules;

/**
 * Provides condition for Rules to check if a token exists.
 */
class ConditionVoteAnswerMakesSense extends \RulesConditionHandlerBase {

  /**
   * Provides information for Rules.
   */
  public static function getInfo() {
    return array(
      'name' => 'voting_vote_answer_makes_sense',
      'label' => t('Answer makes sense'),
      'help' => t('Checks if a answer on a ballot makes sense for the vote.'),
      'group' => t('Secret Voting'),
      'parameter' => array(
        'vote' => array(
          'label' => t('Vote node'),
          'type' => 'node',
          'wrapped' => TRUE,
          'description' => t('The secret vote node to be checked.'),
        ),
        'answer' => array(
          'label' => t('Voting Answer'),
          'type' => 'list<secret_voting_field_answer>',
          'description' => t('The content of the vote which is cast.'),
        ),
      ),
    );
  }
  
  /**
   * Callback that executes the condition.
   */
  public function execute($vote, $answer) {

    if ($vote->value()->type != 'vote') {
      // We only check the right kind of node.
      return FALSE;
    }
    dpm($vote->getPropertyInfo());
    $answers = $vote->field_vote->value();
   
    dpm($answers);
    // dpm(secret_voting_field_unserialize($vote->field_vote->value()));
    dpm($answer);
    
    // TODO: check that this makes sense: 
    //   - same amount of answers as questions
    //   - answer keys are options.
    return TRUE;
  }

}