# ISPManager 5: PHP tips

This tips mainly for Drupal sites.

## After installation new PHP version

Enable PHP extensions:

- xmlreader
- xmlwriter
- opcache
- bcmath (required by drupal/commerce)

### max_execution_time

Set it at least for `60`. `30` by default is to low for some heavy operations. I using `600`.

### post_max_size

`128M` or whatever you want.

### upload_max_filesize

`128M` or whatever you want. Can't be more than `upload_max_filesize`.

### opcache.revalidate_freq

`0`

### opcache.file_update_protection

`10`

### opcache.enable_cli

`1` or `On`

