# README

## SSH keys

### Why do you need this?

* The single SSH key can be used only once at GitHub as Deploy key. You can't use default user-specific key to deploy multiple projects.
* Easier to distinguish what this key is and what project responsible for it.
* Easier to control access based on keys.

### Generating project-specific SSH keys

* `cd ~/Projects/example-5.com`
* `mkdir ssh`
* `ssh-keygen -t rsa -C "example-5.com@SERVER_NAME" -f ./ssh/id_rsa`

### How to specify Git to use this key for a specific repository?

* Navigate into repository root folder.
* `git config core.sshCommand "ssh -i ~/Projects/example-5.com/ssh/id_rsa -F /dev/null"`

[More detailed information](https://superuser.com/a/912281).