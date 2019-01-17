# ISPManager 5 — Drupal NGINX integration instructions

1. `cd /usr/local/mgr5/etc/xml`
2. `touch ispmgr_mod_drupal_nginx.xml`
3. Put this content into it.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<mgrdata>
  <handler name="drupal_nginx" type="xml">
    <event name="webdomain.edit" after="yes" />
  </handler>
  
  <metadata name="webdomain.edit" type="form">
    <form>
      <page name="domain">
        <field name="drupal_nginx">
          <input type="checkbox" name="drupal_nginx" />
        </field>
      </page>
    </form>
  </metadata>
  
  <lang name="ru">
    <messages name="webdomain.edit">
      <msg name="drupal_nginx">Drupal NGINX</msg>
      <msg name="hint_drupal_nginx">Отметьте, чтобы конфигурации NGINX были оптимизированы под Drupal.</msg>
    </messages>
  </lang>
  
  <lang name="en">
    <messages name="webdomain.edit">
      <msg name="drupal_nginx">Drupal NGINX</msg>
      <msg name="hint_drupal_nginx">Check for optimized Drupal NGINX config.</msg>
    </messages>
  </lang>
</mgrdata>
```

4. `/usr/local/mgr5/sbin/mgrctl -m ispmgr exit` will restart panel.
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
9. If you doesn't copy those files before or they doesn't exists, copy them:

```bash
cp default/nginx-vhosts.template ./nginx-vhosts.template
cp default/nginx-vhosts-ssl.template ./nginx-vhosts-ssl.template
```

10. Edit it and add config below before `location /` in **both files** ro somwhere below in `server {}` block.
```nginx
{% if $DRUPAL_NGINX == on %}
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
    location ^~ /sites/configurations/ {
      internal;
    }

    # Don't allow direct access to PHP files in the vendor directory.
    location ~ /vendor/.*\.php$ {
      deny all;
      return 404;
    }

    # Fix for image style generation.
    location ~ ^/sites/.*/files/styles/ {
      try_files $uri @drupal;
      access_log off;
      expires 30d;
      ## No need to bleed constant updates. Send the all shebang in one
      ## fell swoop.
      tcp_nodelay off;
      ## Set the OS file cache.
      open_file_cache max=3000 inactive=120s;
      open_file_cache_valid 45s;
      open_file_cache_min_uses 2;
      open_file_cache_errors off;
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

    # All static files will be served directly.
    location ~* ^.+\.(?:css|cur|js|jpe?g|gif|htc|ico|png|html|otf|ttf|eot|woff2?|svg)$ {
      access_log off;
      expires 30d;
      # No need to bleed constant updates. Send the all shebang in one
      # fell swoop.
      tcp_nodelay off;
      # Set the OS file cache.
      open_file_cache max=3000 inactive=120s;
      open_file_cache_valid 45s;
      open_file_cache_min_uses 2;
      open_file_cache_errors off;
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
    expires 30d;
    # No need to bleed constant updates. Send the all shebang in one
    # fell swoop.
    tcp_nodelay off;
    # Set the OS file cache.
    open_file_cache max=3000 inactive=120s;
    open_file_cache_valid 45s;
    open_file_cache_min_uses 2;
    open_file_cache_errors off;
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
{% endif %}
```

11. Change in your **nginx-vhosts.template** line with SSL at the end from

`{% import etc/templates/default/nginx-vhosts-ssl.template %}`

to

`{% import etc/templates/nginx-vhosts-ssl.template %}`

12. In **both** templates find

```nginx
    location ~* ^.+\.(jpg|jpeg|gif|png|svg|js|css|mp3|ogg|mpe?g|avi|zip|gz|bz2?|rar|swf)$ {
{% if $SRV_CACHE == on %}
      expires [% $EXPIRES_VALUE %];
{% endif %}
{% if $REDIRECT_TO_APACHE == on %}
      try_files $uri $uri/ @fallback;
{% endif %}
    }
```

and replace with

```nginx
    location ~* ^.+\.(jpg|jpeg|gif|png|svg|js|css|mp3|ogg|mpe?g|avi|zip|gz|bz2?|rar|swf)$ {
{% if $SRV_CACHE == on %}
      expires [% $EXPIRES_VALUE %];
{% endif %}
{% if $REDIRECT_TO_APACHE == on %}
      try_files $uri $uri/ @fallback;
{% endif %}
{% if $DRUPAL_NGINX == on %}
      try_files $uri @drupal;
{% endif %}
    }
```

or manually add part for trying Drupal files. This will fix image style generation which brokes wtih ISP.

13. `mkdir /usr/local/mgr5/etc/sql/webdomain.addon` (if not exist)
14. `cd /usr/local/mgr5/etc/sql/webdomain.addon`
15. `touch drupal_nginx`
16. Edit **drupal_nginx** and add this lines:

```conf
default=off
```

17. Kill DB cache `rm -rf /usr/local/mgr5/var/.db.cache*`
18. Restart core `killall core`

Now, visit WWW-domain, on edit form will be new checkbox. Check it and save to apply NGINX configs for Drupal.

![Setting](https://i.imgur.com/w1MT0Fr.png)