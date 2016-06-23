# CTools modal centering.

~~~javascript
Drupal.behaviors.ctools_modal_fix_centering = {
  attach: function (context, settings) {
    var modal = $('#modalContent', context);

    function centering() {
      var modal_width = modal.width(),
        modal_height = modal.height(),
        win_width = $(window).width(),
        win_height = $(window).height(),
        pos_left = Math.max(40, parseInt(win_width / 2 - modal_width / 2)),
        pos_top = Math.max(40, parseInt(win_height / 2 - modal_height / 2));

      modal.css({
        'left': pos_left,
        'top': pos_top
      });
      if (win_height < modal_height) {
        modal.css({'position': 'absolute'});
      }
      else {
        modal.css({'position': 'fixed'});
      }
    }

    centering();
    $(window).resize(function () {
      centering();
    });
    modal.resize(function () {
      centering();
    });
  }
};
~~~
