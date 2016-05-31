<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_datastream_blocks_admin_settings(array $form, array &$form_state) {
  $form = array( 
    'block_dsids' => array(
      '#type' => 'textfield',
      '#title' => t('Create blocks for Datastream ID values'),
      '#description' => t('Will create a block for each Datastream ID listed here.  Multiple values must be separated with a comma.  Click ').
        l(t('Blocks'), "admin/structure/block")." to manage their display options.",
      '#default_value' => variable_get('islandora_datastream_blocks_block_dsids', ''),
    ),  
    'old_block_dsids' => array(
      '#value' => variable_get('islandora_datastream_blocks_block_dsids', ''),
      '#type' => 'hidden'
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    ),
    'reset' => array(
      '#type' => 'submit',
      '#value' => t('Reset to defaults'),
    ),
  );
  return $form;
}

/**
 * Function that sets the Drupal variables with user's input.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_datastream_blocks_admin_settings_submit(array $form, array &$form_state) {
  drupal_set_message(t('The settings have been updated!'));
  $id = $form_state['triggering_element']['#id'];
  switch ($id) {
    case 'edit-submit':
      $old_block_dsids = variable_get('islandora_datastream_blocks_block_dsids', '');
      variable_set('islandora_datastream_blocks_block_dsids', $form_state['values']['block_dsids']);
      islandora_datastream_blocks_sync_blocks($form, $old_block_dsids, $form_state['values']['block_dsids']);
      break;

    case 'edit-reset':
      variable_del('islandora_datastream_blocks_block_dsids');
      break;
  }
}

function islandora_datastream_blocks_sync_blocks($form, $old_block_dsids, $new_block_dsids) {
    return;
    $old_block_dsids_arr = explode(",", $old_block_dsids);
    $new_block_dsids_arr = explode(",", $new_block_dsids);

    $delete_dsids_blocks = $add_dsids_blocks = array();
    foreach ($old_block_dsids_arr as $old_block_dsid) {
        if (!(in_array($old_block_dsid, $new_block_dsids_arr))) {
            // orphan - old block must be deleted
            $delete_dsids_blocks[] = $old_block_dsid;
        }
    }
    foreach ($new_block_dsids_arr as $new_block_dsid) {
        if (!(in_array($new_block_dsid, $old_block_dsids_arr))) {
            // block must be added
            $add_dsids_blocks[] = $new_block_dsid;
        }
    }
    foreach ($add_dsids_blocks as $add_dsid_block) {
        islandora_datastream_blocks_add_block($form, $add_dsid_block);
    }
    foreach ($delete_dsids_blocks as $delete_dsid_block) {
        islandora_datastream_blocks_delete_block($form, $delete_dsid_block);
    }
}

function islandora_datastream_blocks_delete_block($form, $dsid) {
    if ($dsid) {
        form_load_include($form_state, 'inc', 'block', 'block.admin');
        $form_state = array();
        $module = 'islandora_datastream_blocks';
        $delta = 'dsid:'.$dsid;
        $form_state['values'] = array(
          'title' => 'Islandora Datastream block "'.$dsid.'"',
          'info' => 'Block to render datastream element "'.$dsid.'"',
          'visibility' => '0',
          'pages' => NULL,
          'custom' => '0',
          // The block isn't visible initially
          'regions' => array(
              'seven' => '-1',
              'stark' => '-1',
            ),
          'body' => array(
              'value' => '[[show_datastream='.$dsid.']]',
              'format' => 'full_html',
            ),
        );
        // Submit the form programmatically.
        drupal_form_submit('block_custom_block_delete', $form, $form_state, $module, $delta);    
    }
}

function islandora_datastream_blocks_add_block($form, $dsid) {
    if ($dsid) {
        form_load_include($form_state, 'inc', 'block', 'block.admin');
        $form_state = array();
        $form_state['values'] = array(
          'title' => 'Islandora Datastream block "'.$dsid.'"',
          'info' => 'Block to render datastream element "'.$dsid.'"',
          'visibility' => '0',
          'pages' => NULL,
          'custom' => '0',
          // The block isn't visible initially
          'regions' => array(
              'seven' => '-1',
              'stark' => '-1',
            ),
          'body' => array(
              'value' => '[[show_datastream='.$dsid.']]',
              'format' => 'full_html',
            ),
        );
        // Submit the form programmatically.
//        drupal_form_submit('block_add_block_form', $form_state);
        drupal_form_submit('block_admin_configure', $form, $form_state, 'islandora_datastream_blocks', 'dsid:'.$dsid);
//        drupal_form_submit('block_add_block_form_submit', $form_state);    
    }
}
