# ISPManager 6 — Drupal NGINX integration instructions

1. Make sure you complete [addon preparation insutrction](addon-prepare.md).
2. `cd /usr/local/mgr5/etc/xml`
3. `touch ispmgr_mod_drupal_nginx.xml`
4. Put this content into it.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<mgrdata>
  <handler name="drupal_nginx" type="xml">
    <event name="site.edit" after="yes" />
  </handler>
  
  <metadata name="site.edit" type="form">
    <form>
      <page name="additional">
        <field name="drupal_nginx">
          <input type="checkbox" name="drupal_nginx" />
        </field>
      </page>
    </form>
  </metadata>
  
  <lang name="ru">
    <messages name="site.edit">
      <msg name="drupal_nginx">Drupal NGINX</msg>
      <msg name="hint_drupal_nginx">Отметьте, чтобы конфигурации NGINX были оптимизированы под Drupal.</msg>
    </messages>
  </lang>
  
  <lang name="en">
    <messages name="site.edit">
      <msg name="drupal_nginx">Drupal NGINX</msg>
      <msg name="hint_drupal_nginx">Check for optimized Drupal NGINX config.</msg>
    </messages>
  </lang>
</mgrdata>
```

5. `cd /usr/local/mgr5/addon`
6. `touch drupal_nginx`
7. Put this content into it.

```bash
#!/bin/bash

if [[ "$PARAM_drupal_nginx" = "on" ]]
  then
    cat | sed 's|</doc>$|<params><DRUPAL_NGINX>on</DRUPAL_NGINX></params></doc>|'
  else
    cat | sed 's|</doc>$|<params><DRUPAL_NGINX>off</DRUPAL_NGINX></params></doc>|'
fi
```

8. `cd /usr/local/mgr5/etc/templates`
9. `touch nginx-drupal.template`
10. Put this into `nginx-drupal.template`

```nginx
{#} Uncomment it to handle 404 with Drupal. This is not recommended for peroformance
{#} but if you want beautiful 404 pages with full control. That's your choise.
{#} error_page 404 /index.php;

# Buffers definition. allows of up to 260k to be passed in memory.
client_body_buffer_size 1m;
proxy_buffering on;
proxy_buffer_size 4k;
proxy_buffers 8 32k;

location / {
    # Very rarely should these ever be accessed outside of your lan
    location ~* \.(txt|log)$ {
        allow 192.168.0.0/16;
        deny all;
    }

    # Trying to access private files directly returns a 404.
    location ^~ /sites/default/files/private/ {
        internal;
    }

    # For configuration storage.
    location ^~ /sites/default/files/config_.*/ {
        internal;
    }

    # Don't allow direct access to PHP files in the vendor directory.
    location ~ /vendor/.*\.php$ {
        internal;
    }

    # Fix for image style generation.
    location ~ ^/sites/.*/files/styles/ {
        access_log off;
        expires max;
        try_files $uri @drupal;
    }

    # Handle private files through Drupal.
    location ~ ^/system/files/ {
        try_files $uri /index.php?$query_string;
    }

    # Advanced Aggregation module CSS
    # support. http://drupal.org/project/advagg.
    location ^~ /sites/default/files/advagg_css/ {
        expires max;
        add_header ETag '';
        add_header Last-Modified 'Wed, 20 Jan 1988 04:20:42 GMT';
        add_header Accept-Ranges '';
        location ~* ^/sites/default/files/advagg_css/css[__[:alnum:]]+\.css$ {
            allow all;
            access_log off;
            try_files $uri @drupal;
        }
    }

    # Advanced Aggregation module JS
    # support. http://drupal.org/project/advagg.
    location ^~ /sites/default/files/advagg_js/ {
        expires max;
        add_header ETag '';
        add_header Last-Modified 'Wed, 20 Jan 1988 04:20:42 GMT';
        add_header Accept-Ranges '';
        location ~* ^/sites/default/files/advagg_js/js[__[:alnum:]]+\.js$ {
            access_log off;
            try_files $uri @drupal;
        }
    }

    # Replicate the Apache <FilesMatch> directive of Drupal standard
    # .htaccess. Disable access to any code files. Return a 404 to curtail
    # information disclosure. Hide also the text files.
    location ~* ^(?:.+\.(?:htaccess|make|txt|engine|inc|info|install|module|profile|po|pot|sh|.*sql|test|theme|tpl(?:\.php)?|xtmpl)|code-style\.pl|/Entries.*|/Repository|/Root|/Tag|/Template)$ {
        return 404;
    }

    try_files $uri @drupal;
}

location = /favicon.ico {
    log_not_found off;
    access_log off;
    access_log off;
    expires max;
}

# With robotstxt module support.
location = /robots.txt {
    allow all;
    log_not_found off;
    access_log off;
    try_files $uri @drupal;
}

location = /humans.txt {
    allow all;
    log_not_found off;
    access_log off;
    try_files $uri @drupal;
}

# XML Dynamic support
location ~* \.xml {
    try_files $uri @drupal;
}

# Disallow access to .bzr, .git, .hg, .svn, .cvs directories: return
# 404 as not to disclose information.
location ^~ /.bzr {
    return 404;
}

location ^~ /.git {
    return 404;
}

location ^~ /.hg {
    return 404;
}

location ^~ /.svn {
    return 404;
}

location ^~ /.cvs {
    return 404;
}

# Disallow access to patches directory.
location ^~ /patches {
    return 404;
}

# Any other attempt to access PHP files returns a 404.
location ~* ^.+\.php$ {
    return 404;
}

# This rewrites pages to be sent to PHP processing
location @drupal {
    rewrite ^/(.*)$ /index.php;
}
```
12. `cp nginx-drupal.template nginx-drupal-ssl.template` because otherwise ISP thinks he going into recurrsion when used twice.
13. Edit `nginx-vhosts.template`. Add content below before `location /` in **both files** but in `server {}` block.

```nginx
{% if $DRUPAL_NGINX == on %}
  {% import etc/templates/nginx-drupal.template %}
{% endif %}
```
14. Edit `nginx-vhosts-ssl.template`. Add content below before `location /` in **both files** but in `server {}` block.

```nginx
{% if $DRUPAL_NGINX == on %}
  {% import etc/templates/nginx-drupal-ssl.template %}
{% endif %}
```

11. `mkdir /usr/local/mgr5/etc/sql/webdomain.addon` (if not exist)
12. `cd /usr/local/mgr5/etc/sql/webdomain.addon`
13. `touch drupal_nginx`
14. Edit **drupal_nginx** and add this lines:

```conf
default=off
```

15. Kill DB cache `rm -rf /usr/local/mgr5/var/.db.cache*`
16. Restart core `killall core`


Now, visit WWW-domain, on edit form will be new checkbox. Check it and save to apply NGINX configs for Drupal.

![Setting](https://i.imgur.com/w1MT0Fr.png)
