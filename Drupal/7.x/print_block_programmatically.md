
Printing content.
```php
// Printing only content of the block.
$block = module_invoke('module_name', 'block_view', 'block_delta');
print $block['content'];
// print $block['subject']; - title
```

Printing full block with contextual links.

```php
$block = block_load('MODULE_NAME', 'BLOCK_DELTA');
$renderable_array = _block_get_renderable_array(_block_render_blocks(array($block)));
print drupal_render($renderable_array);
```
