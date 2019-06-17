<?php

/**
 * Memodifikasi main menu sehingga hook theme dari property #theme_wrappers
 * dari sebelumnya adalah `menu_tree__main_menu` menjadi `menu_tree__main_menu__level_x`.
 * Cara ini digunakan untuk memberikan class nav.nav-second-level dan
 * nav.nav-third-level pada main menu.
*/
function _sbadmin2_helper_main_menu_modified(&$data) {
    ctools_include('utils', 'sbadmin2_helper');
    return _sbadmin2_helper_main_menu_modified_recursive($data['content']);
}

/**
 * Sub fungsi dari fungsi `_sbadmin2_helper_main_menu_modified`
 * untuk melakukan recursive sampai element terdalam.
 */
function _sbadmin2_helper_main_menu_modified_recursive(&$data, $level = 1) {
    _sbadmin2_helper_utils_replace_theme_wrappers('menu_tree__main_menu', 'menu_tree__main_menu__level_' . $level, $data);
    $childrens = element_children($data);
    foreach ($childrens as $children) {
        if ($data[$children]['#below']) {
            _sbadmin2_helper_main_menu_modified_recursive($data[$children]['#below'], ++$level);
            $level--; // Reset.
        }
    }
}
