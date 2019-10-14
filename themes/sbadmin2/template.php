<?php

spl_autoload_register(function ($class_name) {
    if (file_exists(__DIR__ . '/src/' . $class_name . '.inc')) {
        include __DIR__ . '/src/' . $class_name . '.inc';
    }
});

include_once __DIR__ . '/overrides/block.inc';
include_once __DIR__ . '/overrides/button.inc';
include_once __DIR__ . '/overrides/form_element.inc';
include_once __DIR__ . '/overrides/form_element_label.inc';
include_once __DIR__ . '/overrides/html.inc';
include_once __DIR__ . '/overrides/link.inc';
include_once __DIR__ . '/overrides/menu_link.inc';
include_once __DIR__ . '/overrides/menu_local_task.inc';
include_once __DIR__ . '/overrides/menu_local_tasks.inc';
include_once __DIR__ . '/overrides/page.inc';
include_once __DIR__ . '/overrides/pager.inc';
include_once __DIR__ . '/overrides/select.inc';
include_once __DIR__ . '/overrides/table.inc';
include_once __DIR__ . '/overrides/textfield.inc';
include_once __DIR__ . '/overrides/views_exposed_form.inc';
include_once __DIR__ . '/overrides/views_view.inc';
include_once __DIR__ . '/overrides/views_view_table.inc';
include_once __DIR__ . '/alter/form.inc';
include_once __DIR__ . '/alter/block.inc';

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
 * |                    |            |             | checkbox*              |
 * | textfield2         | -          | -           | textfield2             |
 * | password2          | -          | -           | password2              |
 * | submit2            | -          | -           | submit2                |
 * | button_wrapper     | yes        | yes         | submit2                |
 * | icon               | -          | -           | icon                   |
 * |                    |            |             |                        |
 */
function sbadmin2_theme($existing, $type, $theme, $path) {
    $base = [
        'render element' => 'element',
        'file' => 'theme.inc',
    ];
    return [
        // Implements #theme = 'node_form'
        // @see: drupal_prepare_form() dan node_form().
        'node_form' => [
            'render element' => 'form',
            'template' => 'templates/node-form',
            'file' => 'theme.inc',
        ],
        'menu_nolink' => $base,
        'input_group' => $base + ['template' => 'templates/div-wrapper'],
        'input_group_button' => $base + ['template' => 'templates/div-wrapper'],
        'input_group_addon' => $base + ['template' => 'templates/span-wrapper'],
        'button_group' => $base + ['template' => 'templates/div-wrapper'],
        'button_toolbar' => $base + ['template' => 'templates/div-wrapper'],
        'button_group_input' => $base + ['template' => 'templates/div-wrapper'],
        'list_group' => $base + ['template' => 'templates/ul-wrapper'],
        'list_group_item' => $base + ['template' => 'templates/div-wrapper'],
        'button_group_addon' => $base + ['template' => 'templates/label-wrapper'],
        // `form_element2` digunakan untuk pengganti form_element karena
        // tidak perlu label.
        'form_element2' => $base + ['template' => 'templates/form-element-wrapper'],
        'textfield2' => $base,
        'password2' => $base,
        'submit2' => $base,
        // Karena hook `button` sudah dimiliki oleh Drupal core.
        'button_wrapper' => $base + ['template' => 'templates/button-wrapper'],
        'icon' => $base,
        // Khusus input checkbox, checkboxes, radio, dan radios yang memiliki
        // property #sbadmin_button = true.
        'label_button' => $base + ['template' => 'templates/label-wrapper'],
        'dropdown_menu' => $base + ['template' => 'templates/ul-wrapper'],
        'dropdown_menu_item' => $base,
    ];
}

/**
 * Implements hook_library().
 */
function sbadmin2_library() {
    $path = drupal_get_path('theme', 'sbadmin2');
    $libraries['sbadmin2.managed_file'] = [
        'title' => 'SBAdmin2 Managed file',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/managed-file.js' => [
                'group' => JS_DEFAULT,
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
                'group' => JS_DEFAULT,
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
    ];
    $libraries['sbadmin2.dropdown_menu'] = [
        'title' => 'SBAdmin2 Dropdown Menu',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/dropdown_menu.js' => ['group' => JS_DEFAULT],
        ],
    ];
    $libraries['sbadmin2.icon'] = [
        'title' => 'SBAdmin2 Icon Theme',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/icon.js' => ['group' => JS_DEFAULT],
        ],
    ];
    $libraries['sbadmin2.views_toggle_operator'] = [
        'title' => 'SBAdmin2 Views Toggle Operator',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/views-toggle-operator.js' => ['group' => JS_DEFAULT],
        ],
        'dependencies' => [
            ['sbadmin2', 'sbadmin2.icon'],
        ],
    ];
    $libraries['sbadmin2.views_multiple_select'] = [
        'title' => 'SBAdmin2 Views Multiple Select',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/views-multiple-select.js' => ['group' => JS_DEFAULT],
        ],
        'dependencies' => [
            ['sbadmin2', 'sbadmin2.icon'],
        ],
    ];
    $libraries['sbadmin2.dependent'] = [
        'title' => 'SBAdmin2 Dependent by Class',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/takeover/dependent.js' => ['group' => JS_DEFAULT],
        ],
    ];
    $libraries['sbadmin2.views_collapsible_button'] = [
        'title' => 'SBAdmin2 Views Collapsible Button',
        'website' => 'https://github.com/ijortengab/drupal7-sbadmin2',
        'version' => '1.0.0',
        'js' => [
            $path.'/js/views-collapsible-button.js' => [
                'group' => JS_DEFAULT,
            ],
        ],
    ];
    return $libraries;
}

// Drupal Hook Alter.

/**
 * Implements of hook_element_info_alter.
 */
function sbadmin2_element_info_alter(&$types) {
    foreach (array_keys($types) as $type) {
        $types[$type]['#sbadmin2'] = true;
        $types[$type]['#process'][] = 'sbadmin2_element_process';
        $types[$type]['#pre_render'][] = 'sbadmin2_element_pre_render';
    }
    $reference = system_element_info();
    // @todo: textfield* dan password* diganti sebagai property saja.
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

    $types['submit_button'] = $reference['submit'];
    $types['submit_button']['#theme_wrappers'] = ['button_wrapper'];
    $types['icon'] = [
        '#theme' => 'icon',
        '#bundle' => 'fontawesome',
    ];
    $types['input_group_addon'] = [
        '#theme_wrappers' => [
            'input_group_addon',
        ],
    ];
    $types['button_group_addon'] = [
        '#theme_wrappers' => [
            'button_group_addon',
        ],
    ];
    $types['dropdown_menu'] = [
        '#theme' => 'dropdown_menu_item',
        '#options' => [],
        '#theme_wrappers' => [
            'dropdown_menu',
        ],
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

    // Ambil alih dependent.js. Ganti dengan yang dimiliki oleh sbadmin2 yang telah
    // mendukung selector by class dan selector self instead of parent.
    $ctools_dependent_path = (module_exists('ctools')) ? ctools_attach_js('dependent') : null;
    $sbadmin2_dependent_path = $path . '/js/takeover/dependent.js';
    if (isset($javascript[$ctools_dependent_path]) && isset($javascript[$sbadmin2_dependent_path])) {
        unset($javascript[$ctools_dependent_path]);
    }

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
        $css[$system_takeover]['data'] = $system_takeover;
        unset($css[$system]);
    }
    if (module_exists('date_api')) {
        $date = drupal_get_path('module', 'date_api') . '/date.css';
        if (isset($css[$date])) {
            $date_takeover = $path . '/css/takeover/date.css';
            $css[$date_takeover] = $css[$date];
            $css[$date_takeover]['data'] = $date_takeover;
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
    // nanti bisa diolah oleh sbadmin2_form_element.
    if (isset($form['#sbadmin2_form_horizontal']) && $form['#sbadmin2_form_horizontal'] === true) {
        $element['#sbadmin2_form_horizontal'] = true;
    }
    // Add support to dependency by class instead of by id.
    if (isset($element['#dependency']) && !empty($element['#sbadmin2_dependency'])) {
       sbadmin2_utils::replace_pre_render('ctools_dependent_pre_render', 'sbadmin2_dependent_pre_render', $element);
    }
    return $element;
}

/**
 * Callback of property #pre_render in element.
 */
function sbadmin2_element_pre_render($element) {
    // Property #sbadmin2 sebagi toggle on/off. Untuk mematikan fungsi ini
    // cukup dengan memberikan attribute `#sbadmin = false` pada
    // hook_form_alter().
    if (empty($element['#sbadmin2'])) {
        return $element;
    }
    // Property before modify.
    if (!empty($element['#sbadmin2_class_id'])) {
        $element['#attributes']['class'][] = isset($element['#sbadmin2_class_id_value']) ? $element['#sbadmin2_class_id_value'] : $element['#id'];
    }
    $type = isset($element['#type']) ? $element['#type'] : null;
    switch ($type) {
        case 'form':
            if (isset($element['#sbadmin_input_group']) && $element['#sbadmin_input_group']) {
                $element = sbadmin2_inputgroup::factory($element);
            }
            break;

        case 'textfield':
            sbadmin2_prerender::modifyTextfield($element);
            break;

        case 'password':
        case 'textarea':
        case 'file':
            sbadmin2_prerender::addFormControl($element);
            break;

        case 'submit':
        case 'button':
            sbadmin2_prerender::addButton($element);
            break;

        case 'select':
            sbadmin2_prerender::modifySelect($element);
            break;

        case 'checkbox':
        case 'radio':
            if (!empty($element['#sbadmin2_button'])) {
                sbadmin2_utils::remove_theme_wrappers('form_element', $element);
                array_unshift($element['#theme_wrappers'], 'label_button', 'button_group_input', 'form_element2');
            }
            break;

        case 'checkboxes':
        case 'radios':
            if (!empty($element['#sbadmin2_button'])) {
                sbadmin2_prerender::modifyButtonGroupInput($element);
            }
            break;

        case 'managed_file':
            sbadmin2_prerender::modifyManagedFile($element);
            break;

        default:
            sbadmin2_prerender::modifyOthers($element);
            break;
    }

    // Property after modify.
    if (!empty($element['#sbadmin2_clean_wrapper'])) {
        unset($element['#theme_wrappers']);
        unset($element['#prefix']);
        unset($element['#suffix']);
    }
    return $element;
}

/**
 * Prerender specific yang terdapat property khusus yang tidak perlu
 * di-handle oleh sbadmin2_element_pre_render().
 */
function sbadmin2_element_pre_render_spesific($element) {
    // Property #sbadmin2 sebagi toggle on/off. Untuk mematikan fungsi ini
    // cukup dengan memberikan attribute `#sbadmin = false` pada
    // hook_form_alter().
    if (empty($element['#sbadmin2'])) {
        return $element;
    }
    // Property ini diset oleh module `sbadmin2_helper` ketika mendetect
    // adanya module `entityconnect`.
    if (!empty($element['#sbadmin2_entityconnect'])) {
        $element = sbadmin2_prerender::modifyEntityConnect($element);
    }
    // Property ini diset oleh `sbadmin2_form_views_exposed_form_alter()`.
    if (!empty($element['#sbadmin2_views_date_popup'])) {
        sbadmin2_prerender::modifyViewsDatePopup($element);
    }
    return $element;
}

/**
 * Implements of hook_date_popup_process_alter().
 */
function sbadmin2_date_popup_process_alter(&$element, $form_state, $context) {
    // Pada beberapa kasus, function sbadmin2_element_info_alter() tidak mampu
    // memasukkan element property yang sudah exists misalnya `#process` dan
    // `#pre_render`. Salahsatunya terjadi pada element info yang disediakan
    // oleh module `date_popup`. Oleh karena itu kita gunakan hook ini untuk
    // menginject value pada property `#pre_render`.
    $element['#pre_render'][] = 'sbadmin2_element_pre_render_spesific';
    if (isset($element['#dependency']) && !empty($element['#sbadmin2_dependency'])) {
       sbadmin2_utils::replace_pre_render('ctools_dependent_pre_render', 'sbadmin2_dependent_pre_render', $element);
    }
}

/**
 * Extend function ctools_dependent_pre_render().
 *
 * Add support for class selector and self instead of parent.
 */
function sbadmin2_dependent_pre_render($element) {
  // Preprocess only items with #dependency set.
  if (isset($element['#dependency'])) {
    if (!isset($element['#dependency_count'])) {
      $element['#dependency_count'] = 1;
    }
    if (!isset($element['#dependency_type'])) {
      $element['#dependency_type'] = 'hide';
    }

    $js = array(
      'values' => $element['#dependency'],
      'num' => $element['#dependency_count'],
      'type' => $element['#dependency_type'],
      'class' => isset($element['#sbadmin2_dependency_class']) ? $element['#sbadmin2_dependency_class'] : null,
      'self' => isset($element['#sbadmin2_dependency_self']) ? $element['#sbadmin2_dependency_self'] : null,
    );

    // Add a additional wrapper id around fieldsets, textareas to support depedency on it.
    if (in_array($element['#type'], array('textarea', 'fieldset', 'text_format'))) {
      $element['#theme_wrappers'][] = 'container';
      $element['#attributes']['id'] = $element['#id'] . '-wrapper';
    }

    // Text formats need to unset the dependency on the textarea
    // or it gets applied twice.
    if ($element['#type'] == 'text_format') {
      unset($element['value']['#dependency']);
    }

    $element['#attached']['js'][] = ctools_attach_js('dependent');
    $options['CTools']['dependent'][$element['#id']] = $js;
    $element['#attached']['js'][] = array('type' => 'setting', 'data' => $options);
  }
  return $element;
}
