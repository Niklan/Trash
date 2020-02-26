# php-fpm.conf

Use [this service](https://cmorrell.com/php-fpm/) to calculate your best settings.

This will calculate optimal for performance php-fpm settings.

VestaCP uses templates for each domain, so you need to create new template for this and use it for needed domains.

## Create template

1. Navigate to php-fpm templataes `cd /usr/local/vesta/data/templates/web/php-fpm`
1. Create new file, e.g. `touch performance.conf`.
1. Fill it with data and save.

E.g.:

```conf
; https://cmorrell.com/php-fpm/
[%backend%]
listen = 127.0.0.1:%backend_port%
listen.allowed_clients = 127.0.0.1

user = %user%
group = %user%

; Run php-fpm in "dynamic" mode
pm = dynamic
; Set max_children to ([total RAM - reserved RAM]) / [average php-fpm process])
; Most recently: (1024 * (2 - 1)) / 60 = 17
pm.max_children = 15
; After this many requests, a php-fpm process will respawn. This is useful
; to guard against memory leaks, but causes a small performance hit. Set to
; a high number (or 0) if you're confident that your app does not have any
; memory leaks (and that you're not using any 3rd-party libraries that have
; memory leaks), or set to a lower number if you're aware of a leak.
pm.max_requests = 500
; When php-fpm starts, have this many processes waiting for requests. Set to 50% of
; max on a server that's mostly responsible for running PHP processes
pm.start_servers = 5
; Minimum number spare processes php-fpm will create. In the case of a
; server dedicated to running PHP, we'll set this to the same as start_servers
pm.min_spare_servers = 5
; Maximum number spare processes php-fpm will create. If more than this
; many processes are idle, some will be killed.
pm.max_spare_servers = 10
pm.process_idle_timeout = 10s
pm.status_path = /status

php_admin_value[upload_tmp_dir] = /home/%user%/tmp
php_admin_value[session.save_path] = /home/%user%/tmp

env[HOSTNAME] = $HOSTNAME
env[PATH] = /usr/local/bin:/usr/bin:/bin
env[TMP] = /home/%user%/tmp
env[TMPDIR] = /home/%user%/tmp
env[TEMP] = /home/%user%/tmp
```

Then go to web domain settings and select it.

![Settings](https://i.imgur.com/K6AJDaU.png)
