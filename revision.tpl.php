<?php
// $Id$
/**
 * @file
 * revision.tpl.php
 * Template to render the body of the revision and the menu above it.
 *
 * Variables available:
 * - $submenu_links: an array of <a>-tags, passed on to revision-submenu.tpl.php
 * - $content: body text of the node revision
 */
?>
<?php
  include "revision-submenu.tpl.php";
  print $content;