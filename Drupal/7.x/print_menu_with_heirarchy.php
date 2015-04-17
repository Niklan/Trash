<?php
/**
 * @file
 * Print menu with hierarchy.
 * Warning! Do not put this functions in single line, like:
 * - print render(menu_tree_output(menu_tree_all_data('main-menu')));
 * it cause errors on page, but will working.
 */
$menu_tree_data = menu_tree_all_data('main-menu');
$menu_tree_output = menu_tree_output($menu_tree_data);
print render($menu_tree_output);

