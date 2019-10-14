<?php

/**
 * Override theme_menu_local_tasks().
 */
function sbadmin2_menu_local_tasks(&$variables) {
    $output = '';
    if (!empty($variables['primary'])) {
        $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
        $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs">';
        $variables['primary']['#suffix'] = '</ul>';
        $variables['primary']['#suffix'] .= '<br>';
        $output .= drupal_render($variables['primary']);
    }
    if (!empty($variables['secondary'])) {
        $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
        $variables['secondary']['#prefix'] .= '<ul class="nav nav-pills">';
        $variables['secondary']['#suffix'] = '</ul>';
        $variables['secondary']['#suffix'] .= '<br>';
        $output .= drupal_render($variables['secondary']);
    }
    return $output;
}
