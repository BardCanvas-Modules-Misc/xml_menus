<?php
/**
 * XML Menus - header additions
 *
 * @package    BardCanvas
 * @subpackage xml_menus
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

if( ! file_exists("{$config->datafiles_location}/xml_menu_header_code.dat") ) return;

echo "\n\n<!-- XML Menus: header code -->\n\n";
echo @file_get_contents("{$config->datafiles_location}/xml_menu_header_code.dat");
