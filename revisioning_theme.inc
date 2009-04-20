<?php
// $Id$

/**
 * @file
 * Include file for revisioning.module, dealing with all theming aspects.
 */

/**
 * Implementation of hook_theme().
 * Register the theme_hooks() available in this module, with their arguments
 * and default values.
 */
function revisioning_theme() {
  return array(
    'submenu_revision' => array(
      'arguments' => array('links' => NULL),
      'template' => 'submenu-revision', // submenu-revision.tpl.php
    ),
    'revision' => array(
      'arguments' => array('links' => NULL, 'content' => NULL),
      'template' => 'revision', // revision.tpl.php
    ),
    'revisions_summary' => array(
      'arguments' => array('links' => NULL, 'content' => NULL),
      'template' => 'revisions-summary', // revisions-summary.tpl.php
    )
  );
}

/**
 * Theme the revisions summary of the supplied node via the revisions_summary
 * template.
 * 
 * Uses the following subthemes:
 * o 'table_revisions', falling back to theme.inc/theme_table() if not defined
 * o 'placeholder' (to display current revision status)
 * o 'username'
 *
 * @param $node
 *   Node whose revisions to display
 * @return
 *   Themed table HTML
 *
 * @ingroup themeable
 */
function _theme_revisions_summary($node) {
  $css_path = drupal_get_path('module', 'revisioning') .'/revisioning.css';
  drupal_add_css($css_path, 'module', 'all', FALSE); // also loads /revisioning-rtl.css
  
  drupal_set_title(t('Revisions of %title', array('%title' => $node->title)));
  $show_taxonomy_terms = module_exists('taxonomy');

  $revisions = _get_all_revisions_for_node($node->nid, $show_taxonomy_terms);

  drupal_set_message(format_plural(count($revisions), 
    'This content has only one revision', 
    'This content has @count revisions.'));
  
  // Set up some links according to grants
  $links = array();
  if ($node->status && module_grants_node_revision_access('unpublish current revision', $node)) {
    $links[] = l(t('Unpublish current revision'), "node/$node->nid/unpublish");
  }
  if (module_grants_node_revision_access('delete revisions', $node)) {
    $links[] = l(t('Delete all revisions'), "node/$node->nid/delete");
  }
  // Set up the header
  $header = array(t('Revision'));
  if ($show_taxonomy_terms) {
    $header[] = t('Term');
  }
  $header[] = t('Status');
  $rows = array();

  foreach ($revisions as $revision) {
    $row = array();
    $base_url = "node/$node->nid/revisions/$revision->vid";
    $first_cell = t('Saved !date by !username', 
      array('!date' => l(format_date($revision->timestamp, 'small'), "$base_url/view"),
            '!username' => theme('username', $revision)))
      . ($revision->log != '' ? '<p class="revision-log">'. filter_xss($revision->log) .'</p>' : '');
    if ($revision->vid == $node->vid) {
      $row[] = array('data' => $first_cell, 'class' => 'revision-current');
      if ($show_taxonomy_terms) {
        $row[] = array('data' => $revision->term, 'class' => 'revision-current');
      }
      $row[] = array('data' => theme('placeholder', $revision->status ? t('current revision (published)') : t('current revision (unpublished)')),
                     'class' => 'revision-current');
    }
    else {
      $row[] = array('data' => $first_cell);
      if ($show_taxonomy_terms) {
        $row[] = array('data' => $revision->term);
      }
      $row[] = array('data' => ($revision->vid > $node->vid) ? t('pending moderation') : t('old'));
    }
    $rows[] = $row;
  }
  $attributes = array('class' => 'table-revisions');
  $content = theme(array('table_revisions', 'table'), $header, $rows, $attributes, $caption = NULL);
  return theme(array('revisions_summary'), $links, $content);
}

/**
 * Implement (in your own module) the function below if you want to override
 * the way in which the Revisions table is constructed.
 * If you do, don't forget to register this theme_hook() via <your_module>_theme()
 * in a manner similar to revisioning_theme() in this file.
 * 
 * @param $header
 * @param $rows
 * @return themed HTML, see for instance /includes/theme.inc/theme_table()
 *
 * @ingroup themeable
 * 
function theme_table_revisions($header, $rows) {
}
 */

/**
 * Implementation of <mymodule>_preprocess_hook().
 * Gets called after the node has been fleshed out, but before it is rendered
 * (via node.tpl.php). This gives us the opportunity to insert on the page some 
 * hyperlinks that operate on the content shown, provided the theme is rendered
 * through an ENGINE -- Chameleon, for instance, is NOT.
 * Earlier versions did this by (ab)using drupal_set_message($links).
 * Here we prepend the links, themed as a 'revision', to the content. 
 * This ensures the links are visible in all existing templates.
 * 
 * Uses the following subthemes:
 * o submenu-node.tpl.php, falling back to theme.inc/theme_submenu() if not defined
 *
 * @param $variables
 * @return void
 */
function revisioning_preprocess_node(&$variables, $hook) {
  $css_path = drupal_get_path('module', 'revisioning') .'/revisioning.css';
  drupal_add_css($css_path, 'module', 'all', FALSE); // also loads /revisioning-rtl.css
  $links = generate_links_according_to_permissions($variables['node']);
  $variables['content'] = theme(array('revision'), $links, $variables['content']);
}

/**
 * Renderes the submenu links as part of the content. Use for themes like 
 * Chameleon that don't employ a theme engine.
 * 
 * Uses the following subtheme:
 * o submenu-revision.tpl.php, falling back to theme.inc/theme_submenu() if not defined
 * 
 * @param $node
 * @return themed HTML
 */

function _theme_content_menu(&$node) {
  $css_path = drupal_get_path('module', 'revisioning') .'/revisioning.css';
  drupal_add_css($css_path, 'module', 'all', FALSE); // also loads /revisioning-rtl.css
  $links = generate_links_according_to_permissions($node);
  $node->body = theme(array('submenu_revision', 'submenu'), $links) . $node->body;
}
