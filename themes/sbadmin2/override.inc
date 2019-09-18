<?php

/**
 * @file sbadmin2.override.inc
 *
 * Override theme functions and preprocess theme function for theme hook that
 * provided by Drupal Core or Contributed Module.
 */

/**
 * Implements of #theme: `menu_link__user_menu`.
 * @see: menu_tree_output().
 */
function sbadmin2_menu_link__user_menu(&$variables) {
    sbadmin2_utils::remove_drupal_class($variables['element']);
    return theme_menu_link($variables);
}

/**
 * Implements of #theme: `menu_link__main_menu`.
 * @see: menu_tree_output().
 */
function sbadmin2_menu_link__main_menu(&$variables) {
    sbadmin2_utils::remove_drupal_class($variables['element']);
    return theme_menu_link($variables);
}

/**
 * Override theme_menu_local_task().
 */
function sbadmin2_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<li' . (!empty($variables['element']['#active']) ? ' class="active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

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

function sbadmin2_preprocess_textfield(&$variables) {
    $element = &$variables['element'];
    if ($size = sbadmin2_utils::get_size($element, 'input')) {
        $element['#attributes']['class'][] = 'input-' . $size;
    }
}

function sbadmin2_preprocess_select(&$variables) {
    $element = &$variables['element'];
    if ($size = sbadmin2_utils::get_size($element, 'input')) {
        $element['#attributes']['class'][] = 'input-' . $size;
    }
}

/**
 * Override theme_textfield().
 */
function sbadmin2_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  _form_set_class($element, array('form-text'));

  $extra = '';
  if ($element['#autocomplete_path'] && !empty($element['#autocomplete_input'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#autocomplete_input']['#id'];
    $attributes['value'] = $element['#autocomplete_input']['#url_value'];
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }
  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';
  return $output . $extra;
}

/**
 * Override theme_form_element().
 *
 * - Menghapus class .form-item.
 *   Ini otomatis mengubah file CSS system.theme.css sehingga tidak diperlukan
 *   lagi class .form-item. Contoh: .form-item input.error,
 *   .form-item textarea.error, .form-item select.error
 * - Menambah class `.form-group`
 * - Mengubah class `.description` menjadi `.help-block`
 * - Menambah dukungan terhadap form-horizontal.
 */
function sbadmin2_form_element($variables) {
  $element = &$variables['element'];
  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
    '#type' => null,
  );

  // Khusus radio dan checkbox, maka title harus berada didalam label.
  switch ($element['#type']) {
      case 'radio':
      case 'checkbox':
          $element['#title_display'] = 'inside';
          break;
  }

  $form_horizontal = (isset($element['#sbadmin2_form_horizontal']) && $element['#sbadmin2_form_horizontal']);
  $description = (!empty($element['#description'])) ? '<div class="help-block">' . $element['#description'] . '</div>' : '';

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-group');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
    $attributes['class'][] = strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  // Source from _form_set_class().
  $_element = $element;
  if (isset($element['#type']) && $element['#type'] == 'managed_file') {
      $_element = $element['upload'];
  }
  if (isset($_element['#parents']) && form_get_error($_element) !== NULL && !empty($_element['#validated'])) {
    $attributes['class'][] = 'has-error';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
      $output .= ' ' . theme('form_element_label', $variables);
      ($form_horizontal === false) or $output .= '<div class="col-lg-10">';
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      ($form_horizontal === false) or $output .= $description . '</div>';
      break;

    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      ($form_horizontal === false) or $output .= '<div class="col-lg-10">';
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      ($form_horizontal === false) or $output .= $description . '</div>';
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'inside':
        ($form_horizontal === false) or $output .= '<div class="col-lg-offset-2">';
        $output .= ' ' . theme('form_element_label', $variables) . "\n";
        ($form_horizontal === false) or $output .= $description . '</div>';
        break;
  }
    if ($form_horizontal === false) {
        $output .= $description;
    }

  $output .= "</div>\n";

  if ($form_horizontal) {
      $output = '<div class="form-horizontal">' . $output . '</div>';
  }

  return $output;
}

/**
 * Override theme_form_element_label().
 */
function sbadmin2_form_element_label($variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  if (isset($element['#sbadmin2_form_horizontal']) && $element['#sbadmin2_form_horizontal']) {
      $attributes['class']['control-label'] = 'control-label';
      $attributes['class']['col-lg-2'] = 'col-lg-2';
  }
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'][] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'][] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }
  if ($element['#title_display'] == 'inside') {
    $title = $element['#children'] . $title;
    unset($attributes['class']['control-label']);
    unset($attributes['class']['col-lg-2']);
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
}

/**
 * Override theme_button().
 */
function sbadmin2_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array(
    'id',
    'name',
    'value',
  ));
  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }
  if (isset($element['#value'])) {
      $value = t($element['#value']);
      switch ($value) {
          case 'Save':
              $element['#attributes']['class'][] = 'btn-primary';
              break;

          case 'New content':
          case 'Tambah':
              $element['#attributes']['class'][] = 'btn-info';

              break;

          default:
              // Do something.
              break;
      }
  }
  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

// Obselete.
// todo, convert to formatter.
function sbadmin2_preprocess_field(&$variables) {
    // todo.
    // - jika simple field. cardinality = 1 dan type text.
    //   maka gunakan input text regular.
    // - jika image. maka
    // jika selain itu, maka kembalikan ke design semula.
    // yakni theme_field.
    $element = $variables['element'];
    $field_type = $element['#field_type'];

    switch ($element['#field_type']) {
        case 'text':
        // case 'entityreference':
        case 'datetime':
            $variables['sbadmin2_variant'] = 'simple';
            break;

        case 'file':
            $variables['sbadmin2_variant'] = 'file';
            break;

        default:
            $variables['sbadmin2_variant'] = null;
            break;
    }
}

// Obselete.
// todo, convert to formatter.
function sbadmin2_field($variables) {
    switch ($variables['sbadmin2_variant']) {
        case 'simple':
            return _sbadmin2_field_simple($variables);

        default:
            return theme_field($variables);
    }
}

// Obselete.
// todo, convert to formatter.
function _sbadmin2_field_simple($variables) {
    $output = '';
    if (!$variables['label_hidden']) {
        $output .= '<label class="control-label col-lg-2"><span' . $variables['title_attributes'] . '>' . $variables['label'] . '</span></label>';
    }
    $value = [];
    foreach ($variables['items'] as $delta => $item) {
        $value[] = drupal_render($item);
    }
    $value = implode(', ', $value);
    $value = strip_tags($value);

    $output .= '<div class="col-lg-10">';
    $output .= '<input class="form-control" type="text" readonly="readonly" value="'.$value.'">';
    $output .= '</div>';
    $output = '<div class="form-horizontal"><div class="form-group">' . $output . '</div></div>';
    return $output;
}

// Obselete.
// todo, convert to formatter.
function _sbadmin2_field_file($variables) {
    $output = '';
    if (!$variables['label_hidden']) {
        $output .= '<label class="control-label col-lg-2"><span' . $variables['title_attributes'] . '>' . $variables['label'] . '</span></label>';
    }
    $value = [];

    foreach ($variables['items'] as $delta => $item) {
        $value[] = drupal_render($item);
    }
    $value = implode(', ', $value);
    $value = strip_tags($value);
    $output .= '<div class="col-lg-10">';
    $output .= '<input class="form-control" type="text" readonly="readonly" value="'.$value.'">';
    $output .= '</div>';
    $output = '<div class="form-horizontal"><div class="form-group">' . $output . '</div></div>';
    return $output;
}

/**
 * Implements of hook_preprocess_HOOK().
 *
 * Preprocess for template views_view.
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

/**
 *
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

/**
 * Implemements of hook_preprocess_HOOK().
 *
 * Preprocess theme `views_exposed_form`.
 */
function sbadmin2_preprocess_views_exposed_form(&$variables) {
    // @see: sbadmin2_form_views_exposed_form_alter().
    $form = $variables['form'];

    // Ambil alih variable widget, karena akan render didalam preprocess ini.
    // Nanti tiba di template tinggal print saja.
    $widgets = $variables['widgets'];

    $variables['widgets_rebuild'] = [];
    $widgets_rebuild = &$variables['widgets_rebuild'];

    foreach ($variables['widgets'] as $id => $widget) {
        $element_value = $form[$form['#info'][$id]['value']];
        $element_operator = (isset($form['#info'][$id]['operator']) && isset($form[$form['#info'][$id]['operator']])) ? $form[$form['#info'][$id]['operator']] : [];

        // Group terdiri dari `button` atau `input`. Jika salah satu element
        // terdapat class form-control, maka itu masuk kategori group `input`.
        $group = 'input';
        if (isset($element_value['#sbadmin2_transform']) && $element_value['#sbadmin2_transform'] == 'button') {
            $group = 'button';
        }
        // Prepare label.
        $label = [
            '#type' => ($group == 'input') ? (empty($element_value['#sbadmin2_label_menu']) ? 'input_group_addon' : 'button_group_addon') : 'button_group_addon',
            '#title' => $widget->label,
            '#sbadmin2_size' => isset($element_value['#sbadmin2_size']) ? $element_value['#sbadmin2_size'] : null,
        ];
        // Label toggle.
        $label_toggle = empty($element_value['#sbadmin2_label_menu']) ? [] : [
            '#type' => 'submit_button',
            '#toggle' => 'dropdown',
            '#value' => '<span class="caret"></span>',
            '#sbadmin2_size' => isset($element_value['#sbadmin2_size']) ? $element_value['#sbadmin2_size'] : null,
        ];
        // Label menu.
        $label_menu = empty($element_value['#sbadmin2_label_menu']) ? [] : [
            '#type' => 'dropdown_menu',
            '#options' => $element_value['#sbadmin2_label_menu'],
        ];
        // Operator.
        $operator = empty($widget->operator) ? [] : [
            '#markup' => $widget->operator,
        ];
        // Element khusus multivalue, beri fitur centang all.
        $bulk = empty($element_value['#sbadmin2_bulk_toggle']) ? [] : [
            '#type' => 'submit_button',
            '#value' => '<i class="fa fa-square-o fa-fw"></i>',
            '#attributes' => ['class' => ['bulk-toggle'], 'type' => 'button'],
            '#sbadmin2_size' => isset($element_value['#sbadmin2_size']) ? $element_value['#sbadmin2_size'] : null,
        ];
        // Widget pasti ada.
        $input = [
            '#markup' => $widget->widget,
        ];
        // Mapping Position.
        switch ($group) {
            case 'input':
                $widgets_rebuild[$id] = [
                    '#theme_wrappers' => ['input_group'],
                    'label' => [
                        '#theme_wrappers' => empty($element_value['#sbadmin2_label_menu']) ? [] : ['input_group_button'],
                        'label' => $label,
                        'label_toggle' => $label_toggle,
                        'label_menu' => $label_menu,
                    ],
                    'operator' => [
                        '#theme_wrappers' => empty($operator) ? [] : ['input_group_button'],
                        'operator' => $operator,
                    ],
                    'input' => $input,
                ];
                break;

            case 'button':
                $widgets_rebuild[$id] = [
                    '#theme_wrappers' => empty($element_value['#sbadmin2_label_menu']) ? ['button_group_input'] : ['button_toolbar'],
                    'label' => [
                        '#theme_wrappers' => empty($element_value['#sbadmin2_label_menu']) ? [] : ['button_group'],
                        'label' => $label,
                        'label_toggle' => $label_toggle,
                        'label_menu' => $label_menu,
                    ],
                    'operator' => [
                        '#theme_wrappers' => empty($operator) ? [] : (empty($element_value['#sbadmin2_label_menu']) ? [] : ['button_group']),
                        'operator' => $operator,
                    ],
                    'bulk' => [
                        '#theme_wrappers' => empty($bulk) ? [] : ['button_group'],
                        'bulk' => $bulk,
                    ],
                    'input' => [
                        '#theme_wrappers' => empty($element_value['#sbadmin2_label_menu']) ? [] : ['button_group_input'],
                        'input' => $input,
                    ],
                ];
                break;
        }
        // Copy size, lihat dari element value saja.
        $widgets_rebuild[$id]['#sbadmin2_size'] = isset($element_value['#sbadmin2_size']) ? $element_value['#sbadmin2_size'] : null;
        // Sembunyikan operator jika value sama dengan default, selain itu - berarti ada interfensi user - maka tampilkan.
        if (isset($element_operator['#default_value']) && isset($element_operator['#value']) && $element_operator['#default_value'] == $element_operator['#value']) {
             $widgets_rebuild[$id]['operator']['#attributes']['class'][] = 'element-hidden';
        }

        $widgets_rebuild[$id]['#prefix'] = '<div class="views-exposed-widget">';
        $widgets_rebuild[$id]['#suffix'] = '</div>';
        if (!empty($form['#sbadmin2_listgroup'])) {
            $widgets_rebuild[$id]['#theme_wrappers'][] = 'list_group_item';
            // $widgets_rebuild[$id]['#theme_wrappers'][] = 'list_group';
        }
        else {
            $widgets_rebuild[$id]['#prefix'] = '<div class="form-group">';
            $widgets_rebuild[$id]['#suffix'] = '</div>';
        }
    }


    $widgets_rebuild = drupal_render($widgets_rebuild);
    // $widgets_rebuild = ''; // Untuk development, turn on this line.
    $variables['widgets'] = []; // Untuk development, turn off this line.
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
