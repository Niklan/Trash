<?php
/**
 * Example how you can print blocks in Drupal 7 programmatically.
 */

// Printing only content of the block.
$block = module_invoke('module_name', 'block_view', 'block_delta');
print render($block['content']);

// Printing subject and content.
$block = module_invoke('block', 'block', 'view', 1);
print $block['subject'];
print $block['content'];

