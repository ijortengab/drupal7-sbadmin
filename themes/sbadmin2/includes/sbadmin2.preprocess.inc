<?php

/**
 * @file sbadmin2.theme_override.inc
 *
 * Preprocess theme that provided by Drupal Core or Contributed Module..
 */

/**
 * Implements of hook_preprocess_HOOK().
 *
 * Preprocess for template views_view.
 */
function sbadmin2_preprocess_views_view(&$variables) {

    $view = $variables['view'];
    if ($view->display_handler->get_option('style_plugin') == 'table') {
        $variables['theme_hook_suggestions'][] = 'views_view__table';
        drupal_add_library('sbadmin2', 'sbadmin2.views_table');
    }
    // Tambah variables ke template.
    $variables['dom_id'] = $view->dom_id;

    // Modify Header and Footer.
    $style_options = $view->display_handler->get_option('style_options');
    $header_listgroup_convert = isset($style_options['sbadmin2']['listgroup_convert']['header']) && $style_options['sbadmin2']['listgroup_convert']['header'];
    $footer_listgroup_convert = isset($style_options['sbadmin2']['listgroup_convert']['footer']) && $style_options['sbadmin2']['listgroup_convert']['footer'];
    $empty = empty($variables['rows']);
    if (module_exists('sbadmin2_helper') && $header_listgroup_convert) {
        $headers_bag = [];
        foreach ($view->display_handler->get_handlers('header') as $area) {
            $render = $area->render($empty);
            $headers_bag[] = ($render === '') ? false : $render;
        }
        $headers_bag = array_filter($headers_bag);
        foreach ($headers_bag as $render) {
            $variables['header'] .= '<li class="list-group-item">' . $render . '</li>';
        }
        $variables['header'] = empty($variables['header']) ? '' : '<ul class="list-group view-header">' . $variables['header'] . '</ul>';
    }
    else {
        $variables['header'] = empty($variables['header']) ? '' : '<div class="panel-body view-header">' . $variables['header'] . '</div>';
    }
    if (module_exists('sbadmin2_helper') && $footer_listgroup_convert) {
        $footers_bag = [];
        foreach ($view->display_handler->get_handlers('footer') as $area) {
            $render = $area->render($empty);
            $footers_bag[] = ($render === '') ? false : $render;
        }
        $footers_bag = array_filter($footers_bag);
        foreach ($footers_bag as $render) {
            $variables['footer'] .= '<li class="list-group-item">' . $render . '</li>';
        }
        $variables['footer'] = empty($variables['footer']) ? '' : '<ul class="list-group view-footer">' . $variables['footer'] . '</ul>';
    }
    else {
        $variables['footer'] = empty($variables['footer']) ? '' : '<div class="panel-body view-footer">' . $variables['footer'] . '</div>';
    }
}

function sbadmin2_preprocess_views_view_table(&$variables) {
    $view = $variables['view'];
    $views_key = $view->dom_id;
    $header = $variables['header'];
    $style_options = $view->style_plugin->options;
    $datatables_convert = (isset($style_options['sbadmin2']['datatables_convert']) && $style_options['sbadmin2']['datatables_convert']);
    $datatables_source = isset($style_options['sbadmin2']['datatables_source']) ? $style_options['sbadmin2']['datatables_source'] : 'html';

    $variables['classes_array'][] = 'table';
    $variables['classes_array'][] = 'table-striped';
    $variables['classes_array'][] = 'table-hover';

    if ($datatables_convert) {
        // Add library.
        drupal_add_library('sbadmin2', 'sbadmin2.datatables');
        if ($view->use_ajax) {
            drupal_add_library('sbadmin2', 'sbadmin2.datatables.ajax');
        }
        // Datatables will trigger if there are this variable in javascript
        // `Drupal.settings.sbadmin2.views.datatables.dom_key` and class
        // `table.sbadmin2-datatables`.
        $variables['settings']['sbadmin2']['views']['datatables'][$views_key]['options'] = [];
        $variables['classes_array'][] ='sbadmin2-datatables';
        $options = &$variables['settings']['sbadmin2']['views']['datatables'][$views_key]['options'];
        // For optimize.
        // @see: https://datatables.net/reference/option/autoWidth
        $options = array_merge($options, [
            'autoWidth' => false,
            'dom' => '<"panel-body"<"row"<"col-md-12"<"pull-left"f><"pull-right"i>>>>rt<"panel-body"<"row"<"col-md-12"<"pull-left"l><"pull-right"p>>>>'
        ]);
    }

    // Variable $variables['json'] dipopulate oleh sbadmin2_helper.
    // Hapus rows dan header hanya jika sbadmin2_helper yang mengubah html ke
    // json exists.
    if ($datatables_convert && $datatables_source == 'js' && isset($variables['json'])) {
        $options = array_merge($options, $variables['json']);
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
