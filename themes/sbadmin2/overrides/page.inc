<?php

/**
 * Implements of hook_preprocess_HOOK().
 *
 * Preprocess template `page.tpl.php`.
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
