<?php
// $Id$

/**
 * @file
 *   Views filter override.
 */

/**
 * Filter on revision state, i.e. pending, archived, current.
 */
class revisioning_handler_filter_revision_state extends views_handler_filter_string {

  /**
   *
   * @see sites/all/modules/views/handlers/views_handler_filter#query()
   */
  function query() {
    // Not calling parent::query() as it will treat 'state' as a real db field.
    $this->ensure_my_table();
  }
}