I have separated kernel and home directory disk partition. Docker use kernel by default, this is not good, cuz it's not enough memory to store this amount of data. The simple way to save docker data on another parition.

# Ubuntu 16.04 or more aka systemd

~~~
sudo nano /etc/docker/daemon.json
~~~

~~~
{
  "graph": "/NEW_PATH"
}
~~~

~~~
sudo service docker restart
~~~

# Ubuntu 15.10 or less

~~~
sudo nano /etc/default/docer
~~~

~~~
DOCKER_OPTS="-g /NEW_PATH"
~~~

# Hardcore way

~~~
docker ps -q | xargs docker kill
stop docker
cd /var/lib/docker/devicemapper/mnt
umount ./*
mv /var/lib/docker /NEW_PATH
ln -s /NEW_PATH /var/lib/docker
start docker
~~~
