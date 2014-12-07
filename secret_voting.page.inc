<?php

/**
 * @file
 * Contains page callback.
 */

/**
 *
 */
function secret_voting_vote_page_callback($node) {
  // dpm($node);
  // dpm(arg(3));
  try {
    $node_wrapper = entity_metadata_wrapper('node', $node);

    if ($node_wrapper->field_vote_secret->value()) {
      $form = drupal_get_form('secret_voting_secret_question_form', $node_wrapper);
    }
    else {
      $form = drupal_get_form('secret_voting_public_question_form', $node_wrapper);
    }
  }
  catch (Exception $e) {
    dpm($e->getMessage());
  }
  // dpm($form);
  return $form;


}

function secret_voting_secret_question_form($form, &$form_state, $vote) {
  global $user;
  if (!isset($form_state['vote_state'])) {
    $form_state['vote_state'] = 'selecting';
  }

  switch ($form_state['vote_state']) {
    case 'selecting':
      $options = array();
      foreach (secret_voting_items_allowed_to_vote_for($vote, $user) as $item) {
        $options[$item->getIdentifier()] = $item->name->value();
      }
      $form['selected'] = array(
        '#type' => 'select',
        '#title' => t('Selected'),
        '#options' => $options,
        '#default_value' => key($options),
        '#required' => TRUE,
        '#description' => t('Select the entity to vote for.'),
      );
      $form['token'] = array(
        '#type' => 'textfield',
        '#title' => t('Secret token'),
        '#size' => 60,
        '#maxlength' => 128,
        '#description' => t('Enter the secret token you got for this vote or leave it empty to generate a token.'),
      );
      $form['submit'] = array(
        '#weight' => 50,
        '#type' => 'submit',
        '#value' => t('Continue')
      );
      break;

    case 'voting':
      $secret_token = $form_state['secret_voting']['secret_token'];
      $entity = $form_state['secret_voting']['voting_entity'];
      if (!secret_voting_get_secret_ballot($vote, $secret_token)) {
        $form['info'] = array(
          '#type' => 'fieldset',
          '#title' => t('Voter information'),
          '#weight' => 1,
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
        );
        $form['info']['voting_details'] = array(
          '#markup' => t('Secret token: %token', array('%token' => $secret_token)),
        );
        $form['info']['voting_details_name'] = array(
          '#markup' => t('Voting for: %name', array('%name' => $entity->label())),
        );
        $form = secret_voting_field_vote_question_form($form, $form_state, $vote->field_vote->raw(), FALSE);
        $form['submit'] = array(
          '#weight' => 50,
          '#type' => 'submit',
          '#value' => t('Vote')
        );
        // we break here on purpose within the if statement.
        break;
      }
      else {
        $message = t('You have already voted.');
        $form_state['secret_voting']['success_message'] = $message;
        $form_state['secret_voting']['success'] = FALSE;
      }

    case 'done':
      $success = $form_state['secret_voting']['success'];
      $message = $form_state['secret_voting']['success_message'];
      drupal_set_message($message,($success ? 'status' : 'error'));
      // $form['info_done'] = array('#markup' => $message);
      break;

    default:
      $form['info_error'] = array('#markup' => t('Something went wrong :('));
  }

  return $form;
}


function secret_voting_secret_question_form_validate($form, &$form_state) {
  $vote = $form_state['build_info']['args'][0];

  if ($form_state['vote_state'] == 'selecting') {
    // Load the voting entity in the secelting phase
    $selected_id = $form_state['values']['selected'];
    if ($vote->field_vote_type->value() == 'taxonomy') {
      $entity_type = 'taxonomy_term';
    }
    else {
      $entity_type = 'user';
    }
    $entity = entity_metadata_wrapper($entity_type, $selected_id);
    $form_state['secret_voting']['voting_entity'] = $entity;

    $token = secret_voting_get_vote_token($vote, $entity);
    if ($token) {
      if ($token->field_token_hash->value() != secret_voting_hash($form_state['values']['token'], $entity->getIdentifier())) {
        form_set_error('token', t('The secret token is not valid.'));
      }
    }
  }
  else {
    // in other vote form states we assume the entity has been loaded.
    $entity = $form_state['secret_voting']['voting_entity'];
  }
}

function secret_voting_secret_question_form_submit($form, &$form_state) {

  $vote = $form_state['build_info']['args'][0];
  $entity = $form_state['secret_voting']['voting_entity'];
  $token = secret_voting_get_vote_token($vote, $entity);

  if ($form_state['vote_state'] == 'selecting') {
    if (!$token) {
      // if the voting token doesn't exist, we create it.
      if ($vote->field_vote_type->value() == 'taxonomy') {
        $rule_component = 'rules_voting_create_term_token';
      }
      else {
        $rule_component = 'rules_voting_create_user_token';
      }
      $secret_token = secret_voting_create_secret_token();
      $success = rules_invoke_component($rule_component, $vote->value(), $entity->value(), $secret_token);

      if ($success) {
        $form_state['secret_voting']['secret_token'] = $secret_token;
        $form_state['vote_state'] = 'voting';
        $message = 'A secret token has been generated: %secret_token<br/>You can use it to vote at a later time.';
        drupal_set_message(t($message, array('%secret_token' => $secret_token)));
      }
    }
    else {
      $form_state['secret_voting']['secret_token'] = $form_state['values']['token'];
    }
    $form_state['vote_state'] = 'voting';
  }
  elseif ($form_state['vote_state'] == 'voting') {
    // check if voting is allowed.
    $secret_token = $form_state['secret_voting']['secret_token'];
    $success = FALSE;
    if (!secret_voting_get_secret_ballot($vote, $secret_token)) {
      if ($token->field_token_hash->value() == secret_voting_hash($secret_token, $entity->getIdentifier(), FALSE)) {
        $answer = secret_voting_extract_answer($vote, $form_state);
        $success = rules_invoke_component('rules_voting_register_vote', $vote->value(), $form_state['secret_voting']['secret_token'], $answer);

        if ($success) {
          $message = t('The vote was successfully registered. Your hash is %hash',
              array('%hash' => substr(secret_voting_hash($secret_token, $vote->getIdentifier(), TRUE),0,8))
              );
        }
        else {
          $message = t('There was a problem with the registration of the vote.');
        }
      }
      else {
        $message = t('The secret token is not valid.');
      }
    }
    else {
      $message = t('You have already voted.');
    }
    // drupal_set_message($message,($success ? 'status' : 'error'));
    $form_state['secret_voting']['success_message'] = $message;
    $form_state['secret_voting']['success'] = $success;
    $form_state['vote_state'] = 'done';
  }

  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }
  $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
  $form_state['rebuild'] = TRUE;
}


function secret_voting_public_question_form($form, &$form_state, $vote) {
  global $user;
  if (!isset($form_state['vote_state'])) {
    $form_state['vote_state'] = 'selecting';
  }

  switch ($form_state['vote_state']) {
    case 'selecting':
      $options = array();
      foreach (secret_voting_items_allowed_to_vote_for($vote, $user) as $item) {
        $options[$item->getIdentifier()] = $item->name->value();
      }
      $form['selected'] = array(
        '#type' => 'select',
        '#title' => t('Selected'),
        '#options' => $options,
        '#default_value' => key($options),
        '#required' => TRUE,
        '#description' => t('Select the entity to vote for.'),
      );
      $form['submit'] = array(
        '#weight' => 50,
        '#type' => 'submit',
        '#value' => t('Continue')
      );
      break;

    case 'voting':
      $entity = $form_state['secret_voting']['voting_entity'];
      if (!secret_voting_get_public_ballot($vote, $entity)) {
        $form['info'] = array(
          '#type' => 'fieldset',
          '#title' => t('Voter information'),
          '#weight' => 1,
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
        );
        $form['info']['voting_details_name'] = array(
          '#markup' => t('Voting for: %name', array('%name' => $entity->label())),
        );
        $form = secret_voting_field_vote_question_form($form, $form_state, $vote->field_vote->raw(), FALSE);
        $form['submit'] = array(
          '#weight' => 50,
          '#type' => 'submit',
          '#value' => t('Vote')
        );
        // we break here on purpose within the if statement.
        break;
      }
      else {
        $message = t('You have already voted.');
        $form_state['secret_voting']['success_message'] = $message;
        $form_state['secret_voting']['success'] = FALSE;
      }

    case 'done':
      $success = $form_state['secret_voting']['success'];
      $message = $form_state['secret_voting']['success_message'];
      drupal_set_message($message,($success ? 'status' : 'error'));
      // $form['info_done'] = array('#markup' => $message);
      break;

    default:
      $form['info_error'] = array('#markup' => t('Something went wrong :('));
  }

  return $form;
}


function secret_voting_public_question_form_validate($form, &$form_state) {
  $vote = $form_state['build_info']['args'][0];

  if ($form_state['vote_state'] == 'selecting') {
    // Load the voting entity in the secelting phase
    $selected_id = $form_state['values']['selected'];
    if ($vote->field_vote_type->value() == 'taxonomy') {
      $entity_type = 'taxonomy_term';
    }
    else {
      $entity_type = 'user';
    }
    $entity = entity_metadata_wrapper($entity_type, $selected_id);
    $form_state['secret_voting']['voting_entity'] = $entity;

  }
  else {
    // in other vote form states we assume the entity has been loaded.
    $entity = $form_state['secret_voting']['voting_entity'];
  }
}

function secret_voting_public_question_form_submit($form, &$form_state) {

  $vote = $form_state['build_info']['args'][0];
  $entity = $form_state['secret_voting']['voting_entity'];

  if ($form_state['vote_state'] == 'selecting') {
    $form_state['vote_state'] = 'voting';
  }
  elseif ($form_state['vote_state'] == 'voting') {
    // check if voting is allowed.
    $success = FALSE;
    if (!secret_voting_get_public_ballot($vote, $entity)) {
      $answer = secret_voting_extract_answer($vote, $form_state);
      if ($vote->field_vote_type->value() == 'taxonomy') {
        $rule = 'secret_voting_register_vote_term';
      }
      else {
        $rule = 'secret_voting_secret_voting_register_vote_user';
      }
      $success = rules_invoke_component($rule, $vote->value(), $entity->value(), $answer);
      if ($success) {
        $message = t('The vote was successfully registered.');
      }
      else {
        $message = t('There was a problem with the registration of the vote.');
      }
    }
    else {
      $message = t('You have already voted.');
    }
    // drupal_set_message($message,($success ? 'status' : 'error'));
    $form_state['secret_voting']['success_message'] = $message;
    $form_state['secret_voting']['success'] = $success;
    $form_state['vote_state'] = 'done';
  }

  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }
  $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
  $form_state['rebuild'] = TRUE;
}





function secret_voting_extract_answer($vote, $form_state) {
  $answer = array();
  foreach ($vote->field_vote->raw() as $key => $item) {
    $item = secret_voting_field_unserialize($item);
    // dpm($item);
    $answer_keys = '';
    $answer_array = array();
    $selection = $form_state['values']['voting_options_' . $key];
    // dpm($selection);
    if (!is_array($selection)) {
      $selection_array = array_fill_keys(array_keys($item['options']), 0);
      $selection_array[$selection] = $selection;
      $selection = $selection_array;
    }
    array_walk($selection,
        function (&$value, $key, $options) {
          $value = ($value ? $options[$key] : NULL);
        },
        $item['options']);
    $answer[$key] = array(
      // TODO: make this better...
      'keys' => implode(', ', array_diff($selection, array(NULL))),
      'values' => serialize($selection),
    );
  }
  return $answer;
}

