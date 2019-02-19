# ISPManager 5 — Redirect to main domain

This addon adds possibility to redirect all requests from aliases to main domain.

1. Make sure you complete [addon preparation insutrction](addon-prepare.md).
2. `cd /usr/local/mgr5/etc/xml`
3. `touch ispmgr_mod_redirect_to_main.xml`
4. Put this content into it.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<mgrdata>
  <handler name="redirect_to_main" type="xml">
    <event name="webdomain.edit" after="yes" />
  </handler>
  
  <metadata name="webdomain.edit" type="form">
    <form>
      <page name="domain">
        <field name="redirect_to_main">
          <input type="checkbox" name="redirect_to_main" />
        </field>
      </page>
    </form>
  </metadata>
  
  <lang name="ru">
    <messages name="webdomain.edit">
      <msg name="redirect_to_main">Перенаправлять все запросы на основной домен</msg>
      <msg name="hint_redirect_to_main">Отметьте, чтобы все запросы были направлены на основной домен, включая WWW-перенаправление.</msg>
    </messages>
  </lang>
  
  <lang name="en">
    <messages name="webdomain.edit">
      <msg name="redirect_to_main">Redirect all request to main domain</msg>
      <msg name="hint_redirect_to_main">Check for redirect all requests to main domain including WWW-domain.</msg>
    </messages>
  </lang>
</mgrdata>
```

5. `cd /usr/local/mgr5/addon`
6. `touch redirect_to_main`
7. Put this content into it.

```bash
#!/bin/bash

if [[ "$PARAM_redirect_to_main" = "on" ]]
  then
    cat | sed 's|</doc>$|<params><REDIRECT_TO_MAIN>on</REDIRECT_TO_MAIN></params></doc>|'
  else
    cat | sed 's|</doc>$|<params><REDIRECT_TO_MAIN>off</REDIRECT_TO_MAIN></params></doc>|'
fi
```

8. `cd /usr/local/mgr5/etc/templates`
9. Edit **nginx-vhosts.template** and **nginx-vhosts-ssl.template**, add config below before `location /` in **both files** or somwhere below in `server {}` block.

```nginx
{% if $REDIRECT_TO_MAIN == on %}
	if ($http_host != {% $NAME %}) {
    rewrite  ^(.*)$  $scheme://{% $NAME %}$1 permanent;
  }
{% endif %}
```

10. `mkdir /usr/local/mgr5/etc/sql/webdomain.addon` (if not exist)
11. `cd /usr/local/mgr5/etc/sql/webdomain.addon`
12. `touch redirect_to_main`
13. Edit **redirect_to_main** and add this lines:

```conf
default=off
```

14. Kill DB cache `rm -rf /usr/local/mgr5/var/.db.cache*`
15. Restart core `killall core`

Now, visit WWW-domain, on edit form will be new checkbox.
