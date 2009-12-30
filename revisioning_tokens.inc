<?php
// $Id$

/**
 * @file
 * Tokens pertaining to the Revisioning module.
 * Supported are:
 *   vid: node revision id
 */

/**
 * Implementation of hook_token_list().
 */
function revisioning_token_list($type = 'all') {
  if ($type == 'node' || $type == 'all') {
    $tokens = array();
    $tokens['node']['vid'] = t('Node revision ID');
    return $tokens;
  }
}

/**
 * Implementation of hook_token_values().
 */
function revisioning_token_values($type, $object = NULL, $options = array()) {
  $values = array();
  switch ($type) {
    case 'node':
      $values['vid'] = $object->vid;
      break;

    case 'op':
      switch ($object) {
        case 'publish':
        case 'revert':
        case 'unpublish':
          $node = node_load(array('nid' => arg(1)));
          $values = node_token_values('node', $node, $options);
          $values['vid'] = $node->vid;
      }
      break;
  }
  return $values;
}
