(function ($) {
Drupal.behaviors.sbadmin2managedfile = {
  attach: function (context, settings) {
    $('input.sbadmin2-managed-file[type=file]', context).once('sbadmin2-managed-file',function () {
        var $parent = $(this).parents('.input-group');
        var $upload = $parent.find('.sbadmin2-upload-button');
        var $browse = $parent.find('.sbadmin2-browse-button');
        var $info = $parent.find('.sbadmin2-info-text');
        new Drupal.sbadmin2managedfile(this, $upload, $browse, $info);
    })
  }
};

Drupal.sbadmin2managedfile = function (input, upload, browse, info) {
    this.input = $(input);
    this.uploadButton = upload;
    this.browseButton = browse;
    this.info = info;
    var that = this
    this.browseButton.on('click', function (e) {
        that.input.click();
        e.preventDefault();
    })
    this.input.on('change', function (e) {
        // Javascript `file.js` lebih dahulu mengeksekusi `onchange` daripada
        // kita, sehingga:
        // jika nilai this.value == '', berarti `file.js` menganggap input user
        // tidak valid.
        var valx = this.value;
        console.log(valx);
        if (! this.value == '') {
            // Reference: https://stackoverflow.com/a/18427347
            that.uploadButton.show().parent().append(that.uploadButton);
            // that.browseButton.hide();
            that.info.val(this.value.replace('C:\\fakepath\\', ''));
        }
        else {
            that.info.val('')
            that.uploadButton.hide();
            that.browseButton.show();
        }
        // console.log($(this));
        // console.log(this.value);
        // this.css('opacity', 100)
    });
    // console.log(this);
}
})(jQuery);
