<?php

class sbadmin2_helper_handler_theme_random {

    public $machine_name = 'random';

    /**
     *
     */
    public $options = [];

    /**
     *
     */
    public function options_form(&$form, &$form_state) {
        $form['words'] = [
            '#type' => 'textarea',
            '#title' => 'Words',
            '#description' => 'Separate with new line.',
            '#default_value' => isset($this->options['words']) ? implode("\n", $this->options['words']) : '',
        ];
    }

    /**
     * Buat menjadi array.
     */
    public function options_validate(&$form, &$form_state)
    {
        if (!empty($form_state['values']['options']['sbadmin2']['themes'][$this->machine_name]['options'])) {
            $options = &$form_state['values']['options']['sbadmin2']['themes'][$this->machine_name]['options'];
            // Start validate elements.
            $options['words'] = explode("\n", $options['words']);
            $options['words'] = array_filter(array_map(function ($value) {
                $value = trim($value);
                if ($value === '') {
                    return false;
                }
                return $value;
            }, $options['words']));
        }
    }
}
