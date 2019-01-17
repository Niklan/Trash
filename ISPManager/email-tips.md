# ISPManager 5: Email tips

This tips can be halpful if you're using DNS server from VPS provider, and not from ISP manager. This can lead to problems, but on many VPS's there is no way to handle it via DNS from ISP.

## SPF and DKIM for domain

This can help avoid spam filters.

1. Enable DKIM support: Settings > Features > Mail server > Edit and check OpenDKIM.
2. Add new mail domain: Domains > Mail domains > Add. Enter domain name and check "Enable DKIM for domain".

Edit your DNS entries by adding new ones:

 * **SPF**

  - **Subdomain**: your main domain, f.e. `example.com`
  - **Type**: `TXT`
  - **Value**: `v=spf1 ip4:SERVER_IP ~all` - replace SERVER_IP with IP same as for A record. You you want to use it f.e. with Yandex Mail append `include=_spf.yandex.ru` before `~all`.
  - **TTL**: `600`, or leave it by default. This is not so important.

 * **DKIM**

  - **Subdomain**: `mail._domainkey.example.com` - replace example.com with your domain. Must be the same as for DKIM record created before.
  - **Type**: `TXT`
  - **Value**: `v=DKIM1; k=rsa; p=DKIM_KEY` - you must replace DKIM_KEY with your value. You can find this value only on server. Use shell or SSH for accesing it: `cat /etc/exim/ssl/example.com.txt`.
  - **TTL**: `600`, or leave it by default. This is not so important.

