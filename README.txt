$Id$

DESCRIPTION
===========
This modules forces new (unpublished) content and edits to current content to
first go into a queue for review by a moderator/publisher, rather than 
immediately becoming "live", i.e. visible to the public.

We took our inspiration from the Revision Moderation module by Angie Byron,
but found that a patch could not implement the deviating functionality our
customers required, which would change the current behaviour of the RM module
and surprise existing users.

In the RM module the permissions to edit and revert/publish content are lumped
together, so that it isn't possible to enforce separation of these
responsibilites by role. This module allows you to assign distinct permissions
for authors (to only create and edit content) and moderator roles (to review,
publish, revert, unpublish and optionally delete content).
No unnessary revisions are created when saving a revision that is pending.
Menu navigation has been altered so that users first pick the desired 
revision before being allowed to view, edit, publish, revert, unpublish or 
delete.
Triggers are provided for the publish, unpublish and revert events.
By taking advantage of the Module Grants module this module integrates better
with the Workflow and Taxonomy Access Control (Lite) modules. This means that
you can easily implement fine-grained content access control based on
categories as well as workflow states. With Revisioning installed this all
works for both published and unpublished content.
There's also a "publish-pending-revision" action that may be triggered from
a workflow state transition (like "in review"->"publish").
Unlike RM, Revisioning does not require any additional database tables.

INSTALLATION
============
0. Install the Module Grants module as per its README instructions.
   Optionally install the Diff module if you want to compare revisions and
   highlight the differences.
1. Place the "revisioning" folder in your "sites/all/modules" directory.
2. Enable the module under Administer >> Site building >> Modules.
3. Under Administer >> Content >> Content types, click "edit" next to the
   content types for which you wish to enable/disable revisioning. Under
   "Workflow Settings", Default Options, tick both the "Create new revision"
   and "New revision in draft, pending moderation" checkboxes. Also in this
   section UNtick "Published", so that all new content is created in an 
   unpubished state, i.e. invisible to the public.
4. The module creates a new root menu item, named "My content" with three tabs:
   o "Viewable" shows all nodes that may be viewed by the logged-in user
   o "Editable" shows all nodes that may be edited by the logged-in user
   o "Pending", a subset of "Editable" showing nodes that have been revised
     recently and are awaiting review and publication by an authorised role.
   These menu options will be visible only to roles that have the "access
   content summary" permission, as granted by the administrator.
5. Grant to the various roles the view/delete/revert revisions permissions
   (node access section) and the "edit revisions" permission (revisioning
   section). Typically you'd give authors the "view revisions" and
   "edit revisions" permissions, while moderators will get the same as well
   as the "publish/revert revisions" permission. Neither require the 
   "administer nodes" permission, which is a good thing as this gives 
   excessive rights.

USAGE
=====
You should now be in business. Log in as one of the authors and Create content.
Save. Log out, then log in as a moderator to publish the content via the
My content >> Pending tab. Click on the title of the post, then open the 
desired revision by clicking on the date. Check the content, the press the 
publish link.
Note that up to this point content isn't visible to the public.
Log in as an author again and revise the content. You will notice that upon
saving the new revision, the one visible to the public remains unchanged.
Log in as a moderator again to promote (publish), after optional edits, the
revised content to live.
You can use this module in combination with TAC or TAC-Lite for fine-grained
access control based on vocabularies (such as "region" or "department")
associated with the various content types. Be aware that any permissions
given in the "node module" section override those granted via TAC/TAC-Lite,
so you probably only want to assign a few creation permissions in the node
module and do the view, update and delete grants via TAC/TAC-Lite.
In addition you may want to install the Workflow module to further segragate
the author and moderator roles via access control based on states such as
"in draft", "in review" and "live". Workflow also allows you to notify users
when state transitions occur (e.g. when a moderator declines or publishes a
submitted revision).
A step-by-step guide on the usage of the Revisioning module in combination
with the TAC-Lite and Workflow modules can be found on www.drupal.org.

AUTHOR
======
Rik de Boer for IBS (Melbourne, Australia), inspired by the Revision 
Moderation module by Angie Byron (www.lullabot.com)
