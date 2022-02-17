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

## Backup to remote

Below, you can find an example script to create separate code and database backups for Drupal ([example-5.com](Projects/example-5.com/README.md)).

This script creates backups and upload them to S3 Compatible object storage clouds (Amazon S3, Yandex Object Storage etc).

You can adjust any its settings, by default:

- It creates folder per backup type inside `BACKUP_DIRECTORY`:
  - `daily/`: 7 in total. Monday backup will be overriden by new on next week.
  - `weekly/`: 4 in total. Each week of the month will have its own backup.
  - `monthly/`: 12 in total. Each month of the year will have its own backup. January backup will be overriden by new on next yer.
  - `yearly/`: Not limited by default. If this backup script will work for 5 year, it will have 5 backups for each year.
- It uses [s3cmd](https://github.com/s3tools/s3cmd) tool to upload backups.
- It expects that you have separate `.s3cfg` per project placed at the same dir as this script (`S3CMD_CONFIG`).
- This script is better to be places on per-project basis to adjust it for project needs. E.g. `Projects/example-5.com/scripts/backup.sh`.
- It better to run from system (user) crontab instead of docker. You can find examples inside it.

You can find additional information inside script comments. Don't forget to update variable `S3_BUCKET_URI` for your needs.

```bash
#!/usr/bin/env bash

# This script will create backup of the project and upload it on remote server.
#
# Available options:
# -d: For daily backup.
# -w: For weekly backup.
# -m: For monthly backup.
# -y: For yearly backup.
#
# Examples.
#
# Create a daily backup:
# $ bash backup.sh -d
#
# Create a weekly backup:
# $ bash backup.sh -w
#
# Create a monthly backup:
# $ bash backup.sh -m
#
# Create a yearly backup:
# $ bash backup.sh -y
#
# Backup filenames will use numbers in their filename to avoid duplicating files
# and will override the old one on next backup.
#
# E.g. for daily backup filename will be 'database-$DAY.sql.gz' where $DAY - number
# of the week from 0 to 6, where 0 is Sunday. For Monday it will be 1, which means
# every Monday this backup will be named 'database-1.sql.gz' and uploaded to remote
# server overriding previous file with the same name. This way you don't need to
# delete an old backups.
#
# Same logic applied for other parameters.
#
# Use it in crontab (crontab -e):
#
# For daily backups at 00:00:
# '0 0 * * * /usr/bin/bash /path/to/backup.sh -d'
#
# For weekly backups at 01:00 on Sunday:
# '0 1 * * 0 /usr/bin/bash /path/to/backup.sh -w'
#
# For monthly backups at 02:00 on 1 day of month
# '0 2 1 * * /usr/bin/bash /path/to/backup.sh -m'
#
# For yearly backups at 03:00 on 1th January.
# '0 3 1 1 * /usr/bin/bash /path/to/backup.sh -y'

# For crontab.
export TERM=xterm
set -e
set +x

# Settings for backup script.
# A path where is current script is placed.
SCRIPT_PATH=$(realpath $(dirname "$0"));
# A path where is project root is located.
PROJECT_PATH="$SCRIPT_PATH/.."
# A path to directory, where backups should be saved.
BACKUP_DIRECTORY="$PROJECT_PATH/backups"
# A path for s3cmd tool configuration. This is used to upload to S3 compatible storages.
S3CMD_CONFIG=$SCRIPT_PATH/.s3cfg
# An URI for root backet for backups.
S3_BUCKET_URI=s3://example-5.com/backups
# A list of tables from Drupal to be exported with structure only.
# This reduces dabase dump size significantly.
STRUCTURE_TABLES_LIST=(cache,cache_*,flood,history,queue,search_index,search_api_*,semaphore,sequences,sessions,watchdog)
# A paramter for drush combines structure tables above.
DRUSH_STRUCTURE_TABLES_LIST=''
for TABLE in "${STRUCTURE_TABLES_LIST[@]}"
do :
   DRUSH_STRUCTURE_TABLES_LIST+=" --structure-tables-list=${TABLE}"
done

# Provides the function for backup project and upload it in remote storage.
backup() {
  cd "$PROJECT_PATH"

  echo "Make sure destination directory is exists."
  mkdir -p "$PROJECT_PATH"

  echo "Make sure backup directory is exists."
  mkdir -p "$BACKUP_DIRECTORY"

  echo "Prepare a database dump."
  docker compose exec -T -e DRUSH_STRUCTURE_TABLES_LIST="$DRUSH_STRUCTURE_TABLES_LIST" php sh -c 'drush sql:dump --gzip $DRUSH_STRUCTURE_TABLES_LIST' > $BACKUP_DIRECTORY/$DATABASE_FILENAME

  echo "Upload database backup."
  s3cmd -c $S3CMD_CONFIG --storage-class COLD put $BACKUP_DIRECTORY/$DATABASE_FILENAME $S3_BACKUP_URI/$DATABASE_FILENAME

  echo "Clean up local files."
  rm -rf "$BACKUP_DIRECTORY"
}

while getopts "dwmy" arg; do
  case $arg in
    d)
      S3_BACKUP_URI="$S3_BUCKET_URI/daily"
      DAY=$(date +%w)
      DATABASE_FILENAME="database-$DAY.sql.gz"
      backup
      ;;
    w)
      S3_BACKUP_URI="$S3_BUCKET_URI/weekly"
      # Use code below if you want backup for each week of the year.
      #WEEK=$(date +%U)
      # The code below get week of the month. Assuming that Monday is
      # first day of the week (remove '+1' if you want Sunday).
      WEEK=$((($(date +%-d)-1)/7+1))
      DATABASE_FILENAME="database-$WEEK.sql.gz"
      backup
      ;;
    m)
      S3_BACKUP_URI="$S3_BUCKET_URI/monthly"
      MONTH=$(date +%m)
      DATABASE_FILENAME="database-$MONTH.sql.gz"
      backup
      ;;
    y)
      S3_BACKUP_URI="$S3_BUCKET_URI/yearly"
      YEAR=$(date +%Y)
      DATABASE_FILENAME="database-$YEAR.sql.gz"
      backup
      ;;
    *)
      exit 0
      ;;
  esac
done

```