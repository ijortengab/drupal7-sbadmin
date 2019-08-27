<?php

/**
 * Pada keadaan tertentu, objek ini akan menambah property pada instance
 * $view, yakni: `sbadmin2_rendered_fields_array`.
 */
class sbadmin2_helper_handler_field_field_datetime extends views_handler_field_field {

    use sbadmin2_helper_handler_field_trait;

    /**
     * Implements sbadmin2_helper_handler_field_trait::render_origin().
     */
    public function render_origin($values)
    {
        return parent::render($values);
    }
}
