# Drush Launcher installation for ISPManager 5

Installation instruction for [Drush launcher](https://github.com/drush-ops/drush-launcher).

```bash
# On root user.
wget -O drush.phar https://github.com/drush-ops/drush-launcher/releases/download/0.6.0/drush.phar
chmod +x drush.phar
sudo mv drush.phar /usr/local/bin/drush-bin
```

## Different PHP versions

1. `touch /usr/local/bin/drush`.
2. 

```bash
#!/bin/bash
/opt/php72/bin/php /usr/local/bin/drush-bin "$@"
```

3. `chmod +x /usr/local/bin/drush`

You can create as many as you want same files with different php version. F.e. /usr/local/bin/drush56 for PHP 5.6.
