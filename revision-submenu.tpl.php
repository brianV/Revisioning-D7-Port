<?php
// $Id$
/**
 * @file
 * revision-submenu.tpl.php, included by revision.tpl.php
 * This template handles the layout of the submenu that appears above the
 * body text of the displayed revision.
 *
 * Variables available:
 * - $links: an array of <a>-tags
 */
?>
<div class="submenu revision">
  <?php print implode(' | ', $links); ?>
</div>
<hr/>