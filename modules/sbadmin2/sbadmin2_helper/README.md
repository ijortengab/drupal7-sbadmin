Start Bootstrap Admin versi 2
-----------------------------

Module ini sebagai module pelengkap dan pengaya Theme SBAdmin2 karena layer theme memilki keterbatasan terutama dalam membuat route.

## Perubahan yang dilakukan

- Membuat route baru, yakni:
  - /sbadmin2-login
  - /sbadmin2-front

- Pada route "/admin/config/system/site-information".
  - Disabled input "Default front page"
  - Variable awal "site_frontpage" dibackup sebagai variable "sbadmin2_helper_site_frontpage_old".
  - Variable "site_frontpage" diset "sbadmin2-front"

- Pada route "/admin/structure/block/list/sbadmin2"
  - Seluruh block pada region Header, Sidebar, Content disabled.
  - Pada region Sidebar: Search form, Main menu.
  - Pada region Content: Main page content
  - Pada region Header: User menu

## Penambahan fitur

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

- Memberikan property baru pada element yakni: `#sbadmin2_form_horizontal`. Dengan property ini, maka element akan menjadi horizontal.

## Reference:

https://usebootstrap.com/preview/sb-admin-2/
