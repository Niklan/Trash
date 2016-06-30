# Remove system page title, breadcrumbs and tabs for feature Panels use.

Sometimes you want to present full page via panels with all elements like page title, breadcrumbs and tabs for users. But they will duplicate with original from page.tpl.php, if you need them on some page, and do not want to create template file for each page where it's needed, there is easy way to do it.

This code can be written in module and template.php file.

~~~php
/**
 * Implements hook_preprocess_page().
 */
function THEMENAME_preprocess_page(&$variables) {
  if ($page_display = panels_get_current_page_display()) {
    switch ($page_display->uuid) {
      // Your UUID will be different, print them to discover them.
      case 'ab7fbeba-0503-4857-bfab-23f2a29bc383': // Catalog page
      case 'c5086b45-a761-4e10-b68f-fbdbfebf58e1': // Frontpage
        // Your variables may be different correspond to base theme.
        $variables['breadcrumb'] = FALSE;
        $variables['tabs'] = FALSE;
        $variables['title'] = FALSE;
    }
  }
}
~~~

Don't forget in your page.tpl.php wrap this variables with condition. F.e.

~~~php
<?php if ($breadcrumb): ?>
  <?php print $breadcrumb; ?>
<?php endif; ?>
<?php print render($title_prefix); ?>
<?php if ($title): ?>
  <h1 id="page-title"><?php print $title; ?></h1>
<?php endif; ?>
<?php print render($title_suffix); ?>
<?php if ($tabs): ?>
  <?php print render($tabs); ?>
<?php endif; ?>
~~~
