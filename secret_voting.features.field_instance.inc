<?php
/**
 * @file
 * secret_voting.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function secret_voting_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-vote-body'
  $field_instances['node-vote-body'] = array(
    'bundle' => 'vote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Explain what is voted on.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Description',
    'required' => 0,
    'settings' => array(
      'display_summary' => 1,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-vote-field_vote'
  $field_instances['node-vote-field_vote'] = array(
    'bundle' => 'vote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Provide the question and answer options for the secret vote',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'secret_voting_field',
        'settings' => array(),
        'type' => 'secret_voting_field_example_vote',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_vote',
    'label' => 'Voting Details',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'secret_voting_field',
      'settings' => array(),
      'type' => 'secret_voting_field_vote',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-vote-field_vote_attachments'
  $field_instances['node-vote-field_vote_attachments'] = array(
    'bundle' => 'vote',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_table',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_vote_attachments',
    'label' => 'Attachments',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => '',
      'file_extensions' => 'pdf doc xls ods odt zip tar ppt pptx docx xlsx pps odp',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-vote-field_vote_closing_date'
  $field_instances['node-vote-field_vote_closing_date'] = array(
    'bundle' => 'vote',
    'deleted' => 0,
    'description' => 'Indicate when a vote will end. It does not automatically close yet.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_vote_closing_date',
    'label' => 'Vote closes',
    'required' => 1,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 1,
        'input_format' => 'd/m/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-vote-field_vote_roles'
  $field_instances['node-vote-field_vote_roles'] = array(
    'bundle' => 'vote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'rolereference',
        'settings' => array(),
        'type' => 'rolereference_default',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_vote_roles',
    'label' => 'Roles',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-vote-field_vote_secret'
  $field_instances['node-vote-field_vote_secret'] = array(
    'bundle' => 'vote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_vote_secret',
    'label' => 'Secret vote',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-vote-field_vote_state'
  $field_instances['node-vote-field_vote_state'] = array(
    'bundle' => 'vote',
    'default_value' => array(
      0 => array(
        'value' => 'open',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_vote_state',
    'label' => 'State',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(
        'apply_chosen' => 0,
        'display_empty' => 0,
        'formatter' => '',
        'formatter_settings' => array(),
      ),
      'type' => 'field_extrawidgets_read_only',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-vote-field_vote_terms'
  $field_instances['node-vote-field_vote_terms'] = array(
    'bundle' => 'vote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_vote_terms',
    'label' => 'Organisation',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-vote-field_vote_type'
  $field_instances['node-vote-field_vote_type'] = array(
    'bundle' => 'vote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Select a modality for voting.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_vote_type',
    'label' => 'Vote type',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'taxonomy_term-voting_terms-field_voting_term_code'
  $field_instances['taxonomy_term-voting_terms-field_voting_term_code'] = array(
    'bundle' => 'voting_terms',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The section code or country code, used for automatically fill the voting opion',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_voting_term_code',
    'label' => 'code',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'taxonomy_term-voting_terms-field_voting_term_email'
  $field_instances['taxonomy_term-voting_terms-field_voting_term_email'] = array(
    'bundle' => 'voting_terms',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This email is notified when a token for this term has been generated.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_voting_term_email',
    'label' => 'Email',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'email',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'email_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'user-user-field_user_vote_terms'
  $field_instances['user-user-field_user_vote_terms'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_vote_terms',
    'label' => 'Vote terms',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'vote_ballot-term_ballot-field_ballot_answer'
  $field_instances['vote_ballot-term_ballot-field_ballot_answer'] = array(
    'bundle' => 'term_ballot',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'secret_voting_field',
        'settings' => array(),
        'type' => 'secret_voting_field_simple_answer',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_ballot_answer',
    'label' => 'Answer',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'secret_voting_field',
      'settings' => array(),
      'type' => 'secret_voting_field_none',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'vote_ballot-term_ballot-field_token_term'
  $field_instances['vote_ballot-term_ballot-field_token_term'] = array(
    'bundle' => 'term_ballot',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_token_term',
    'label' => 'term',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'vote_ballot-term_ballot-field_token_vote'
  $field_instances['vote_ballot-term_ballot-field_token_vote'] = array(
    'bundle' => 'term_ballot',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_token_vote',
    'label' => 'Vote',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'vote_ballot-user_ballot-field_ballot_answer'
  $field_instances['vote_ballot-user_ballot-field_ballot_answer'] = array(
    'bundle' => 'user_ballot',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'secret_voting_field',
        'settings' => array(),
        'type' => 'secret_voting_field_simple_answer',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_ballot_answer',
    'label' => 'Answer',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'secret_voting_field',
      'settings' => array(),
      'type' => 'secret_voting_field_none',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'vote_ballot-user_ballot-field_token_user'
  $field_instances['vote_ballot-user_ballot-field_token_user'] = array(
    'bundle' => 'user_ballot',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_token_user',
    'label' => 'user',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(
        'display_empty' => 0,
        'formatter' => 'entityreference_label',
        'formatter_settings' => array(
          'link' => 0,
        ),
      ),
      'type' => 'field_extrawidgets_read_only',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'vote_ballot-user_ballot-field_token_vote'
  $field_instances['vote_ballot-user_ballot-field_token_vote'] = array(
    'bundle' => 'user_ballot',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_token_vote',
    'label' => 'Vote',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'vote_ballot-vote_ballot-field_ballot_answer'
  $field_instances['vote_ballot-vote_ballot-field_ballot_answer'] = array(
    'bundle' => 'vote_ballot',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'secret_voting_field',
        'settings' => array(),
        'type' => 'secret_voting_field_simple_answer',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_ballot_answer',
    'label' => 'Answer',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'secret_voting_field',
      'settings' => array(),
      'type' => 'secret_voting_field_none',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'vote_ballot-vote_ballot-field_token_hash'
  $field_instances['vote_ballot-vote_ballot-field_token_hash'] = array(
    'bundle' => 'vote_ballot',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_token_hash',
    'label' => 'hash',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(),
      'type' => 'field_extrawidgets_hidden',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'vote_ballot-vote_ballot-field_token_vote'
  $field_instances['vote_ballot-vote_ballot-field_token_vote'] = array(
    'bundle' => 'vote_ballot',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_ballot',
    'field_name' => 'field_token_vote',
    'label' => 'Vote',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(
        'display_empty' => 0,
        'formatter' => '',
        'formatter_settings' => array(),
      ),
      'type' => 'field_extrawidgets_read_only',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'vote_token-taxonomy_token-field_token_hash'
  $field_instances['vote_token-taxonomy_token-field_token_hash'] = array(
    'bundle' => 'taxonomy_token',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_token',
    'field_name' => 'field_token_hash',
    'label' => 'hash',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(),
      'type' => 'field_extrawidgets_hidden',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'vote_token-taxonomy_token-field_token_term'
  $field_instances['vote_token-taxonomy_token-field_token_term'] = array(
    'bundle' => 'taxonomy_token',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_token',
    'field_name' => 'field_token_term',
    'label' => 'term',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
        'display_empty' => 0,
        'formatter' => 'taxonomy_term_reference_link',
        'formatter_settings' => array(),
      ),
      'type' => 'options_select',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'vote_token-taxonomy_token-field_token_vote'
  $field_instances['vote_token-taxonomy_token-field_token_vote'] = array(
    'bundle' => 'taxonomy_token',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_token',
    'field_name' => 'field_token_vote',
    'label' => 'Vote',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
        'display_empty' => 0,
        'formatter' => 'entityreference_label',
        'formatter_settings' => array(
          'link' => 0,
        ),
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'vote_token-user_token-field_token_hash'
  $field_instances['vote_token-user_token-field_token_hash'] = array(
    'bundle' => 'user_token',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_token',
    'field_name' => 'field_token_hash',
    'label' => 'hash',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(),
      'type' => 'field_extrawidgets_hidden',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'vote_token-user_token-field_token_user'
  $field_instances['vote_token-user_token-field_token_user'] = array(
    'bundle' => 'user_token',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_token',
    'field_name' => 'field_token_user',
    'label' => 'user',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(
        'display_empty' => 0,
        'formatter' => 'entityreference_label',
        'formatter_settings' => array(
          'link' => 0,
        ),
      ),
      'type' => 'field_extrawidgets_read_only',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'vote_token-user_token-field_token_vote'
  $field_instances['vote_token-user_token-field_token_vote'] = array(
    'bundle' => 'user_token',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'vote_token',
    'field_name' => 'field_token_vote',
    'label' => 'Vote',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(
        'display_empty' => 0,
        'formatter' => 'entityreference_label',
        'formatter_settings' => array(
          'link' => 0,
        ),
      ),
      'type' => 'field_extrawidgets_read_only',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Answer');
  t('Attachments');
  t('Description');
  t('Email');
  t('Explain what is voted on.');
  t('Indicate when a vote will end. It does not automatically close yet.');
  t('Organisation');
  t('Provide the question and answer options for the secret vote');
  t('Roles');
  t('Secret vote');
  t('Select a modality for voting.');
  t('State');
  t('The section code or country code, used for automatically fill the voting opion');
  t('This email is notified when a token for this term has been generated.');
  t('Vote');
  t('Vote closes');
  t('Vote terms');
  t('Vote type');
  t('Voting Details');
  t('code');
  t('hash');
  t('term');
  t('user');

  return $field_instances;
}
