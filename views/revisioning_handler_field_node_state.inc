<?php
// $Id$

/**
 * Field handler to show a revision's moderation state, i.e. pending, current or archived.
 */
class revisioning_handler_field_node_state extends views_handler_field {
  
  function construct() {
    parent::construct();
    // Request node fields required to calculate the 'state' when rendering
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['vid'] = 'vid';
    $this->additional_fields['published'] = array('field' => 'status');
  }

  /**
   * 
   * @see sites/all/modules/views/includes/views_handler#access()
   */
  function access() {
    return user_access('access content');
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
   * Implement the rendering of the state value.
   *
   * Note that $values contains:
   *   o nid
   *   o node_type (content type) 
   *   o node_vid (current revision id)
   *   o node_status (published flag)
   *
   * @see sites/all/modules/views/handlers/views_handler_field#render($values)
   */
  function render($values) {
    $published = $values->{$this->aliases['published']};
    $nid = $values->{$this->aliases['nid']};
    $current_vid = $values->{$this->aliases['vid']};
    $latest_vid = revisioning_get_latest_revision_id($nid);
    $is_initial_unpublished_draft = !$published && (node_tools_get_number_of_revisions($nid) == 1);
    $is_pending = ($latest_vid > $current_vid) || $is_initial_unpublished_draft;
    $description = $is_pending
      ? t('Revision pending')
      : ($published && ($latest_vid == $current_vid) ? t('Current, published') : t('Archived'));
    $content_type = $values->{$this->aliases['type']};
    if (!node_tools_content_is_moderated($content_type)) {
      $description .= t(' (not moderated)');
    }
    return $description;
  }
}
