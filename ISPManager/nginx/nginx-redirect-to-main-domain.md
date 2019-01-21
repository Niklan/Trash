# ISPManager 5 — Redirect to main domain

This addon adds possibility to redirect all requests from aliases to main domain.

1. `cd /usr/local/mgr5/etc/xml`
2. `touch ispmgr_mod_redirect_to_main.xml`
3. Put this content into it.

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

4. `cd /usr/local/mgr5/addon`
5. `touch redirect_to_main`
6. Put this content into it.

```bash
#!/bin/bash

if [[ "$PARAM_redirect_to_main" = "on" ]]
  then
    cat | sed 's|</doc>$|<params><REDIRECT_TO_MAIN>on</REDIRECT_TO_MAIN></params></doc>|'
  else
    cat | sed 's|</doc>$|<params><REDIRECT_TO_MAIN>off</REDIRECT_TO_MAIN></params></doc>|'
fi
```

7. `cd /usr/local/mgr5/etc/templates`
8. Copy those two files **if they not exists**:

```bash
cp default/nginx-vhosts.template ./nginx-vhosts.template
cp default/nginx-vhosts-ssl.template ./nginx-vhosts-ssl.template
```

9. Edit it and add config below before `location /` in **both files** or somwhere below in `server {}` block.

```nginx
{% if $REDIRECT_TO_MAIN == on %}
	if ($http_host != {% $NAME %}) {
    rewrite  ^(.*)$  $scheme://{% $NAME %}$1;
  }
{% endif %}
```

10. Change in your **nginx-vhosts.template** line with SSL at the end from, **only if you just copied those two files and not done it before**

`{% import etc/templates/default/nginx-vhosts-ssl.template %}`

to

`{% import etc/templates/nginx-vhosts-ssl.template %}`

13. `mkdir /usr/local/mgr5/etc/sql/webdomain.addon` (if not exist)
14. `cd /usr/local/mgr5/etc/sql/webdomain.addon`
15. `touch redirect_to_main`
16. Edit **redirect_to_main** and add this lines:

```conf
default=off
```

17. Kill DB cache `rm -rf /usr/local/mgr5/var/.db.cache*`
18. Restart core `killall core`

Now, visit WWW-domain, on edit form will be new checkbox.
