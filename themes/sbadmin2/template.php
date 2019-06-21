<?php

/**
 * Implements hook_theme().
 */
function sbadmin2_theme($existing, $type, $theme, $path) {
    return [
        'node_form' => [
            'render element' => 'form',
            'template' => 'templates/node-form',
        ],
        'menu_nolink' => [
            'render element' => 'element',
        ],
    ];
}

/**
 * Preprocessor for template node_form.
 */
function sbadmin2_preprocess_node_form(&$variables) {
    hide($variables['form']['actions']);
    hide($variables['form']['additional_settings']);
}

function sbadmin2_preprocess_page(&$variables) {
}

function sbadmin2_preprocess_menu_local_tasks(&$variables) {
}

function sbadmin2_preprocess_menu_local_task(&$variables) {
}

function sbadmin2_preprocess_menu_link(&$variables) {
}

function sbadmin2_preprocess_menu_tree(&$variables) {
}

function sbadmin2_preprocess_form(&$variables) {
}

function sbadmin2_preprocess_block(&$variables) {
}

function sbadmin2_preprocess_region(&$variables) {
}


function sbadmin2_preprocess_menu_link__user_menu(&$variables) {
}


function sbadmin2_preprocess_views_view_table(&$variables) {
    $variables['classes_array'][] = 'table';
    $variables['classes_array'][] = 'table-striped';
    $variables['classes_array'][] = 'table-bordered';
    $variables['classes_array'][] = 'table-hover';
}

function sbadmin2_preprocess_table(&$variables) {
    $variables['attributes']['class'][] = 'table';
    $variables['attributes']['class'][] = 'table-striped';
    $variables['attributes']['class'][] = 'table-bordered';
    $variables['attributes']['class'][] = 'table-hover';
}

function sbadmin2_menu_link__user_menu(&$variables) {
    sbadmin2_unset_drupal_class($variables);
    return theme_menu_link($variables);
}

function sbadmin2_menu_link__main_menu(&$variables) {
    sbadmin2_unset_drupal_class($variables);
    return theme_menu_link($variables);
}

function sbadmin2_menu_nolink(&$variables) {
    sbadmin2_unset_drupal_class($variables);
    $element = $variables['element'];
    $sub_menu = '';
    if ($element['#below']) {
        $sub_menu = drupal_render($element['#below']);
    }
    $element['#localized_options']['external'] = true;
    $output = l($element['#title'], 'javascript:void(0)', $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}


function sbadmin2_unset_drupal_class(&$variables) {
    // $tempe = $variables['element'];

  // Hapus class bawaan Drupal yakni first, last, dan leaf.
  if (in_array('first', $variables['element']['#attributes']['class'])) {
      $key = array_search('first', $variables['element']['#attributes']['class']);
      unset($variables['element']['#attributes']['class'][$key]);
  }
  if (in_array('last', $variables['element']['#attributes']['class'])) {
      $key = array_search('last', $variables['element']['#attributes']['class']);
      unset($variables['element']['#attributes']['class'][$key]);
  }
  if (in_array('leaf', $variables['element']['#attributes']['class'])) {
      $key = array_search('leaf', $variables['element']['#attributes']['class']);
      unset($variables['element']['#attributes']['class'][$key]);
  }
  if (in_array('active-trail', $variables['element']['#attributes']['class'])) {
      $key = array_search('active-trail', $variables['element']['#attributes']['class']);
      unset($variables['element']['#attributes']['class'][$key]);
  }
  if (in_array('expanded', $variables['element']['#attributes']['class'])) {
      $key = array_search('expanded', $variables['element']['#attributes']['class']);
      unset($variables['element']['#attributes']['class'][$key]);
  }
}

// theme_menu_local_task($variables)

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
 * Menghapus class .form-item,
 * Ini otomatis mengubah file CSS system.theme.css
 * sehingga tidak diperlukan lagi class .form-item
 * Contoh:
 * .form-item input.error, .form-item textarea.error, .form-item select.error
 * Menambah class .form-group
 * Mengubah class .description menjadi .help-block
 * Menambah dukungan terhadap form-horizontal.
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

  // if (!isset($element['#sbadmin2_form_horizontal'])) {
      // $element['#sbadmin2_form_horizontal'] = true;
  // }

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

function sbadmin2_preprocess_field(&$variables) {
    // todo.
    // - jika simple field. cardinality = 1 dan type text.
    //   maka gunakan input text regular.
    // - jika image. maka
    // jika selain itu, maka kembalikan ke design semula.
    // yakni theme_field.
    $element = $variables['element'];
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

function sbadmin2_field($variables) {
    switch ($variables['sbadmin2_variant']) {
        case 'simple':
            return _sbadmin2_field_simple($variables);

        // case 'file':
            // return _sbadmin2_field_file($variables);

        default:
            return theme_field($variables);
    }

}

function _sbadmin2_field_simple($variables) {
  /*
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . ':&nbsp;</div>';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
  foreach ($variables['items'] as $delta => $item) {
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';
 */
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

function _sbadmin2_field_file($variables) {

  /*
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . ':&nbsp;</div>';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
  foreach ($variables['items'] as $delta => $item) {
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';
 */
    // module_load_include();
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
