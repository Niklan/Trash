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

## Install PHP 7.2

~~~bash
service php-fpm stop
yum -y --enablerepo=remi install php72-php php72-php-pear php72-php-bcmath php72-php-pecl-jsond-devel php72-php-mysqlnd php72-php-gd php72-php-common php72-php-fpm php72-php-intl php72-php-cli php72-php php72-php-xml php72-php-opcache php72-php-pecl-apcu php72-php-pecl-jsond php72-php-pdo php72-php-gmp php72-php-process php72-php-pecl-imagick php72-php-devel php72-php-mbstring php72-php-pecl-zip
# Link new php to default binary
rm -f /usr/bin/php
ln -s /usr/bin/php72 /usr/bin/php
# Replace old PHP.ini with new one MAKE BACKUP BEFORE THAT IF YOU DO CHANGES.
rm -f /etc/php.ini
ln -s /etc/opt/remi/php72/php.ini /etc/php.ini
~~~

Test installation

~~~
php -v
PHP 7.2.16 (cli) (built: Mar  5 2019 13:10:50) ( NTS )
Copyright (c) 1997-2018 The PHP Group
Zend Engine v3.2.0, Copyright (c) 1998-2018 Zend Technologies
    with Zend OPcache v7.2.16, Copyright (c) 1999-2018, by Zend Technologies
~~~

Additional configuration

~~~bash
sudo nano /etc/opt/remi/php72/php-fpm.conf
# Change include line in FPM configuration group (first) to
include=/etc/php-fpm.d/*.conf
service php72-php-fpm start
# Re-link old services
rm -f /usr/lib/systemd/system/php-fpm.service
ln -s /usr/lib/systemd/system/php72-php-fpm.service /usr/lib/systemd/system/php-fpm.service
systemctl daemon-reload
service nginx restart
~~~
