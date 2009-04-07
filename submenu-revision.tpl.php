<?php
// $Id$
/**
 * @file
 * submenu-revision.tpl.php
 * This template handles the layout of the submenu that appears above the
 * body text of the displayed revision.
 *
 * Variables available:
 * - $links: an array <a>-tags
 */
?>
<div class="submenu submenu-revision">
  <?php print implode(' | ', $links); ?>
</div>
<hr/>