<?php

class sbadmin2_helper_handler_theme_bootstrap_links {

    const COLORIZE = [
        'default' => 'Default', 'primary' => 'Primary',
        'success' => 'Success', 'info' => 'Info',
        'warning' => 'Warning', 'danger' => 'Danger',
    ];

    const SIZE = [
        'lg' => 'Large', 'normal' => 'Normal',
        'sm' => 'Small', 'xs' => 'Extra small',
    ];

    public function options_form(&$form, &$form_state) {

        $form['columnDefs'] = [
            '#title' => 'Split Button Dropdowns',
            '#type' => 'value',
            '#value' => ['searchable' => false, 'sortable' => false],
        ];

        $form['split'] = [
            '#title' => 'Split Button Dropdowns',
            '#type' => 'checkbox',
            '#default_value' => isset($this->options['split']) ? $this->options['split'] : 1,
        ];

        $form['arrow_position'] = [
            '#title' => 'Arrow Position',
            '#type' => 'select',
            '#options' => drupal_map_assoc(range(0,9)),
            '#description' => 'Index of links to place arrow as toggle dropdown.',
            '#default_value' => isset($this->options['arrow_position']) ? $this->options['arrow_position'] : 1,
        ];

        $form['colorize'] = [
            '#title' => 'Colorize',
            '#type' => 'select',
            '#options' => self::COLORIZE,
            '#default_value' => isset($this->options['colorize']) ? $this->options['colorize'] : 'default',
        ];

        $form['size'] = [
            '#title' => 'Sizing',
            '#type' => 'select',
            '#options' => self::SIZE,
            '#default_value' => isset($this->options['size']) ? $this->options['size'] : 'normal',
        ];
    }
}
