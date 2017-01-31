# Reducre Time To First Bite (TTFB) for Nginx

![Example TTFB](http://i.imgur.com/uMUF9ht.png)


At first, edit `/etc/nginx/nginx.conf`

~~~bash
#ssh to server
sudo -s
nano /etc/nginx/nginx.conf
~~~

And add ne lines

~~~
fastcgi_cache_path /etc/nginx-cache levels=1:2 keys_zone=phpcache:100m inactive=60m;
fastcgi_cache_key "$scheme$request_method$host$request_uri";
~~~

Save and close this file.

Nex you need to edit template for Vesta CP. You can find all of them in `/usr/local/vesta/data/templates/web/nginx/php-fpm`.

In needed template, better both `.tpl` and `.stpl` find lines like this:

~~~
location ~ [^/]\.php(/|$) {
~~~

Add after them new config lines. This will be looks like this:

~~~
location ~ [^/]\.php(/|$) {
    # Cache
    fastcgi_cache phpcache; # The name of the cache key-zone to use
    fastcgi_cache_valid 200 30m; # What to cache: 'Code 200' responses, for half an hour
    fastcgi_cache_methods GET HEAD; # What to cache: only GET and HEAD requests (not POST)
    add_header X-Fastcgi-Cache $upstream_cache_status; # Add header so we can see if the cache hits or misses
~~~

Then you need to update all nginx configs for users

~~~
/usr/local/vesta/bin/v-rebuild-web-domains USERNAME
~~~

After that all domains will be regenerated and new lines will appear according to template.
