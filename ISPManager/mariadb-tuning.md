# MariaDB tuning in ISPManager 5

## Common improvements

### max-allowed-packet

Set it to `256M`.

Default to `10M` is cause "ERROR 2006 (HY000) at line 1977: MySQL server has gone away" error. You won't be able to import big database.