(function ($) {

/**
 * Support behaviours untuk mendukung output dari theme `bootstrap_links`
 * agar hasil bisa satu baris tanpa break seperti nowrap pada CSS.
 */
Drupal.behaviors.bootstrapLinksNoWrap = {
    attach: function (context, settings) {
        $('.btn-group', context).once('btn-group-nowrap', function () {
            var width = 0;
            var $childs = $(this).find(" > .btn").each(function () {
                width += $(this).outerWidth();
            });
            $(this).css('min-width', width)
        });
    }
};

Drupal.theme.prototype.empty_string = function () {
    return '';
}

Drupal.theme.prototype.stronger = function (data) {
    return '<strong>' + data + '</strong>';
}

Drupal.theme.prototype.random = function () {
    var data = arguments[0] ? arguments[0] : '';
    var options = arguments[1] ? arguments[1] : null;
    options = options || {}
    if (options.words) {
        var words = options.words || {};
        var array = [];
        for(key in words) {
            if(words.hasOwnProperty(key)){
                array.push(words[key]);
            }
        }
        if (array.length > 0) {
            return array[Math.floor(Math.random()*array.length)];
        }
    }
    return data;
}

/**
 *
 * @todo, icon atau icon+text didalam button.
 * @todo support separator, dan header.
 */
Drupal.theme.prototype.bootstrap_links = function () {
    // Play cache first.
    if (arguments[2] && arguments[2] == 'datatables') {
        var cid = arguments[5].settings.oInit.sbadmin2.views_key + '-' + arguments[5].col.toString() + '-' + arguments[5].row.toString();
        var cache = Drupal.themejs.cache.get(cid);
        if (cache !== null) {
            return cache;
        }
    }
    var data = arguments[0] ? arguments[0] : '';
    var options = arguments[1] ? arguments[1] : null;
    // Membutuhkan array.
    if (!$.isArray(data)) {
        return data;
    }
    // Define options.
    var options = options || {}

    options.arrow_position = options.hasOwnProperty('arrow_position') ? options.arrow_position : 1;
    options.split = options.hasOwnProperty('split') ? options.split : 1;
    options.colorize = options.colorize || 'default';
    options.alignment = options.alignment || 'right';
    // @todo, support vertically stacked, support dropup.
    options.stacked = options.stacked || 'horizontally'; // vertically , horizontally.

    // Helper variable.
    var wrapperElement = Drupal.themejs.defaultElement();
    var visibleBag = []
    var hiddenBag = []
    var insertTo = 'visibleBag';
    var splitButtonDropdowns = (options.split == 1);
    var hasButtonDropdowns = false;
    var size = null;
    switch (options.size) {
        case 'lg':
        case 'sm':
        case 'xs':
            size = 'btn-' + options.size;
            break;
    }

    // Validate.
    if (options.arrow_position >= data.length) {
        splitButtonDropdowns = false;
    }

    for (x in data) {
        // Seperti informasi yang dijelaskan pada constant
        // `sbadmin2_helper_handler_field_ctools_dropdown::order`,
        // urutan dari array tiap-tiap links adalah informasi sebagai berikut:
        // $order = ['title', 'href', 'fragment', 'query', 'absolute', 'alias', 'prefix'];
        // jika href = *, maka itu berarti header
        // jika title = '-' dan href = *, maka itu berarti separator.
        var title = (data[x][0]) ? data[x][0] : "";
        var href = (data[x][1]) ? data[x][1] : null;
        var fragment = (data[x][2]) ? data[x][2] : null;
        var query = (data[x][3]) ? data[x][3] : null;
        var absolute = (data[x][4]) ? data[x][4] : null;
        var alias = (data[x][5]) ? data[x][5] : null;
        var prefix = (data[x][6]) ? data[x][6] : null;
        var elements = Drupal.themejs.defaultElement();
        switch (insertTo) {
            case 'visibleBag':
                elements[0] = (href) ? "a" : "button";
                if (href) {
                    elements[1].role = 'button';
                    elements[1].href = Drupal.themejs.url(href, {query: query, fragment: fragment});
                }
                elements[1].class.push('btn');
                elements[1].class.push('btn-'+options.colorize);
                if (size) {
                    elements[1].class.push(size);
                }
                elements[2] = title;
                visibleBag.push(elements);
                break;
            case 'hiddenBag':
                elements[0] = "a";
                if (href) {
                    elements[1].href = Drupal.themejs.url(href, {query: query, fragment: fragment});
                }
                elements[2] = title;
                hiddenBag.push(elements);
                break;
        }

        // Next.
        if (splitButtonDropdowns && x == (options.arrow_position - 1)) {
            var elements = Drupal.themejs.defaultElement();
            elements[0] = "button";
            elements[1].class.push('btn');
            elements[1].class.push('btn-'+options.colorize);
            if (size) {
                elements[1].class.push(size);
            }
            elements[1].class.push('dropdown-toggle');
            elements[1].attributes.push(['data-toggle', 'dropdown']);
            elements[1].attributes.push(['aria-haspopup', 'true']);
            elements[1].attributes.push(['aria-expanded', 'false']);
            elements[2] = [['span',{class:['caret']},null],['span',{class:['sr-only']},'Toggle Dropdown']];
            visibleBag.push(elements);
            // Modify flag variable.
            splitButtonDropdowns = false;
            hasButtonDropdowns = true;
            // Next insert is to hidden bag.
            insertTo = 'hiddenBag';
        }
        if (!hasButtonDropdowns) {
            if (x == options.arrow_position) {
                elements[1].class.push('dropdown-toggle');
                elements[1].attributes.push(['data-toggle', 'dropdown']);
                // Convert from string to array of elements.
                elements[2] = [elements[2] + ' ', ['span',{class:['caret']},null]]
                hasButtonDropdowns = false;
                // Next insert is to hidden bag.
                insertTo = 'hiddenBag';
            }
        }
    }
    // Finishing.
    wrapperElement[0] = 'div';
    wrapperElement[1].class.push('btn-group');
    for (x in visibleBag) {
        wrapperElement[2].push(visibleBag[x]);
    }
    if (hiddenBag.length) {
        var ulElement = ['ul',{class: ['dropdown-menu']},[]];
        if (options.alignment == 'right') {
            ulElement[1].class.push('dropdown-menu-right');
        }
        for (x in hiddenBag) {
            var liElement = ['li',{},[]];
            liElement[2].push(hiddenBag[x]);
            ulElement[2].push(liElement);
        }
        wrapperElement[2].push(ulElement);
    }
    var render = Drupal.themejs.renderElement(wrapperElement);
    if (arguments[2] && arguments[2] == 'datatables') {
        Drupal.themejs.cache.set(cid, render);
    }
    return render;
}

})(jQuery);
