<?php

// Theme Wrapper.

/**
 * Menyediakan variables $attributes dan $element untuk template.
 */
function _template_preprocess_wrapper_common(&$variables, $class = null) {
    $class === null or $variables['element']['#attributes']['class'][] = $class;
    $variables['attributes'] = '';
    // Variable $attributes akan diisi oleh template_process()
    // melalui key attributes_array.
    $variables['attributes_array'] = isset($variables['element']['#attributes']) ? $variables['element']['#attributes'] : [];
    $variables['element'] = $variables['element']['#children'];
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function template_preprocess_input_group(&$variables) {
    _template_preprocess_wrapper_common($variables, 'input-group');
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function template_preprocess_input_group_button(&$variables) {
    _template_preprocess_wrapper_common($variables, 'input-group-btn');
}

/**
 * Implements template_preprocess_HOOK().
 *
 * @see template_preprocess()
 * @see template_process()
 */
function template_preprocess_input_group_addon(&$variables) {
    if (isset($variables['element']['#tooltip'])) {
        $variables['element']['#attributes']['data-toggle'] = 'tooltip';
        $tooltip = $variables['element']['#tooltip'];
        is_array($tooltip) or $tooltip = ['title' => $tooltip];
        empty($tooltip['title']) or $variables['element']['#attributes']['title'] = $tooltip['title'];
        empty($tooltip['placement']) or $variables['element']['#attributes']['data-placement'] = $tooltip['placement'];
    }
    _template_preprocess_wrapper_common($variables, 'input-group-addon');
}

/**
 * Implements template_preprocess_HOOK() for theme_sbadmin2_form_element().
 * @see: template_preprocess_menu_tree()
 */
function template_preprocess_form_element2(&$variables) {
    $variables['#element'] = $variables['element'];
    $variables['element'] = $variables['element']['#children'];
    $variables['description'] = isset($variables['#element']['#description']) ? $variables['#element']['#description'] : '';
}

function template_preprocess_submit3(&$variables) {
    $element = &$variables['element'];
    $element['#attributes']['type'] = 'submit';
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
    _template_preprocess_wrapper_common($variables);
}

/**
 *
 */
function theme_textfield2($variables) {
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
function theme_password2($variables) {
    $variables['element']['#attributes']['class'][] = 'form-control';
    if (isset($variables['element']['#title'])) {
        $variables['element']['#attributes']['placeholder'] = $variables['element']['#title'];
        $variables['element']['#title'] = '';
    }
    return theme_password($variables);
}

function theme_submit2($variables) {
    return isset($variables['element']['#value']) ? $variables['element']['#value'] : '';
}

function theme_icon($variables) {
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
