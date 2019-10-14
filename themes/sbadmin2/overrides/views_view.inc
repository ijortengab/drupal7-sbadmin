<?php

/**
 * Implements of hook_preprocess_HOOK().
 *
 * Preprocess for template `views-view.tpl.php`.
 */
function sbadmin2_preprocess_views_view(&$variables) {
    $view = $variables['view'];
    $collapsible_button = [];
    $header_rerender = false;
    $views_name_hash = substr(md5($view->name), 0, 6); // md5 is faster.
    // $view_name = $view->n;
    if ($view->display_handler->get_option('style_plugin') == 'table') {
        $variables['theme_hook_suggestions'][] = 'views_view__table';
        if (!empty($variables['exposed'])) {
            $collapsible_button[] = [
                'label' => 'Filter',
                // 'id' => 'Filter',
                'target' => '#views-filter-' . $views_name_hash,
                // 'id' => 'views-header-' . ,
            ];
        }

        foreach ($view->display_handler->get_handlers('header') as $handler) {
            $options = $handler->options;
            $is_collapsible = isset($options['sbadmin2']['is_collapsible']) && !empty($options['sbadmin2']['is_collapsible']);
            $collapsible_button_label = isset($options['sbadmin2']['collapsible_button_label']) && !empty($options['sbadmin2']['collapsible_button_label']);
            if ($is_collapsible && $collapsible_button_label) {
                $header_rerender = true;
                $collapsible_button[$options['id']] = [
                    'label' => $options['sbadmin2']['collapsible_button_label'],
                    'target' => '#views-header-' . $options['id'] . '-' . $views_name_hash,
                ];
            }
        }
        if (empty($collapsible_button)) {
            $variables['collapsible_button'] = false;
        }
        else {
            $variables['collapsible_button'] = $collapsible_button;
            drupal_add_library('sbadmin2', 'sbadmin2.views_collapsible_button');
        }
    }
    // Tambah variables ke template.
    $variables['views_name_hash'] = $views_name_hash;

    // Modify Header and Footer.
    $style_options = $view->display_handler->get_option('style_options');
    $header_listgroup_convert = isset($style_options['sbadmin2']['listgroup_convert']['header']) && $style_options['sbadmin2']['listgroup_convert']['header'];
    $footer_listgroup_convert = isset($style_options['sbadmin2']['listgroup_convert']['footer']) && $style_options['sbadmin2']['listgroup_convert']['footer'];
    $exposed_form_listgroup_convert = isset($style_options['sbadmin2']['listgroup_convert']['exposed_form']) && $style_options['sbadmin2']['listgroup_convert']['exposed_form'];
    $header_rerender = ($header_listgroup_convert) ? true : $header_rerender;
    $variables['sbadmin2_listgroup_class'] = $exposed_form_listgroup_convert ? ' list-group' : '';
    if ($header_rerender) {
        $empty = empty($variables['rows']);
        // Header perlu kita render lagi. Tapi jika module `sbadmin2_helper`
        // exist, maka Header memang belum di-render sehingga lebih efisien.
        // @see: sbadmin2_helper_plugin_display_default::render_area().
        $variables['header'] = '';
        $headers_bag = [];
        foreach ($view->display_handler->get_handlers('header') as $area) {
            $render = $area->render($empty);
            $headers_bag[] = ($render === '') ? false : ['render' => $render, 'id' => $area->options['id']];
        }
        $headers_bag = array_filter($headers_bag);
        foreach ($headers_bag as $bag) {
            // $anu = 'tempe';
            $class_addition = isset($collapsible_button[$bag['id']]) ? ' collapse': '';
            if ($header_listgroup_convert) {
                $variables['header'] .= '<ul id="views-header-'.$bag['id'].'-'.$views_name_hash.'" class="list-group view-header'.$class_addition.'"><li class="list-group-item">'.$bag['render'].'</li></ul>';
            }
            else {
                $variables['header'] .= '<div id="views-header-'.$bag['id'].'-'.$views_name_hash.'" class="panel-body view-header'.$class_addition.'">'.$bag['render'].'</div>';
            }
        }
    }
    else {
        // .panel-body.view-header terdapat di CSS.
        $variables['header'] = empty($variables['header']) ? '' : '<div class="panel-body view-header">' . $variables['header'] . '</div>';
    }
    if ($footer_listgroup_convert) {
        // Footer perlu kita render lagi. Tapi jika module `sbadmin2_helper`
        // exist, maka Footer memang belum di-render sehingga lebih efisien.
        // @see: sbadmin2_helper_plugin_display_default::render_area().
        $variables['footer'] = '';
        $footers_bag = [];
        foreach ($view->display_handler->get_handlers('footer') as $area) {
            $render = $area->render($empty);
            $footers_bag[] = ($render === '') ? false : $render;
        }
        $footers_bag = array_filter($footers_bag);
        foreach ($footers_bag as $render) {
            $variables['footer'] .= '<li class="list-group-item">' . $render . '</li>';
        }
    }
    else {
        $variables['footer'] = empty($variables['footer']) ? '' : '<div class="panel-body view-footer">' . $variables['footer'] . '</div>';
    }
    if (!$exposed_form_listgroup_convert) {
        $variables['exposed'] = empty($variables['exposed']) ? '' : '<div class="panel-body">' . $variables['exposed'] . '</div>';
    }
}
