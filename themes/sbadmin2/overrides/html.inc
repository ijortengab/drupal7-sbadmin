<?php

/**
 * Implements of hook_preprocess_HOOK(). 
 *
 * Preprocess template `html.tpl.php`.
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
