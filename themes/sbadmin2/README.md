
Start Bootstrap Admin versi 2
-----------------------------

Theme untuk mengadaptasi SBAdmin2 versi Bootstrap 3.

Theme ini juga dilengkapi dengan modifikasi pada Bootstrap 3 sehingga dicapai kebutuhan yang diinginkan.

## Reference:

https://usebootstrap.com/preview/sb-admin-2/

[http://ijortengab.id/static/sbadmin2/pages/index.html](http://ijortengab.id/static/sbadmin2/pages/index.html)


## Catatan Bagi Developer Drupal

- Secara default, element type `password`, `select`, `textarea`, `textfield`,
  dan `file` akan diberi property baru bernama '#sbadmin' dengan default value
  `true`. Dengan nilai '#sbadmin' = TRUE, maka akan ditambahkan class
  `form-control` saat render.
  Untuk menonaktifkan fitur ini, gunakan hook_form_alter, dan jadikan '#sbadmin'
  bernilai false.

- Memberikan informasi theme baru, yakni:
  - input_group
  - input_group_button
  - input_group_addon

- Memberikan definisi property baru pada element yakni: `#sbadmin2_form_horizontal`.
  Dengan property ini, maka element akan menjadi horizontal.

## Button Group Addon dan Segmented Button

Component [Button Group][1] dari Bootstrap 3 bisa digunakan untuk [element radio ataupun checkbox][2].

Pada Component [Input Group][4] terdapat fitur berupa [addon][3] dan [segmented button][5].

Berikut ini modifikasi agar Component `Button Group` juga bisa terdapat fitur `addon` dan `segmented button`.

Tambahkan class `.btn.btn-group-addon` pada element yang akan dijadikan `addon`.

```html
<div class="btn-group" data-toggle="buttons">
    <span class="btn btn-group-addon">Status Permintaan</span>
    <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> <span class="caret"></span> <span class="sr-only">Toggle Dropdown</span> </button>
    <ul class="dropdown-menu">
        <li><a href="#">Action</a></li>
        <li><a href="#">Another action</a></li>
        <li><a href="#">Something else here</a></li>
        <li role="separator" class="divider"></li>
        <li><a href="#">Separated link</a>
        </li>
    </ul>
    <span class="btn btn-default"><span aria-hidden="true" class="fa fa-fw fa-question-circle"></span></span>
    <label class="btn btn-default">
        <input type="checkbox" autocomplete="off" checked> Belum Diproses
    </label>
    <label class="btn btn-default">
        <input type="checkbox" autocomplete="off"> Sedang Diproses
    </label>
 </div>
```

Tambahkan CSS berikut untuk menjadikannya seperti addon-nya `Input Group`. CSS ini sudah terdapat pada file `sbadmin2-bootstrap.css`.

```css
.btn-group-addon {
    background-color: #eee;
    cursor: text;
    border: 1px solid #ccc;
    -webkit-user-select: auto;
    -moz-user-select: auto;
    -ms-user-select: auto;
    user-select: auto;
}
.btn-group-addon:active {
    -webkit-box-shadow: none;
    -moz-box-shadow: none;
    -ms-box-shadow: none;
    box-shadow: none;
}
```

Untuk fitur `segmented buttons`, perlu modifikasi CSS tambahan sebagai
berikut:

```css
.btn-group[data-toggle="buttons"]>.btn+.dropdown-toggle {
    border-top-right-radius: 0;
    border-bottom-right-radius: 0;
    margin-right: -1px;
}
```

[1]: https://getbootstrap.com/docs/3.3/components/#btn-groups
[2]: https://getbootstrap.com/docs/3.3/javascript/#buttons-checkbox-radio
[3]: https://getbootstrap.com/docs/3.3/components/#input-groups-basic
[4]: https://getbootstrap.com/docs/3.3/components/#input-groups
[5]: https://getbootstrap.com/docs/3.3/components/#input-groups-buttons-segmented

## Tambahan class pada List Group Contextual Classes

Terdapat [empat kelas][6] yang `built in` untuk variasi warna background pada list group item.

Berikut ini modifikasi agar Component `List Group` terdapat warna background seperti `panel-default`.

Tambakan class `list-group-item-default` pada setiap list item didalam `List Group` kemudian definisikan CSS-nya sebagai berikut:

```css
.list-group-item-default {
    background-color: #f5f5f5;
}
```
CSS ini sudah terdapat pada file `sbadmin2-bootstrap.css`.

Contohnya penerapan sebagai berikut:

```html
<ul class="list-group">
  <li class="list-group-item list-group-item-default">Dapibus ac facilisis in</li>
</ul>
```
[6]: https://getbootstrap.com/docs/3.3/components/#list-group-contextual-classes

