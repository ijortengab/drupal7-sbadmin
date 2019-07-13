<?php

/**
 * @file sbadmin2.inc
 *
 * Collection of theme function override and preprocess theme.
 */

/**
 * Preprocessor for template node_form.
 */
function sbadmin2_preprocess_node_form(&$variables) {
    hide($variables['form']['actions']);
    hide($variables['form']['additional_settings']);
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
    sbadmin2_utils::remove_drupal_class($variables['element']);
    return theme_menu_link($variables);
}

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

        default:
            return theme_field($variables);
    }
}

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
 * Implements hook_preprocess_HOOK().
 * Preprocess theme `link`.
 */
function sbadmin2_preprocess_link(&$variables) {

    // return;
    if (!empty($variables['options']) && !empty($variables['options']['sbadmin2_icon'])) {
        $variables['options']['html'] = TRUE;
        $variables['text'] = '<i class="fa fa-'. check_plain($variables['options']['sbadmin2_icon']) . ' fa-fw"></i> ' . $variables['text'];
    }
}

/**
 * Implements of hook_preprocess_HOOK().
 *
 * Preprocess theme_hook `page`.
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
 * Implements of hook_preprocess_HOOK().
 *
 * Preprocess theme_hook `block`.
 *
 * Menambah variable $messages ke template block--user--login.tpl.
 */
function sbadmin2_preprocess_block(&$variables) {
    if ($variables['block']->module == 'user' && $variables['block']->delta == 'login') {
        $variables['messages'] = theme('status_messages');
    }
}

/**
 * Implements hook_preprocess_html().
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
