<?php

class sbadmin2_prerender
{
    /**
     *
     */
    public static function addFormControl(&$element)
    {
        $element['#attributes']['class'][] = 'form-control';
    }

    /**
     *
     */
    public static function addButton(&$element)
    {
        $element['#attributes']['class'][] = 'btn';
        $element['#attributes']['class'][] = 'btn-default';
    }

    /**
     *
     */
    public static function modifySelect(&$element)
    {
        $transform = isset($element['#sbadmin2_transform']) ? $element['#sbadmin2_transform'] : null;
        switch ($transform) {
            case 'auto':
                self::transformSelect($element);
                break;

            case 'button':
                self::transformSelect($element);
                self::modifyButtonGroupInput($element);
                break;

            case 'select2':
                self::addFormControl($element);
                self::modifySelect2($element);
                break;

            case 'button_dropdown_input':
                self::modifyButtonDropdownInput($element);
                break;

            default:
                self::addFormControl($element);
                break;
        }
    }

    /**
     *
     */
    public static function modifyTextfield(&$element)
    {
        $transform = isset($element['#sbadmin2_transform']) ? $element['#sbadmin2_transform'] : null;
        switch ($transform) {
            case 'select2':
                if (isset($element['#autocomplete_path'])) {
                    sbadmin2_utils::remove_theme_wrappers('form_element', $element);
                    $id = $element['#id'];
                    // Convert to select.
                    $element['#type'] = 'select';//@todo: clear this line.
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
                    // Property `#value` terisi jika trigger error, kemudian form rebuild.
                    // @see form_builder(), _form_validate().
                    if (isset($element['#value'])) {
                        $settings['data']['sbadmin2']['element'][$id]['defaultValue'] = $element['#value'];
                    }
                    self::modifySelect2($element, $settings);
                }
                break;

            case 'input_group':
                $textfield = $element;
                $element = ['#theme_wrappers' => ['input_group']];
                // Hapus. Jika tidak, terjadi unlimited looping.
                unset($textfield['#sbadmin2_transform']);
                sbadmin2_utils::remove_theme_wrappers('form_element', $textfield);
                $prefix_addon = [];
                $suffix_addon = [];
                if ((!empty($textfield['#title']) && $textfield['#title_display'] != 'invisible')) {
                    switch ($textfield['#title_display']) {
                        case 'before':
                            $prefix_addon = [
                                '#type' => 'input_group_addon',
                                '#title' => $textfield['#title'],
                                '#weight' => -1,
                            ];
                            break;

                        case 'after':
                            $suffix_addon = [
                                '#type' => 'input_group_addon',
                                '#title' => $textfield['#title'],
                                '#weight' => 1,
                            ];
                            break;
                    }
                }
                if (!empty($textfield['#description'])) {
                    $position = isset($textfield['#sbadmin2_description_display']) ? $textfield['#sbadmin2_description_display'] : 'before';
                    switch ($position) {
                        case 'before':
                            !empty($prefix_addon) or $prefix_addon = [
                                '#type' => 'input_group_addon',
                                '#weight' => -1,
                            ];
                            $prefix_addon += [
                                '#tooltip' => $textfield['#description'],
                                'icon' => [
                                    '#type' => 'icon',
                                    '#icon' => isset($textfield['#sbadmin2_description_icon']) ? $textfield['#sbadmin2_description_icon'] : 'question-circle',
                                ],
                            ];
                            break;

                        case 'after':
                            !empty($suffix_addon) or $suffix_addon = [
                                '#type' => 'input_group_addon',
                                '#weight' => 1,
                            ];
                            $suffix_addon += [
                                '#tooltip' => $textfield['#description'],
                                'icon' => [
                                    '#type' => 'icon',
                                    '#icon' => 'question-circle',
                                ],
                            ];
                            break;
                    }
                }
                if (!empty($textfield['#sbadmin2_class_id'])) {
                    $prefix_addon['#attributes']['class'][] = isset($textfield['#sbadmin2_class_id_value']) ? $textfield['#sbadmin2_class_id_value'] : $textfield['#id'];
                    $suffix_addon['#attributes']['class'][] = isset($textfield['#sbadmin2_class_id_value']) ? $textfield['#sbadmin2_class_id_value'] : $textfield['#id'];
                }
                if (!empty($textfield['#sbadmin2_clean_wrapper'])) {
                    $element['#sbadmin2_clean_wrapper'] = $textfield['#sbadmin2_clean_wrapper'];
                }
                // Finisihing.
                $element['_prefix_addon'] = $prefix_addon;
                $element['_suffix_addon'] = $suffix_addon;
                $element['_textfield'] = $textfield;
                break;

            default:
                self::addFormControl($element);
                break;
        }
    }

    /**
     * Modifying supported element.
     */
    public static function modifyOthers(&$element)
    {
        $type = isset($element['#type']) ? $element['#type'] : null;
        switch ($type) {
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
    }

    /**
     * Berlaku untuk yang punya #options.
     */
    public static function modifyButtonGroupInput(&$element)
    {
        array_key_exists('#theme_wrappers', $element) or $element['#theme_wrappers'] = [];
        array_unshift($element['#theme_wrappers'], 'button_group_input');
        unset($element['#name']);
        if (count($element['#options']) > 0) {
            foreach ($element['#options'] as $key => $choice) {
                array_key_exists('#theme_wrappers', $element[$key]) or $element[$key]['#theme_wrappers'] = [];
                sbadmin2_utils::remove_theme_wrappers('form_element', $element[$key]);
                array_unshift($element[$key]['#theme_wrappers'], 'label_button');
                $element[$key]['#sbadmin2_size'] = isset($element['#sbadmin2_size']) ? $element['#sbadmin2_size'] : null;
                $element[$key]['#sbadmin2_colorize'] = isset($element['#sbadmin2_colorize']) ? $element['#sbadmin2_colorize'] : null;
            }
        }
    }

    public static function modifyManagedFile(&$element)
    {
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
                '#type' => 'submit_button',
                '#weight' => 2,
                '#value' => t('Select'),
            ];
        }
        if (empty($element['#value']['fid']) && !empty($element['#description'])) {
            // Description asli kita kembalikan ke tempat semula.
            // Sementara description tambahan karena validator, kita taro di
            // input group addon.
            $original_description = $element['#description'];
            $validator_description = theme('file_upload_help', array('description' => '', 'upload_validators' => $element['#upload_validators']));
            if (!empty($validator_description)) {
                $position = strpos($element['#description'], $validator_description);
                if ($position !== false) {
                    $original_description = substr($element['#description'], 0, $position);
                    empty($original_description) or $original_description = preg_replace('/<br \/>$/', '', $original_description);
                    $validator_description = substr($element['#description'], $position);
                }
            }
            // New element.
            $icon = empty($validator_description) ? 'file-o' : 'question-circle';
            $element['sbadmin2_info_sign'] = [
                '#type' => 'icon',
                '#icon' => $icon,
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
                '#type' => 'submit_button',
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
        $element = sbadmin2_inputgroup::factory($element);
    }

    public static function modifyEntityConnect($element)
    {
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
        $element['#attached']['libraray'][] = ['sbadmin2', 'sbadmin2.tooltip'];
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

    public static function modifyViewsDatePopup(&$element)
    {
        foreach (element_children($element) as $child) {
            $element_child = &$element[$child];
            // Element yang tidak kosong ditandai dengan property
            // `#processed = true`.
            if ($element_child['#processed']) {
                $element_child['#sbadmin2_transform'] = 'input_group';
                $element_child['#sbadmin2_description_icon'] = ($child == 'date') ? 'calendar' : 'clock-o';
                $element_child['#attributes']['autocomplete'] = 'off';
                // Copy property jika ada.
                if (!empty($element['#sbadmin2_class_id'])) {
                    $element_child['#sbadmin2_class_id'] = $element['#sbadmin2_class_id'];
                    $element_child['#sbadmin2_class_id_value'] = $element['#id'];
                }
                // Tidak perlu form element.
                $element_child['#sbadmin2_clean_wrapper'] = true;
            }
        }
        if (!empty($element['#title']) && $element['#title_display'] != 'invisible') {
            // Ambil informasi description pada date.
            $description = '';
            $description_icon = '';
            if (isset($element['date']['#description'])) {
                $description = $element['date']['#description'];
                $element['date']['#description'] = '';
                $description_icon = 'calendar';
            }
            elseif (isset($element['time']['#description'])) {
                $description = $element['time']['#description'];
                $element['time']['#description'] = '';
                $description_icon = 'clock-o';
            }
            $element = [ '_prefix_addon' => [
                '#type' => 'input_group_addon',
                '#title' => $element['#title'],
                '#weight' => -1,
            ]] + $element;
            if (!empty($description)) {
                $element['_prefix_addon'] += [
                    '#tooltip' => $description,
                    'icon' => [
                        '#type' => 'icon',
                        '#icon' => empty($description_icon) ? 'question-circle' : $description_icon,
                    ],
                ];
            }
            if (!empty($element['#sbadmin2_class_id'])) {
                $element['_prefix_addon']['#attributes']['class'][] = $element['#id'];
            }
        }
        // Clear wrapper.
        unset($element['#prefix']);
        unset($element['#suffix']);
        unset($element['#theme_wrappers']);
    }

    /**
     * Convert select to checkboxes or radios.
     */
    protected static function transformSelect(&$element)
    {
        // Clear theme_select.
        unset($element['#theme']);
        $is_multiple = !empty($element['#multiple']);
        // form_process_select() telah memberikan #attributes][name
        // dan ini auto digunakan oleh theme_chechkbox(), tetapi
        // belum tersedia oleh theme_radio().
        if ($is_multiple) {
            unset($element['#attributes']['multiple']);
        }
        else {
            $element['#attributes']['name'] = $element['#name'];
        }
        $element['#theme_wrappers'][] = $is_multiple ? 'checkboxes' : 'radios';
        $element = $is_multiple ? form_process_checkboxes($element) : form_process_radios($element);
        // Lakukan kembali apa yang dilakukan oleh #prerender checkboxes/radios.
        if ((isset($element['#title']) || isset($element['#description'])) === false) {
            sbadmin2_utils::remove_theme_wrappers('form_element', $element);
        }
        if ($is_multiple) {
            // Property #checked di proses oleh form_process_checkbox().
            // Kita sesuikan asalkan #checked tetap terbentuk.
            foreach (element_children($element) as $key) {
                $element[$key]['#checked'] = isset($element[$key]['#default_value']);
            }
        }
        else {
            // theme_radio membutuhkan #value, ambil dari cara property
            // #default_value dibuat oleh form_process_radios().
            foreach (element_children($element) as $key) {
                $element[$key]['#value'] = isset($element['#value']) ? $element['#value'] : FALSE;
            }
        }
    }

    protected static function modifySelect2(&$element, $settings = [])
    {
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

    /**
     *
     */
    protected static function modifyButtonDropdownInput(&$element)
    {
        // Hapus theme_select.
        unset($element['#theme']);
        // Bikin element button.
        $element['button']['#type'] = 'submit_button';
        $element['button']['#toggle'] = 'dropdown';
        $element['button']['#value'] = $element['#options'][$element['#value']];
        $element['button']['#value'] .= ' <span class="caret"></span>';
        // Copy from parent.
        $element['button']['#sbadmin2_size'] = isset($element['#sbadmin2_size']) ? $element['#sbadmin2_size'] : null;
        $element['button']['#attributes'] = isset($element['#attributes']) ? $element['#attributes'] : [];
        // Bikin element menu dropdown.
        $element['menu']['#type'] = 'dropdown_menu';
        $element['menu']['#options'] = $element['#options'];
        // Bikin element hidden.
        $element['input']['#type'] = 'hidden';
        $element['input']['#attributes']['id'] = $element['#id'];
        $element['input']['#name'] = $element['#name'];
        $element['input']['#value'] = $element['#value'];
        // Bungkus.
        sbadmin2_utils::remove_theme_wrappers('form_element', $element);
        if ((in_array('button_group', $element['#theme_wrappers']) || in_array('input_group_button', $element['#theme_wrappers'])) == false) {
            $element['#theme_wrappers'][] = 'button_group'; // default.
        }
        // Kasih javascript.
        $element['#attached']['library'][] = ['sbadmin2', 'sbadmin2.dropdown_menu'];
    }
}
