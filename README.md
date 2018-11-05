islandora_datastream_blocks
==============

This module allows a drupal block to be configured to display a datastream related to the current islandora object.

## Configuration

There are two steps to configuring a block to appear.  The first step defines which datastreams to expose as Drupal blocks.  This is done at `admin/islandora/tools/islandora_datastream_blocks` by specifying the datastream ID values that you want to use (for example "TN,DESC")*.  After this step, these blocks will be exposed to Drupal -- and they can be assigned to a region in any theme using the Drupal at `admin/structure/block`.

*In the above example, DESC is a HTML formatted datastream that is created and managed with the  [islandora_datastream_htmleditor](https://github.com/ulsdevteam/islandora_datastream_htmleditor) module which uses the Ckeditor WYSIWYG editor to add HTML to any object.*

## Author / License

Written by Willow Gillingham for the [University of Pittsburgh](http://www.pitt.edu).  Copyright (c) University of Pittsburgh.

Released under a license of GPL v2 or later.
