(function ($) {

Drupal.sbadmin2 = Drupal.sbadmin2 || {};

Drupal.sbadmin2.parseAutocompleteValue = function (i) {
    // Hapus double quote yang mungkin ada, jika terdapat karakter comma atau
    // kurung.
    i = i.replace(/^"/,'');
    i = i.replace(/"$/,'');
    var myRegexp = /^(.*)\s\((\d+)\)$/g;
    var match = myRegexp.exec(i)
    var result = []
    if (match && match.length == 3) {
        return {id: match[0], text: match[1]}
    }
}

Drupal.behaviors.sbadmin2select2 = {
  attach: function (context, settings) {
    $('select.sbadmin2-select2', context).once('sbadmin2-select2', function () {
        // Clone as new object.
        var options = $.extend(true, {}, settings.sbadmin2.defaultOptions);
        if (typeof settings.sbadmin2.element[this.id] !== 'undefined') {
            var id = this.id;
            if (typeof settings.sbadmin2.element[id].route !== 'undefined') {
                var frontController = settings.sbadmin2.element[id].frontController;
                var route = settings.sbadmin2.element[id].route;
                options.ajax = {
                    url: settings.basePath + frontController,
                    dataType: 'json',
                    data: function (params) {
                        var query = {q: route + '/' + params.term}
                        return query;
                    },
                    processResults: function (data) {
                        var obj = {results: []}
                        for (i in data){
                            var result = Drupal.sbadmin2.parseAutocompleteValue(i)
                            if (typeof result == 'object') {
                                obj.results.push({id: result.id, text: result.text})
                            }
                            else {
                                // Jika gagal parse, akan bernilai undefined.
                                obj.results.push({id: i, text: data[i]})
                            }
                        }
                        return obj;
                    }
                }
            }
            // Merge.
            if (typeof settings.sbadmin2.element[id].defaultOptions !== 'undefined') {
                options = $.extend(options, settings.sbadmin2.element[id].defaultOptions);
            }
            // Run select2.
            $(this).select2(options);

            // Tambah default value jika form rebuild karena (salahsatunya) error.
            if (typeof settings.sbadmin2.element[this.id] !== 'undefined' && typeof settings.sbadmin2.element[id].defaultValue !== 'undefined') {
                var id = this.id;
                var result = Drupal.sbadmin2.parseAutocompleteValue(settings.sbadmin2.element[id].defaultValue)
                if (typeof result == 'object') {
                    var newOption = new Option(result.text, result.id, false, false);
                    $(this).append(newOption).trigger('change');
                }
            }
        }
    });
  }
};
})(jQuery);
