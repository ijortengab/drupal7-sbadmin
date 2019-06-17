<div class="row">
    <div class="col-md-8">
        <div class="panel panel-default">
            <div class="panel-heading">
                Form
            </div>
            <div class="panel-body">
                <?= drupal_render_children($form);?>
            </div>
        </div>
        <div class="panel panel-default">
            <div class="panel-body">
            <?= render($form['additional_settings']);?>
            </div>
        </div>
    </div>
    <div class="col-md-4">
        <div class="panel panel-default">
            <div class="panel-heading">
                Actions
            </div>
            <div class="panel-body">
                <?= render($form['actions']);?>
            </div>
        </div>
    </div>
</div>
