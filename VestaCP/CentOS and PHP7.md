# VestaCP + CentOS + Nginx + PHP 7

This is simple instruction how to upgrade php to 7.1 version on VestaCP using CentOS and nginx + php-fpm version of Vesta CP.

**Do not use this instruction on apache server, and over OS's than CentOS 7.x+**

_I don't guarantee that this will work for you, better test it on celan droplet before do that on production._

First things, first. For this instruction you must have enabled REMI repositories for CentOS. This is done by default Vesta installation, if you don't disable it manually.

If you do so, than enable them:

~~~bash
yum install https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
yum install http://rpms.remirepo.net/enterprise/remi-release-7.rpm
yum install yum-utils
~~~

## Install PHP 7.1

~~~bash
service php-fpm stop
yum -y --enablerepo=remi install php71-php php71-php-pear php71-php-bcmath php71-php-pecl-jsond-devel php71-php-mysqlnd php71-php-gd php71-php-common php71-php-fpm php71-php-intl php71-php-cli php71-php php71-php-xml php71-php-opcache php71-php-pecl-apcu php71-php-pecl-jsond php71-php-pdo php71-php-gmp php71-php-process php71-php-pecl-imagick php71-php-devel php71-php-mbstring php71-php-pecl-zip
# Link new php to default binary
rm -f /usr/bin/php
ln -s /usr/bin/php71 /usr/bin/php
# Replace old PHP.ini with new one MAKE BACKUP BEFORE THAT IF YOU DO CHANGES.
rm -f /etc/php.ini
ln -s /etc/opt/remi/php71/php.ini /etc/php.ini
~~~

Test installation

~~~
php -v
PHP 7.1.2RC1 (cli) (built: Feb  2 2017 09:23:52) ( NTS )
Copyright (c) 1997-2017 The PHP Group
Zend Engine v3.1.0, Copyright (c) 1998-2017 Zend Technologies
    with Zend OPcache v7.1.2RC1, Copyright (c) 1999-2017, by Zend Technologies
~~~

Additional configuration

~~~bash
sudo nano /etc/opt/remi/php71/php-fpm.conf
# Change include line in FPM configuration group (first) to
include=/etc/php-fpm.d/*.conf
service php71-php-fpm start
# Re-link old services
rm -f /usr/lib/systemd/system/php-fpm.service
ln -s /usr/lib/systemd/system/php71-php-fpm.service /usr/lib/systemd/system/php-fpm.service
systemctl daemon-reload
service nginx restart
~~~
