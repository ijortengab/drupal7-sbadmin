// Dengan drupal behaviours, maka eksekusi tooltip(), akan terus
// berlanjut meski ajax mengganti element.
(function ($) {
Drupal.behaviors.sbadmin2tooltip = {
  attach: function (context, settings) {
    $('[data-toggle="tooltip"]').once('tooltip', function () {
        $(this).tooltip({html:true, trigger: 'hover focus click'})
    });
  }
};
})(jQuery);
