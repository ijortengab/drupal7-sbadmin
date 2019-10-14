<?php

/**
 * Implements of hook_block_view_MODULE_DELTA_alter().
 *
 * Melakukan modifikasi theme_wrappers dari main menu.
 */
function sbadmin2_block_view_system_main_menu_alter(&$data, $block) {
    return sbadmin2_menu::menu_tree_modify('main-menu', $data['content']);
}

/**
 * Implements of hook_block_view_MODULE_DELTA_alter().
 *
 * Melakukan modifikasi theme_wrappers dari main menu.
 */
function sbadmin2_block_view_system_user_menu_alter(&$data, $block) {
    global $user;
    if ($user->uid) {
        $data['content']['2']['#title'] = $user->name;
    }
}


