<?php

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

