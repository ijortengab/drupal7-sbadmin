<div class="login-panel panel panel-default">
    <div class="panel-heading">
        <?= render($title_prefix); ?>
        <h3 class="panel-title"><?= $block->subject ?></h3>
        <?= render($title_suffix); ?>
    </div>
    <div class="panel-body">
        <?= $messages ?>
        <?= $content ?>
    </div>
</div>
