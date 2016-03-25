# Programmatically adding field in header\footer of views.

~~~php
/**
 * Implements hook_views_pre_view().
 */
function HOOK_views_pre_view(&$view, &$display_id, &$args) {
  if ($view->name == 'VIEW_NAME' && $display_id == 'DISPLAY_ID_NAME') {
    // Add to header.
    // 'header1' must be unique for each item.
    $view->add_item($display_id, 'header', 'views', 'header1', array(
      'content' => 'Header content',
      'format' => 'full_html'
    ));
    // Add to footer
    $view->add_item($display_id, 'footer', 'views', 'footer1', array(
      'content' => 'Footer content',
      'format' => 'full_html'
    ));
  }
}
~~~