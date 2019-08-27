<?php

include_once __DIR__ . '/includes/classes/sbadmin2.utils.inc';
include_once __DIR__ . '/includes/classes/sbadmin2.inputgroup.inc';
include_once __DIR__ . '/includes/classes/sbadmin2.menu.inc';
include_once __DIR__ . '/includes/sbadmin2.theme_override.inc';
include_once __DIR__ . '/includes/sbadmin2.preprocess.inc';
include_once __DIR__ . '/includes/sbadmin2.pre_render.inc';
include_once __DIR__ . '/includes/sbadmin2.form_alter.inc';
include_once __DIR__ . '/includes/sbadmin2.block_alter.inc';

/**
 * Clear any previously set element_info() static cache.
 *
 * If element_info() was invoked before the theme was fully initialized, this
 * can cause the theme's alter hook to not be invoked.
 *
 * @see https://www.drupal.org/node/2351731
 *
 * Credit: https://www.drupal.org/project/bootstrap.
 */
drupal_static_reset('element_info');

// Drupal Hook.

/**
 * Implements hook_theme().
 *
 * | Theme Hook         | Is Wrapper | Is Template | Element Type           |
 * |--------------------|------------|-------------|------------------------|
 * | input_group        | yes        | yes         |                        |
 * | input_group_button | yes        | yes         |                        |
 * | input_group_addon  | yes        | yes         |                        |
 * | menu_nolink        | -          | -           |                        |
 * | form_element2      | yes        | yes         | textfield2,  password2 |
 * | textfield2         | -          | -           | textfield2             |
 * | password2          | -          | -           | password2              |
 * | submit2            | -          | -           | submit2                |
 * | submit3            | yes        | yes         | submit2                |
 * | icon               | -          | -           | icon                   |
 * |                    |            |             |                        |
 */
function sbadmin2_theme($existing, $type, $theme, $path) {
    return [
        // Implements #theme = 'node_form'
        // @see: drupal_prepare_form() dan node_form().
        'node_form' => [
            'render element' => 'form',
            'template' => 'templates/node-form',
        ],
        'menu_nolink' => [
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
        ],
        'input_group' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
            'template' => 'templates/div-wrapper',
        ),
        'input_group_button' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
            'template' => 'templates/div-wrapper',
        ),
        'input_group_addon' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
            'template' => 'templates/span-wrapper',
       ),
        'form_element2' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
            'template' => 'templates/form-element-wrapper',
        ),
        'textfield2' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
        ),
        'password2' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
        ),
        'submit2' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
        ),
        'submit3' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
            'template' => 'templates/button-wrapper',
        ),
        'icon' => array(
            'render element' => 'element',
            'file' => 'includes/sbadmin2.theme.inc',
        ),
    ];
}

/**
 * Implements hook_library().
 */
function sbadmin2_library() {
    $path = drupal_get_path('theme', 'sbadmin2');
    $libraries['sbadmin2.core'] = [
        'title' => 'SBAdmin2 Core',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/sbadmin2.js' => [
                'group' => JS_THEME,
            ],
        ],
    ];
    $libraries['sbadmin2.managed_file'] = [
        'title' => 'SBAdmin2 Managed file',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/managed-file.js' => [
                'group' => JS_THEME,
            ],
        ],
        'css' => [
            $path.'/css/managed-file.css' => [],
        ],
    ];
    $libraries['sbadmin2.tooltip'] = [
        'title' => 'SBAdmin2 Tooltip',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/tooltip.js' => [
                'group' => JS_THEME,
            ],
        ],
    ];
    $libraries['sbadmin2.select2'] = [
        'title' => 'SBAdmin2 Select2',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/vendor/select2/4.0.5/js/select2.min.js' => ['group' => JS_LIBRARY],
            $path.'/js/select2.js' => ['group' => JS_DEFAULT],
        ],
        'css' => [
            $path.'/vendor/select2/4.0.5/css/select2.min.css' => ['group' => CSS_DEFAULT],
            $path.'/vendor/select2-bootstrap-theme/0.1.0-beta.10/select2-bootstrap.min.css' => ['group' => CSS_THEME],
        ],
    ];
    $libraries['sbadmin2.datatables'] = [
        'title' => 'SBAdmin2 Datatables',
        'website' => 'https://datatables.net/',
        'version' => '1.10.19',
        'js' => [
            $path.'/vendor/datatables/1.10.19/js/jquery.dataTables.min.js' => ['group' => JS_LIBRARY],
            $path.'/vendor/datatables/1.10.19/js/dataTables.bootstrap.min.js' => ['group' => JS_LIBRARY],
            $path.'/js/datatables.js' => ['group' => JS_DEFAULT],
        ],
        'css' => [
            $path.'/vendor/datatables/1.10.19/css/dataTables.bootstrap.min.css' => ['group' => CSS_DEFAULT],
        ],
    ];
    $libraries['sbadmin2.datatables.ajax'] = [
        'title' => 'SBAdmin2 Datatables Ajax',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/datatables-ajax.js' => ['group' => JS_DEFAULT],
        ],
        'dependencies' => [
            ['system', 'drupal.ajax'],
        ],
    ];
    $libraries['sbadmin2.timeago'] = [
        'title' => 'SBAdmin2 Timeago',
        'website' => 'https://timeago.org/',
        'version' => '3.0.2',
        'js' => [
            $path.'/vendor/timeago.js/3.0.2/timeago.js' => ['group' => JS_LIBRARY],
            $path.'/js/timeago.js' => ['group' => JS_DEFAULT],
        ],
        'css' => [
            $path.'/vendor/datatables/1.10.19/css/dataTables.bootstrap.min.css' => ['group' => CSS_DEFAULT],
        ],
    ];
    return $libraries;
}

// Drupal Hook Alter.

/**
 * Implements of hook_element_info_alter.
 */
function sbadmin2_element_info_alter(&$types) {
    $form_elements = [
        'form', 'textarea', 'textfield', 'password', 'select', 'submit',
        'checkbox', 'button', 'file', 'managed_file', 'date_combo'
    ];
    foreach ($form_elements as $element) {
        // Give toggle to allow custom module ignore sbadmin2 via
        // hook_form_alter().
        $types[$element]['#sbadmin2'] = true;
        $types[$element]['#process'][] = 'sbadmin2_element_process';
        $types[$element]['#pre_render'][] = 'sbadmin2_element_pre_render';
    }
    $reference = system_element_info();
    // Type: `textfield2`.
    $types['textfield2'] = $reference['textfield'];
    $types['textfield2']['#theme'] = 'textfield2';
    $types['textfield2']['#theme_wrappers'] = ['form_element2'];
    // Type: `textfield3`.
    $types['textfield3'] = $reference['textfield'];
    $types['textfield3']['#theme_wrappers'] = [];

    $types['password2'] = $reference['password'];
    $types['password2']['#theme'] = 'password2';
    $types['password2']['#theme_wrappers'] = ['form_element2'];

    $types['submit2'] = $reference['submit'];
    $types['submit2']['#theme'] = 'submit2';
    $types['submit2']['#theme_wrappers'] = ['submit3'];
    $types['submit3'] = $reference['submit'];
    $types['submit3']['#theme_wrappers'] = ['submit3'];
    $types['icon'] = [
        '#theme' => 'icon',
        '#bundle' => 'fontawesome',
    ];
}

/**
 * Implements hook_js_alter().
 */
function sbadmin2_js_alter(&$javascript) {
    // Javascript dibawah ini harus sebagai grup library.
    $path = drupal_get_path('theme', 'sbadmin2');
    $javascript[$path . '/vendor/twitter-bootstrap/3.3.7/js/bootstrap.min.js']['group'] = JS_LIBRARY;
    $javascript[$path . '/vendor/metisMenu/1.1.3/metisMenu.min.js']['group'] = JS_LIBRARY;
    // Pindahkan seluruh javascript ke footer.
    foreach ($javascript as $key => &$value) {
        $value['scope'] = 'footer';
    }
}

/**
 * Implements hook_css_alter().
 */
function sbadmin2_css_alter(&$css) {
    // CSS dibawah ini harus sebagai grup system.
    $path = drupal_get_path('theme', 'sbadmin2');
    $css[$path . '/vendor/twitter-bootstrap/3.3.7/css/bootstrap.min.css']['group'] = CSS_SYSTEM;
    $css[$path . '/vendor/font-awesome/4.7.0/css/font-awesome.min.css']['group'] = CSS_SYSTEM;
    $css[$path . '/vendor/metisMenu/1.1.3/metisMenu.min.css']['group'] = CSS_SYSTEM;

    // Replace CSS tertentu karena sulit dioverride.
    $system = drupal_get_path('module', 'system') . '/system.theme.css';
    if (isset($css[$system])) {
        $system_takeover = $path . '/css/takeover/system.theme.css';
        $css[$system_takeover] = $css[$system];
        unset($css[$system]);
    }
    if (module_exists('date_api')) {
        $date = drupal_get_path('module', 'date_api') . '/date.css';
        if (isset($css[$date])) {
            $date_takeover = $path . '/css/takeover/date.css';
            $css[$date_takeover] = $css[$date];
            unset($css[$date]);
        }
    }
}

// Callback function.

/**
 * Callback of property #process in element.
 */
function sbadmin2_element_process($element, &$form_state, $form) {
    // Oper informasi form horizontal dari form ke element sehingga
    // nanti bisa dioleh oleh theme_form_element.

    if (isset($form['#sbadmin2_form_horizontal']) && $form['#sbadmin2_form_horizontal'] === true) {
        $element['#sbadmin2_form_horizontal'] = true;
    }

    // Add support to select2. Ketika
    if (!empty($element['#sbadmin2_select2'])) {
        // Jika trigger form error, maka value dari form_state perlu kita
        // kembalikan ke element.
        $default_value = drupal_array_get_nested_value($form_state['values'], $element['#parents']);
        empty($default_value) or $element['#sbadmin2_select2_default_value'] = $default_value;

        if (is_numeric($default_value)) {
            // Ini berarti hasil dari kembalian dari halaman edit entityconnect
            // karena module telah mengubahnya menjadi numeric.
            empty($element['#value']) or $element['#sbadmin2_select2_default_value'] = $element['#value'];
        }
    }

    // Attach library kayaknya disini deh.
    if (isset($element['#type']) && $element['#type'] == 'managed_file' && !empty($element['#sbadmin2'])) {
        $element['#attached']['library'][] = ['sbadmin2', 'sbadmin2.managed_file'];
    }
    return $element;
}

/**
 * Callback of property #pre_render in element.
 */
function sbadmin2_element_pre_render($element) {
    if (isset($element['#sbadmin2']) && $element['#sbadmin2'] === true) {
        return _sbadmin2_element_pre_render($element);
    }
    return $element;
}

/**
 * Callback of property #pre_render in element.
 */
function sbadmin2_element_pre_render_entityconnect($element) {
    if (isset($element['#sbadmin2']) && $element['#sbadmin2'] === true) {
        return _sbadmin2_element_pre_render_entityconnect($element);
    }
    return $element;
}
