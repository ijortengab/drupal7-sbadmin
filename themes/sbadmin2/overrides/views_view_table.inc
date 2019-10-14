<?php

/**
 * Implements of hook_preprocess_HOOK().
 *
 * Preprocess for template `views-view-table.tpl.php`.
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
            //@todo: gunakan javascript agar permanen.
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
