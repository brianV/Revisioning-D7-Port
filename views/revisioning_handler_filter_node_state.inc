<?php
// $Id$

/**
 * @file
 *   Views filter override.
 */

/**
 * Filter on node state, i.e. pending, archived, current.
 */
class revisioning_handler_filter_node_state extends views_handler_filter_in_operator {

  /**
   * Override the query, in particular the WHERE clause.
   *
   * @see sites/all/modules/views/handlers/views_handler_filter_in_operator#query()
   */
  function query() {
    if (empty($this->value)) {
      return;
    }
    $node_table = $this->ensure_my_table();
    $revisions_table = $this->query->ensure_table('node_revisions');
    $subclauses = array();
    foreach ($this->value as $state_code) {
      switch ($state_code) {
        case REVISION_ARCHIVED:
          $subclauses[] = "($node_table.status=0)";
          break;
        case REVISION_CURRENT:
          $subclauses[] = "($node_table.status=1 AND $node_table.vid=(SELECT MAX(vid) FROM $revisions_table WHERE nid=$node_table.nid))";
          break;
        case REVISION_PENDING:
          $subclauses[] = "($node_table.vid<(SELECT MAX(vid) FROM $revisions_table WHERE $node_table.nid=$revisions_table.nid) OR ($node_table.status=0 AND (SELECT COUNT(vid) FROM $revisions_table WHERE vid=$node_table.vid)=1))";
          break;
      }
    }
    if (!empty($subclauses)) {
      $where_clause = implode(' OR ', $subclauses);
      if ($this->operator == 'not in') {
        $where_clause = "!($where_clause)";
      }
      $this->query->add_where($this->options['group'], $where_clause);
    }
  }

  function get_value_options() {
    $this->value_title = t('Revision state');
    $this->value_options = revisioning_revision_states();
  }
}