# Upload Vesta backups on Amazon S3.

* Login to SSH as root, or admin.
* Install latest version of [s3cmd](https://github.com/s3tools/s3cmd)
* Create file `s3backups` or name it like you want it.
* Insert code into file:

~~~sh
#!/bin/bash
s3cmd sync --delete-removed /home/backup/*.tar s3://BUCKET/OBJECT/ --storage-class REDUCED_REDUNDANCY
~~~

Make this file executable
~~~sh
chmod +x s3backups
~~~

* Add this file to cron, how often you want to upload backups to Amazon S3. For me, it doing every day at 3PM.

![Cron](http://i.imgur.com/rHbfTjE.png)

This will backup all files in /home/backup which has .tar file extension. This file will be uploaded as 'Reduced Redundancy' files, so their price will be lower.

You can call this scrip manualy when you want it, use code like in cron: `sudo /root/s3backups`.
