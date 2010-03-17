<?php
// $Id$

/**
 * Field handler to show a revision's moderation state, i.e. pending, current or archived.
 */
class revisioning_handler_field_revision_state extends views_handler_field {
  
  function construct() {
    parent::construct();
    // Collect additional data required prior to rendering
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['vid'] = 'vid';
    $this->additional_fields['published'] = array('table' => 'node', 'field' => 'status');
    $this->additional_fields['current_vid']  = array('table' => 'node', 'field' => 'vid');
    $this->additional_fields['type'] = array('table' => 'node', 'field' => 'type');
  }

  /**
   * 
   * @see sites/all/modules/views/includes/views_handler#access()
   */
  function access() {
    return user_access('view revisions');
  }

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
   *   o node_type (content type)
   *   o node_revisions_nid (node id)
   *   o node_status (published flag)
   *   o node_vid (current revision id)
   *
   * @see sites/all/modules/views/handlers/views_handler_field#render($values)
   */
  function render($values) {
    $nid = $values->{$this->aliases['nid']};
    $vid = $values->{$this->aliases['vid']};
    $published = $values->{$this->aliases['published']};
    $current_vid = $values->{$this->aliases['current_vid']};
    $is_initial_unpublished_draft = !$published && (node_tools_get_number_of_revisions($nid) == 1);
    $is_pending = ($vid > $current_vid) || $is_initial_unpublished_draft;
    $state_code = $is_pending ? REVISION_PENDING : ($vid == $current_vid ? REVISION_CURRENT : REVISION_ARCHIVED);
    $description = revisioning_revision_states($state_code);
    $content_type = $values->{$this->aliases['type']};
    if (!node_tools_content_is_moderated($content_type)) {
      $description .= t(' (not moderated)');
    }
    return $description;
  }
}
