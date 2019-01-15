# ISPManager 5 — Redirect to main domain

1. Open NGINX config for needed domain as root user.
2. Add at the begginging:

```nginx
# HTTP
server {
  listen $IP:80;
  server_name $ALIASES;
  return 301 $scheme://example.com$request_uri;
}
# HTTPS
server {
  listen $IP:443 ssl http2;
  server_name $ALIASES;
  
  # SSL Certificate. REPLACE it with values you can find in HTTPS server below.
  ssl_certificate "/var/www/httpd-cert/username/example.com_le1.crtca";
  ssl_certificate_key "/var/www/httpd-cert/username/example.com_le1.key";
  ssl_ciphers EECDH:+AES256:-3DES:RSA+AES:!NULL:!RC4;
  ssl_prefer_server_ciphers on;
  ssl_protocols TLSv1 TLSv1.1 TLSv1.2;
  add_header Strict-Transport-Security "max-age=31536000;";
  ssl_dhparam /etc/ssl/certs/dhparam4096.pem;
  
  return 301 $scheme://example.com:443$request_uri;
}
```

3. Replace values. You can find it below in the config.

 * `$IP` with server ip
 * `$ALIASES` with aliases only, **without** main domain. E.g. `www.main-domain.com www.example.com example.com`.
 * `example.com` with main domain.

Fore testing porupses for first time is recommended to use 302 redirect.

P.S. Remove `http2` if you not use it.