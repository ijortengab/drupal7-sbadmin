<?php
/**
 * Clone dari template modules/search/search-block-form.tpl.php.
 *
 * Modifikasi yakni menghilangkan div wrappper `./container-inline`.
 */
?>
<?php if (empty($variables['form']['#block']->subject)): ?>
<h2 class="element-invisible"><?php print t('Search form'); ?></h2>
<?php endif; ?>
<?php print $search_form; ?>
