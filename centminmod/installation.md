 
## swap

```
sudo fallocate -l 1G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
sudo nano /etc/fstab
```

```
/swapfile   swap    swap    sw  0   0
```

## Installation

1. Disable SELINUX

    ```
    vi /etc/selinux/config
    ```

    ```
    SELINUX=enforcing

    to 

    SELINUX=disabled
    ```

    and reboot system.

2. Install centmin Mod stable

    ```
    yum -y update; curl -O https://centminmod.com/installer.sh && chmod 0700 installer.sh && bash installer.sh
    ```

3. Use it `centmin`.