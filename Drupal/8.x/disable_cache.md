# Disable caching for development

# Official way

At first you must uncomment this lines in `settings.php` file. They at the bottom of file.

```php
if (file_exists($app_root . '/' . $site_path . '/settings.local.php')) {
  include $app_root . '/' . $site_path . '/settings.local.php';
}
```

Then you must redirect cache backand to /dev/null

For this you must copy the file `sites/example.settings.local.php` to `sites/default/settings.local.php`:

```sh
sudo cp sites/example.settings.local.php sites/default/settings.local.php
```

In new file `settings.local.php` uncomment two lines:

```php
$settings['cache']['bins']['render'] = 'cache.backend.null';
$settings['cache']['bins']['dynamic_page_cache'] = 'cache.backend.null';
$settings['cache']['bins']['page'] = 'cache.backend.null';
```

Then move null backed settings:

```sh
sudo cp sites/development.services.yml sites/default/development.services.yml
```

## Want theming, but twig caches?

If you don't have `services.yml`:

```sh
sudo cp sites/default/default.services.yml sites/default/services.yml
```

Disable it by editing `services.yml` file, by setting change parameters to this:

```yaml
parameters:
  twig.config:
    debug : true
    auto_reload: true
    cache: false
```

## Finish him!

Clear the cache and your done.

```sh
drush cr
```

or manualy go to `/core/rebuild.php`.

### Example

An example of development.services.yml.

```yaml
# Local development services.
#
# To activate this feature, follow the instructions at the top of the
# 'example.settings.local.php' file, which sits next to this file.
parameters:
  http.response.debug_cacheability_headers: true
  session.storage.options:
    gc_probability: 1,
    gc_divisor: 100,
    gc_maxlifetime: 200000,
    cookie_lifetime: 2000000
  twig.config:
    debug: true,
    auto_reload: true,
    cache: true
  renderer.config:
    required_cache_contexts: ['languages:language_interface', theme, user.permissions], auto_placeholder_conditions: { max-age: 0, contexts: [session, user], tags: {  } } }
  factory.keyvalue: { }
  factory.keyvalue.expirable: { }
  filter_protocols: [http, https, ftp, news, nntp, tel, telnet, mailto, irc, ssh, sftp, webcal, rtsp]
  cors.config: { enabled: false, allowedHeaders: {  }, allowedMethods: {  }, allowedOrigins: ['*'], exposedHeaders: false, maxAge: false, supportsCredentials: false }

services:
  cache.backend.null:
    class: Drupal\Core\Cache\NullBackendFactory
```

# Semi-official way

This is the same thing as described above, but require less operations and can looks a little bit "dirty". But this is the best and fastest way to disable cache on demand.

At first you must create a file named **services.dev.yml**. You can name it whatever you like, but don't forget to corret that name in PHP code below. Put this file in **/sites/default/services.dev.yml**.

### services.dev.yml

```yaml
services:
  cache.backend.null:
    class: Drupal\Core\Cache\NullBackendFactory
parameters:
  session.storage.options:
    gc_probability: 1
    gc_divisor: 100
    gc_maxlifetime: 200000
    cookie_lifetime: 2000000
  twig.config:
    debug: true
    auto_reload: true
    cache: false
  renderer.config:
    required_cache_contexts:
      - url
      - route
      - languages:language_interface
      - theme
      - user.permissions
    auto_placeholder_conditions:
      max-age: 0
      contexts:
        - session
        - user
      tags: [ ]
  http.response.debug_cacheability_headers: true
  factory.keyvalue: [ ]
  factory.keyvalue.expirable: [ ]
  filter_protocols:
    - http
    - https
    - mailto
    - ssh
    - sftp
```
## settings.php

Now you must add some changes to settings.php to enable this service and parameters. To do that, you must add this line to **settings.php**.

```php
/**
 * Development mode.
 */
if (TRUE) {
  assert_options(ASSERT_ACTIVE, TRUE);
  \Drupal\Component\Assertion\Handle::register();
  $settings["container_yamls"][] = __DIR__ . "/services.dev.yml";
  $config["system.logging"]["error_level"] = "verbose";
  $config["system.performance"]["css"]["preprocess"] = FALSE;
  $config["system.performance"]["js"]["preprocess"] = FALSE;
  $settings["cache"]["bins"]["render"] = "cache.backend.null";
  $settings["cache"]["bins"]["dynamic_page_cache"] = "cache.backend.null";
  $settings['cache']['bins']['page'] = 'cache.backend.null';
  $settings["extension_discovery_scan_tests"] = TRUE;
  $settings["rebuild_access"] = TRUE;
  $settings["skip_permissions_hardening"] = TRUE;
}
```
When you need to enable caching and disable all debug tools, you can just change condition statement to `FALSE`.

I recommend to add this code right after this lines:

```php
#if (file_exists($app_root . '/' . $site_path . '/settings.local.php')) {
#  include $app_root . '/' . $site_path . '/settings.local.php';
#}
```

# Using DrupalConsole

This will be only disable Twig caches, but not disable entire cache which affect code.

```bash
drupal site:mode dev
```

Revert back

```
drupal site:mode prod
```
