Start Bootstrap Admin versi 2
-----------------------------

Theme untuk mengadaptasi SBAdmin2 versi Bootstrap 3.

## Reference:

https://usebootstrap.com/preview/sb-admin-2/


## Catatan Bagi Developer

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
