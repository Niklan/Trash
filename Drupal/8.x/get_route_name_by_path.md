# Get route name by path.


~~~php
\Drupal::service('path.validator')->getUrlIfValid('PATH');
\Drupal::service('path.validator')->getUrlIfValid('node');
\Drupal::service('path.validator')->getUrlIfValid('node/*');
~~~
