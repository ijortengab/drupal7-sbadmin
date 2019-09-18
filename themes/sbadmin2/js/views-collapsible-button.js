/**
 * @see: https://getbootstrap.com/docs/3.3/javascript/#collapse-events
 */
(function ($) {

Drupal.behaviors.sbadmin2ViewsCollapsibleButton = {
    attach: function (context, settings) {
        $('.views-collapsible-button .btn', context).once('views-collapsible-button', function () {
            var target = $(this).data('target');
            new Drupal.sbadmin2ViewsCollapsibleButton($(target, context));
        });
    }
};

Drupal.sbadmin2ViewsCollapsibleButton = function ($target) {
    this.$target = $target;
    var id = this.$target.attr('id');
    var that = this;
    this.key = window.location.pathname + '-is-collapse-' + id;
    this.isHide = $(this.$target).is(':hidden');
    this.$target.on('hide.bs.collapse', function () {
        that.isHide = !(that.isHide);
    });
    this.$target.on('show.bs.collapse', function () {
        that.isHide = !(that.isHide);
    });
    this.$target.on('hidden.bs.collapse', function () {
        that.save();
    });
    this.$target.on('shown.bs.collapse', function () {
        that.save();
    });
    var isCollapse = window.localStorage.getItem(this.key);
    if (isCollapse == 0) {
        this.$target.addClass('in');
        this.isHide = false;
    }
    else {
        this.$target.removeClass('in');
        this.isHide = true;
    }
}

Drupal.sbadmin2ViewsCollapsibleButton.prototype.save = function () {
    window.localStorage.setItem(this.key, (this.isHide ? 1 : 0));
}
})(jQuery);
