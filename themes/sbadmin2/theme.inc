<?php

// Preprocess Theme.

/**
 * Implements hook_preprocess_HOOK(). Preprocess theme `node_form`.
 */
function sbadmin2_preprocess_node_form(&$variables) {
    hide($variables['form']['actions']);
    hide($variables['form']['additional_settings']);
}

// Preprocess Theme Wrapper.

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function sbadmin2_preprocess_input_group(&$variables) {
    $element = &$variables['element'];
    if ($size = sbadmin2_utils::get_size($element)) {
        $element['#attributes']['class'][] = 'input-group-' . $size;
    }
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'input-group');
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function sbadmin2_preprocess_input_group_button(&$variables) {
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'input-group-btn');
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function sbadmin2_preprocess_dropdown_menu(&$variables) {
    $element = &$variables['element'];
    if (isset($element['#align']) && $element['#align'] == 'right') {
        // $element['#attributes']['class'][] = 'dropdown-menu-right';
    }
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'dropdown-menu');
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function sbadmin2_preprocess_list_group_item(&$variables) {
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'list-group-item');
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function sbadmin2_preprocess_input_group_addon(&$variables) {
    $element = &$variables['element'];
    if (isset($element['#tooltip'])) {
        $element['#attributes']['data-toggle'] = 'tooltip';
        $tooltip = $element['#tooltip'];
        is_array($tooltip) or $tooltip = ['title' => $tooltip];
        empty($tooltip['title']) or $element['#attributes']['title'] = $tooltip['title'];
        empty($tooltip['placement']) or $element['#attributes']['data-placement'] = $tooltip['placement'];
    }
    $element['#children'] = isset($element['#title']) ? $element['#title'] . ' ' . $element['#children'] : $element['#children'];
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'input-group-addon');
}

/**
 * Implements template_preprocess_HOOK() for theme_sbadmin2_form_element().
 * @see: template_preprocess_menu_tree()
 */
function sbadmin2_preprocess_form_element2(&$variables) {
    // return;
    $variables['#element'] = $variables['element'];
    $variables['element'] = $variables['element']['#children'];
    $variables['description'] = isset($variables['#element']['#description']) ? $variables['#element']['#description'] : '';
}

/**
 *
 */
function sbadmin2_preprocess_button_wrapper(&$variables) {
    $element = &$variables['element'];
    // Attribute `type` dapat diset sebagai button.
    $element['#attributes']['type'] = isset($element['#attributes']['type']) ? $element['#attributes']['type']: 'submit';
    element_set_attributes($element, array('id', 'name', 'value'));
    $element['#attributes']['class'][] = 'btn';
    $element['#attributes']['class'][] = 'btn-default';
    if (!empty($element['#attributes']['disabled'])) {
        $element['#attributes']['class'][] = 'form-button-disabled';
    }
    // Move value.
    $element['#children'] = $element['#attributes']['value'];
    unset($element['#attributes']['value']);
    // Path.
    if (isset($element['#path'])) {
        $element['#attributes']['onclick'] = "window.location.href='".$element['#path']."'";
        $element['#attributes']['type'] = 'button';
        unset($element['#attributes']['name']);
    }
    // Attract as toggle.
    if (!empty($element['#toggle'])) {
        $element['#attributes']['type'] = 'button';
        $element['#attributes']['data-toggle'] = $element['#toggle'];
        unset($element['#attributes']['name']);
        if ($element['#toggle'] == 'dropdown') {
            $element['#attributes']['class'][] = 'dropdown-toggle';
        }
    }
    if ($size = sbadmin2_utils::get_size($element)) {
        $element['#attributes']['class'][] = 'btn-' . $size;
    }
    sbadmin2_utils::preprocess_theme_wrapper($variables);
}

/**
 *
 */
function sbadmin2_preprocess_label_button(&$variables) {
    $element = &$variables['element'];
    unset($element['#attributes']['name']);
    $element['#attributes']['class'][] = 'btn';
    $element['#attributes']['class'][] = 'btn-' . sbadmin2_utils::get_colorize($element);
    if ($size = sbadmin2_utils::get_size($element)) {
        $element['#attributes']['class'][] = 'btn-' . $size;
    }

    switch ($element['#type']) {
        case 'checkbox':
            if ($element['#checked']) {
                $element['#attributes']['class'][] = 'active';
            }
            break;

        case 'radio': // @see theme_radio().
            if (isset($element['#return_value']) && $element['#value'] !== FALSE && $element['#value'] == $element['#return_value']) {
                $element['#attributes']['class'][] = 'active';
            }
            break;
    }
    $label = isset($element['#title']) ? $element['#title'] : $element['#name'];
    $element['#children'] .= $label;
    sbadmin2_utils::preprocess_theme_wrapper($variables);
}

function sbadmin2_preprocess_button_group(&$variables) {
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'btn-group');
}

function sbadmin2_preprocess_button_toolbar(&$variables) {
    sbadmin2_utils::preprocess_theme_wrapper($variables, 'btn-toolbar');
}

function sbadmin2_preprocess_button_group_input(&$variables) {
    $element = &$variables['element'];
    $element['#attributes']['class'][] = 'btn-group';
    $element['#attributes']['data-toggle'] = 'buttons';
    if (isset($element['#parents']) && form_get_error($element) !== NULL && !empty($element['#validated'])) {
        $element['#attributes']['class'][] = 'has-error';
    }
    sbadmin2_utils::preprocess_theme_wrapper($variables);
}

function sbadmin2_preprocess_button_group_addon(&$variables) {
    $element = &$variables['element'];
    $element['#attributes']['class'][] = 'btn';
    $element['#attributes']['class'][] = 'btn-group-addon';
    $element['#children'] = isset($element['#title']) ? $element['#title'] : $element['#children'];

    if ($size = sbadmin2_utils::get_size($element)) {
        $element['#attributes']['class'][] = 'btn-' . $size;
    }
    // $element['#attributes']['data-toggle'] = 'buttons';
    // @todo: attribute for
    // @todo: attribute size button
    // if (isset($element['#parents']) && form_get_error($element) !== NULL && !empty($element['#validated'])) {
        // $element['#attributes']['class'][] = 'has-error';
    // }
    sbadmin2_utils::preprocess_theme_wrapper($variables);
}

// Theme function.

/**
 *
 */
function sbadmin2_textfield2($variables) {
    $variables['element']['#attributes']['class'][] = 'form-control';
    if (isset($variables['element']['#title'])) {
        $variables['element']['#attributes']['placeholder'] = $variables['element']['#title'];
        $variables['element']['#title'] = '';
    }
    return theme_textfield($variables);
}

/**
 *
 */
function sbadmin2_password2($variables) {
    $variables['element']['#attributes']['class'][] = 'form-control';
    if (isset($variables['element']['#title'])) {
        $variables['element']['#attributes']['placeholder'] = $variables['element']['#title'];
        $variables['element']['#title'] = '';
    }
    return theme_password($variables);
}

function sbadmin2_submit2($variables) {
    return isset($variables['element']['#value']) ? $variables['element']['#value'] : '';
}

function sbadmin2_icon($variables) {
    $element = $variables['element'];
    $bundle = isset($element['#bundle']) ? $element['#bundle'] : 'fontawesome';
    $icon = isset($element['#icon']) ? $element['#icon'] : '';
    $attributes = [];
    switch ($bundle) {
        case 'glyphicon':
            $attributes['class'][] = 'icon';
            $attributes['class'][] = 'glyphicon';
            empty($element['#icon']) or $attributes['class'][] = 'glyphicon-' . $element['#icon'];
            break;

        case 'fontawesome':
            $attributes['class'][] = 'fa';
            $attributes['class'][] = 'fa-fw';
            empty($element['#icon']) or $attributes['class'][] = 'fa-' . $element['#icon'];
            break;

        default:
            // Do something.
            break;
    }
    return '<span aria-hidden="true"' . drupal_attributes($attributes) . '></span>';
}

function sbadmin2_menu_nolink($variables) {
    sbadmin2_utils::remove_drupal_class($variables['element']);
    $element = $variables['element'];
    $sub_menu = '';
    if (isset($element['#below'])) {
        $sub_menu = drupal_render($element['#below']);
    }
    $element['#localized_options']['external'] = true;
    $output = l($element['#title'], 'javascript:void(0)', $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function sbadmin2_dropdown_menu_item($variables) {
    $element = $variables['element'];
    $render = '';
    foreach ($element['#options'] as $key => $value) {
        if (is_array($value)) {
            $render .= '<li>'. drupal_render($value) .'</li>'."\n";
        }
        else {
            $render .= '<li><a href="#" data-value="'. check_plain($key) .'">'.check_plain($value).'</a></li>'."\n";
        }
    }
    return $render;
}
