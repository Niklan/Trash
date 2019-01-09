 # Drush Launcher installation for ISPManager 5

Installation instruction for [Drush launcher](https://github.com/drush-ops/drush-launcher).

```bash
# On root user.
wget -O drush.phar https://github.com/drush-ops/drush-launcher/releases/download/0.6.0/drush.phar
chmod +x drush.phar
sudo mv drush.phar /usr/local/bin/drush
```

## Different PHP versions

1. Create `/etc/profile.d/global_aliases.sh` if not exists.
2. Add

```bash
# Don't forget to default php versions.
alias drush="/opt/php72/bin/php /usl/local/bin/drush"
# You can also add additional aliases for older (newer) versions.
alias drush56="/opt/php56/bin/php /usl/local/bin/drush"
```
