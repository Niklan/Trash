# Change WWW docroot

ISPManager only allows to set docroot when you create new www-domain, but then, not allows to change it via UI.

There are three ways.

1. Delet domain and add again, but this method will erase all your data. It's not acceptable for production sites.
2. Change this value in ISP Database.

```bash
sqlite3 /usr/local/mgr5/etc/ispmgr.db
```

Looking for domain id:

```sql
select * from webdomain;
```

Update location. Don't forget to change $USERNAME$, $DOMAIN$, $DOMAIN_ID$ on your values.

```sql
update webdomain set docroot="/var/www/$USERNAME$/data/www/$DOMAIN_ID$/web" where id=1
```

Press `Ctrl + D` to exit.

3. Delete WWW-domain, but not check for removing data. Recreate WWW-domain with new values.