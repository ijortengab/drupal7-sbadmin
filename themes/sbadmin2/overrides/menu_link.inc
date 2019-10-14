<?php

/**
 * Implements of `theme_menu_link__user_menu`.
 * @see: menu_tree_output().
 */
function sbadmin2_menu_link__user_menu(&$variables) {
    sbadmin2_utils::remove_drupal_class($variables['element']);
    return theme_menu_link($variables);
}

/**
 * Implements of `theme_menu_link__user_menu`.
 * @see: menu_tree_output().
 */
function sbadmin2_menu_link__main_menu(&$variables) {
    sbadmin2_utils::remove_drupal_class($variables['element']);
    return theme_menu_link($variables);
}
