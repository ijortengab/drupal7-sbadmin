(function ($) {

Drupal.ajax.prototype.commands.sbadmin2DatatablesRedraw = function (ajax, response, status) {
    if (response.settings && response.settings.sbadmin2 && response.settings.sbadmin2.views) {
        var key = response.key;
        // Save memory with destroy table first, then delete instance.
        Drupal.sbadmin2Datatables.instance[key].destroyTable();
        delete Drupal.sbadmin2Datatables.instance[key];
        // Delete setting yang lama.
        for (x in response.settings.sbadmin2.views) {
            // In case something special missing order.
            if (Drupal.settings.sbadmin2.views.hasOwnProperty(x)) {
                delete Drupal.settings.sbadmin2.views[x][key];
            }
        }
        Drupal.settings = $.extend(true, Drupal.settings, response.settings);
        Drupal.behaviors.sbadmin2Datatables.attach(window, Drupal.settings)
    }
};

})(jQuery);
