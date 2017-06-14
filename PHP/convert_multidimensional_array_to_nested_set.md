# PHP: Convert multidimensional array to nested set array

[Nested set model on wikipedia.](https://en.wikipedia.org/wiki/Nested_set_model)

This code sort multidimensional array to new array with nested set, also set left, right and depth keys.

![Example](https://upload.wikimedia.org/wikipedia/commons/thumb/4/41/NestedSetModel.svg/701px-NestedSetModel.svg.png)

The result must be:

| Node          | Left | Right  | Depth |
|---------------|------|--------|-------|
|Clothing       | 1    | 22     | 0     |
|Men's          | 2    | 9      | 1     |
|Women's        | 10   | 21     | 1     |
|Suits          | 3    | 8      | 2     |
|Slacks         | 4    | 5      | 3     |
|Jackets        | 6    | 7      | 3     |
|Dresses        | 11   | 16     | 2     |
|Skirts         | 17   | 18     | 2     |
|Blouses        | 19   | 20     | 2     |
|Evening Gowns  | 12   | 13     | 3     |
|Sun Dresses    | 14   | 15     | 3     |

## Function

```php
function convert_to_nested_tree($items, &$left = 1, $depth = 0) {
  if (count($items) > 0) {
    foreach ($items as &$item) {
      $item['depth'] = $depth;
      $item['left'] = $left++;
      if (count($item['children']) > 0) {
        $item['children'] = convert_to_nested_tree($item['children'], $left, $depth + 1);
      }
      $item['right'] = $left++;
    }
  }
  return $items;
}
```

### Example of usage

```php
$items = array(
  array(
    'name' => 'clothing',
    'children' => array(
      array(
        'name' => 'Men\'s',
        'children' => array(
          array(
            'name' => 'Suits',
            'children' => array(
              array(
                'name' => 'Slacks',
              ),
              array(
                'name' => 'Jackets',
              ),
            ),
          ),
        ),
      ),
      array(
        'name' => 'Women\'s',
        'children' => array(
          array(
            'name' => 'Dresses',
            'children' => array(
              array(
                'name' => 'Evening gowns',
              ),
              array(
                'name' => 'Sun dresses',
              ),
            ),
          ),
          array(
            'name' => 'Skirts',
          ),
          array(
            'name' => 'Blouses',
          ),
        ),
      ),
    ),
  ),
);
$result = convert_to_nested_tree($items);
```

![Result](http://i.imgur.com/u9yPxxE.png)