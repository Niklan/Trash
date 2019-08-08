# NGINX tips

## Improve gzip mimes

If you are using gzip on site, the ISP is provide very common mime types to handle with gzip. It can be broader.

1. Open `/usr/local/mgr5/etc/ispmgr.conf`.
2. Add

```
path nginx-gzip-types text/css text/javascript text/xml text/plain text/x-component application/javascript application/x-javascript application/json application/xml application/rss+xml application/atom+xml font/ttf font/opentype font/woff font/woff2 application/vnd.ms-fontobject image/svg+xml
```

You can edit by your needs. It will apply to all configs. If you want it only for specific website, edit config directly.

## Improve MIME types assotiation

ISP is not provides mime types for fonts at all, which results to response for them with octet-stream type. Which is not a good idea. It will lead to miss gzip and other possible slowdowns.

1. Open `/etc/nginx/mime.types`
2. Add

```
    font/ttf                                         ttf;
    font/opentype                                    otf;
    font/woff                                        woff;
    font/woff2                                       woff2;
    application/vnd.ms-fontobject                    eot;
```
