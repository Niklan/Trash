# Composer installation for ISPManager 6

```bash
# On root user.
php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"
php composer-setup.php
php -r "unlink('composer-setup.php');"
sudo chmod +x composer.phar
sudo mv composer.phar /usr/local/bin/composer
```

## Specific PHP version for Composer for specific user

1. Log in as that user.
2. `mkdir ~/bin`
3. `touch ~/bin/php`
4. Edit `~/bin/php` and add this content, specifing a required PHP version for binary and configs and changing path with username:

```sh
#!/bin/sh
PHP_EXEC="/opt/php81/bin/php -c /var/www/USERNAME/data/php-bin-isp-php81"
$PHP_EXEC "$@"
```
5. `chmod +x ~/bin/php`
5. Edit or create `~/.bash_profile`
   1. **Create a new one** (default, because file doesn'e exists): `echo "export PATH=$HOME/bin:$PATH" >> ~/.bash_profile`
   7. Update `PATH` with appending `~/bin`.

## Specific PHP version for Composer for all users

1. `mv /usr/local/bin/composer /usr/local/bin/composer-bin`
1. `touch /usr/local/bin/composer`.
2. E.g., for PHP 8.1.

```bash
#!/bin/bash
env PATH="/opt/php81/bin:$PATH" php /usr/local/bin/composer-bin "$@"
```

3. `chmod +x /usr/local/bin/composer`

You can create as many as you want, same files with different PHP version. F.e. `/usr/local/bin/composer56` for PHP 5.6.
