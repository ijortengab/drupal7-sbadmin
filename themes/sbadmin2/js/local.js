(function ($) {

/**
 * Mengganti icon bar bawaan font-awesome yang lebih elegan dibandingkan
 * default (glyphicon).
 */
$('.nav-pills, .nav-tabs').tabdrop({text: '<i class="fa fa-bars"></i>'});

/**
 * Eksekusi function `$('#side-menu').metisMenu()` pada file `/vendor/startbootstrap-sb-admin-2/3.3.7+1/js/sb-admin-2.js`
 * berarti menjalankan jQuery plugin metisMenu() versi `1.1.3` pada file `/vendor/metisMenu/1.1.3/metisMenu.min.js`.
 *
 * Plugin `metisMenu` tidak terdapat event yang memberitahukan bahwa eksekusi
 * sudah selesai. Namun, eksekusi `metisMenu()` yang sudah selesai akan
 * menambahkan jQuery.data() yang disimpan pada DOM (lihat code) dan ini bisa
 * kita jadikan penanda sebagai pengganti event dengan melakukan pengecekan
 * menggunakan javascript setInterval() per 0.1 detik.
 */
var checkFinishingMetisMenu = setInterval(function() {
    var data = $("#side-menu").data();
    if (data.metisMenu) {
        clearInterval(checkFinishingMetisMenu);
        var $element = data.metisMenu.element;
        // Jika link item merupakan MENU_NORMAL_ITEM, maka event click yang
        // di-set oleh `metisMenu()` perlu kita revoke agar user bisa
        // menge-click tautan link tersebut. Lihat pula function PHP
        // `sbadmin2_menu::modified_menu_tree()`.
        $element.find("li.menu-normal-item").has("ul").children("a").off("click.metisMenu");
        $element.find("li.menu-normal-item").has("ul").children("ul").removeClass('collapse');
    }
}, 100);
})(jQuery);
