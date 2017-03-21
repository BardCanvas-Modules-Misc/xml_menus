<?php
/**
 * XML Menus editor
 *
 * @package    BardCanvas
 * @subpackage xml_menus
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

include "../config.php";
include "../includes/bootstrap.inc";

if( ! $account->_is_admin ) throw_fake_401();
$_engine_template = $settings->get("engine.template");

if( $_POST["mode"] == "save" )
{
    @file_put_contents("{$config->datafiles_location}/xml_menu_menu_code.dat", stripslashes($_POST["xml_code"]));
    @file_put_contents("{$config->datafiles_location}/xml_menu_header_code.dat", stripslashes($_POST["html_head"]));
}

$title = $current_module->language->editor_title;
$template->set_page_title($title);
$template->page_contents_include = "contents/editor.inc";
include "{$template->abspath}/admin.php";
