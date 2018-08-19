<?php
    
/**
 * 
 */
function theme_sbadmin2_textfield3($variables) {
    $variables['element']['#attributes']['class'][] = 'form-control';
    if (isset($variables['element']['#title'])) {
        $variables['element']['#attributes']['placeholder'] = $variables['element']['#title'];
    }
    return theme_textfield($variables);
}

/**
 *
 */
function theme_sbadmin2_password3($variables) {
    $variables['element']['#attributes']['class'][] = 'form-control';
    if (isset($variables['element']['#title'])) {
        $variables['element']['#attributes']['placeholder'] = $variables['element']['#title'];
    }
    return theme_password($variables);
}

function theme_sbadmin2_submit3($variables) {
    $variables['element']['#attributes']['class'] = array('btn', 'btn-lg', 'btn-success', 'btn-block');
    return theme_button($variables);
}

/**
 * Implements template_preprocess_HOOK() for theme_sbadmin2_form_element().
 * @see: template_preprocess_menu_tree()
 */
function template_preprocess_sbadmin2_form_element(&$variables) {
    $variables['#element'] = $variables['element'];
    $variables['element'] = $variables['element']['#children'];
}

