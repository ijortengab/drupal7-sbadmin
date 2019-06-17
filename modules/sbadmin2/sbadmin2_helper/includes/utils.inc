<?php




function _sbadmin2_helper_utils_erase_theme_wrappers($which, &$element) {
    if (isset($element['#theme_wrappers']) && in_array($which, $element['#theme_wrappers'])) {
        $key = array_search($which, $element['#theme_wrappers']);
        unset($element['#theme_wrappers'][$key]);
    }
}

function _sbadmin2_helper_utils_replace_theme_wrappers($find, $replace, &$element) {

    if (isset($element['#theme_wrappers']) && in_array($find, $element['#theme_wrappers'])) {
        $key = array_search($find, $element['#theme_wrappers']);
        $element['#theme_wrappers'][$key] = $replace;
    }
}
