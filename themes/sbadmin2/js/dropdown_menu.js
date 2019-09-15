(function ($) {
Drupal.behaviors.sbadmin2DropDownMenu = {
    attach: function (context, settings) {
        $('.dropdown-toggle + .dropdown-menu + input', context).once('dropdown-menu', function () {
            new Drupal.sbadmin2DropDownMenu(this, $(this).prev()[0], $(this).prev().prev()[0]);
        });
    }
};

Drupal.sbadmin2DropDownMenu = function (input, menu, button) {
    this.input = input;
    this.menu = menu;
    this.button = button;
    var that = this;
    $(this.menu).find('a').click(function (event) {
        var value = $(this).data('value');
        var label = $(this).text() + ' <span class="caret"></span>';
        $(that.button).html(label);
        $(that.input).val(value).change();
        event.preventDefault();
    });
}
})(jQuery);
