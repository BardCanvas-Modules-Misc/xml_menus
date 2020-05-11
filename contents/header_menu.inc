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
use hng2_modules\categories\categories_repository;

global $modules;

$config->globals["@xml_menus:current_menu_tree"] = null;

if( ! file_exists("{$config->datafiles_location}/xml_menu_menu_code.dat") ) return;
if( filesize("{$config->datafiles_location}/xml_menu_menu_code.dat") == 0 ) return;

$cats_repo = new categories_repository();
$menu_xml  = simplexml_load_string(
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
    
    $is_cats_fill = trim($menu["categories_autofill"]);
    if( ! empty($is_cats_fill) && (empty($id) || ! $modules["categories"]->enabled) ) continue;
    
    if( empty($is_cats_fill) )
    {
        if( ! empty($link) && stristr($_SERVER["REQUEST_URI"], $link) !== false && $link != "/" )
            $classes  .=  " current";
    }
    else
    {
        $max_category_level  = trim($menu["max_category_level"]);
        $excluded_categories = preg_split("/\s*,\s*/", trim($menu["excluded_categories"]));
        
        $listing = $cats_repo->get_for_listings(0, 0, "parent_category, title", true);
        if( ! empty($listing) )
        {
            $reordered = array();
            foreach($listing as $row) $reordered[strtolower("/" . trim(dirname($row->path) . "/" . $row->title, "/"))] = $row;
            ksort($reordered);
            $is_tree = false;
            foreach($reordered as $path => $cat_record)
            {
                if( strpos($path, "/", 1) !== false )
                {
                    $is_tree = true;
                    break;
                }
            }
            if( $is_tree) $listing = $reordered;
            foreach($listing as $row)
            {
                $level = count(explode("/", $row->path)) - 2;
                if( $max_category_level > 0 && $level > $max_category_level ) continue;
                if( in_array($row->slug, $excluded_categories) ) continue;
                
                $space = 6 + ($level * 24);
                $item = $menu->addChild("item");
                $item->addAttribute("icon", "fa-folder");
                $item->addAttribute("style", "padding-left: {$space}px;");
                $item->addChild("caption", htmlspecialchars($row->title));
                $item->addChild("link", "{$config->full_root_path}/category/$row->slug");
            }
        }
    }
    
    if( empty($menu->item) )
        $template->add_menu_item(
            $caption,
            "<a class='main_menu_item $classes' id='$id' href='{$link}'>
                <span class='fa {$icon}'></span>
                {$caption}
            </a>",
            $priority
        );
    else
        $template->add_menu_item(
            $caption,
            "<span class='main_menu_item $classes is_submenu_trigger' data-module='xml_menus' style='cursor: pointer;' 
                  id='$id' data-submenu='#{$id}_menu_items'>
                <span class='fa {$icon}'></span>
                <span clasS='caption'>{$caption}</span>
                <span class='menu_toggle'>
                    <span class='fa fa-caret-down'></span>
                    <span class='fa fa-caret-up' style='display: none;'></span>
                </span>
            </span>",
            $priority
        );
}

$config->globals["@xml_menus:current_menu_tree"] = $menu_xml;
