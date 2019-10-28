<?php

/**
 * Memodifikasi main menu sehingga sesuai dengan behaviour dari SBAdmin2.
 *
 * Setiap menu link di Drupal terbagi menjadi 4 type utama yang setiap type
 * memiliki flag dalam bentuk bit, yakni:
 *
 * - MENU_CALLBACK
 * - MENU_NORMAL_ITEM = MENU_VISIBLE_IN_TREE | MENU_VISIBLE_IN_BREADCRUMB
 * - MENU_LOCAL_TASK = MENU_IS_LOCAL_TASK | MENU_VISIBLE_IN_BREADCRUMB
 * - MENU_DEFAULT_LOCAL_TASK = MENU_IS_LOCAL_TASK | MENU_LINKS_TO_PARENT | MENU_VISIBLE_IN_BREADCRUMB
 *
 * Fakta terkait Menu di Drupal adalah sebagai berikut: Menu link yang memiliki
 * bit `MENU_VISIBLE_IN_TREE` akan *tidak muncul* di tree meski dapat di-access
 * dan parent expanded, jika parent TIDAK memiliki bit `MENU_VISIBLE_IN_TREE`.
 *
 * Contoh Visualisasi adalah sebagai berikut:
 *
 * - LEVEL 1A          MENU_NORMAL_ITEM
 *     - LEVEL 2A      MENU_DEFAULT_LOCAL_TASK
 *         - LEVEL 3A  MENU_DEFAULT_LOCAL_TASK
 *         - LEVEL 3B  MENU_LOCAL_TASK | MENU_NORMAL_ITEM
 *         - LEVEL 3C  MENU_LOCAL_TASK | MENU_NORMAL_ITEM
 *     - LEVEL 2B      MENU_LOCAL_TASK | MENU_NORMAL_ITEM
 *     - LEVEL 2C      MENU_LOCAL_TASK | MENU_NORMAL_ITEM
 * - LEVEL 1B          MENU_NORMAL_ITEM
 *
 * Pada contoh diatas, maka menu item `LEVEL 3B` dan `LEVEL 3C` tidak tampak
 * pada tree menu, meski semua menu link dapat di access dan expanded karena
 * parent mereka yakni `LEVEL 2A` tidak memiliki bit `MENU_VISIBLE_IN_TREE`.
 *
 * Yang terlihat adalah sebagai berikut:
 *     - LEVEL 1A      MENU_NORMAL_ITEM
 *       - LEVEL 2B    MENU_LOCAL_TASK | MENU_NORMAL_ITEM
 *       - LEVEL 2C    MENU_LOCAL_TASK | MENU_NORMAL_ITEM
 *     - LEVEL 1B      MENU_NORMAL_ITEM
 *
 * Setelah ditelusuri, penyebabnya adalah sebagai berikut:
 *
 * - Pada function `menu_rebuild()`, semua `type` yang tidak mengandung
 *   MENU_VISIBLE_IN_TREE (termasuk MENU_DEFAULT_LOCAL_TASK) maka akan
 *   diaktifkan property `hidden`.
 * - Kemudian function `menu_tree_output()`, akan menghapus link item yang
 *   terdapat property hidden aktif (yakni: menu item `LEVEL 2A`) dan otomatis
 *   child-nya juga akan terhapus (yakni: menu item `LEVEL 3B` dan `level 3C`)
 *   karena function tersebut recursive.
 *
 * SBAdmin2 membutuhkan seluruh menu link terlihat sehingga perlu solusi atas
 * masalah diatas.
 *
 * Solusi untuk hal ini adalah membuat alternative menggantikan function
 *  `menu_tree()` yang mana function `menu_tree()` menggunakan `menu_tree_page_data()`
 * yang result-nya sudah meng-eliminir menu link dengan kondisi diatas.
 *
 * Kita akan menggunakan `menu_tree_all_data()` untuk mendapat semua menu link
 * yang belum tereliminir. Kemudian menu link dengan type `MENU_DEFAULT_LOCAL_TASK`
 * kita buat terlihat di menu tree dan di-modif agar menjadi toggle.
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
        self::modified_menu_tree($tree);
    }

    /**
     * Meng-override nilai `hidden` pada setiap menu link ber-type
     * `MENU_DEFAULT_LOCAL_TASK` dan mengcopy link dari parent.
     */
    protected static function unhide_default_local_task(&$tree, &$parent = null)
    {
        foreach ($tree as $i => $data) {
            $type = isset($data['link']['type']) ? $data['link']['type'] : null;
            if ($parent !== null && self::is_default_local_task($type)) {
                $tree[$i]['link']['hidden'] = 0;
                // Link MENU_DEFAULT_LOCAL_TASK pada primary atau secondary tab
                // benar-benar dibuat menjadi parent. Oleh karena itu
                // Pada link di tree kita buat menyerupai parent juga
                // agar javascript-nya SBAdmin2 tidak keliru dalam mengasih
                // class `active` dan auto on/off collapsed berdasarkan
                // kesesuaian path.
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
    protected static function modified_menu_tree(&$tree, $level = 1, &$parent = null)
    {
        sbadmin2_utils::replace_theme_wrappers('menu_tree__main_menu', 'menu_tree__main_menu__level_' . $level, $tree);
        $router_item = menu_get_item();
        $childrens = element_children($tree);
        foreach ($childrens as $mlid) {
            // Hapus class `active` yang muncul tidak konsisten pada parent.
            // @see: menu_tree_output().
            if ($tree[$mlid]['#original_link']['href'] == $router_item['tab_root_href'] && $tree[$mlid]['#original_link'] != $_GET['q']) {
                if (isset($tree[$mlid]['#localized_options']['attributes']['class']) && in_array('active', $tree[$mlid]['#localized_options']['attributes']['class'])) {
                    $key = array_search('active', $tree[$mlid]['#localized_options']['attributes']['class']);
                    unset($tree[$mlid]['#localized_options']['attributes']['class'][$key]);
                }
            }
            $type = isset($tree[$mlid]['#original_link']['type']) ? $tree[$mlid]['#original_link']['type'] : null;
            // link yang termasuk MENU_NORMAL_ITEM perlu diberikan class agar
            // nanti @todo.
            if (self::is_normal_item($type)) {
                $tree[$mlid]['#attributes']['class'][] = 'menu-normal-item';
            }
            // Link pada parent harus diganti menjadi non URL
            // agar javascript-nya SBAdmin2 tidak keliru dalam mengasih
            // class `active` berdasarkan kesesuaian path.
            if ($parent !== null && self::is_default_local_task($type)) {
                // Theme ini akan membuat attribute `href` menjadi `javascript:void()`.
                $parent['#theme'] = 'menu_nolink';
                // Tambahkan arrow.
                $parent['#title'] .= ' <span class="fa arrow"></span>';
                $parent['#localized_options']['html'] = true;
                // Kemudian parent harus dihapus class `menu-normal-item` agar
                // tidak terhapus event onclick oleh `local.js`.
                sbadmin2_utils::remove_class($parent, ['menu-normal-item']);
            }
            self::modified_menu_tree($tree[$mlid]['#below'], $level + 1, $tree[$mlid]);
        }
    }

    /**
     * Memastikan bahwa type link item merupakan MENU_DEFAULT_LOCAL_TASK tapi
     * bukan MENU_LOCAL_TASK.
     */
    protected static function is_default_local_task($type)
    {
        return (!($type & MENU_VISIBLE_IN_TREE) && ($type & MENU_LINKS_TO_PARENT));
    }

    /**
     * Memastikan bahwa type link item merupakan MENU_NORMAL_ITEM.
     */
    protected static function is_normal_item($type)
    {
        return ($type & MENU_VISIBLE_IN_TREE);
    }
}
