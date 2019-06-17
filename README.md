## Drupal distribution of SbAdmin2

Theme menggunakan start bootstrap admin versi 2.

https://startbootstrap.com/template-overviews/sb-admin-2/

https://blackrockdigital.github.io/startbootstrap-sb-admin-2/pages/index.html

## Cara Menggunakan

1. Tentukan direktori Drupal Anda. Contoh `/var/www/html/drupal7`.

```
export DRUPAL_ROOT=/var/www/html/drupal7
```

2. Clone Repository ini dan masuk ke direktori.

```
git clone https://github.com/ijortengab/drupal7-sbadmin2
cd drupal7-sbadmin2
```

3. Buat direktori custom modules dan themes.

```
mkdir -p $DRUPAL_ROOT/sites/all/themes/custom
mkdir -p $DRUPAL_ROOT/sites/all/modules/custom
```

4. Copy module dan theme ke direktori Drupal.

```
cp -rf themes/sbadmin2 -t $DRUPAL_ROOT/sites/all/themes/custom
cp -rf modules/sbadmin2 -t $DRUPAL_ROOT/sites/all/modules/custom
```

5. Download library vendor theme dan module.

```
cd $DRUPAL_ROOT/sites/all/themes/custom/sbadmin2
chmod +x grab.sh
./grab.sh
```

Ketik 'yes' dan enter

```
cd $DRUPAL_ROOT/sites/all/modules/custom/sbadmin2/sbadmin2_helper
chmod +x grab.sh
./grab.sh
```

Ketik 'yes' dan enter

6. Module dan Theme siap di-enable.


