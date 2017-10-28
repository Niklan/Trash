# Drush wrapper for composer

## Global

1. `touch /usr/local/bin/drush`
2. `vi /usr/local/bin/drush`
3.
  ```bash
  #!/usr/bin/env sh
  #
  # A wrapper script which launches the Drush that is in your project's /vendor
  # directory.
  #
  ./vendor/bin/drush --local $@
  ```
