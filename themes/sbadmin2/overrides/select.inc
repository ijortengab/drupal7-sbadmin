<?php

/**
 * Implements of hook_preprocess_HOOK().
 */
function sbadmin2_preprocess_select(&$variables) {
    $element = &$variables['element'];
    if ($size = sbadmin2_utils::get_size($element, 'input')) {
        $element['#attributes']['class'][] = 'input-' . $size;
    }
}
