<?php

/**
 * Pada keadaan tertentu, objek ini akan menambah property pada instance
 * $view, yakni: `sbadmin2_rendered_fields_array`.
 */
class sbadmin2_helper_handler_field_ctools_dropdown extends views_handler_field_ctools_dropdown {

    const order = ['title', 'href', 'fragment', 'query', 'absolute', 'alias', 'prefix'];

    use sbadmin2_helper_handler_field_trait;

    /**
     * Implements sbadmin2_helper_handler_field_trait::render_original().
     */
    public function render_origin($values)
    {
        // Hanya jika field options memang meminta rewrite javascript baru kita
        // return value dalam bentuk array.
        if (!empty($this->options['sbadmin2']['rewrite'])
         && !empty($this->options['sbadmin2']['theme_selected'])
         && $this->options['sbadmin2']['theme_selected'] == 'bootstrap_links'
        ) {
            return $this->minified_links($this->get_links());
        }
        else {
            return parent::render($values);
        }
    }

    /**
     * Terdapat bug pada Dropbutton Views 7.x-3.x. Sehingga kita perlu
     * menggantikan method asli.
     * Menggantikan baris kode dari:
     * ```if (empty($this->view->field[$field]->last_render_text))```
     * menjadi
     * ```if (empty($this->view->style_plugin->get_field($this->view->row_index, $field)))```
     */
    public function get_links() {
        $links = array();
        foreach ($this->options['fields'] as $field) {
            if (empty($this->view->style_plugin->get_field($this->view->row_index, $field))) {
                continue;
            }
            $title = $this->view->field[$field]->last_render_text;
            // Use the alter settings for the link field source not this links field.
            $alter = $this->view->field[$field]->options['alter'];
            $url = array('query' => array());

            // Copy code from views_handler_field::render_as_link().
            $path = $alter['path'];
            if (!empty($path) && $path != '<front>') {
                // Leave path alone on <front> as strip_tags() would remove this.
                // Replace tokens and strip any HTML tags in the path.
                $tokens = $this->get_render_tokens(array());
                $path = strip_tags(decode_entities(strtr($path, $tokens)));

                if (!empty($alter['path_case']) && $alter['path_case'] != 'none') {
                    $path = $this->case_transform($path, $alter['path_case']);
                }

                if (!empty($alter['replace_spaces'])) {
                    $path = str_replace(' ', '-', $path);
                }

                $url = drupal_parse_url($path);
                if (empty($url)) {
                    // Seriously malformed URLs may return FALSE or empty arrays.
                    continue;
                }
                $path = $url['path'];

                // Check router menu item access for the current user.
                if ($this->options['check_access']) {
                    $menu_item = menu_get_item($path);
                    if (!$menu_item || empty($menu_item['access'])) {
                        continue;
                    }
                }

                if (!empty($this->options['destination']) && empty($alter['external'])) {
                    // Override any destination argument included in URL.
                    $url['query'] = array_merge($url['query'], drupal_get_destination());
                }

                // Omit tweaks of query, fragment, and link_class.
                $alt = strtr($alter['alt'], $tokens);
                if ($alt && $alt != $title) {
                    // Set the title attribute only if it improves accessibility.
                    $url['attributes']['title'] = decode_entities($alt);
                }

                if (!empty($alter['rel']) && $rel = strtr($alter['rel'], $tokens)) {
                    $url['attributes']['rel'] = $rel;
                }

                $target = check_plain(trim(strtr($alter['target'], $tokens)));
                if (!empty($target)) {
                    $url['attributes']['target'] = $target;
                }
            }
            $links[$field] = array(
                'href' => $path,
                'title' => $title,
            ) + $url;
        }
        return $links;
    }

    /**
     * Member array yang kosong maka dihapus dari array.
     */
    public function minified_links($links)
    {
        $links = array_values($links);
        $order = self::order;
        $order = array_flip($order);
        $order = array_map(function ($value) {
            return "";
        }, $order);
        $links = array_map(function ($each) use ($order) {
            // Delete unused key.
            $each = array_intersect_key($each, $order);
            $each = array_merge($order, $each);
            end($each);
            do {
                $value = current($each);
                if ($value === "" || $value === []) {
                    $key = key($each);
                    prev($each);
                    unset($each[$key]);
                }
                else {
                    break;
                }
            }
            while (true);
            return array_values($each);
        }, $links);
        return $links;
    }
}
