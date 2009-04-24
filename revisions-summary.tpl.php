<?php
// $Id$
/**
 * @file
 * revisions-summary.tpl.php
 * Template to handle layout details of the submenu that appears above the
 * summary of node revisions.
 *
 * Variables available:
 * - $links: an array of <a>-tags
 * - $content: summary of node revisions (as a table)
 */
?>
<?php if ($links) { ?>
  <div class="submenu revisions">
    <?php print implode(' <strong>|</strong> ', $links); ?>
  </div>
  <hr/>
<?php } ?>
<?php print $content;
