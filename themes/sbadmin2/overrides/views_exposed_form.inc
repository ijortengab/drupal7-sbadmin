<?php

/**
 * Implemements of hook_preprocess_HOOK().
 *
 * Preprocess theme `views_exposed_form`.
 */
function sbadmin2_preprocess_views_exposed_form(&$variables) {
    // @see: sbadmin2_form_views_exposed_form_alter().
    $form = $variables['form'];

    // Ambil alih variable widget, karena akan render didalam preprocess ini.
    // Nanti tiba di template tinggal print saja.
    $widgets = $variables['widgets'];

    $variables['widgets_rebuild'] = [];
    $widgets_rebuild = &$variables['widgets_rebuild'];

    foreach ($variables['widgets'] as $id => $widget) {
        $element_value = $form[$form['#info'][$id]['value']];
        $element_operator = (isset($form['#info'][$id]['operator']) && isset($form[$form['#info'][$id]['operator']])) ? $form[$form['#info'][$id]['operator']] : [];

        // Group terdiri dari `button` atau `input`. Jika salah satu element
        // terdapat class form-control, maka itu masuk kategori group `input`.
        $group = 'input';
        if (isset($element_value['#sbadmin2_transform']) && $element_value['#sbadmin2_transform'] == 'button') {
            $group = 'button';
        }
        // Prepare label.
        $label = [
            '#type' => ($group == 'input') ? (empty($element_value['#sbadmin2_label_menu']) ? 'input_group_addon' : 'button_group_addon') : 'button_group_addon',
            '#title' => $widget->label,
            '#sbadmin2_size' => isset($element_value['#sbadmin2_size']) ? $element_value['#sbadmin2_size'] : null,
        ];
        // Label toggle.
        $label_toggle = empty($element_value['#sbadmin2_label_menu']) ? [] : [
            '#type' => 'submit_button',
            '#toggle' => 'dropdown',
            '#value' => '<span class="caret"></span>',
            '#sbadmin2_size' => isset($element_value['#sbadmin2_size']) ? $element_value['#sbadmin2_size'] : null,
        ];
        // Label menu.
        $label_menu = empty($element_value['#sbadmin2_label_menu']) ? [] : [
            '#type' => 'dropdown_menu',
            '#options' => $element_value['#sbadmin2_label_menu'],
        ];
        // Operator.
        $operator = empty($widget->operator) ? [] : [
            '#markup' => $widget->operator,
        ];
        // Element khusus multivalue, beri fitur centang all.
        $bulk = empty($element_value['#sbadmin2_bulk_toggle']) ? [] : [
            '#type' => 'submit_button',
            '#value' => '<i class="fa fa-square-o fa-fw"></i>',
            '#attributes' => ['class' => ['bulk-toggle'], 'type' => 'button'],
            '#sbadmin2_size' => isset($element_value['#sbadmin2_size']) ? $element_value['#sbadmin2_size'] : null,
        ];
        // Widget pasti ada.
        $input = [
            '#markup' => $widget->widget,
        ];
        // Mapping Position.
        switch ($group) {
            case 'input':
                $widgets_rebuild[$id] = [
                    '#theme_wrappers' => ['input_group'],
                    'label' => [
                        '#theme_wrappers' => empty($element_value['#sbadmin2_label_menu']) ? [] : ['input_group_button'],
                        'label' => $label,
                        'label_toggle' => $label_toggle,
                        'label_menu' => $label_menu,
                    ],
                    'operator' => [
                        '#theme_wrappers' => empty($operator) ? [] : ['input_group_button'],
                        'operator' => $operator,
                    ],
                    'input' => $input,
                ];
                break;

            case 'button':
                $widgets_rebuild[$id] = [
                    '#theme_wrappers' => empty($element_value['#sbadmin2_label_menu']) ? ['button_group_input'] : ['button_toolbar'],
                    'label' => [
                        '#theme_wrappers' => empty($element_value['#sbadmin2_label_menu']) ? [] : ['button_group'],
                        'label' => $label,
                        'label_toggle' => $label_toggle,
                        'label_menu' => $label_menu,
                    ],
                    'operator' => [
                        '#theme_wrappers' => empty($operator) ? [] : (empty($element_value['#sbadmin2_label_menu']) ? [] : ['button_group']),
                        'operator' => $operator,
                    ],
                    'bulk' => [
                        '#theme_wrappers' => empty($bulk) ? [] : ['button_group'],
                        'bulk' => $bulk,
                    ],
                    'input' => [
                        '#theme_wrappers' => empty($element_value['#sbadmin2_label_menu']) ? [] : ['button_group_input'],
                        'input' => $input,
                    ],
                ];
                break;
        }
        // Copy size, lihat dari element value saja.
        $widgets_rebuild[$id]['#sbadmin2_size'] = isset($element_value['#sbadmin2_size']) ? $element_value['#sbadmin2_size'] : null;
        // Sembunyikan operator jika value sama dengan default, selain itu - berarti ada interfensi user - maka tampilkan.
        if (isset($element_operator['#default_value']) && isset($element_operator['#value']) && $element_operator['#default_value'] == $element_operator['#value']) {
             $widgets_rebuild[$id]['operator']['#attributes']['class'][] = 'element-hidden';
        }

        $widgets_rebuild[$id]['#prefix'] = '<div class="views-exposed-widget">';
        $widgets_rebuild[$id]['#suffix'] = '</div>';
        if (!empty($form['#sbadmin2_listgroup'])) {
            $widgets_rebuild[$id]['#theme_wrappers'][] = 'list_group_item';
            // $widgets_rebuild[$id]['#theme_wrappers'][] = 'list_group';
        }
        else {
            $widgets_rebuild[$id]['#prefix'] = '<div class="form-group">';
            $widgets_rebuild[$id]['#suffix'] = '</div>';
        }
    }
    $widgets_rebuild = drupal_render($widgets_rebuild);
    // $widgets_rebuild = ''; // Untuk development, turn on this line.
    $variables['widgets'] = []; // Untuk development, turn off this line.
}
