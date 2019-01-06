# How to import MySQL database dump to docker container

Find MySQL container ID

~~~bash
docker ps
~~~

F.e.

~~~bash
CONTAINER ID        IMAGE                               COMMAND                  CREATED             STATUS              PORTS                                      NAMES
dac45cf128f6        dockerizedrupal/apache-2.4:1.2.3    "/src/entrypoint.sh r"   About an hour ago   Up About an hour    80/tcp, 443/tcp                            test_apache_1
7687de8f626d        dockerizedrupal/php-5.6:1.2.9       "/src/entrypoint.sh r"   About an hour ago   Up About an hour    9000/tcp                                   test_php_1
a20fb38c2f2d        dockerizedrupal/mysql:1.2.2         "/src/entrypoint.sh r"   5 weeks ago         Up About an hour    3306/tcp                                   test_mysql_1
~~~

My container ID is a20fb38c2f2d, so next is import dump

~~~bash
docker exec -i CONTAINER_ID mysql -uUSERNAME -pPASSWORD DATABASE_NAME < BACKUPFILENAME.sql
~~~

~~~bash
docker exec -i a20fb38c2f2d mysql -uusername -p123qwerty main < backup.sql
~~~


From .sql.gz

```bash
zcat /path/to/file.sql.gz | mysql -uusername -p123qwerty your_database
```
