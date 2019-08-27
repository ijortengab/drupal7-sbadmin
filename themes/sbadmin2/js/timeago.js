(function ($) {
Drupal.behaviors.sbadmin2Timeago = {
    attach: function (context, settings) {
        var toggleTimeago = function () {
            if (typeof $(this).data('timeagoFactory') == 'undefined') {
                $(this).data('timeagoFactory', timeago());
                $(this).data('timeagoOrigin', this.innerHTML);
                $(this).data('timeagoToggle', false)
            }
            if (!$(this).data('timeagoToggle')) {
                $(this).data('timeagoToggle', true);
                ($(this).data('timeagoFactory')).render(this);
            }
            else {
                $(this).data('timeagoToggle', false);
                timeago.cancel(this);
                this.innerHTML = $(this).data('timeagoOrigin');
            }
        }
        $('time.timeago', context).each(function () {
            $(this).once('sbadmin2-timeago', toggleTimeago).click(toggleTimeago);
        });
    }
};
})(jQuery);
