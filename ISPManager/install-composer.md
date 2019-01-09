# Composer installation for ISPManager 5

```bash
# On root user.
php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');"
php composer-setup.php
php -r "unlink('composer-setup.php');"
sudo chmod +x composer.phar
sudo mv composer.phar /usr/local/bin/composer
```

## Different PHP versions

1. Create `/etc/profile.d/global_aliases.sh` if not exists.
2. Add

```bash
# Don't forget to default php versions.
alias composer="/opt/php72/bin/php /usl/local/bin/composer"
# You can also add additional aliases for older (newer) versions.
alias composer56="/opt/php56/bin/php /usl/local/bin/composer"
```