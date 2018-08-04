<?php

function sbadmin2_preprocess_page(&$variables) {
    $debugname = 'variables'; $debugfile = 'debug.html'; $debugvariable = '|||wakwaw|||'; if (array_key_exists($debugname, get_defined_vars())) { $debugvariable = $$debugname; } elseif (isset($this) && property_exists($this, $debugname)) { $debugvariable = $this->{$debugname}; $debugname = '$this->' . $debugname; } if ($debugvariable !== '|||wakwaw|||') { ob_start(); echo "\r\n<pre>" . basename(__FILE__ ). ":" . __LINE__ . " (Time: " . date('c') . ", Direktori: " . dirname(__FILE__) . ")\r\n". 'var_dump(' . $debugname . '): '; var_dump($debugvariable); echo "</pre>\r\n"; $debugoutput = ob_get_contents();ob_end_clean(); file_put_contents($debugfile, $debugoutput, FILE_APPEND); }
}

function sbadmin2_preprocess_menu_local_tasks(&$variables) {
    // $debugname = 'variables'; $debugfile = 'debug.html'; $debugvariable = '|||wakwaw|||'; if (array_key_exists($debugname, get_defined_vars())) { $debugvariable = $$debugname; } elseif (isset($this) && property_exists($this, $debugname)) { $debugvariable = $this->{$debugname}; $debugname = '$this->' . $debugname; } if ($debugvariable !== '|||wakwaw|||') { ob_start(); echo "\r\n<pre>" . basename(__FILE__ ). ":" . __LINE__ . " (Time: " . date('c') . ", Direktori: " . dirname(__FILE__) . ")\r\n". 'var_dump(' . $debugname . '): '; var_dump($debugvariable); echo "</pre>\r\n"; $debugoutput = ob_get_contents();ob_end_clean(); file_put_contents($debugfile, $debugoutput, FILE_APPEND); }
}

function sbadmin2_preprocess_menu_local_task(&$variables) {
    // $debugname = 'variables'; $debugfile = 'debug.html'; $debugvariable = '|||wakwaw|||'; if (array_key_exists($debugname, get_defined_vars())) { $debugvariable = $$debugname; } elseif (isset($this) && property_exists($this, $debugname)) { $debugvariable = $this->{$debugname}; $debugname = '$this->' . $debugname; } if ($debugvariable !== '|||wakwaw|||') { ob_start(); echo "\r\n<pre>" . basename(__FILE__ ). ":" . __LINE__ . " (Time: " . date('c') . ", Direktori: " . dirname(__FILE__) . ")\r\n". 'var_dump(' . $debugname . '): '; var_dump($debugvariable); echo "</pre>\r\n"; $debugoutput = ob_get_contents();ob_end_clean(); file_put_contents($debugfile, $debugoutput, FILE_APPEND); }
}

function sbadmin2_preprocess_menu_link(&$variables) {
    // $debugname = 'variables'; $debugfile = 'debug.html'; $debugvariable = '|||wakwaw|||'; if (array_key_exists($debugname, get_defined_vars())) { $debugvariable = $$debugname; } elseif (isset($this) && property_exists($this, $debugname)) { $debugvariable = $this->{$debugname}; $debugname = '$this->' . $debugname; } if ($debugvariable !== '|||wakwaw|||') { ob_start(); echo "\r\n<pre>" . basename(__FILE__ ). ":" . __LINE__ . " (Time: " . date('c') . ", Direktori: " . dirname(__FILE__) . ")\r\n". 'var_dump(' . $debugname . '): '; var_dump($debugvariable); echo "</pre>\r\n"; $debugoutput = ob_get_contents();ob_end_clean(); file_put_contents($debugfile, $debugoutput, FILE_APPEND); }
}

function sbadmin2_preprocess_menu_tree(&$variables) {
    // $debugname = 'variables'; $debugfile = 'debug.html'; $debugvariable = '|||wakwaw|||'; if (array_key_exists($debugname, get_defined_vars())) { $debugvariable = $$debugname; } elseif (isset($this) && property_exists($this, $debugname)) { $debugvariable = $this->{$debugname}; $debugname = '$this->' . $debugname; } if ($debugvariable !== '|||wakwaw|||') { ob_start(); echo "\r\n<pre>" . basename(__FILE__ ). ":" . __LINE__ . " (Time: " . date('c') . ", Direktori: " . dirname(__FILE__) . ")\r\n". 'var_dump(' . $debugname . '): '; var_dump($debugvariable); echo "</pre>\r\n"; $debugoutput = ob_get_contents();ob_end_clean(); file_put_contents($debugfile, $debugoutput, FILE_APPEND); }
}

function sbadmin2_preprocess_block(&$variables) {
    // $debugname = 'variables'; $debugfile = 'debug.html'; $debugvariable = '|||wakwaw|||'; if (array_key_exists($debugname, get_defined_vars())) { $debugvariable = $$debugname; } elseif (isset($this) && property_exists($this, $debugname)) { $debugvariable = $this->{$debugname}; $debugname = '$this->' . $debugname; } if ($debugvariable !== '|||wakwaw|||') { ob_start(); echo "\r\n<pre>" . basename(__FILE__ ). ":" . __LINE__ . " (Time: " . date('c') . ", Direktori: " . dirname(__FILE__) . ")\r\n". 'var_dump(' . $debugname . '): '; var_dump($debugvariable); echo "</pre>\r\n"; $debugoutput = ob_get_contents();ob_end_clean(); file_put_contents($debugfile, $debugoutput, FILE_APPEND); }
}

function sbadmin2_preprocess_region(&$variables) {
    // $debugname = 'variables'; $debugfile = 'debug.html'; $debugvariable = '|||wakwaw|||'; if (array_key_exists($debugname, get_defined_vars())) { $debugvariable = $$debugname; } elseif (isset($this) && property_exists($this, $debugname)) { $debugvariable = $this->{$debugname}; $debugname = '$this->' . $debugname; } if ($debugvariable !== '|||wakwaw|||') { ob_start(); echo "\r\n<pre>" . basename(__FILE__ ). ":" . __LINE__ . " (Time: " . date('c') . ", Direktori: " . dirname(__FILE__) . ")\r\n". 'var_dump(' . $debugname . '): '; var_dump($debugvariable); echo "</pre>\r\n"; $debugoutput = ob_get_contents();ob_end_clean(); file_put_contents($debugfile, $debugoutput, FILE_APPEND); }
}


function sbadmin2_preprocess_menu_link__user_menu(&$variables) {
    // $debugname = 'variables'; $debugfile = 'debug.html'; $debugvariable = '|||wakwaw|||'; if (array_key_exists($debugname, get_defined_vars())) { $debugvariable = $$debugname; } elseif (isset($this) && property_exists($this, $debugname)) { $debugvariable = $this->{$debugname}; $debugname = '$this->' . $debugname; } if ($debugvariable !== '|||wakwaw|||') { ob_start(); echo "\r\n<pre>" . basename(__FILE__ ). ":" . __LINE__ . " (Time: " . date('c') . ", Direktori: " . dirname(__FILE__) . ")\r\n". 'var_dump(' . $debugname . '): '; var_dump($debugvariable); echo "</pre>\r\n"; $debugoutput = ob_get_contents();ob_end_clean(); file_put_contents($debugfile, $debugoutput, FILE_APPEND); }
}

function sbadmin2_menu_link__user_menu(&$variables) {
    sbadmin2_unset_drupal_class($variables);
    return theme_menu_link($variables);
}

function sbadmin2_menu_link__main_menu(&$variables) {
    sbadmin2_unset_drupal_class($variables);
    return theme_menu_link($variables);
}

function sbadmin2_unset_drupal_class(&$variables) {
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

