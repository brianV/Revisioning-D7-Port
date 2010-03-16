<?php
// $Id$

/**
 * @file
 *   Views filter override.
 */

/**
 * Filter on node state, i.e. pending, archived, current.
 */
class revisioning_handler_filter_node_state extends views_handler_filter_string {

  /**
   *
   * @see sites/all/modules/views/handlers/views_handler_filter#query()
   */
  function query() {
    // Not calling parent::query() as it will treat 'state' as a real db field.
    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";
    $upper = $this->case_transform();

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($field, $upper);
    }
  }
  
  function op_equal($field, $upper) {
    // operator is either = or !=
    $this->query->add_where($this->options['group'], "$upper(%s) $this->operator $upper('%s')", $field, $this->value);
  }
}