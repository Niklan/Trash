# Disable caching for development

At first you must uncomment this lines in `settings.php` file. They at the bottom of file.

~~~php
if (file_exists(__DIR__ . '/settings.local.php')) {
  include __DIR__ . '/settings.local.php';
}
~~~

Then you must redirect cache backand to /dev/null

For this you must copy the file `sites/example.settings.local.php` to `sites/default/settings.local.php`:

~~~bash
sudo cp sites/example.settings.local.php sites/default/settings.local.php
~~~

In new file `settings.local.php` uncomment two lines:

~~~php
$settings['cache']['bins']['render'] = 'cache.backend.null';
$settings['cache']['bins']['dynamic_page_cache'] = 'cache.backend.null';
~~~

Then move null backed settings:

~~~bash
sudo cp sites/development.services.yml sites/default/development.services.yml
~~~

## Want theming, but twig caches?

Disable it by editing `development.services.yml` file, by setting change parameters to this:

~~~yml
parameters:
  twig.config:
    debug : true
    auto_reload: true
    cache: false
~~~

## Finish him!

Clear the cache and your done.

~~~bash
drush cr
~~~

or manualy go to `/core/rebuild.php`.


