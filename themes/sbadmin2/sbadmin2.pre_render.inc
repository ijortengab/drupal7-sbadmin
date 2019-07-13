<?php

/**
 * Melakukan eksekusi pre_render terhadap element yang telah memiliki
 * attribute #sbadmin = true.
 */
function _sbadmin2_element_pre_render($element) {

    // Menambah class form-control.
    switch ($element['#type']) {
        case 'textfield':
        case 'textarea':
        case 'select':
        case 'password':
        case 'file':
            $element['#attributes']['class'][] = 'form-control';
            break;
    }

    // Menambah class btn btn-default.
    switch ($element['#type']) {
        case 'submit':
        case 'button':
            $element['#attributes']['class'][] = 'btn';
            $element['#attributes']['class'][] = 'btn-default';
            break;
    }

    // Melakukan modifikasi terkait input group.
    switch ($element['#type']) {
        case 'form':
            // Contoh form search dan masquerade.
            if (isset($element['#sbadmin_input_group']) && $element['#sbadmin_input_group']) {
                return sbadmin2_inputgroup::factory($element);
            }
            break;
    }

    // Melakukan modifikasi terkait managed_file
    switch ($element['#type']) {
        case 'managed_file':
            $element = _sbadmin2_element_pre_render_managed_file($element);
            break;
    }

    // Otomatis menggunakan select2 jika options > 15.
    switch ($element['#type']) {
        case 'select':
            if (count($element['#options']) > 15) {
                _sbadmin2_element_pre_render_select2($element);
            }
            break;
    }

    // Melakukan modifikasi terkait date time.
    switch ($element['#type']) {
        case 'date_combo':
            // Kasus jika hanya field date yang ada.
            // todo, test pada kasus lain.
            sbadmin2_utils::replace_theme_wrappers('date_form_element', 'form_element', $element);
            sbadmin2_utils::remove_theme_wrappers('date_popup', $element['value']);
            sbadmin2_utils::remove_theme_wrappers('form_element', $element['value']['date']);
            $description = $element['value']['date']['#description'];
            $element['value']['#sorted'] = false;
            $element['value']['sbadmin2_info_sign'] = [
                '#type' => 'icon',
                '#icon' => 'question-circle',
                '#weight' => -1,
                '#tooltip' => ['title' => $description, 'placement' => 'auto left'],
            ];
            $element['value'] = sbadmin2_inputgroup::factory($element['value']);


            break;
    }

    // Melakukan
    switch ($element['#type']) {
        case 'textfield':
            if (!empty($element['#sbadmin2_select2']) && !empty($element['#autocomplete_path'])) {
                sbadmin2_utils::remove_theme_wrappers('form_element', $element);
                $id = $element['#id'];
                // Convert to select.
                $element['#type'] = 'select';
                $element['#theme'] = 'select';
                $element['#options'] = [];
                unset($element['#size']);
                $settings['data']['sbadmin2']['element'][$id] = [
                    'frontController' => 'index.php',
                    'route' => $element['#autocomplete_path'],
                    'defaultOptions' => [
                        'minimumInputLength' => 1,
                    ],
                ];
                if (!empty($element['#sbadmin2_select2_default_value'])) {
                    $settings['data']['sbadmin2']['element'][$id]['defaultValue'] = $element['#sbadmin2_select2_default_value'];
                }
                _sbadmin2_element_pre_render_select2($element, $settings);
            }
            break;
    }
    return $element;
}

function _sbadmin2_element_pre_render_managed_file($element) {
    $element['#attached']['library'][] = ['sbadmin2', 'sbadmin2.managed_file'];
    $element['#attached']['library'][] = ['sbadmin2', 'sbadmin2.tooltip'];

    if (empty($element['#value']['fid']) && isset($element['upload'])) {
        // Class to hide element by CSS.
        $element['upload']['#attributes']['class'][] = 'sbadmin2-managed-file';
        $element['upload']['#sbadmin2'] = true;
        // New element.
        $element['sbadmin2_info_text'] = [
            '#attributes' => ['readonly' => 'readonly', 'class' => ['form-control','sbadmin2-info-text']],
            '#type' => 'textfield3',
        ];
    }
    if (empty($element['#value']['fid']) && isset($element['upload_button'])) {
        // Class to trigger JS.
        $element['upload_button']['#attributes']['class'][] = 'sbadmin2-upload-button';
        $element['upload_button']['#weight'] = 1;
        // New element.
        $element['sbadmin2_browse_button'] = [
            '#attributes' => ['class' => ['sbadmin2-browse-button']],
            '#id' => str_replace($element['upload_button']['#id'], 'upload-button','browse-button'),
            '#type' => 'submit2',
            '#weight' => 2,
            '#value' => t('Select'),
        ];
    }
    if (empty($element['#value']['fid']) && !empty($element['#description'])) {
        // Description asli kita kembalikan ke tempat semula.
        // Sementara description tambahan karena validator, kita taro di
        // input group addon.
        $_validator_description = theme('file_upload_help', array('description' => '', 'upload_validators' => $element['#upload_validators']));
        $validator_description_position = strpos($element['#description'], $_validator_description);
        $original_description = substr($element['#description'], 0, $validator_description_position);
        empty($original_description) or $original_description = preg_replace('/<br \/>$/', '', $original_description);
        $validator_description = substr($element['#description'], $validator_description_position);
        // New element.
        $element['sbadmin2_info_sign'] = [
            '#type' => 'icon',
            '#icon' => 'question-circle',
            '#weight' => -15,
            '#tooltip' => ['title' => $validator_description, 'placement' => 'auto left'],
        ];
        // Modify Wrapper.
        $element['#description'] = $original_description;
    }

    if (!empty($element['#value']['fid']) && isset($element['remove_button'])) {
        // Move.
        // $element['element_group']['button_group']['remove_button'] = $element['remove_button'];
        // $element['remove_button']['#printed'] = true;

        // New element.
        // $element['sbadmin2_info_text'] = [
            // '#attributes' => ['readonly' => 'readonly', 'class' => ['form-control','sbadmin2-info-text']],
            // '#type' => 'textfield3',
            // '#weight' => -10,
        // ];
    }
    if (!empty($element['#value']['fid']) && isset($element['#file'])) {
        $file = $element['#file'];
        $element['sbadmin2_download_sign'] = [
            // '#prefix' => '<span data-toggle="tooltip" data-placement="auto left" title="Download" class="file btn btn-default">',
            // '#suffix' => '</span>',
            // '#theme' => 'link',
            '#type' => 'submit3',
            // '#type' => 'button',
            // '#value' => theme('icon', ['element' => ['#icon' => 'download']]),
            '#value' => 'Download',
            '#path' => file_create_url($file->uri),
            '#options' => ['html' => true],
            '#weight' => -20,
        ];

        $element['sbadmin2_info_text'] = [
            '#attributes' => ['readonly' => 'readonly', 'class' => ['form-control','sbadmin2-info-text']],
            '#type' => 'textfield3',
            '#weight' => -10,
            '#value' => $file->filename,
        ];
        $element['filename']['#access'] = false;
    }
    return sbadmin2_inputgroup::factory($element);
}

function _sbadmin2_element_pre_render_select2(&$element, $settings = []) {
    $id = $element['#id'];
    $element['#attributes']['class'][] = 'sbadmin2-select2';
    $element['#attached']['library'][] = ['sbadmin2', 'sbadmin2.select2'];
    $_settings = [
        'type' => 'setting',
        'data' => [
            'sbadmin2' => [
                'defaultOptions' => [
                    'width' => '100%',
                    'theme' => 'bootstrap',
                ],
                'element' => [
                    $id => [],
                ]
            ],
        ],
    ];
    $settings = array_replace_recursive($_settings, $settings);
    $element['#attached']['js'][] = $settings;
}

function _sbadmin2_element_pre_render_entityconnect($element) {
    // Jika ada element tambahan add_entityconnect atau edit_entityconnect.
    $is_exist = $is_exist_add = $is_exist_edit = false;
    foreach (element_children($element) as $children) {
        if (strpos($children, 'add_entityconnect') === 0) {
            $is_exist = true;
            $is_exist_add = true;
            // Prefix dan Suffix pada widget autocomplete hanya untuk reposisi pada
            // javascript, karena reposisi sudah kita ambil alih, maka info tersebut
            // perlu kita hapus.
            unset($element[$children]['#prefix']);
            unset($element[$children]['#suffix']);
        }
        elseif (strpos($children, 'edit_entityconnect') === 0) {
            $is_exist = true;
            $is_exist_edit = true;
            unset($element[$children]['#prefix']);
            unset($element[$children]['#suffix']);
        }
    }
    if ($is_exist === false) {
        return $element;
    }
    $element['target_id']['#weight'] = -3;// Karena add_entityconnect = -2
    $element['#attached']['js'][] = [
        'type' => 'file',
        'data' => drupal_get_path('module', 'sbadmin2_helper').'/js/tooltip.js',
        'group' => JS_THEME,
    ];
    if ($is_exist_add && $is_exist_edit) {
        $description = t("Set value by search then you can edit the result, or add if you don't find it.");
    }
    elseif ($is_exist_add) {
        $description = t("Search first, you can add new if you don't find it.");
    }
    elseif ($is_exist_edit) {
        $description = t('Search first, then you can edit it if needed.');
    }
    // Hapus #theme_wrapper "form_element" pada element children "target_id".
    sbadmin2_utils::remove_theme_wrappers('form_element', $element['target_id']);
    // Tambah #theme_wrapper "form_element" pada element ini.
    sbadmin2_utils::prepend_theme_wrappers('form_element', $element);

    // Copy attribute untuk form element.
    foreach ($element['target_id'] as $property => $info) {
        switch ($property) {
            case '#title':
            case '#required':
            case '#description':
                $element[$property] = $element['target_id'][$property];
                break;
        }
        // Semua property yang bagian dari sbadmin2 juga perlu dipindahkan.
        if (strpos($property, '#sbadmin2') === 0) {
            $element[$property] = $element['target_id'][$property];
        }
    }

    // New element.
    $element['sbadmin2_info_sign'] = [
        '#type' => 'icon',
        '#icon' => 'question-circle',
        '#weight' => -15,
        '#tooltip' => ['title' => $description, 'placement' => 'auto left'],
    ];
    return sbadmin2_inputgroup::factory($element);
}
