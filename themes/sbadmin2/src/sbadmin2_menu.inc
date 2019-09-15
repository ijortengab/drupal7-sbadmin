<?php

/**
 * Memodifikasi main menu sehingga sesuai dengan behaviour dari SBAdmin2.
 *
 * Menu link yang memiliki bit `MENU_VISIBLE_IN_TREE` akan tidak muncul di tree
 * meski dapat di-access dan parent expanded, jika parent TIDAK memiliki bit
 * `MENU_VISIBLE_IN_TREE`.
 *
 * Contoh:
 *     - LEVEL 1 A      MENU_NORMAL_ITEM
 *       - LEVEL 2 A    MENU_DEFAULT_LOCAL_TASK
 *         - LEVEL 3 A  MENU_DEFAULT_LOCAL_TASK
 *         - LEVEL 3 B  MENU_LOCAL_TASK | MENU_NORMAL_ITEM
 *         - LEVEL 3 C  MENU_LOCAL_TASK | MENU_NORMAL_ITEM
 *       - LEVEL 2 B    MENU_LOCAL_TASK
 *       - LEVEL 2 C    MENU_LOCAL_TASK
 *     - LEVEL 1 B
 *
 * Pada contoh diatas, maka menu item `LEVEL 3B` dan `LEVEL 3C` tidak tampak
 * pada tree menu, meski semua menu link dapat di access dan expanded.
 *
 * Yang terlihat adalah sebagai berikut:
 *     - LEVEL 1 A      MENU_NORMAL_ITEM
 *       - LEVEL 2 B    MENU_LOCAL_TASK
 *       - LEVEL 2 C    MENU_LOCAL_TASK
 *     - LEVEL 1 B
 *
 * Pada function `menu_rebuild()`, semua `type` yang tidak mengandung
 * MENU_VISIBLE_IN_TREE (termasuk MENU_DEFAULT_LOCAL_TASK) maka akan diaktifkan
 * property `hidden`.
 * Kemudian function `menu_tree_output()`, akan menghapus link item yang terdapat
 * property hidden aktif (yakni: menu item `LEVEL 2 A`) dan otomatis child-nya
 * juga akan terhapus (yakni: menu item `LEVEL 3 B` dan `level 3C`) karena
 * function tersebut recursive.
 *
 * Solusi untuk hal ini adalah membuat function baru menggantikan function
 *  `menu_tree()`. Function `menu_tree()` menggunakan `menu_tree_page_data()`
 * yang result-nya sudah meng-eliminir menu link dengan kondisi diatas.
 * Kita akan menggunakan `menu_tree_all_data()` untuk mendapat semua menu link
 * yang belum tereliminir. Kemudian menu link dengan type
 * `MENU_DEFAULT_LOCAL_TASK` kita buat terlihat di menu tree dan di-modif
 * agar menjadi toggle.
 */
class sbadmin2_menu
{
    /**
     * Initialize.
     */
    public static function menu_tree_modify($menu_name, &$tree)
    {
        $tree = menu_tree_all_data($menu_name);
        self::unhide_default_local_task($tree);
        $tree = menu_tree_output($tree);
        self::modified_default_local_task($tree);
    }

    /**
     * Meng-override nilai `hidden` pada setiap menu link ber-type
     * `MENU_DEFAULT_LOCAL_TASK`.
     */
    protected static function unhide_default_local_task(&$tree, &$parent = null)
    {
        foreach ($tree as $i => $data) {
            if ($parent !== null && isset($data['link']['type']) && !($data['link']['type'] & MENU_VISIBLE_IN_TREE) && ($data['link']['type'] & MENU_LINKS_TO_PARENT)) {
                $tree[$i]['link']['hidden'] = 0;
                $tree[$i]['link']['href'] = $parent['link']['href'];
            }
            self::unhide_default_local_task($tree[$i]['below'], $tree[$i]);
        }
    }

    /**
     * Memodifikasi main menu sehingga hook theme dari property #theme_wrappers
     * dari sebelumnya adalah `menu_tree__main_menu` menjadi `menu_tree__main_menu__level_x`.
     * Cara ini digunakan untuk memberikan class nav.nav-second-level dan
     * nav.nav-third-level pada main menu.
     *
     * Memodifikasi menu link parent agar tidak menjadi link, dan membuatnya menjadi
     * toggle untuk expand/collapse menu.
     */
    protected static function modified_default_local_task(&$tree, $level = 1, &$parent = null)
    {
        sbadmin2_utils::replace_theme_wrappers('menu_tree__main_menu', 'menu_tree__main_menu__level_' . $level, $tree);
        $childrens = element_children($tree);
        foreach ($childrens as $mlid) {
            if ($parent !== null && isset($tree[$mlid]['#original_link']['type']) && !($tree[$mlid]['#original_link']['type'] & MENU_VISIBLE_IN_TREE) && ($tree[$mlid]['#original_link']['type'] & MENU_LINKS_TO_PARENT)) {
                $parent['#theme'] = 'menu_nolink';
                $parent['#title'] .= ' <span class="fa arrow"></span>';
                $parent['#localized_options']['html'] = true;
                // Ganti li.active-trail menjadi li.active agar class .fa.arrow
                // menyesuaikan arahnya menjadi kebawah.
                if (in_array('active-trail', $parent['#attributes']['class'])) {
                    $key = array_search('active', $parent['#attributes']['class']);
                    $parent['#attributes']['class'][$key] = 'active';
                }
            }
            self::modified_default_local_task($tree[$mlid]['#below'], $level + 1, $tree[$mlid]);
        }
    }
}
