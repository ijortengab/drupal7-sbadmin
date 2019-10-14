<?php

/**
 * Implements of hook_preprocess_HOOK(). 
 *
 * Preprocess template `block.tpl.php`.
 *
 * Menambah variable $messages ke template block--user--login.tpl.
 */
function sbadmin2_preprocess_block(&$variables) {
    if ($variables['block']->module == 'user' && $variables['block']->delta == 'login') {
        $variables['messages'] = theme('status_messages');
    }
}
