(function ($) {

/**
 * Melakukan rewrite terhadap column pada views table.
 */
Drupal.behaviors.sbadmin2Rewrite = {
    attach: function (context, settings) {
        if (settings.sbadmin2 && settings.sbadmin2.views && settings.sbadmin2.views.rewrite) {
            var rewrite = settings.sbadmin2.views.rewrite;
            for (x in rewrite) {
                var selector = '.view-dom-id-' + x + ' table';
                $(selector, context).once('sbadmin2-rewrite', function () {
                   for (y in rewrite[x]) {
                       var column = rewrite[x][y].column;
                       var theme = rewrite[x][y].theme;
                       var options = rewrite[x][y].options;
                       var selector = 'tbody tr td:nth-child('+(1+column)+')';
                       var views_key = x;
                       var row = 0;
                       $(selector, this).each(function () {
                            var data = this.innerHTML;
                            // Cek multivalue.
                            if ($.trim(data) == '' && Drupal.settings.sbadmin2.views.multivalue
                             && Drupal.settings.sbadmin2.views.multivalue[views_key]
                             && Drupal.settings.sbadmin2.views.multivalue[views_key][row]
                             && Drupal.settings.sbadmin2.views.multivalue[views_key][row][column]
                            ) {
                                // Jika ada, maka ganti data dengan yang ada pada
                                // multivalue (array). Biarlah theme function
                                // yang menerima data array ini.
                                data = Drupal.settings.sbadmin2.views.multivalue[views_key][row][column];
                            }
                            if (typeof Drupal.theme.prototype[theme] == 'function' || typeof Drupal.theme[theme] == 'function') {
                                this.innerHTML = Drupal.theme(theme, data, options, this, context, settings);
                            }
                            row++;
                       })
                   }
                });
            }
        }
    }
}

})(jQuery);
