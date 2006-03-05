Drupal bbcode.module README.txt
==============================================================================

The Drupal bbcode.module adds a BBCode filter to Drupal. This allows you
to use HTML-like tags as an alternative to HTML itself for adding markup
to your posts. BBCode is easier to use than HTML and helps to prevent
malicious users from disrupting your site's formatting.

See the help screen of the module (or the code) for information on which
tags and variants are supported. This implementation is not necessarily the
same as the original BBCode implementaion.
 
Note that this filter also recognizes and converts URLs and email addresses
to links automatically.

Installation
------------------------------------------------------------------------------
 
  - Download the BBCode module from http://drupal.org/project/bbcode

  - Copy bbcode.module, bbcode-help.inc and bbcode-filter.inc to your modules
    directory (suggestion: create a subdirectory .../modules/bbcode/)

  - Enable the module as usual from Drupal's admin pages 
    (Administer -> Modules)
 
Configuration
------------------------------------------------------------------------------

  - Before using BBCode you need to enable the BBCode filter in an input
    format (see Administer -> Input formats -> add input format)

  - You can enable/ disable the following features in the configuration page
    of the input format in which BBCode is enabled:

    * Javascript encoding of emails
    * Smart paragraph and line breaks
    * Print debugging info

  - If you've disabled "smart paragraph and line breaks", you need to enable
    Drupal's "Line break converter" with the BBCode filter. Don't use both
    together!

  - If you would like to use BBCode as a replacement for HTML, you could
    enable Drupal's "HTML filter" to remove or escape user entered HTML tags.

  - If you've enabled multiple filters, you may need to rearrange them to
    ensure they execute in the correct order.

Complementing Modules
------------------------------------------------------------------------------

The following optional modules may be used to enhance your BBCode 
installation:

  - BBCode Formatting Bar - http://drupal.org/node/24875

  - Smileys module - http://drupal.org/project/smileys

Note: these are different independent projects. Please do not report issues
with them as BBCode problems!

Credits / Contacts
------------------------------------------------------------------------------

  - The original author of this module is Alastair Maw, who can be reached at
    drupal-bbcode[at]almaw.com. 

  - Gabor Hojtsy (goba[at]php.net) also contributed to the module and is the 
    active maintainer.

  - Javascript encoding of emails by László Bácsi (lackac[at]math.bme.hu).

  - Frank Naude converted this module to the Drupal 4.7 Forms API and added 
    support for more BBCode tags.

TODO List
------------------------------------------------------------------------------

 - Do not allow users to disrupt the HTML output with malicious
   parameters (color, url, etc.).

 - Configuration of which bbcode tags are allowed.

