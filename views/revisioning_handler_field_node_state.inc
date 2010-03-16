<?php
// $Id$

/**
 * Field handler to show a revision's moderation state, i.e. pending, current or archived.
 */
class revisioning_handler_field_node_state extends views_handler_field {
  
  function construct() {
    parent::construct();
    // Collect additional data required prior to rendering
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['vid'] = 'vid';
    $this->additional_fields['published'] = array('field' => 'status');
  }

  /**
   * 
   * @see sites/all/modules/views/includes/views_handler#access()
   *
  function access() {
    return user_access('view revisions'); // TODO use Module Grants
  }
  */
  /**
   * 
   * @see sites/all/modules/views/handlers/views_handler_field#query()
   */
  function query() {
    // Not calling parent::query() as it will treat 'state' as a real db field.
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Note that $contains: 
   *   o vid
   *   o node_revisions_nid (node id)
   *   o node_status (published flag)
   *   o node_vid (current revision id)
   *
   * @see sites/all/modules/views/handlers/views_handler_field#render($values)
   */
  function render($values) {
    $nid = $values->{$this->aliases['nid']};
    $published = $values->{$this->aliases['published']};
    $current_vid = $values->{$this->aliases['vid']};

    $is_initial_unpublished_draft = !$published && (node_tools_get_number_of_revisions($nid) == 1);
    $latest_vid = revisioning_get_latest_revision_id($nid);
    $is_pending = ($latest_vid > $current_vid) || $is_initial_unpublished_draft;
    return $is_pending ? t('Revision pending') : ($published && ($latest_vid == $current_vid) ? t('Up to date') : 'Archived');
  }
}
