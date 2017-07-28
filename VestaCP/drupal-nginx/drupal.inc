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
    location ~ ^/system/files/ { # For Drupal >= 7
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

location @drupal {
    rewrite ^/(.*)$ /index.php;
}
