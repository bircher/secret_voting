<?php

/**
 * @file
 * Contains rules hooks.
 */


/**
 * Implements hook_rules_data_info().
 */
function secret_voting_field_rules_data_info() {
  return array(
    'secret_voting_field_answer' => array(
      'label' => t('Answer'),
    ),
  );
}