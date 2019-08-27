(function ($) {

// Object repository.
Drupal.sbadmin2Datatables = {instance: {}};

Drupal.behaviors.sbadmin2Datatables = {
    attach: function (context, settings) {
        if (settings.sbadmin2 && settings.sbadmin2.views && settings.sbadmin2.views.datatables) {
            var datatables = settings.sbadmin2.views.datatables;
            for (x in datatables) {
                if (!Drupal.sbadmin2Datatables.instance.hasOwnProperty(x)) {
                    Drupal.sbadmin2Datatables.instance[x] = new Drupal.sbadmin2Datatables.dataTables(x, datatables[x]);
                }
            }
        }
    }
};

// Class Object.
Drupal.sbadmin2Datatables.dataTables = function (views_key, settings) {
    this.settings = settings;
    this.views_key = views_key;
    var selector = '.view-dom-id-' + views_key + ' table.sbadmin2-datatables';
    this.$table = $(selector);
    this.$table.once(jQuery.proxy(this.drawtable, this));
    this.destroyTable = function () {
        this.$dataTable.destroy();
    }
};

Drupal.sbadmin2Datatables.dataTables.prototype.drawtable = function () {
    // Define variable options that passing to Datatables when intialiazed.
    var options = {columnDefs: []};
    // Import options that contains column and data if source set to json.
    if (this.settings.options) {
        options = $.extend(true, options, this.settings.options);
    }
    // Play with rewrite. Property ini dibuat oleh sbadmin2_helper, namun
    // diproses ditheme ini biar sekalian dengan init datatables.
    if (this.settings.rewrite) {
        // Beri informasi tambahan pada options. Beri nama property `sbadmin2`
        // agar tidak dikenali oleh DataTables. Informasi dibutuhkan untuk
        // render menggunakan theme javascript. Subproperty views_key dibutuhkan
        // untuk mengecek multivalue dan cache.
        options.sbadmin2 = {rewrite: {}, views_key: this.views_key}
        for (x in this.settings.rewrite) {
            // Masukkan di options.
            var column = this.settings.rewrite[x].column;
            options.sbadmin2.rewrite[column] = {
                theme: this.settings.rewrite[x].theme,
                options: this.settings.rewrite[x].options
            };
            var columnDefs = {
                // Property targets bisa array, bisa juga integer. Kita pilih array.
                targets: [column],
                render: function (data, type, row, meta) {
                    var init = meta.settings.oInit
                    if (init.sbadmin2 && init.sbadmin2.rewrite && init.sbadmin2.rewrite[meta.col]) {
                        // Jika data adalah empty string, cek apakah multivalue.
                        var views = Drupal.settings.sbadmin2.views;
                        var views_key = meta.settings.oInit.sbadmin2.views_key;
                        if (data == '' && views.multivalue && views.multivalue[views_key]
                         && views.multivalue[views_key][meta.row] && views.multivalue[views_key][meta.row][meta.col])
                        {
                             data = Drupal.settings.sbadmin2.views.multivalue[views_key][meta.row][meta.col];
                        }
                        var theme = init.sbadmin2.rewrite[meta.col].theme;
                        var options = init.sbadmin2.rewrite[meta.col].options;
                        if (typeof Drupal.theme.prototype[theme] == 'function' || typeof Drupal.theme[theme] == 'function') {
                            return Drupal.theme(theme, data, options, 'datatables', type, row, meta);
                        }
                    }
                    return data;
                }
            };
            // Additional ColumnDefs from form interface in views.
            if (this.settings.rewrite[x].options.columnDefs) {
                columnDefs = $.extend(true, columnDefs, this.settings.rewrite[x].options.columnDefs);
            }
            // Merge.
            options.columnDefs.push(columnDefs);
        }
    }

    // Jalankan Datatables dan pastikan Drupal JS behaviour tereksekusi
    // pada saat event init dan redraw agar module dapat mengubah tampilan
    // element table.
    var that = this;

    this.$dataTable = this.$table.on('init.dt', function () {
        Drupal.attachBehaviors(this, that.settings);
    }).DataTable(options).on('draw.dt', function () {
        Drupal.attachBehaviors(this, that.settings);
    });
}

})(jQuery);
