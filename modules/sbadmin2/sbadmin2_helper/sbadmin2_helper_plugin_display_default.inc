<?php

/**
 * Mengambil alih method :render_area() agar men-support fitur list group baik
 * pada header maupun footer.
 */
class sbadmin2_helper_plugin_display_default extends views_plugin_display_default
{
    /**
     * {@inheritdoc}
     */
    public function render_area($area, $empty = FALSE) {
        $style_options = $this->get_option('style_options');
        $header_listgroup_convert = isset($style_options['sbadmin2']['listgroup_convert']['header']) && $style_options['sbadmin2']['listgroup_convert']['header'];
        $footer_listgroup_convert = isset($style_options['sbadmin2']['listgroup_convert']['footer']) && $style_options['sbadmin2']['listgroup_convert']['footer'];
        // Kembalikan empty string karena akan diproses oleh sbadmin2_preprocess_views_view().
        if ($area == 'header' && $header_listgroup_convert) {
            return '';
        }
        elseif ($area == 'footer' && $footer_listgroup_convert) {
            return '';
        }
        $return = '';
        foreach ($this->get_handlers($area) as $area) {
            $return .= $area->render($empty);
        }
        return $return;
    }
}
