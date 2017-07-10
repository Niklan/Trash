# Print block programmatically

## Content blocks

This block are created via default Drupal core block system.

Block id is integer value from database. `block_content:dae619eb-d5f5-4804-8534-6b520a4a1815` — this **is not** block id. The fastes way to find block id, is to navigate to `/admin/structure/block/block-content` and look at the URL of needed block.

```php
$block = \Drupal\block_content\Entity\BlockContent::load('BLOCK_ID');
$block_array = \Drupal::entityTypeManager()->getViewBuilder('block_content')->view($block);
```

## Plugin blocks

Those kind of block are defined in the modules via Plugin API system.

```php
$block_manager = \Drupal::service('plugin.manager.block');
$block_plugin = $block_manager->createInstance('BLOCK_ID', []);
$block_array = $plugin_block->build();
```

Some blocks might have require some access or cache information, you can pass them via methods and call directly.

```php
$block_access = $plugin_block->access(\Drupal::currentUser());
$cache_contexts = $plugin_block->getCacheContexts();
$cache_tags = $plugin_block->getCacheTags();
```