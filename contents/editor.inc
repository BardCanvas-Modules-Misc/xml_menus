<?php
/**
 * XML Menus editor
 *
 * @package    BardCanvas
 * @subpackage xml_menus
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */
?>

<!-- CodeMirror -->
<link rel="stylesheet" href="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/lib/codemirror.css">
<link rel="stylesheet" href="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/addon/fold/foldgutter.css">
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/lib/codemirror.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/addon/fold/foldcode.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/addon/fold/foldgutter.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/addon/fold/brace-fold.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/addon/fold/xml-fold.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/addon/fold/indent-fold.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/addon/fold/markdown-fold.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/addon/fold/comment-fold.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/mode/xml/xml.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/mode/javascript/javascript.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/mode/css/css.js"></script>
<script                 src="<?=$config->full_root_path?>/lib/CodeMirror-5.16.2/mode/htmlmixed/htmlmixed.js"></script>
<style type="text/css">
    .CodeMirror {
        border:      1px solid silver;
        height:      auto;
        font-family: 'Lucida Console', 'Courier new', Courier, monospace !important; font-size: 8pt;
        width:       100%;
    }
    .CodeMirror-scroll { min-height: 100px; }
    td.indented { padding-left: 18px; }
    td.details  { width: 60%; }
    td.control  { width: 40%; }
    
    .toplinks          { margin-bottom: 10px; }
    .toplinks .toplink { margin: 0 5px 5px 0; font-family: "Arial Narrow", Arial, Arial, Helvetica, sans-serif; }
    
    #settings_filter                    { display: inline-block; font-size: 24px; line-height: 24px; white-space: nowrap; }
    #settings_filter input[type="text"] { padding-right: 24px; }
    #settings_filter .cleanup           { position: absolute; margin-left: -24px; margin-top: 8px; cursor: pointer; color: ButtonText; }
    
    .highlight { background-color: yellow }
</style>

<script type="text/javascript">
    $(document).ready(function()
    {
        $('textarea.CodeMirror').each(function()
        {
            var mode    = $(this).attr('mode');
            var element = $(this).get(0);
        
            CodeMirror.fromTextArea(element, {
                viewPortMargin: Infinity,
                lineNumbers:    true,
                mode:           mode,
                foldGutter:     true,
                gutters:        ["CodeMirror-linenumbers", "CodeMirror-foldgutter"]
            });
        });
    });
</script>

<h1>
    <button class="pull-right" onclick="location.href = './'">
        <i class="fa fa-refresh"></i>
        <?= $language->reload ?>
    </button>
    
    <?= $current_module->language->editor_title ?>
</h1>

<form id="menu_data" method="post" action="<?= $_SERVER["PHP_SELF"] ?>">
    <input type="hidden" name="mode" value="save">
    
    <? $info_handler = "{$current_module->name}_menu_code"; ?>
    <section>
        <h2>
            <?= $current_module->language->menu_code ?>
            <span class="pseudo_link" onclick="toggle_info_section('<?= $info_handler ?>')"><span
                  class="fa fa-question-circle-o" title="<?= $language->toggle_info ?>"></span></span>
        </h2>
        <div class="framed_content">
            <div class="info_handler framed_content state_highlight" id="<?= $info_handler ?>"
                 style="margin-top: 0; white-space: normal; <? if($account->engine_prefs[$info_handler] == "hidden") echo "display: none;"; ?>">
                <span class="fa fa-times-circle pseudo_link pull-right" onclick="toggle_info_section('<?= $info_handler ?>')"></span>
                <span class="fa fa-question-circle"></span>
                <?= $current_module->language->format_instructions ?>
            </div>
            <textarea class="CodeMirror" mode="xml" name="xml_code"><?php
                echo htmlspecialchars(@file_get_contents("{$config->datafiles_location}/xml_menu_menu_code.dat"));
            ?></textarea>
        </div>
    </section>
    
    <? $info_handler = "{$current_module->name}_html_for_header"; ?>
    <section>
        <h2>
            <?= $current_module->language->html_in_header ?>
            <span class="pseudo_link" onclick="toggle_info_section('<?= $info_handler ?>')"><span
                  class="fa fa-question-circle-o" title="<?= $language->toggle_info ?>"></span></span>
        </h2>
        <div class="framed_content">
            <div class="info_handler framed_content state_highlight" id="<?= $info_handler ?>"
                 style="margin-top: 0; white-space: normal; <? if($account->engine_prefs[$info_handler] == "hidden") echo "display: none;"; ?>">
                <span class="fa fa-times-circle pseudo_link pull-right" onclick="toggle_info_section('<?= $info_handler ?>')"></span>
                <span class="fa fa-question-circle"></span>
                <?= $current_module->language->html_info ?>
            </div>
            <textarea class="CodeMirror" mode="htmlmixed" name="html_head"><?php
                echo htmlspecialchars(@file_get_contents("{$config->datafiles_location}/xml_menu_header_code.dat")); 
            ?></textarea>
        </div>
    </section>
    
    <div align="center">
        <button type="submit" class="big_form_submit_button">
            <i class="fa fa-save"></i>
            <?= $language->save ?>
        </button>
    </div>
</form>
