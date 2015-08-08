<?php
/**
 * Example how you can print blocks in Drupal 7 programmatically.
 */

// Printing only content of the block.
$block = module_invoke('module_name', 'block_view', 'block_delta');
print $block['content'];
// print $block['subject']; - title
