<?php

/**
 * Implements of hook_views_data_alter().
 *
 * Knowledge base: Dua hook ini, yakni `hook_views_handler_option_definition_alter` dan
 * `hook_views_plugin_option_definition_alter` tersedia untuk meng-override
 * method `::options_form()` maupun `::option_definition()`.
 *
 * Untuk mengoverride method `::render()` dari class
 * `views_handler_field_ctools_dropdown`, cara yang tersedia hanya dengan
 * menggantikan handler class melalui hook `hook_views_data_alter`.
 */
function sbadmin2_helper_views_data_alter(&$data) {
    // Ganti handler dari sebelumnya `views_handler_field_ctools_dropdown`.
    // karena akan dioprek dengan menambah form options dan juga
    // perbaikan bug pada views_handler_field_ctools_dropdown::get_links().
    $data['views']['ctools_dropdown']['field']['override handler'] = 'sbadmin2_helper_handler_field_ctools_dropdown';
}
