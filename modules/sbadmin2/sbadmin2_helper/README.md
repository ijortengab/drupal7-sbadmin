README
Cara menginstall Drupal
drush site-install minimal --db-url='mysql://kppri:h2nCHPwjYclP@localhost/kppri' --site-name=KPPRI --db-prefix=systemix_


Cara backup data
mysqldump -u kppri -p kppri --replace --skip-set-charset --lock-tables=false --skip-add-locks > kppri.sql

kppri   h2nCHPwjYclP


 $password = 'h2nCHPwjYclP';
}
else {
    $password = 'Tahw7aeg';
    
drush sql-query "DELETE from systemix_system where name = 'ldap_sso' AND type = 'module';"

Export

Local

```
cd
rsync -avz public_html/ kppri@kppri.ui.ac.id:public_html
mysqldump -u kppri -ph2nCHPwjYclP kppri --replace --skip-set-charset --lock-tables=false --skip-add-locks > kppri.sql
scp kppri.sql kppri@kppri.ui.ac.id:kppri.sql
ssh kppri@kppri.ui.ac.id 'mysql -u kppri -pTahw7aeg kppri < kppri.sql'
```

Remote
```
cd
mysql -u kppri -pTahw7aeg kppri < kppri.sql
```

