 # Remove 'No content for frontpage' and title from frontpage


 ~~~php
 /**
  * Implements hook_preprocess_page().
  */
 function THEMENAME_preprocess_page(&$variables) {
   if (drupal_is_front_page()) {
     // Remove default message.
     unset($variables['page']['content']['system_main']['default_message']);
     // If you want to remove blocks from frontpage. F.e. for Context,
     // uncomment this line and delete upper.
     // unset($variables['page']['content']['system_main']);
     // Remove title.
     drupal_set_title('');
   }
 }
 ~~~
