# Generate first-level menu

This code generates only the first menu level. Conveniently, for example for output to a footer.

```php
$menu_tree_data = menu_tree('main-menu');
$menu = drupal_render($menu_tree_data);
```


### Example

template.php file of theme.

```php
/**
 * Implements hook_preprocess_region().2
 * @param $variables
 */
function THEMENAME_preprocess_region(&$variables) {
  if ($variables['elements']['#region'] == 'footer') {
    $menu_tree_data = menu_tree('main-menu');
    // Add $menu variable to our region template.
    $variables['menu'] = drupal_render($menu_tree_data);
  }
}

```

region--footer.tpl.php

```php
<?php
/**
 * @file
 * Footer region template.
 */
?>
<?php if ($content): ?>
  <footer id="footer" class="footer" role="contentinfo">
    <?php print $menu; ?>
    <div class="blocks">
      <?php print $content; ?>
    </div>
  </footer>
<?php endif; ?>

```

Result

[Result](http://i.imgur.com/VkGjIYA.png)