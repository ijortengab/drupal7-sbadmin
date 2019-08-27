<?php

/**
 * Trait untuk digunakan bersama oleh class yang menjadi `override handler`.
 *
 * @see sbadmin2_helper_views_data_alter().
 *
 * Trait ini membuat property baru pada object view dengan nama variable
 * `rendered_fields_array`. Digunakan untuk menyimpan render output yang
 * merupakan array.
 */
trait sbadmin2_helper_handler_field_trait {

    /**
     * Menyimpan instance dari theme handler.
     */
    public $theme_handlers = [];

    /**
     * Method ::render() diambil alih oleh Trait untuk mensupport multivalue.
     * Class yang menggunakan trait ini wajib mendefinsikan method
     * ::render_origin() sebagai pengganti ::render().
     */
    abstract function render_origin($values);

    /**
     * Menambah definisi baru yakni `sbadmin2` dengan default value adalah
     * empty array.
     */
    public function option_definition() {
        $options = parent::option_definition();
        $options['sbadmin2'] = ['default' => []];
        return $options;
    }

    /**
     * Menyediakan interface form bagi handler theme JS.
     * Hanya berlaku bagi display table.
     */
    public function options_form(&$form, &$form_state) {
        parent::options_form($form, $form_state);
        if (!sbadmin2_helper_is_views_display_table($this)) {
            return;
        }
        $form['sbadmin2'] = array(
            '#type' => 'fieldset',
            '#title' => t('SBAdmin2'),
            '#tree' => true,
            '#collapsible' => true,
        );
        $form['sbadmin2']['rewrite'] = array(
            '#type' => 'checkbox',
            '#title' => t('Rewrite Columns'),
            '#description' => t('Allow SbAdmin2 rewrite columns via Javascript.'),
            '#default_value' => isset($this->options['sbadmin2']['rewrite']) ? $this->options['sbadmin2']['rewrite'] : false,
        );
        $form['sbadmin2']['theme_selected'] = [
            '#type' => 'radios',
            '#title' => t('Themes'),
            '#description' => t('Theme function provided by Javascript for Rewrite Columns.'),
            '#options' => themejs_options($this),
            '#default_value' => isset($this->options['sbadmin2']['theme_selected']) ? $this->options['sbadmin2']['theme_selected'] : null,
            '#dependency' => [
                'edit-options-sbadmin2-rewrite' => [1]
            ],
        ];
        // Process dibawah mengenai options dari theme.
        foreach (themejs_info() as $theme => $info) {
            // Create Fieldset.
            $form['sbadmin2']['themes'][$theme]['options'] = [
                '#type' => 'fieldset',
                '#tree' => true,
                '#description' => isset($info['description']) ? $info['description'] : '',
                '#collapsible' => true,
                '#title' => t($info['title']),
                // Menggunakan #states-nya Drupal, karena #dependency-nya
                // CTools tidak berhasil.
                '#states' => [
                    'visible' => [
                        ':input[name="options[sbadmin2][theme_selected]"]' => [
                            'value' => $theme,
                        ],
                        ':input[name="options[sbadmin2][rewrite]"]' => [
                            'checked' => true,
                        ],
                    ],
                ],
            ];
            if (method_exists($info['handler'], 'options_form')) {
                $this->theme_handlers[$theme] = new $info['handler'];
                $handler = $this->theme_handlers[$theme];
                $handler->options = isset($this->options['sbadmin2']['themes'][$theme]['options']) ? $this->options['sbadmin2']['themes'][$theme]['options'] : [];
                $handler->options_form($form['sbadmin2']['themes'][$theme]['options'], $form_state);
            }
        }
    }

    /**
     * Perantara bagi method options_validate yang dimiliki oleh handler
     * dari theme js.
     */
    public function options_validate(&$form, &$form_state)
    {
        parent::options_validate($form, $form_state);
        if (!empty($form_state['values']['options']['sbadmin2']['rewrite']) && !empty($form_state['values']['options']['sbadmin2']['theme_selected'])) {
            $theme = $form_state['values']['options']['sbadmin2']['theme_selected'];
            if (!empty(themejs_info($theme)['handler'])) {
                $handler = $this->theme_handlers[$theme];
                if (method_exists($handler, 'options_validate')) {
                    $handler->options_validate($form['sbadmin2']['themes'][$theme]['options'], $form_state);
                }
            }
        }
    }

    /**
     * Memberi dukungan untuk value pada column dalam bentuk array. Biasanya
     * yang berbentuk array adalah ul li. Column yang menghasilkan multivalue
     * ini hanya bisa diproses oleh theme function di Javascript yang dipilih
     * melalui konfigurasi field di Views Admin.
     */
    public function render($values)
    {
        // Ambil langsung.
        $render_origin = $this->render_origin($values);
        if (is_array($render_origin)) {
            // Function render sebenarnya harus mengembalikan string.
            // Jika array, maka simpan value untuk sementara ke property
            // yang kita buat sendiri, lalu kembalikan empty string.
            // Biar nanti yang mengolah adalah preprocess.
            $this->view->rendered_fields_array[$this->view->row_index][$this->options['id']] = $render_origin;
            return '';
        }
        return $render_origin;
    }
}
