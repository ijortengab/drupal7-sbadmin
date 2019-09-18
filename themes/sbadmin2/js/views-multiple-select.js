(function ($) {

Drupal.behaviors.sbadmin2ViewsMultipleSelect = {
    attach: function (context, settings) {
        $('.views-multiple-select', context).once('dropdown-menu', function () {
            new Drupal.sbadmin2ViewsMultipleSelect(this, $(this).parents('.views-exposed-widget')[0]);
        });
    }
};

Drupal.sbadmin2ViewsMultipleSelect = function (a, container) {
    this.container = container
    this.a = a
    // Ciri khas theme button_group_input adalah attribute dibawah ini.
    this.widget = $(container).find('[data-toggle="buttons"]')[0];
    this.$inputs = $(this.widget).find('input');
    this.bulkToggle = $(this.container).find('.bulk-toggle')[0];
    this.bulkToggleContainer = $(this.bulkToggle).parent()[0];
    this.isMultiple = false;
    this.checkAll = false;
    this.currentSingleChecked;
    var name = this.$inputs.attr('name');
    if (name.substr(-2) == '[]') {
        name = name.replace( /.{2}$/g, "");
    }
    this.key = window.location.pathname + '-is-views-multiple-select-' + name;
    // Mulai listen event.
    var that = this;
    $(this.a).click(function (e) {
        e.preventDefault();
        that.isMultiple = !(that.isMultiple);
        $(that.bulkToggleContainer).toggle(300);
        that.modifyAnchorChecklist();
        that.save();
        // Jika masih ada yang checked, clear all.
        if (!that.isMultiple && that.$inputs.filter(':checked').length > 1) {
            that.$inputs.prop("checked", false);
            that.$inputs.parent().removeClass('active');
        }
        // Sesuaikan checklist.
        if (that.isMultiple) {
            that.modifyInputChecklist();
        }
        else {
            that.$inputs.parent().find('> i').remove();
        }
    });
    this.$inputs.change(function () {
        if (!that.isMultiple && this != that.currentSingleChecked) {
            // Clear semua dulu, kadang ter-set via URL.
            that.$inputs.prop("checked", false);
            //
            this.checked = true;
            // Efek click dihilangkan.
            that.$inputs.filter(':not(:checked)').parent().removeClass('active');
            // Simpan current element.
            that.currentSingleChecked = this;
        }
        if (that.isMultiple) {
            that.modifyInputChecklist(this);
        }
    });
    $(this.bulkToggleContainer).click(function (e) {
        that.checkAll = !(that.checkAll)
        if (that.checkAll) {
            // Checklist semua.
            that.$inputs.prop('checked', true).change();
            that.$inputs.parent().addClass('active');
        }
        else {
            that.$inputs.prop('checked', false).change();
            that.$inputs.parent().removeClass('active');
        }
        that.modifyBulkChecklist();
    });
    // Jika page datang dengan query yang sudah multivalue, maka set sebagai
    // multivalue ignore state storage.
    var isMultiple = window.localStorage.getItem(this.key);
    if (this.$inputs.filter(':checked').length > 1) {
        this.isMultiple = true;
        this.modifyAnchorChecklist();
        this.save();
    }
    else if (isMultiple == 0) {
        this.isMultiple = false;
        this.modifyAnchorChecklist();
    }
    else if (isMultiple == 1) {
        this.isMultiple = true;
        this.modifyAnchorChecklist();
    }
    else {
        this.modifyAnchorChecklist();
    }
    // Jika page datang dengan query yang hanya satu value, sementara
    // state memang tidak multiple select, maka taro element tersebut
    // pada property.
    if (!this.isMultiple && this.$inputs.filter(':checked').length == 1) {
        this.currentSingleChecked = this.$inputs.filter(':checked')[0];
    }
    // Mainkan bulkToggle.
    if (this.isMultiple) {
        $(this.bulkToggle).show()
    }
    else {
        $(this.bulkToggle).css('display', 'none');
    }
    // Mainkan checklist pada input.
    this.modifyInputChecklist();
}

Drupal.sbadmin2ViewsMultipleSelect.prototype.save = function () {
    window.localStorage.setItem(this.key, (this.isMultiple ? 1 : 0));
}

Drupal.sbadmin2ViewsMultipleSelect.prototype.modifyAnchorChecklist = function () {
    var text = $(this.a).text();
    if (!this.isMultiple) {
        $(this.a).html(Drupal.theme('icon','square-o') + ' ' + text);
    }
    else {
        $(this.a).html(Drupal.theme('icon','check-square-o') + ' ' + text);
    }
}

Drupal.sbadmin2ViewsMultipleSelect.prototype.modifyBulkChecklist = function () {
    if (this.checkAll) {
        $(this.bulkToggle).html(Drupal.theme('icon','check-square-o'));
    }
    else {
        $(this.bulkToggle).html(Drupal.theme('icon','square-o'));
    }
}

Drupal.sbadmin2ViewsMultipleSelect.prototype.modifyInputChecklist = function (element) {
    if (this.isMultiple) {
        if (typeof element == 'undefined') {
            var $element = this.$inputs;
        }
        else {
            var $element = $(element);
        }
        $element.filter(':not(:checked)').parent().each(function () {
            // Clear dulu.
            $(this).find('> i').remove();
            $(Drupal.theme('icon','square-o')).prependTo(this);
        });
        $element.filter(':checked').parent().each(function () {
            // Clear dulu.
            $(this).find('> i').remove();
            $(Drupal.theme('icon','check-square-o')).prependTo(this);
        });
    }
}
})(jQuery);
