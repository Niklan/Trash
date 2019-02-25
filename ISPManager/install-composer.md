# Composer installation for ISPManager 5

```bash
# On root user.
php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"
php composer-setup.php
php -r "unlink('composer-setup.php');"
sudo chmod +x composer.phar
sudo mv composer.phar /usr/local/bin/composer-bin
```

## Different PHP versions

1. `touch /usr/local/bin/composer`.
2. 

```bash
#!/bin/bash
env PATH="/opt/php73/bin:$PATH" php /usr/local/bin/composer-bin "$@"
```

3. `chmod +x /usr/local/bin/composer`

You can create as many as you want same files with different php version. F.e. /usr/local/bin/composer56 for PHP 5.6.
