# Upload Vesta backups on Amazon S3.

* Login to SSH as root, or admin.
* Install latest version of [s3cmd](https://github.com/s3tools/s3cmd)
* Create file `s3backups` or name it like you want it.
* Insert code into file:

~~~sh
#!/bin/bash

# Importing system variables
source /etc/profile

s3cmd sync --delete-removed /home/backup/*.tar s3://BUCKET-NAME/FOLDER/ --storage-class REDUCED_REDUNDANCY
~~~

Move this file to `/usr/local/vesta/bin/`

Make this file executable
~~~sh
chmod a+x s3backups
~~~

* Add this file to cron, how often you want to upload backups to Amazon S3. For me, it doing every day at 3PM.

![Cron](https://i.imgur.com/TXwHl8t.png)

This will backup all files in /home/backup which has .tar file extension. This file will be uploaded as 'Reduced Redundancy' files, so their price will be lower.

You can call this scrip manualy when you want it, use code like in cron: `sudo /usr/local/vesta/bin/s3backups`.
