# README

The current folder is base Project folder to configure reverse proxy which will route all requests to specific projects.

## docker-compose.yml

This docker compose file is simple, we define single service - traefik. We include `traefik.yml` file with our settings into image and expose two ports.

We also create here a custom network named `web` and attach traefik container to it. This network will be used only by containers that want to be access from public web. 

### traefik.yml

Traefik is configured to listen `:80` (HTTP) and `:443` (HTTPS) ports. That means any other connection to a different port will be handled by hoist system and ignored by Traefik. Open new ports with caution.

### providers.docker.exposedByDefault: false

By default docker provider exposed by default. This means that all docker container up and running will be visible to Traefik and it will generate default routing and other settings for them.

We disable that behavior because it creates a lot of unused settings and can potentially lead to security problems.

We will explicitly expose only trusted containers to Traefik.

### certificatesResolvers.letsencrypt

We configure certificate provider `letsencrypt` which wil lbe used as free certificate generator. You should change email to your own, or most likely it wont work because of API limits.

## Examples

* [example-1.com](https://github.com/Niklan/Trash/tree/master/docker-based-vps/Projects/example-1.com): The most simplistic example with Traefik whoami.
* [example-2.com](https://github.com/Niklan/Trash/tree/master/docker-based-vps/Projects/example-2.com): This example show how to serve simple static HTML website with NGINX.
* [example-3.com](https://github.com/Niklan/Trash/tree/master/docker-based-vps/Projects/example-3.com): This example shows how to serve simple PHP application with `index.php`.
* [example-4.com](https://github.com/Niklan/Trash/tree/master/docker-based-vps/Projects/example-4.com): This example shows how to configure project for Drupal. On top of PHP and NGINX container here is added MariaDB for database.
* [example-5.com](https://github.com/Niklan/Trash/tree/master/docker-based-vps/Projects/example-5.com): The most complex example. As addition for example-4.com adds SSH keys for deployments, node container for compiling CSS and JS and configure system cron.