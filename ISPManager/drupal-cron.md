# ISPManager 5: Drupal cron

You can run cron in multiple ways. This is summary of [this documentation](https://www.drupal.org/docs/7/setting-up-cron/configuring-cron-jobs-using-the-cron-command).

## Recommendations

- Run cron regulary, don't forget to run it at least once per day.
- Don't use **Automated cron** module shipped with Drupal core and installed by default on **Standard** profile. **Uninstall it**. It's reduces performance for random user is very drstically.
- It's better to run cron via CLI, not with HTTP URL, because, often, CLI is faster and has less restrictions, e.g. execution time for CLI often is disabled completely.

**Best cron approach**:

1. `drush cron` or manually `php /path/to/cron.php`. This is **CLI** mode. It's faster and have less restrictions. Didn't touch web-server in any way and didn't affect users.
2. `wget` or `curl` with cron URL. This is not a bad solution, but better user #1.
3. Automated Cron — use it only on shared hostings where you can't create cron operation with CLI method.

## Before

- Log in as user with domain which need to be configured to run cron.
- Navigate to Dashboard > Scheduler (cron)
- Add

## Drush

Configure [Drush](install-drush.md) and use it! It's simpliest way.

`export HOME=PATH_TO_SITE_ROOT; /usr/local/bin/drush cron --quiet --root=$HOME`

- `PATH_TO_SITE_ROOT` - path to site root. This is essential, because cron doesn't know anything about environment variables, but Drush trying to get `$HOME` in every request. So it's mandatory. E.g. `/var/www/USERNAME/data/DOMAIN_NAME`
- `--quiet` - for not printing any data to cron. If you wan't to send email with cron results, remove it.

You can use `/usr/local/bin/drush7` or other version you install by instructions to handle multiple Drupal versions and PHP versions.

## WGET

`wget --spider CRON_URL`
