# README

This is section about how I set up docker-based VPS for websites.

## Prerequisite

- Linux-based OS
- Docker & Docker Compose

## Structure

Consider the current folder as `$HOME` directory of user under which projects will be served.

## Backup to localhost

If you want to do manual backups time to time, there is a handy starting shell script for that:

```bash
#!/usr/bin/env bash

set -e
set +x

PROJECT_NAME=""
PROJECT_PATH="~/Projects/$PROJECT_NAME"
MIRROR_DIR="$PWD/$PROJECT_NAME"
SERVER_USERNAME=""
SERVER_HOST=""

clear
notify-send 'Backup' 'Backup script started!'
echo -e "\033[5;44;1m Backup $PROJECT_NAME remote directory \033[0m"

echo "Make sure destination directory is exists."
mkdir -p $MIRROR_DIR/$PROJECT_NAME

echo "Prepare a database dump."
ssh $SERVER_USERNAME@$SERVER_HOST "
  cd $PROJECT_PATH
  docker compose exec mariadb sh -c 'mysqldump -u root -p\$MYSQL_ROOT_PASSWORD --all-databases | gzip' > ./dump.sql.gz
"

echo "Sync project files."
rsync \
  -avz \
  --delete \
  --exclude /database \
  $SERVER_USERNAME@$SERVER_HOST:$PROJECT_PATH/ \
  $MIRROR_DIR

echo "The backup is saved at: $MIRROR_DIR"
notify-send 'Backup' 'Backup script finished!'
sleep 3
```

### What does this script do

* Creates special localhost directory where backup will be stored.
* Using SSH connection it will create a database dump in project folder from the `mariadb` container.
* Using `rsync` it will transfer all project directory folders and files (except `/database` which is bind-mount of DB) to your local directory.
* This script only downloads new or updated files on second+ runs, also it will remove an outdated files which is not presented on remote anymore.

### How to configure script

* `$PROJECT_NAME`: The product name. This name will be used to navigate into project remote directory and as directory name for backup on localhost.
* `$PROJECT_PATH`: The directory with project (where `docker-compose.yml` and `.env` files are located). This is a directory, the contents of which will be backup.
* `$MIRROR_DIR`: The localhost destination path to save backup files.
* `$SERVER_USERNAME`: The username of a remote server.
* `$SERVER_HOST`: The hostname or IP of a remote server.