# ISPManager 6 — Drupal NGINX integration instructions

1. Make sure you complete [addon preparation insutrction](addon-prepare.md).
2. `cd /usr/local/mgr5/etc/xml`
3. `touch ispmgr_mod_drupal_nginx.xml` (prefix `ispmgr_mod_` is required)
4. Put this content into it.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<mgrdata>
  <metadata name="site.edit" type="form">
    <form>
      <page name="additional">
        <!-- Note 'site_' prefix is important for site.edit. -->
        <field name="site_drupal_nginx">
          <input type="checkbox" name="site_drupal_nginx" />
        </field>
      </page>
    </form>
  </metadata>
  
  <!-- Backward compatibility with an older form. -->
  <metadata name="webdomain.edit" type="form">
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
      <msg name="site_drupal_nginx">Drupal NGINX</msg>
      <msg name="hint_site_drupal_nginx">Отметьте, чтобы конфигурации NGINX были оптимизированы под Drupal.</msg>
    </messages>
    <messages name="webdomain.edit">
      <msg name="drupal_nginx">Drupal NGINX</msg>
      <msg name="hint_drupal_nginx">Отметьте, чтобы конфигурации NGINX были оптимизированы под Drupal.</msg>
    </messages>
  </lang>
  
  <lang name="en">
    <messages name="site.edit">
      <msg name="site_drupal_nginx">Drupal NGINX</msg>
      <msg name="hint_site_drupal_nginx">Check for optimized Drupal NGINX config.</msg>
    </messages>
    <messages name="webdomain.edit">
      <msg name="drupal_nginx">Drupal NGINX</msg>
      <msg name="hint_drupal_nginx">Check for optimized Drupal NGINX config.</msg>
    </messages>
  </lang>
</mgrdata>
```

5. `cd /usr/local/mgr5/etc/templates`
6. `touch nginx-drupal.template`
7. Put this into `nginx-drupal.template`

```nginx
# Uncomment it to handle 404 with Drupal. This is not recommended for peroformance
# but if you want beautiful 404 pages with full control. That's your choise.
#error_page 404 /index.php;

# Buffers definition. allows of up to 260k to be passed in memory.
client_body_buffer_size 1m;
proxy_buffering on;
proxy_buffer_size 4k;
proxy_buffers 8 32k;

# Hide default Drupal headers. Worthless payload for production.
fastcgi_hide_header 'X-Drupal-Cache';
fastcgi_hide_header 'X-Generator';
fastcgi_hide_header 'X-Drupal-Dynamic-Cache';

location / {
    # Private files shouldn't be accessible from outside.
    location ~* /sites/.+/files/private/ {
        internal;
    }

    # Image styles should be processed by Drupal, not as static files.
    # Also it supports Drupal 10.1+ new JS/CSS aggregation system.
    location ~* /files/(css|js|styles)/ {
        access_log off;
        expires 1y;
        try_files $uri @drupal;
    }

    location ~* /sites/.+/files/.+\.txt {
        access_log off;
        expires 1y;
        tcp_nodelay off;
        open_file_cache max=1000 inactive=30s;
        open_file_cache_valid 30s;
        open_file_cache_min_uses 2;
        open_file_cache_errors off;
    }

    # drupal/advagg
    location ~* /sites/.+/files/advagg_css/ {
        expires max;
        add_header ETag '';
        add_header Last-Modified 'Wed, 20 Jan 1988 04:20:42 GMT';
        add_header Accept-Ranges '';
        location ~* /sites/.*/files/advagg_css/.+\.css$ {
            access_log off;
            add_header Cache-Control "public, max-age=31536000, no-transform, immutable";
            try_files $uri @drupal;
        }
    }

    # drupal/advagg
    location ~* /sites/.+/files/advagg_js/ {
        expires max;
        add_header ETag '';
        add_header Last-Modified 'Wed, 20 Jan 1988 04:20:42 GMT';
        add_header Accept-Ranges '';
        location ~* /sites/.*/files/advagg_js/.+\.js$ {
            access_log off;
            add_header Cache-Control "public, max-age=31536000, no-transform, immutable";
            try_files $uri @drupal;
        }
    }

    # drupal/hacked
    location ~* /admin/reports/hacked/.+/diff/ {
        try_files $uri @drupal;
    }

    # Allow dynamic XML endpoints. You need that if you have routes with '.xml' ending.
    #location ~* ^.+\.xml {
    #    try_files $uri @drupal;
    #}

    # Force 'sitemap.xml' to be processed by Drupal, this is not a static file for 99.99%.
    location ~* /sitemap.xml {
        try_files $uri @drupal;
    }

    # Do not allow to dowonload any config.
    location ^~ /sites/.+/files/config_.*/ {
        internal;
    }

    # Don't allow direct access to PHP files in the vendor directory.
    location ~ ^/vendor/ {
        internal;
    }

    # Handle private files through Drupal.
    location ~ ^/system/files/ {
        try_files $uri @drupal;
    }

    # Replica of regex from Drupals core .htaccess.
    location ~* \.(engine|txt|inc|install|make|module|profile|po|sh|.*sql|theme|twig|tpl(\.php)?|xtmpl|yml)(~|\.sw[op]|\.bak|\.orig|\.save)?$|^(\.(?!well-known).*|Entries.*|Repository|Root|Tag|Template|composer\.(json|lock)|(package|package-lock)\.json|yarn\.lock|web\.config)$\.php(~|\.sw[op]|\.bak|\.orig|\.save)$ {
        return 404;
    }

    # Static files.
    location ~* ^.+\.(?:css|cur|js|jpe?g|gif|htc|ico|png|xml|otf|ttf|eot|woff|woff2|svg|mp4|svgz|ogg|ogv|pdf|pptx?|zip|tgz|gz|rar|bz2|doc|xls|exe|tar|mid|midi|wav|bmp|rtf|txt|map|webp)$ {
        access_log off;
        tcp_nodelay off;
        expires 1y;

        add_header Pragma "cache";
        add_header Cache-Control "public";

        open_file_cache max=1000 inactive=30s;
        open_file_cache_valid 30s;
        open_file_cache_min_uses 2;
        open_file_cache_errors off;
    }

    try_files $uri @drupal;
}

# This rewrites pages to be sent to PHP processing
location @drupal {
    rewrite ^/(.*)$ /index.php;
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

```

8. `cp nginx-drupal.template nginx-drupal-ssl.template` because otherwise ISP thinks he going into recurrsion when used twice.
9. Edit `nginx-vhosts.template`. Add content below before `location /` in **both files** but in `server {}` block.

```nginx
{% if $DRUPAL_NGINX == on %}
  {% import etc/templates/nginx-drupal.template %}
{% endif %}
```
10. Edit `nginx-vhosts-ssl.template`. Add content below before `location /` in **both files** but in `server {}` block.

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

15. `/usr/local/mgr5/sbin/mgrctl -m ispmgr exit`
16. Kill DB cache `rm -rf /usr/local/mgr5/var/.db.cache*`
17. Restart core `killall core`


Now, visit WWW-domain, on edit form will be new checkbox. Check it and save to apply NGINX configs for Drupal.

![Setting](https://i.imgur.com/w1MT0Fr.png)
