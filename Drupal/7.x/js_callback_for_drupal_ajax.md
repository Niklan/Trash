# Callback after Drupal AJAX complete.

~~~js
/**
 * @file
 * Action page actions.
 */
"use strict";
(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.NAME = {
    attach: function (context, settings) {
      // Save original.
      var ajaxSuccess = Drupal.ajax.prototype.success;
      // Rewrite original by own.
      Drupal.ajax.prototype.success = function(response, status) {
        // Call original callback before own code.
        ajaxSuccess.call(response, status);
        // Your code after AJAX complete.
      }
    }
  };

})(jQuery, Drupal, this, this.document);
~~~
