# Drush installation for ISPManager 6

### Different PHP versions

E.g, for PHP 8.1.

1. `touch /usr/local/bin/drush81`.
2. Add content:

```bash
#!/bin/bash
env PATH="/opt/php81/bin:./vendor/bin:$PATH" drush "$@"
```

3. `chmod +x /usr/local/bin/drush81`

You can create as many as you want same files with different php version. F.e. /usr/local/bin/drush56 for PHP 5.6.

## Drush 7 for Drupal 7

_This can be used for multiple drush version on one server._

You might be needing Drush 7.x for older sites. This is also possible, but better to create new command for it.

1. `cd /usr/local/src`
2. `git clone https://github.com/drush-ops/drush.git drush7`
3. `cd drush7`
4. `git checkout 7.4.0` or whatever [version](https://github.com/drush-ops/drush/tags) you want.
5. `ln -s /usr/local/src/drush7/drush /usr/local/bin/drush7`
6. `composer install` (must be installed)
7. `drush7 --version`
