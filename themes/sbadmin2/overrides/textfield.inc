<?php

/**
 * Implements of hook_preprocess_HOOK().
 */
function sbadmin2_preprocess_textfield(&$variables) {
    $element = &$variables['element'];
    if ($size = sbadmin2_utils::get_size($element, 'input')) {
        $element['#attributes']['class'][] = 'input-' . $size;
    }
}

/**
 * Override theme_textfield().
 */
function sbadmin2_textfield($variables) {
    $element = $variables['element'];
    $element['#attributes']['type'] = 'text';
    element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
    _form_set_class($element, array('form-text'));
    $extra = '';
    if ($element['#autocomplete_path'] && !empty($element['#autocomplete_input'])) {
        drupal_add_library('system', 'drupal.autocomplete');
        $element['#attributes']['class'][] = 'form-autocomplete';
        $attributes = array();
        $attributes['type'] = 'hidden';
        $attributes['id'] = $element['#autocomplete_input']['#id'];
        $attributes['value'] = $element['#autocomplete_input']['#url_value'];
        $attributes['disabled'] = 'disabled';
        $attributes['class'][] = 'autocomplete';
        $extra = '<input' . drupal_attributes($attributes) . ' />';
    }
    $output = '<input' . drupal_attributes($element['#attributes']) . ' />';
    return $output . $extra;
}
