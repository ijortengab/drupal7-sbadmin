    <div id="wrapper">
        <!-- Navigation -->
        <nav class="navbar navbar-default navbar-static-top" role="navigation" style="margin-bottom: 0">
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <?php if ($logo): ?>
                <a class="logo pull-left" href="<?= $front_page; ?>" title="<?= t('Home'); ?>">
                    <img src="<?= $logo; ?>" alt="<?= t('Home'); ?>" />
                </a>
                <?php endif; ?>

                <a class="navbar-brand<?php if ($logo): ?> has_logo<?php endif; ?>" href="<?= $front_page; ?>">
                <?= $site_name;?>
                </a>
            </div>
            <!-- /.navbar-header -->
            <?= render($page['header']) ;?>
            <?= render($page['sidebar']) ;?>
        </nav>
        <div id="page-wrapper">
            <?php if ($messages): ?>
                <div class="row">
                    <div class="col-lg-12">
                    <?= $messages; ?>
                    </div>
                </div>
            <?php endif; ?>

            <?= render($title_prefix); ?>
            <?php if ($title): ?>
                <div class="row">
                    <div class="col-lg-12">
                        <h1 class="page-header"><?= $title; ?></h1>
                    </div>
                </div>
                <?php if ($tabs): ?><div class="tabs"><?= render($tabs); ?></div><?php endif; ?>
            <?php endif; ?>
            <?= render($title_suffix); ?>
            <?= render($page['content']) ;?>
        </div>
        <!-- /#page-wrapper -->
    </div>
    <!-- /#wrapper -->
