 # Drupal 8 get page title programmatically.


```php
$request = \Drupal::request();
$route_match = \Drupal::routeMatch();
$title = \Drupal::service('title_resolver')->getTitle($request, $route_match->getRouteObject());
```