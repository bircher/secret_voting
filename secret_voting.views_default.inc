<?php
/**
 * @file
 * secret_voting.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function secret_voting_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'secret_voting';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_vote_ballot';
  $view->human_name = 'Secret Voting';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Secret Voting Results';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'field_token_hash' => 'field_token_hash',
    'field_token_term' => 'field_token_term',
    'field_token_user' => 'field_token_user',
    'field_ballot_answer' => 'field_ballot_answer',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_token_hash' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_token_term' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_token_user' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_ballot_answer' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Vote ballot: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_vote_ballot';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  /* Field: Field: hash */
  $handler->display->display_options['fields']['field_token_hash']['id'] = 'field_token_hash';
  $handler->display->display_options['fields']['field_token_hash']['table'] = 'field_data_field_token_hash';
  $handler->display->display_options['fields']['field_token_hash']['field'] = 'field_token_hash';
  $handler->display->display_options['fields']['field_token_hash']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_token_hash']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['field_token_hash']['settings'] = array(
    'trim_length' => '8',
  );
  /* Field: Field: term */
  $handler->display->display_options['fields']['field_token_term']['id'] = 'field_token_term';
  $handler->display->display_options['fields']['field_token_term']['table'] = 'field_data_field_token_term';
  $handler->display->display_options['fields']['field_token_term']['field'] = 'field_token_term';
  $handler->display->display_options['fields']['field_token_term']['hide_empty'] = TRUE;
  /* Field: Field: user */
  $handler->display->display_options['fields']['field_token_user']['id'] = 'field_token_user';
  $handler->display->display_options['fields']['field_token_user']['table'] = 'field_data_field_token_user';
  $handler->display->display_options['fields']['field_token_user']['field'] = 'field_token_user';
  $handler->display->display_options['fields']['field_token_user']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_token_user']['settings'] = array(
    'link' => 0,
  );
  /* Field: vote ballot: Answer */
  $handler->display->display_options['fields']['field_ballot_answer']['id'] = 'field_ballot_answer';
  $handler->display->display_options['fields']['field_ballot_answer']['table'] = 'field_data_field_ballot_answer';
  $handler->display->display_options['fields']['field_ballot_answer']['field'] = 'field_ballot_answer';
  $handler->display->display_options['fields']['field_ballot_answer']['click_sort_column'] = 'keys';
  $handler->display->display_options['fields']['field_ballot_answer']['delta_offset'] = '0';
  /* Sort criterion: Field: hash (field_token_hash) */
  $handler->display->display_options['sorts']['field_token_hash_value']['id'] = 'field_token_hash_value';
  $handler->display->display_options['sorts']['field_token_hash_value']['table'] = 'field_data_field_token_hash';
  $handler->display->display_options['sorts']['field_token_hash_value']['field'] = 'field_token_hash_value';
  /* Contextual filter: Field: Vote (field_token_vote) */
  $handler->display->display_options['arguments']['field_token_vote_target_id']['id'] = 'field_token_vote_target_id';
  $handler->display->display_options['arguments']['field_token_vote_target_id']['table'] = 'field_data_field_token_vote';
  $handler->display->display_options['arguments']['field_token_vote_target_id']['field'] = 'field_token_vote_target_id';
  $handler->display->display_options['arguments']['field_token_vote_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_token_vote_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_token_vote_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_token_vote_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_token_vote_target_id']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'node/%/vote-results';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Results';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['secret_voting'] = $view;

  return $export;
}
