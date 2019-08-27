Start Bootstrap Admin versi 2
-----------------------------

Module ini sebagai module pelengkap dan pengaya Theme SBAdmin2 karena layer
theme memilki keterbatasan terutama dalam membuat route. Function hook_menu()
dan hook_views_api() tidak berjalan pada theme layer.

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
