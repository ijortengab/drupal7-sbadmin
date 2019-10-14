<?php

/**
 * Implements of hook_preprocess_HOOK().
 *
 * Preprocess for theme_table().
 */
function sbadmin2_preprocess_table(&$variables) {
    $variables['attributes']['class'][] = 'table';
    $variables['attributes']['class'][] = 'table-striped';
    $variables['attributes']['class'][] = 'table-bordered';
    $variables['attributes']['class'][] = 'table-hover';
}
