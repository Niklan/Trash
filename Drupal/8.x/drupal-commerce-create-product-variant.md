# Drupal Commerce 2 create product programmatically

## Example 1

```php
$price = new \Drupal\commerce_price\Price('117', 'RUB');
$variant = ProductVariation::create([
  'type' => 'led_light',
  'sku' => 'test',
  'status' => 1,
  'price' => $price,
]);
```
