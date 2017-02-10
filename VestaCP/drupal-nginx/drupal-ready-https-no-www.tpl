server {
    listen      %ip%:%web_port%;
    server_name %domain_idn% %alias_idn%;
    return      302 https://%domain_idn%$request_uri;
}
