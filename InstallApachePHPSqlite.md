# Details #
## Install packages ##
```
$ apt-get install apache2 php5 php5-sqlite
```
## Enable support for userdir www folders ##
```
$ a2enmod userdir
$ nano /etc/apache2/sites-enabled/007-qad
UserDir enabled *
UserDir disabled root
<Directory /home/*/public_html/cgi-bin/>
 Options ExecCGI
 SetHandler cgi-script
</Directory>
```
## enable php5 for userdir ##
read comments in /etc/apache2/mods-enabled/php5.conf.

## test php5 installation ##
```
<?php 
phpinfo();
?>
```
## enable python support ##
```
$ apt-get install libapache2-mod-python
$ nano /etc/apache2/sites-enabled/008-qad-python
AddHandler mod_python .py
PythonHandler mod_python.publisher
PythonDebug On
```

## test python installation ##
```
#!/usr/bin/python

def index(req):
        return "Hello World"

```
## Restart Apache2 ##
```
$ service apache2 restart
```