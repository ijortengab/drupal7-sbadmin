<?php

class InputGroup
{
    protected $element;

    protected $is_valid = [
        'has_form_control' => false,
        'has_other' => false,
    ];

    protected $current_bag_type;

    protected $bag = [];

    protected $x = 0;

    public static function factory($element)
    {
        return (new static($element))->process()->getElement();
    }

    public function __construct($element) {
        $this->element = $element;
    }

    /**
     *
     */
    public static function arrayKeyFirst($array)
    {
        foreach ($array as $key => $value) { return $key; }
    }

    public function process()
    {
        $element = $this->element;
        foreach (element_children($this->element, true) as $child_name) {
            $this->processChildren($child_name, $this->element[$child_name]);
        }
        $this->populatePseudoElement();
        return $this;
    }

    /**
     *
     */
    public function getElement()
    {
        return $this->element;
    }

    /**
     *
     */
    protected function processChildren($name, $element)
    {
        if (isset($element['#sbadmin2']) && $element['#sbadmin2'] === false) {
            return;
        }
        if (isset($element['#access']) && $element['#access'] === false) {
            return;
        }
        $type = isset($element['#type']) ? $element['#type'] : (isset($element['#theme']) ? $element['#theme'] : null);
        switch ($type) {
            case 'file':
            case 'textfield':
            case 'textfield2':
            case 'textfield3':
                $this->addToBag('form_control', $name);
                break;

            case 'submit':
            case 'submit2':
            case 'submit3':
            case 'button':
            case 'link':
            case 'actions':
                $this->addToBag('button', $name);
                break;

            case 'icon':
                $this->addToBag('addon', $name);
                break;

        }
        // return $this;
    }

    /**
     *
     */
    protected function addToBag($type, $element_name)
    {
        if (null === $this->current_bag_type) {
            $this->current_bag_type = $type;
        }
        elseif ($this->current_bag_type != $type) {
            $this->current_bag_type = $type;
            $this->x++;
        }
        $this->bag[$this->x][$this->current_bag_type][] = $element_name;
        switch ($type) {
            case 'button':
            case 'addon':
                $this->is_valid['has_other'] = true;
                break;

            case 'form_control':
                $this->is_valid['has_form_control'] = true;
                break;
        }
    }


    /**
     *
     */
    protected function populatePseudoElement()
    {
        // Minimal harus ada satu form control dan salah satu dari button
        // atau addon.
        if (in_array(false, $this->is_valid)) {
            return;
        }
        $this->element['element_group'] = [
            '#theme_wrappers' => ['input_group'],
        ];
        foreach ($this->bag as $i => $group) {
            $key = $this->arrayKeyFirst($group);
            switch ($key) {
                case 'button':
                    $this->element['element_group'][$i] = ['#theme_wrappers' => ['input_group_button']];
                case 'form_control':
                    while($element_name = array_shift($group[$key])){
                        // hapus
                        _sbadmin2_helper_utils_erase_theme_wrappers('form_element', $this->element[$element_name]);
                        _sbadmin2_helper_utils_erase_theme_wrappers('container', $this->element[$element_name]);
                        $this->element['element_group'][$i][$element_name] = $this->element[$element_name];
                        $this->element[$element_name]['#printed'] = true;
                    }
                    break;

                case 'addon':
                    while($element_name = array_shift($group[$key])){
                        $this->element['element_group'][$i][$element_name] = $this->element[$element_name];
                        $this->element['element_group'][$i][$element_name]['#theme_wrappers'][] = 'input_group_addon';
                        $this->element[$element_name]['#printed'] = true;
                    }
                    break;
            }
        }

    }


}


/**
 * Melakukan eksekusi pre_render terhadap element yang telah memiliki
 * attribute #sbadmin = true.
 */
function _sbadmin2_helper_pre_render($element) {

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
            $element = _sbadmin2_helper_input_group_factory($element);
            break;
    }

    // Melakukan modifikasi terkait managed_file
    switch ($element['#type']) {
        case 'managed_file':
            $element = _sbadmin2_helper_managed_file_factory($element);
            break;
    }

    // Otomatis menggunakan select2 jika options > 15.
    switch ($element['#type']) {
        case 'select':
            if (count($element['#options']) > 15) {
                _sbadmin2_helper_attach_select2_library($element);
            }
            break;
    }

    // Melakukan modifikasi terkait date time.
    switch ($element['#type']) {
        case 'date_combo':
            ctools_include('utils', 'sbadmin2_helper');
            // Kasus jika hanya field date yang ada.
            // todo, test pada kasus lain.
            _sbadmin2_helper_utils_replace_theme_wrappers('date_form_element', 'form_element', $element);
            _sbadmin2_helper_utils_erase_theme_wrappers('date_popup', $element['value']);
            _sbadmin2_helper_utils_erase_theme_wrappers('form_element', $element['value']['date']);
            $description = $element['value']['date']['#description'];
            $element['value']['#sorted'] = false;
            $element['value']['sbadmin2_info_sign'] = [
                '#type' => 'icon',
                '#icon' => 'question-circle',
                '#weight' => -1,
                '#tooltip' => ['title' => $description, 'placement' => 'auto left'],
            ];
            $element['value'] = InputGroup::factory($element['value']);


            break;
    }

    // Melakukan
    if (!empty($element['#sbadmin2_select2']) && !empty($element['#autocomplete_path'])) {
        ctools_include('utils', 'sbadmin2_helper');
        _sbadmin2_helper_utils_erase_theme_wrappers('form_element', $element);
        $id = $element['#id'];
        // Convert
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
        _sbadmin2_helper_attach_select2_library($element, $settings);
        // $element['#js_callback'] = ['sbadmin2_helper' => 'entityreference_autocomplete_single'];
    }



    return $element;
}

function _sbadmin2_helper_input_group_factory($element) {
    ctools_include('utils', 'sbadmin2_helper');
    if (!isset($element['#sbadmin_input_group'])) {
        return $element;
    }
    return InputGroup::factory($element);
    foreach ($element['#sbadmin_input_group'] as $new_element_container => $childs) {
        $element[$new_element_container] = [
            '#theme_wrappers' => ['input_group'],
            'button_group' => [
                '#theme_wrappers' => ['input_group_button'],
                '#weight' => 10,
            ],
        ];
        foreach ($childs as $child) {
            switch ($element[$child]['#type']) {
                case 'actions':
                    $element[$new_element_container]['button_group'][$child] = $element[$child];
                    _sbadmin2_helper_utils_erase_theme_wrappers('container', $element[$new_element_container]['button_group'][$child]);
                    break;

                // case '':
                    // Do something.
                    // break;

                default:
                    $element[$new_element_container][$child] = $element[$child];
                    _sbadmin2_helper_utils_erase_theme_wrappers('form_element', $element[$new_element_container][$child]);
                    break;
            }
            // todo. perlu recursive terutama untuk action > submit
            // array_unshift($element[$new_element_container][$child]['#array_parents'], $new_element_container);
            $element[$child]['#printed'] = true;

            // $element[$child]['#access'] = false;
        }
    }

    return $element;
}

function _sbadmin2_helper_input_group_factory_auto($element) {
    $a = var_export($element);
    echo $a;
    $input_group = new InputGroup($element);
    $input_group->process();
    return $element;

}

function _sbadmin2_helper_managed_file_factory($element) {
    ctools_include('utils', 'sbadmin2_helper');
    $element['#attached']['library'][] = ['sbadmin2_helper', 'sbadmin2.managed_file'];
    $element['#attached']['library'][] = ['sbadmin2_helper', 'sbadmin2.tooltip'];

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
    return InputGroup::factory($element);
}

function _sbadmin2_helper_attach_select2_library(&$element, $settings = []) {
    $id = $element['#id'];
    $element['#attributes']['class'][] = 'sbadmin2-select2';
    $element['#attached']['js'][] = [
        'type' => 'file',
        'data' => drupal_get_path('module', 'sbadmin2_helper').'/js/select2.js',
        'group' => JS_THEME,
    ];
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

function _sbadmin2_helper_entityconnect_pre_render($element) {
    // Jika ada element tambahan add_entityconnect atau edit_entityconnect.
    $is_exist = false; $is_exist_add = false; $is_exist_edit = false;
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
    ctools_include('utils', 'sbadmin2_helper');
    _sbadmin2_helper_utils_erase_theme_wrappers('form_element', $element['target_id']);
    // Tambah #theme_wrapper "form_element" pada element ini.
    isset($element['#theme_wrappers']) or $element['#theme_wrappers'] = array();
    array_unshift($element['#theme_wrappers'], 'form_element');
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
    return InputGroup::factory($element);
}
