<?php

/**
 * Implements hook_preprocess_HOOK(). 
 * 
 * Preprocess theme_link().
 */
function sbadmin2_preprocess_link(&$variables) {
    if (!empty($variables['options']) && !empty($variables['options']['sbadmin2_icon'])) {
        $variables['options']['html'] = TRUE;
        $variables['text'] = '<i class="fa fa-'. check_plain($variables['options']['sbadmin2_icon']) . ' fa-fw"></i> ' . $variables['text'];
    }
}
