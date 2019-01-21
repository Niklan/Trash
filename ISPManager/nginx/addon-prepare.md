# ISPManager 5: Preparation before NGINX addon creation

This instruction is needs to be done before any addon from other instructions will be created.

Do it only once, because copying can broke files.

1. `cd /usr/local/mgr5/etc/templates`
2. Copy default templates to working directory.

```bash
cp default/nginx-vhosts.template ./nginx-vhosts.template
cp default/nginx-vhosts-ssl.template ./nginx-vhosts-ssl.template
```

3. Open **nginx-vhosts.template** and change line with SSL at the end from

`{% import etc/templates/default/nginx-vhosts-ssl.template %}`

to

`{% import etc/templates/nginx-vhosts-ssl.template %}`

