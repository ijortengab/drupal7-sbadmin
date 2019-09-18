(function ($) {

Drupal.behaviors.sbadmin2ViewsToggleOperator = {
    attach: function (context, settings) {
        $('.views-toggle-operator', context).once('dropdown-menu', function () {
            new Drupal.sbadmin2ViewsToggleOperator(this, $(this).parents('.views-exposed-widget')[0]);
        });
    }
};

Drupal.sbadmin2ViewsToggleOperator = function (a, container) {
    this.container = container
    this.a = a
    this.operator = $(container).find('.views-operator').parent()[0];
    // this.isHide = $(this.operator).is(':hidden');
    // Otherwise hide. Use css rather than hide() because hide()
    // does not work if the item is already hidden, for example,
    // in a collapsed fieldset.
    // Class `.element-hidden` ini bikin rusak tampilan.
    this.isHide = ($(this.operator).css('display') == 'none');
    // Meski efek hidden teroverride oleh `toggle()` tetap perlu di remove.
    if ($(this.operator).hasClass('element-hidden')) {
        $(this.operator).hide();
        $(this.operator).removeClass('element-hidden');
    }
    var that = this;
    $(this.a).click(function (e) {
        $(that.operator).toggle(300, function () {
            that.save();
            that.modifyChecklist();
        });
        e.preventDefault();
    });
    var name = $(this.operator).find('input').attr('name');
    this.key = window.location.pathname + '-is-views-operator-hidden-' + name;
    var isHide = window.localStorage.getItem(this.key);
    if (isHide == 0) {
        $(this.operator).show(0);
    }
    else if (isHide == 1) {
        // Otherwise hide. Use css rather than hide() because hide()
        // does not work if the item is already hidden, for example,
        // in a collapsed fieldset.
        $(this.operator).css('display', 'none');
    }
    this.modifyChecklist();
}

Drupal.sbadmin2ViewsToggleOperator.prototype.save = function () {
    window.localStorage.setItem(this.key, ($(this.operator).is(':hidden') ? 1 : 0));
}

Drupal.sbadmin2ViewsToggleOperator.prototype.modifyChecklist = function () {
    var text = $(this.a).text();
    // Otherwise hide. Use css rather than hide() because hide()
    // does not work if the item is already hidden, for example,
    // in a collapsed fieldset.
    if ($(this.operator).css('display') == 'none') {
        $(this.a).html(Drupal.theme('icon','square-o') + ' ' + text);
    }
    else {
        $(this.a).html(Drupal.theme('icon','check-square-o') + ' ' + text);
    }
}

})(jQuery);
