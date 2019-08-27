<?php


class sbadmin2_timeago_handler_field_date extends views_handler_field_date
{
    use sbadmin2_helper_handler_field_trait;

    /**
     * Implements sbadmin2_helper_handler_field_trait::render_original().
     */
    public function render_origin($values)
    {
        $render = parent::render($values);
        if (isset($this->options['sbadmin2']['rewrite'])
         && isset($this->options['sbadmin2']['theme_selected'])
         && $this->options['sbadmin2']['rewrite']
         && $this->options['sbadmin2']['theme_selected'] == 'timeago'
        ) {
            return sbadmin2_timeago_return(new DateTime('@' . $this->get_value($values)), $render);
        }
        else {
            return $render;
        }
    }
}
