# Composer insallation

```
php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"
php composer-setup.php
php -r "unlink('composer-setup.php');"
```

If you want to make it global

```
sudo chmod +x composer.phar
sudo mv composer.phar /usr/local/composer
```
