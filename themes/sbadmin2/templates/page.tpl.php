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
                <a class="navbar-brand" href="<?php print $front_page; ?>"><?php print $site_name;?></a>
            </div>
            <!-- /.navbar-header -->
            <?php print render($page['header']) ;?>
            <?php print render($page['sidebar']) ;?>
        </nav>
        <div id="page-wrapper">
                
            <?php print render($title_prefix); ?>
            <?php if ($title): ?>
                <div class="row">
                    <div class="col-lg-12">
                        <h1 class="page-header"><?php print $title; ?></h1>
                    </div>
                    <!-- /.col-lg-12 -->
                </div>
                <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
            <?php endif; ?>
            <?php print render($title_suffix); ?>
            <?php print render($page['content']) ;?>
        </div>
        <!-- /#page-wrapper -->
    </div>
    <!-- /#wrapper -->
