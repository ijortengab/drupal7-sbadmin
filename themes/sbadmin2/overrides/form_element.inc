<?php

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
      ($form_horizontal === false) or $output .= '<div class="col-sm-10">';
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      ($form_horizontal === false) or $output .= $description . '</div>';
      break;

    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      ($form_horizontal === false) or $output .= '<div class="col-sm-10">';
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
        ($form_horizontal === false) or $output .= '<div class="col-sm-offset-2">';
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
