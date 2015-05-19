<?php
/**
 * @file 
 * Examples and snippets for hook_menu().
 */

/**
 * @example #1
 * Implements hook_menu().
 * This hook adds group TITLE on configuration page.
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

/**
 * @example #2
 * Implements hook_menu().
 * This example adds menu group in toolbar (admin_menu).
 */
function MYMODULE_menu() {
  $items['admin/NAME'] = array(
    'title' => 'TITLE',
    'weight' => 0, // Greater moves to right, lower to the left.
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('access administration pages'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
    'position' => 'right',
  );

  return $items;
}
