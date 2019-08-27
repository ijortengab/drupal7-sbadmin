<?php

/**
 * Implements of hook_views_data_alter().
 */
function sbadmin2_timeago_views_data_alter(&$data) {
    // Ganti handler semua date, karena akan dikasih support untuk implements
    // fitur jquery timeago.
    foreach ($data as $table => $table_info) {
        foreach ($data[$table] as $field => $field_info) {
            if (isset($field_info['field']['handler'])) {
                switch ($field_info['field']['handler']) {
                    case 'views_handler_field_date':
                        $data[$table][$field]['field']['override handler'] = 'sbadmin2_timeago_handler_field_date';
                        break;

                    case 'views_handler_field_field':
                        $field_name = $field_info['field']['field_name'];
                        $field_type = field_info_field($field_name)['type'];
                        switch ($field_type) {
                            case 'datetime': //@todo: date, datestamp.
                                $data[$table][$field]['field']['override handler'] = 'sbadmin2_timeago_handler_field_field_datetime';
                                break;
                        }
                        break;
                }
            }
        }
    }
}
