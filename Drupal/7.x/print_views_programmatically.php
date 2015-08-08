<?php
/**
 * Examples how prints views programmatically.
 */

/**
 * @example 1
 * Simple way, just print it.
 */
print views_embed_view('view_name', 'display_name');

/**
 * @example 2
 * This more complex, but we can check result for empty result.
 */
$view = views_get_view('view_name');
$view->set_display('display_name');
$output = $view->preview();
// If view has result.
if ($view->result) {
  return $output;
}
