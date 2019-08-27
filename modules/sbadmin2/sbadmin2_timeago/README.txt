Module ini sebagai contoh bahwa Function Theme pada Javascript dapat
di-control oleh module dan dapat modular (diintegrasikan dengan fitur
rewrite-nya SBAdmin2).

Untuk rewrite column pada Views Table, langkah-langkahnya adalah sebagai
berikut:
 - Pastikan field handler yang ingin direwrite telah mengimplements trait
   `sbadmin2_helper_handler_field_trait`. Jika belum, maka override handler
   tersebut.
 -
