<?php
/**
 * @file 
 * Example how to create panel (container) in /admin/config page like Users, 
 * Content, System.
 */

/**
 * Implements hook_menu().
 */
function MYMODULE_menu() {
  $items['admin/config/NAME'] = array(
    'title' => 'TITLE',
    'weight' => 0,
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('access administration pages'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
    'position' => 'right', // or left
  );

  return $items;
}
