<?php
// $Id$
/**
 * @file
 * revision.tpl.php
 * Template to render the body of the revision and the menu above it.
 *
 * Variables available:
 * - $links: an array of <a>-tags, passed on to submenu-revision.tpl.php
 * - $content: body text of the node revision
 */
?>
<?php
  include "submenu-revision.tpl.php";
  print $content;