<?php


class sbadmin2_timeago_handler_field_date extends views_handler_field_date
{
    use sbadmin2_helper_handler_field_trait;

    /**
     * Implements sbadmin2_helper_handler_field_trait::render_original().
     */
    public function render_origin($values)
    {
        // Hanya jika field options memang meminta rewrite javascript baru kita
        // return value dalam bentuk array.
        $render = parent::render($values);
        if (!empty($this->options['sbadmin2']['rewrite'])
         && !empty($this->options['sbadmin2']['theme_selected'])
         && $this->options['sbadmin2']['theme_selected'] == 'timeago'
        ) {
            return sbadmin2_timeago_return_array(new DateTime('@' . $this->get_value($values)), $render);
        }
        else {
            return $render;
        }
    }
}
