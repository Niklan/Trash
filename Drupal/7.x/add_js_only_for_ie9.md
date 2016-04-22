# Adding JavaScript code only for InternetExplorer 9

~~~php
// Attach script only of IE 9.
$ie_script =  array(
  '#browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE),
  '#tag' => 'script',
  '#attributes' => array(
    'type' => "text/javascript",
  ),
  '#value' => '$(document).ready(function () { console.log('This is IE9'); });',
  '#pre_render' => array('drupal_pre_render_conditional_comments'),
  '#weight' =>  999,
);
drupal_add_html_head($ie_script, 'bottom_subscribe_form_placeholder');
~~~
