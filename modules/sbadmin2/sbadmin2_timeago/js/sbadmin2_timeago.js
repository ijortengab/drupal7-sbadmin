(function ($) {

/**
 * Theme timeago.
 */
Drupal.theme.prototype.timeago = function (datetime) {
    return '<time data-trigger="hover" data-toggle="tooltip" title="'+datetime[1]+'" class="timeago" datetime='+datetime[0]+'>'+datetime[1]+'</time>'
}
})(jQuery);
