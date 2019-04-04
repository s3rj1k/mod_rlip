# mod_rlip

### Summary

Apache2.4 module that fixes `SERVER_ADDR`, `REMOTE_ADDR` then web server is used as backend, behind reverse-proxy,
the values must be provided by an upstream reverse proxy via `X-Server-IP`, `X-Real-IP` request headers.

### Compile Debian/Ubuntu Package and Install
```
    sudo apt-get install build-essential apache2-threaded-dev
    make
    make install
```
### Compile and Install for RedHat/CentOS
```
    yum install httpd-devel
    make
    make install
```
### NginX as reverse proxy config example
```
    proxy_hide_header X-Server-IP;                                                                                                                                                        
    proxy_set_header X-Server-IP $server_addr;                                                                                                                                            
                                                                                                                                                                                              
    proxy_hide_header X-Real-IP;                                                                                                                                                          
    proxy_set_header X-Real-IP $remote_addr;
```
## Authors:

* s3rj1k <evasive.gyron@gmail.com>
