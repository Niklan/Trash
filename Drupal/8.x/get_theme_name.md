# Get theme name

## Example 1

This method returns diffirent theme nemes depends on where you are.
F.e. on node page it can show `bartik`, but on admin sections is `seven`.

So - this code returns current theme for current page.

~~~php
$theme = \Drupal::theme()->getActiveTheme()->getName();
~~~

## Example 2

This example returns current active theme selected as default for site.

~~~php
$theme = \Drupal::config('system.theme')->get('default');
~~~
