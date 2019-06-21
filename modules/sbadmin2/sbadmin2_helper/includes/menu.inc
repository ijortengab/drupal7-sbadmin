<?php

/**
 * Memodifikasi main menu sehingga hook theme dari property #theme_wrappers
 * dari sebelumnya adalah `menu_tree__main_menu` menjadi `menu_tree__main_menu__level_x`.
 * Cara ini digunakan untuk memberikan class nav.nav-second-level dan
 * nav.nav-third-level pada main menu.
 * Menambah element list <li> tanpa link <a> dengan fungsi khusus on/off toggle
 * collapsed pada sub menu didalam list.
*/
function _sbadmin2_helper_main_menu_modified(&$data) {
    ctools_include('utils', 'sbadmin2_helper');
    _sbadmin2_helper_main_menu_modified_recursive($data['content']);
}

/**
 * Sub fungsi dari fungsi `_sbadmin2_helper_main_menu_modified`
 * untuk melakukan recursive sampai element terdalam.
 */
function _sbadmin2_helper_main_menu_modified_recursive(&$data, $level = 1, $cloned_menu_link = null) {
    _sbadmin2_helper_utils_replace_theme_wrappers('menu_tree__main_menu', 'menu_tree__main_menu__level_' . $level, $data);
    $childrens = element_children($data);
    foreach ($childrens as $children) {
        if ($data[$children]['#below']) {
            $_cloned_menu_link = _sbadmin2_helper_main_menu_modified_clone_menu_link($children, $data[$children]);
            _sbadmin2_helper_main_menu_modified_sanitize_origin_menu_link($data[$children]);
            _sbadmin2_helper_main_menu_modified_recursive($data[$children]['#below'], ++$level, $_cloned_menu_link);
            $level--; // Reset.
        }
    }
    if ($cloned_menu_link !== null) {
        $data = $cloned_menu_link + $data;
    }
}

function _sbadmin2_helper_main_menu_modified_clone_menu_link($mlid, $element) {
    // Clear children.
    $element['#below'] = [];
    // Ganti title, jika ada.
    $path = $element['#href'];
    $result = db_query('SELECT path FROM {menu_router} where type = :type AND path LIKE :path', [':type' => MENU_DEFAULT_LOCAL_TASK, ':path' => '%'.$path.'%'])->fetchCol();
    if (!empty($result)) {
        $found = null;
        foreach ($result as $record) {
            // Filter hanya pada link yang tepat satu level dibawah.
            $regex = '/^'.str_replace('/',"\/",preg_quote($path))."\/[^\/]+$/";
            if (preg_match($regex, $record)) {
                $found = $record;
                break;
            }
        }
        if ($found !== null) {
            $title = db_query('SELECT link_title from {menu_links} WHERE link_path = :found', [':found' => $found])->fetchCol();
            $element['#title'] = array_shift($title);
        }
    }
    return [$mlid => $element];
}

function _sbadmin2_helper_main_menu_modified_sanitize_origin_menu_link(&$element) {
    $element['#theme'] = 'menu_nolink';
    $element['#title'] .= ' <span class="fa arrow"></span>';
    $element['#localized_options']['html'] = true;
    // Ganti li.active-trail menjadi li.active agar class .fa.arrow
    // menyesuaikan arahnya menjadi kebawah.
    if (in_array('active-trail', $element['#attributes']['class'])) {
        $key = array_search('active', $element['#attributes']['class']);
        $element['#attributes']['class'][$key] = 'active';
    }
}
