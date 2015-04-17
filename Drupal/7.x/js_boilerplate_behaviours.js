(function ($, Drupal, window, document, undefined) {

    Drupal.behaviors = {
        attach: function (context, settings) {
            // Category selector on forum.
            $('.forum-category-select', context).on('click', function () {
                $('.forum-category-select', context).removeClass('opened');
                $(this, context).toggleClass('opened');
            });

            // Hide divs if clicked outside needed div.
            $(document).mouseup(function (e) {
                var container = $('.forum-category-select', context);

                if (!container.is(e.target) && container.has(e.target).length === 0) {
                    $(container).removeClass('opened');
                }
            });
        }
    };

})(jQuery, Drupal, this, this.document);

