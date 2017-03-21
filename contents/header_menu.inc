<?php
/**
 * XML Menus - main menu items renderer
 *
 * @package    BardCanvas
 * @subpackage xml_menus
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 *             
 * @var account  $account
 * @var settings $settings
 * @var config   $config
 * @var template $template
 */

use hng2_base\account;
use hng2_base\config;
use hng2_base\settings;
use hng2_base\template;

if( ! file_exists("{$config->datafiles_location}/xml_menu_menu_code.dat") ) return;
if( filesize("{$config->datafiles_location}/xml_menu_menu_code.dat") == 0 ) return;

$menu_xml = simplexml_load_string(
    "<?xml version=\"1.0\" encoding=\"utf-8\"?><xml_menu>\n" .
    file_get_contents("{$config->datafiles_location}/xml_menu_menu_code.dat") .
    "\n</xml_menu>"
);
foreach($menu_xml->menu as $menu)
{
    $min_level = trim($menu["min_level"]); if( empty($min_level) ) $min_level = 0;
    $max_level = trim($menu["max_level"]); if( empty($max_level) ) $max_level = 255;
    if( $account->level < $min_level || $account->level > $max_level ) continue;
    
    $id        = trim($menu["id"]);
    $priority  = trim($menu["priority"]);
    $icon      = trim($menu["icon"]);
    $caption   = trim($menu["caption"]);
    $link      = trim($menu["href"]);
    $classes   = trim($menu["class"]);
    
    if( ! empty($link) && stristr($_SERVER["REQUEST_URI"], $link) !== false && $link != "/" )
        $classes  .=  " current";
    
    if( empty($menu->item) )
        $template->add_menu_item(
            $caption,
            "<a class='main_menu_item <? $classes ?>' id='$id' href='{$link}'>
                <span class='fa {$icon}'></span>
                {$caption}
            </a>",
            $priority
        );
    else
        $template->add_menu_item(
            $caption,
            "<span class='main_menu_item $classes is_submenu_trigger' data-module='foroelite_menus' style='cursor: pointer;' 
                  id='$id' data-submenu='#{$id}_menu_items'>
                <span class='fa {$icon}'></span>
                {$caption}
                <span class='menu_toggle'>
                    <span class='fa fa-caret-down'></span>
                    <span class='fa fa-caret-up' style='display: none;'></span>
                </span>
            </span>",
            $priority
        );
}
