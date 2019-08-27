<?php

/**
 * Tidak support untuk multivalue. Jika multivalue, maka hanya akan mengambil
 * first array.
 */
class sbadmin2_timeago_handler_field_field_datetime extends views_handler_field_field {

    use sbadmin2_helper_handler_field_trait;

    var $allow_advanced_render = false;

    /**
     * Implements sbadmin2_helper_handler_field_trait::render_origin().
     */
    public function render_origin($values)
    {
        // Untuk mendapatkan formatted date, maka kita perlu gunakan fungsi
        // advanced render.
        $this->allow_advanced_render = true;
        $render = parent::advanced_render($values);
        $this->allow_advanced_render = false;
        if (isset($this->options['sbadmin2']['rewrite'])
         && isset($this->options['sbadmin2']['theme_selected'])
         && $this->options['sbadmin2']['rewrite']
         && $this->options['sbadmin2']['theme_selected'] == 'timeago'
        ) {
            // Contoh result $get_value = [['value' => '2019-05-29 00:00:00', 'timezone' => 'Asia/Jakarta', 'timezone_db' => 'Asia/Jakarta', 'date_type' => 'datetime']];
            $value = $this->get_value($values);
            // if (count($value) > 1) {
                // @todo: Beri warning bahwa kita hanya support untuk satu value.
            // }
            $value = array_shift($value); // 2019-05-29 00:00:00
            $date_time = DateTime::createFromFormat('Y-m-d H:i:s', $value['value'], new DateTimeZone($value['timezone']));
            return sbadmin2_timeago_return($date_time, strip_tags($render));
        }
        else {
            return $render;
        }
    }

    /**
     * Kita perlu membuat views_handler_field::allow_advanced_render() me-return
     * false, sehingga views_handler_field::advanced_render() tetap mengeksekusi
     * views_handler_field::render(). Tidak jadi meng-eksekusi
     * views_handler_field_field::get_items(), ::render_item() dan
     * ::render_items().
    */
    public function allow_advanced_render() {
        return $this->allow_advanced_render;
    }
}
