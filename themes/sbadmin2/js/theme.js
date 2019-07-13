(function ($) {

Drupal.behaviors.bootstrapButtonDropdowns = {
    attach: function (context, settings) {
        $('a.btn + button.btn', context).once('bootstrap-button-dropdowns', function() {
            var $button = $(this);
            var $a = $button.prev();
            // Lihat jarak ke atas layar, sama apakah tidak
            var buttonDistanceToTop = Math.round($button.offset().top);
            var aDistanceToTop = Math.round($a.offset().top);
            if (buttonDistanceToTop != aDistanceToTop) {
                var buttonWidth = $button.outerWidth();
                var aWidth = $a.outerWidth();
                var total = buttonWidth + aWidth;
                $button.parent().css('min-width', total);
            }
        });
    }
};

/**
 * theme_links javascript version.
 * @todo: sort by weight.
 */
Drupal.theme.prototype.bootstrapLinks = function (_variables, _replacement) {
    // Clone as new object.
    var variables = $.extend(true,{},_variables);
    // Default property.
    variables.links = variables.links || [];
    // Default function.
    var setAttribute = function (jQueryObject, AttributeObject) {
        var attributes = {};
        $.each(AttributeObject, function (key, value) {
            switch (key) {
                case 'class':
                    var _value = [];
                    $.each(value, function (k, v) {
                        _value.push(v);
                    })
                    value = _value.join(' ');
                    attributes[key] = value;
                    break;

                case 'other':
                    $.each(value, function (k, v) {
                        jQueryObject.attr(v[0], v[1]);
                    })
                    break;

                default:
                    attributes[key] = value;
                    break;
            }
        });
        jQueryObject.attr(attributes);
    }
    // Helper variable.
    var elementVisible = []
    var elementHidden = []
    var indexCaret = 0
    var insertTo = 'visible';
    // Populate
    $.each(variables.links, function (key, value) {
        // Default.
        value.defaultAttributes = {}
        value.defaultAttributes.class = {}
        value.defaultAttributes.other = []
        if (!value.type) {
            value.type = 'link'
        }
        switch (insertTo) {
            case 'visible':
                value.defaultAttributes.class.btn = 'btn';
                elementVisible.push(variables.links[key])
                if (value.type == 'toggle') {
                    value.defaultAttributes.other.push(['data-toggle', 'dropdown'])
                    value.defaultAttributes.class.dropdownToggle = 'dropdown-toggle';
                    // For next.
                    insertTo = 'hidden';
                    indexCaret = elementVisible.length - 1
                }
                break;

            case 'hidden':
                elementHidden.push(variables.links[key])
                break;
        }
    });


    // Wrapper.
    variables.wrapper = variables.wrapper || {}
    variables.wrapper.defaultAttributes = {}
    variables.wrapper.defaultAttributes.class = {}
    if (elementVisible.length > 1) {
        variables.wrapper.defaultAttributes.class.btnGroup = 'btn-group';
    }
    else {
        variables.wrapper.defaultAttributes.class.dropdown = 'dropdown';
    }
    variables.wrapper.attributes = variables.wrapper.attributes || {}
    variables.wrapper.attributes = $.extend(true, variables.wrapper.attributes, variables.wrapper.defaultAttributes)
    var $wrapper = $(document.createElement("div"));
    setAttribute($wrapper, variables.wrapper.attributes)
    // Visible.
    $.each(elementVisible, function (key, value) {
        var nodeElement = value.href ? "a" : "button";
        if (!value.title) {
            value.title = '';
        }
        // Check caret.
        if (elementHidden.length && key == indexCaret) {
            switch (value.type) {
                case 'link':
                    if (value.title) {
                        value.html = true;
                        value.title = value.title + ' <span class="caret"></span>';
                    }
                    break;

                case 'toggle':
                    nodeElement = 'button';
                    value.html = true;
                    value.title = value.title + ' <span class="caret"></span><span class="sr-only">Toggle Dropdown</span>';
                    break;
            }
        }
        // Default Attributes.
        switch (nodeElement) {
            case 'a':
                if (Drupal.urlIsLocal(value.href)) {
                    value.defaultAttributes.href = Drupal.settings.basePath + value.href;
                }
                else {
                    value.defaultAttributes.href = value.href;
                }
                break;

            case 'button':
                break;
        }
        if (!value.colorize) {
            value.colorize = 'default';
        }
        value.defaultAttributes.class.btnColorize = 'btn-' + value.colorize
        var $element = $(document.createElement(nodeElement));
        value.attributes = value.attributes || {}
        value.attributes = $.extend(true, value.attributes, value.defaultAttributes)
        setAttribute($element, value.attributes)
        if (value.html) {
            $element.html(value.title)
        }
        else {
            $element.text(value.title)
        }
        $element.appendTo($wrapper);
    });
    // Hidden Wrapper.
    if (elementHidden.length) {
        var $ulWrapper = $(document.createElement("ul")).addClass('dropdown-menu');
        if (variables.alignment && variables.alignment == 'right') {
            $ulWrapper.addClass('dropdown-menu-right');
        }
        $.each(elementHidden, function (key, value) {
            var $liWrapper = $(document.createElement("li"));
            switch (value.type) {
                case 'header':
                    $liWrapper.addClass('dropdown-header');
                    if (value.title) {
                        $liWrapper.text(value.title);
                    }
                    break;
                case 'separator':
                    $liWrapper.addClass('divider').attr('role', 'separator');
                    break;

                case 'link':
                    var $element = $(document.createElement("a"));
                    if (value.href) {
                        value.defaultAttributes.href = value.href;
                    }
                    value.attributes = value.attributes || {}
                    value.attributes = $.extend(true, value.attributes, value.defaultAttributes)
                    setAttribute($element, value.attributes)
                    if (!value.title) {
                        value.title = '';
                    }
                    if (value.html) {
                        $element.html(value.title)
                    }
                    else {
                        $element.text(value.title)
                    }
                    $element.appendTo($liWrapper)
                    break;
            }
            $liWrapper.appendTo($ulWrapper)
        });
        $ulWrapper.appendTo($wrapper)
    }
    // String.
    var stringify = $wrapper[0].outerHTML;
    $wrapper.remove();
    // Play with replacement.
    if (typeof _replacement == 'string') {
        stringify = Drupal.stringReplace(stringify, {'[data]': _replacement});
    }
    else {
        stringify = Drupal.stringReplace(stringify, _replacement);
    }
    return stringify;
}
})(jQuery);
