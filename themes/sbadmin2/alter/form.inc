<?php

/**
 * Implements of hook_form_FORM_ID_alter().
 *
 * Modifikasi form id `masquerade_block_1`.
 */
function sbadmin2_form_masquerade_block_1_alter(&$form, &$form_state) {
    $form['#sbadmin_input_group'] = true;
    $form['masquerade_user_field']['#sbadmin2_transform'] = 'select2';
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
    $form['actions']['submit']['#type'] = 'submit_button';
    // Tambah children berupa icon.
    $form['actions']['submit']['icon_search'] = [
        '#type' => 'icon',
        '#icon' => 'search',
        '#bundle' => 'glyphicon',
    ];
}

/**
 * Implements of hook_form_FORM_ID_alter.
 *
 * Form ID: user_login_block.
 */
function sbadmin2_form_user_login_block_alter(&$form, &$form_state) {
    $form['name']['#type'] = 'textfield2';
    $form['pass']['#type'] = 'password2';
}

/**
 * Implements of hook_form_FORM_ID_alter.
 *
 * Form ID: views_exposed_form.
 */
function sbadmin2_form_views_exposed_form_alter(&$form, &$form_state) {
    $view = $form_state['view'];
    if ($view->display_handler->get_option('style_plugin') == 'table') {
        $style_options = $form_state['view']->display_handler->get_option('style_options');
        $exposed_form_listgroup_convert = isset($style_options['sbadmin2']['listgroup_convert']['exposed_form']) && $style_options['sbadmin2']['listgroup_convert']['exposed_form'];
        if ($exposed_form_listgroup_convert) {
            // Akan digunakan oleh preprocess.
            // @see: sbadmin2_preprocess_views_exposed_form().
            $form['#sbadmin2_listgroup'] = true;
            $form['submit'] = [
                'submit' => $form['submit'],
                // '#prefix' => '<div class="views-exposed-widget">',
                // '#suffix' => '</div>',
                '#theme_wrappers' => ['list_group_item'],
                '#sbadmin2_colorize' => 'default',
            ];
        }
    }
    foreach ($form['#info'] as $id => $info) {
        // Property #info sudah pasti terdapat minimal 3 key sebagai berikut:
        // value, label, description.
        // @see: views_handler_filter::exposed_info()
        $element_value = &$form[$info['value']];
        // Modifikasi value.
        $element_value['#sbadmin2_size'] = 'sm';
        $type = isset($element_value['#type']) ? $element_value['#type'] : null;
        switch ($type) {
            case 'select':
                // Select tidak user friendly, ganti ke button atau select2.
                $count  = count($element_value['#options']);
                if (isset($element_value['#options']['All'])) { // Ada di views exposed form.
                    $count -= 1;
                }
                if ($count <= 6) { //@todo, set sebagai theme options.
                    $element_value['#sbadmin2_transform'] = 'button';
                    if (!empty($element_value['#multiple'])) {
                        // @todo: ada interface untuk toggle.
                        // Beritahu preprocess bahwa kita perlu mendaftar ke label menu.
                        $element_value['#sbadmin2_label_menu'][] = [
                            '#theme' => 'link',
                            '#text' => t('Multiple Select'),
                            '#path' => '#',
                            '#options' => [
                                'external' => true,
                                'attributes' => [
                                    'class' => ['views-multiple-select'],
                                ],
                                'html' => false,
                            ],
                        ];
                        // Beritahu preprocess bahwa kita butuh element toggle.
                        $element_value['#sbadmin2_bulk_toggle'] = true;
                        // Multiple select dan bulk toggle, keduanya perlu
                        // javascript dibawah ini.
                        $element_value['#attached']['library'][] = ['sbadmin2','sbadmin2.views_multiple_select'];
                    }
                }
                else {
                    // Selain itu, gunakan select2.
                    $element_value['#sbadmin2_transform'] = 'select2';
                }
                $element_value['#sbadmin2_clean_wrapper'] = true;
                break;

            case 'textfield':
                $element_value['#sbadmin2_clean_wrapper'] = true;
                if (!empty($element_value['#autocomplete_path'])) {
                    $element_value['#sbadmin2_transform'] = 'select2';
                }
                break;
        }

        // Untuk kasus field date yang terdapat 3 textfield tambahan
        // (value, min, max).
        foreach (element_children($element_value) as $child) {
            $type = isset($element_value[$child]['#type']) ? $element_value[$child]['#type'] : null;
            // $element_value[$child]['#sbadmin2_views_date_popup'] = true;
            if (isset($element_value[$child]['#dependency'])) {
                // sini.
                $element_value[$child]['#attached']['library'][] = ['sbadmin2', 'sbadmin2.dependent'];
                $element_value[$child]['#sbadmin2_dependency'] = true;
                $element_value[$child]['#sbadmin2_dependency_class'] = true;
                $element_value[$child]['#sbadmin2_dependency_self'] = true;
            }
            switch ($type) {
                case 'textfield': // Ini berarti field created dan updated.
                    $element_value[$child]['#sbadmin2_clean_wrapper'] = true;
                    $element_value[$child]['#sbadmin2_transform'] = 'input_group';
                    // $element_value[$child]['#sbadmin2_label'] = true;
                    $element_value[$child]['#sbadmin2_class_id'] = true;
                    // Agar konsisten dengan module `date`.
                    switch ($child) {
                        case 'min':
                            $element_value[$child]['#title'] = t('Start date');
                            break;

                        case 'max':
                            $element_value[$child]['#title'] = t('End date');
                            break;
                    }
                    break;

                case 'date_popup':
                    // Flag untuk prerender `sbadmin2_element_pre_render_spesific()`.
                    $element_value[$child]['#sbadmin2_views_date_popup'] = true;
                    $element_value[$child]['#sbadmin2_class_id'] = true;
                    break;
            }
        }

        // Modifikasi operator.
        if (isset($info['operator']) && isset($form[$info['operator']])) {
            $element_operator = &$form[$info['operator']];
            $element_operator['#sbadmin2_size'] = 'sm';
            // @todo, ada interface untuk ini.
            $element_value['#sbadmin2_label_menu'][] = [
                '#theme' => 'link',
                '#text' => t('Show Operator'),
                '#path' => '#',
                '#options' => [
                    'external' => true,
                    'attributes' => [
                        'class' => ['views-toggle-operator'],
                    ],
                    'html' => false,
                ],
            ];
            $element_value['#attached']['library'][] = ['sbadmin2','sbadmin2.views_toggle_operator'];
            $element_operator['#attributes']['class'][] = 'views-operator';
            // Penyembunyian element dengan menambahkan class `element-hidden`
            // dilakukan di preprocess. @see sbadmin2_preprocess_views_exposed_form().
            // Transform.
            switch ($element_operator['#type']) {
                // Select operator ganti bentuk menjadi input hidden.
                case 'select':
                    $element_operator['#sbadmin2_transform'] = 'button_dropdown_input';
                    // Wrapper diambil alih oleh preprocess.
                    // @see: sbadmin2_preprocess_views_exposed_form().
                    $element_operator['#sbadmin2_clean_wrapper'] = true;
                    break;
            }
        }
    }
}
