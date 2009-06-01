<?php
// $Id$
/**
 * @file
 * revision-submenu.tpl.php, included by revision.tpl.php
 * This template handles the layout of the submenu that appears above the
 * body text of the displayed revision.
 *
 * Variables available:
 * - $submenu_links: an array of <a>-tags
 */
?>
<?php if ($submenu_links): ?>
  <div class="submenu revision">
    <?php print implode(' | ', $submenu_links); ?>
  </div>
  <hr/>
<?php endif;
