<?php

/**
 * Mengambil alih method :render_area() agar men-support fitur list group baik
 * pada header maupun footer.
 */
class sbadmin2_helper_plugin_display_default extends views_plugin_display_default
{
    use sbadmin2_helper_plugin_display_trait;
}
