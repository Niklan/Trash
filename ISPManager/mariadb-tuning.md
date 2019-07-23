# MariaDB tuning in ISPManager 5

Settings > Database

## Common improvements

### max-allowed-packet

Set it to `256M` (268435456).

Default to `10M` is cause "ERROR 2006 (HY000) at line 1977: MySQL server has gone away" error. You won't be able to import big database.

### query-cache-limit and query-cache-size

Set it to `1M` (1048576, default) and `10M` (10485760).

### innodb-flush-log-at-trx-commit

By default is set to `1` - and this is most safety choice.

But when set to `2` you can expect better performance ([~x75-150](https://dba.stackexchange.com/a/56673) times faster for write operations)

Change it on your own choice, and before change, read [this](https://dba.stackexchange.com/questions/12611/is-it-safe-to-use-innodb-flush-log-at-trx-commit-2).
