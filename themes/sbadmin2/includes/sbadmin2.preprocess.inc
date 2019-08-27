<?php

/**
 * @file sbadmin2.theme_override.inc
 *
 * Preprocess theme that provided by Drupal Core or Contributed Module..
 */

function sbadmin2_preprocess_views_view_table(&$variables) {
    $view = $variables['view'];
    $views_key = $view->dom_id;
    $header = $variables['header'];
    $style_options = $view->style_plugin->options;
    $datatables_convert = (isset($style_options['sbadmin2']['datatables_convert']) && $style_options['sbadmin2']['datatables_convert']);
    $datatables_source = isset($style_options['sbadmin2']['datatables_source']) ? $style_options['sbadmin2']['datatables_source'] : 'html';

    $variables['classes_array'][] = 'table';
    $variables['classes_array'][] = 'table-striped';
    $variables['classes_array'][] = 'table-bordered';
    $variables['classes_array'][] = 'table-hover';

    if ($datatables_convert) {
        // Add library.
        drupal_add_library('sbadmin2', 'sbadmin2.datatables');
        if ($view->use_ajax) {
            drupal_add_library('sbadmin2', 'sbadmin2.datatables.ajax');
        }
        // Two lines below required to create datatables.
        $variables['settings']['sbadmin2']['views']['datatables'][$views_key]['options'] = [];
        $variables['classes_array'][] ='sbadmin2-datatables';
    }

    // Variable $variables['json'] dipopulate oleh sbadmin2_helper.
    // Hapus rows dan header hanya jika sbadmin2_helper yang mengubah html ke
    // json exists.
    if ($datatables_convert && $datatables_source == 'js' && isset($variables['json'])) {
        $variables['settings']['sbadmin2']['views']['datatables'][$views_key]['options'] = $variables['json'];
        // Hapus row dan header.
        $variables['rows'] = $variables['header'] = [];
    }
    if (isset($variables['settings'])) {
        drupal_add_js($variables['settings'], array('type' => 'setting'));
    }
}

/**
 * Preprocess for template `table`.
 */
function sbadmin2_preprocess_table(&$variables) {
    $variables['attributes']['class'][] = 'table';
    $variables['attributes']['class'][] = 'table-striped';
    $variables['attributes']['class'][] = 'table-bordered';
    $variables['attributes']['class'][] = 'table-hover';
}

/**
 * Implements hook_preprocess_HOOK(). Preprocess theme `link`.
 */
function sbadmin2_preprocess_link(&$variables) {

    // return;
    if (!empty($variables['options']) && !empty($variables['options']['sbadmin2_icon'])) {
        $variables['options']['html'] = TRUE;
        $variables['text'] = '<i class="fa fa-'. check_plain($variables['options']['sbadmin2_icon']) . ' fa-fw"></i> ' . $variables['text'];
    }
}

/**
 * Implements of hook_preprocess_HOOK(). Preprocess theme `page`.
 *
 * Mematikan $messages pada template page pada route `/sbadmin2-login` karena
 * variable tersebut akan digunakan pada template `block__user__login`.
 *
 * @see template_preprocess_page.
 */
function sbadmin2_preprocess_page(&$variables) {
    if (current_path() == 'sbadmin2-login') {
        $variables['show_messages'] = false;
    }
}

/**
 * Implements of hook_preprocess_HOOK(). Preprocess theme `block`.
 *
 * Menambah variable $messages ke template block--user--login.tpl.
 */
function sbadmin2_preprocess_block(&$variables) {
    if ($variables['block']->module == 'user' && $variables['block']->delta == 'login') {
        $variables['messages'] = theme('status_messages');
    }
}

/**
 * Implements of hook_preprocess_HOOK(). Preprocess theme `html`.
 *
 * Memberikan informasi meta viewport.
 */
function sbadmin2_preprocess_html(&$variables) {
    $html_tag = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => 'width=device-width, initial-scale=1',
      ),
    );
    drupal_add_html_head($html_tag, 'viewport');
}
