<?php

/**
 * Implements of hook_form_FORM_ID_alter().
 *
 * Modifikasi form id `masquerade_block_1`.
 */
function sbadmin2_form_masquerade_block_1_alter(&$form, &$form_state) {
    $form['#sbadmin_input_group'] = true;
    $form['masquerade_user_field']['#sbadmin2_select2'] = true;
    $form['masquerade_desc']['#weight'] = 10000;
    unset($form['masquerade_user_field']['#prefix']);
    unset($form['submit']['#suffix']);
}

/**
 * Implements of hook_form_FORM_ID_alter().
 *
 * Modifikasi form id `search_block_form`.
 */
function sbadmin2_form_search_block_form_alter(&$form, &$form_state) {
    // Jadikan kedua element menyatu.
    $form['#sbadmin_input_group'] = true;
    // Convert #type element submit yang mendukung children.
    $form['actions']['submit']['#type'] = 'submit3';
    // Tambah children berupa icon.
    $form['actions']['submit']['icon_search'] = [
        '#type' => 'icon',
        '#icon' => 'search',
        '#bundle' => 'glyphicon',
    ];
}

/**
 * Implements of hook_form_FORM_ID_alter.
 * Form ID: user_login_block.
 */
function sbadmin2_form_user_login_block_alter(&$form, &$form_state) {
    $form['name']['#type'] = 'textfield2';
    $form['pass']['#type'] = 'password2';
}
