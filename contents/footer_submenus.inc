<?php
/**
 * XML Menus - submenus renderer
 *
 * @package    BardCanvas
 * @subpackage xml_menus
 * @author     Alejandro Caballero - lava.caballero@gmail.com
 */

if( empty($config->globals["@xml_menus:current_menu_tree"]) ) return;

$menu_xml = $config->globals["@xml_menus:current_menu_tree"];

foreach($menu_xml->menu as $menu):
    if( empty($menu->item) ) continue;
    
    $id = trim($menu["id"]) . "_menu_items";
    ?>
    
    <!-- xml menus :: footer -->
    
    <div id="<?= $id ?>" class="dropdown_menu" style="display: none;">
        <?
        foreach($menu->item as $item):
            $user_scope = trim($item["user_scope"]);
            $icon       = trim($item["icon"]);
            $caption    = trim($item->caption);
            $link       = trim($item->link);
            $target     = trim($item->link["target"]);
            $classes    = trim($item["class"]);
            $style      = trim($item["style"]);
            
            $min_level = trim($item["min_level"]); if( empty($min_level) ) $min_level = 0;
            $max_level = trim($item["max_level"]); if( empty($max_level) ) $max_level = 255;
            if( $account->level < $min_level || $account->level > $max_level ) continue;
            
            if( $user_scope == "offline" &&   $account->_exists ) continue;
            if( $user_scope == "online"  && ! $account->_exists ) continue;
            if( $link == "@user_home"    && ! $account->_exists ) continue;
            
            if( $link == "@user_home" ) $link = "$config->full_root_path/user/{$account->user_name}";
    
            $added_class = "";
            if( ! empty($link) && stristr($_SERVER["REQUEST_URI"], $link) !== false && $link != "/" )
                $added_class =  "current";
            
            if( $item["is_separator"] ): ?>
                <hr>
            <? else: ?>
                <a class="main_menu_item <?= "$classes $added_class" ?>" <? if( ! empty($target)) echo "target='$target'"; ?>
                   style="cursor: pointer; <?= $style ?>" href="<?= $link ?>">
                    <? if( ! empty($icon) ): ?><span class="fa <?= $icon ?>"></span><? endif; ?>
                    <span class="caption"><?= $caption ?></span>
                </a>
            <? endif; ?>
        <? endforeach; ?>
    </div>
    
    <?
endforeach;
