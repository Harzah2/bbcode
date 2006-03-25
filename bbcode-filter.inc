<?php
// $Id$

function _bbcode_filter_process(&$body, $format = -1) {
  
  $quote_text = t('Quote');
  $quote_user = t('\\1 wrote');

  $mode = variable_get("bbcode_paragraph_breaks", 2);
  if ($mode) {		// Apply line and paragraph breaks

    // Step 1: strip preformatted code blocks from text
    $pre = array(); $i = 0;
    while ($pre_str = stristr($body, '[code]')) {
      $pre_str = substr($pre_str, 0, strpos(strtolower($pre_str), '[/code]')+7);
      $body    = str_replace($pre_str, "***pRe_sTrInG$i***", $body);
      $pre[$i] = str_replace(array('<', '>'), array('&lt;', '&gt;'), $pre_str);
      $i++;
    }

    // Step 2: Apply line and paragraph breaks (skipping preformatted code)
    if ($mode == 1) 	// Line breaks only
      $body = nl2br($body);
    if ($mode == 2) {	// Line and paragraph breaks
      $body  = preg_replace("/(\r\n|\n|\r)/", "\n", $body);
      $body  = preg_replace("/\n\n+/", "\n\n", $body);
      $parts = explode("\n\n", $body);
      for ($i=0; $i<sizeof($parts); $i++) {
         // No linebreaks if paragraph starts with an HTML tag
         if ( !preg_match("/^<.*>/", $parts[$i]) ) 
           $parts[$i] = nl2br($parts[$i]);

         // Some tags may not be in paragraph blocks
         if ( !preg_match("/^(?:<|\[)(?:table|list|ol|ul|pre|select|form|blockquote|hr)/i", $parts[$i]) ) 
           $parts[$i] = '<p>'. $parts[$i] .'</p>';
      }
      $body = implode("\n\n", $parts);
    }

    // Step 3: Reinsert preformatted code blocks
    $cp = count($pre)-1;
    for ($i=0; $i <= $cp; $i++) 
       $body = str_replace("***pRe_sTrInG$i***", '<pre>'.substr($pre[$i],6,-7).'</pre>', $body);
  }

  // Add closing tags to prevent users from disruping your site's HTML
  // (required for nestable tags only: [list] and [quote])
  preg_match_all('/\[quote/i', $body, $matches);
  $opentags = count($matches['0']);
  preg_match_all('/\[\/quote\]/i', $body, $matches);
  $unclosed = $opentags - count($matches['0']);
  for ($i = 0; $i < $unclosed; $i++)
     $body .= '[/quote]';
  preg_match_all('/\[list/i', $body, $matches);
  $opentags = count($matches['0']);
  preg_match_all('/\[\/list\]/i', $body, $matches);
  $unclosed = $opentags - count($matches['0']);
  for ($i = 0; $i < $unclosed; $i++) 
     $body .= '[/list]';

  $preg = array(
    // Implement [notag]
    '#\[notag(?::\w+)?\](.*?)\[/notag(?::\w+)?\]#sie'        => '_bbcode_notag_tag("\\1")',

    // Headings - articles will almost always need them
    '#\[h([1-4])(?::\w+)?\](.*?)\[/h[1-4](?::\w+)?\]#si'     => '<h\\1>\\2</h\\1>',

    // Font, text and alignment
    '#\[color=(.*?)(?::\w+)?\](.*?)\[/color(?::\w+)?\]#si'   => '<span style="color:\\1">\\2</span>',
    '#\[size=(\d+)(?::\w+)?\](.*?)\[/size(?::\w+)?\]#sie'    => '_bbcode_size_tag(\\1, "\\2")',
    '#\[font=(.*?)(?::\w+)?\](.*?)\[/font(?::\w+)?\]#si'     => '<span style="font-family:\\1">\\2</span>',
    '#\[align=(.*?)(?::\w+)?\](.*?)\[/align(?::\w+)?\]#si'   => '<span style="text-align:\\1">\\2</span>',
    '#\[float=(.*?)(?::\w+)?\](.*?)\[/float(?::\w+)?\]#si'   => '<span style="float:\\1">\\2</span>',
    '#\[justify(?::\w+)?\](.*?)\[/justify(?::\w+)?\]#si'     => '<div style="text-align:justify;">\\1</div>',
    '#\[b(?::\w+)?\](.*?)\[/b(?::\w+)?\]#si'                 => '<span style="font-weight:bold">\\1</span>',
    '#\[i(?::\w+)?\](.*?)\[/i(?::\w+)?\]#si'                 => '<span style="font-style:italic">\\1</span>',
    '#\[u(?::\w+)?\](.*?)\[/u(?::\w+)?\]#si'                 => '<span style="text-decoration:underline">\\1</span>',
    '#\[s(?::\w+)?\](.*?)\[/s(?::\w+)?\]#si'                 => '<s>\\1</s>',
    '#\[sup(?::\w+)?\](.*?)\[/sup(?::\w+)?\]#si'             => '<sup>\\1</sup>',
    '#\[sub(?::\w+)?\](.*?)\[/sub(?::\w+)?\]#si'             => '<sub>\\1</sub>',
    '#\[center(?::\w+)?\](.*?)\[/center(?::\w+)?\]#si'       => '<div style="text-align:center">\\1</div>',
    '#\[left(?::\w+)?\](.*?)\[/left(?::\w+)?\]#si'           => '<div style="text-align:left">\\1</div>',
    '#\[right(?::\w+)?\](.*?)\[/right(?::\w+)?\]#si'         => '<div style="text-align:right">\\1</div>',
    
    // Links without a protocol, with a protocol and with good looking text
    '#\[url(?::\w+)?\]www\.(.*?)\[/url(?::\w+)?\]#si'        => '<a href="http://www.\\1" class="bb-url">\\1</a>',
    '#\[url(?::\w+)?\](.*?)\[/url(?::\w+)?\]#si'             => '<a href="\\1" class="bb-url">\\1</a>',
    '#\[url=www\.(.*?)\](.*?)\[/url(?::\w+)?\]#si'           => '<a href="http://www.\\1" class="bb-url">\\2</a>',
    '#\[url=(.*?)\](.*?)\[/url(?::\w+)?\]#si'                => '<a href="\\1" class="bb-url">\\2</a>',

    // Anchor tags for linking within documents
    '#\[anchor=(.*?)(?::\w+)?\](.*?)\[/anchor(?::\w+)?\]#si' => '<a name="\\1">\\2</a>',
    
    // Images without or with client-side sizing
    '#\[img(?::\w+)?\](.*?)\[/img(?::\w+)?\]#si'             => '<img src="\\1" alt="" class="bb-image" />',
    '#\[img=(.*?)x(.*?)(?::\w+)?\](.*?)\[/img(?::\w+)?\]#si' => '<img width="\\1" height="\\2" alt="" src="\\3" class="bb-image" />',

    // Flash animations and other special effects
    '#\[flash=(.*?)x(.*?)(?::\w+)?\](.*?)\[/flash(?::\w+)?\]#si' => '<object type="application/x-shockwave-flash" data="\\3" width="\\1" height="\\2"><param name="movie" value="\\3" /></object>', 
    '#\[move(?::\w+)?\](.*?)\[/move(?::\w+)?\]#si'           => '<marquee>\\1</marquee>',

    // Acronyms - show description when mouse moves over tag
    '#\[acronym=(.*?)(?::\w+)?\](.*?)\[/acronym(?::\w+)?\]#si'=> '<acronym title="\\1">\\2</acronym>',

    
    // Quoting with or without specifying the source
    '#\[quote(?::\w+)?\]#i'                                    => '<div class="bb-quote">'.$quote_text.':<div class="bb-quote-body">',
    '#\[quote=(?:&quot;|"|\')?(.*?)["\']?(?:&quot;|"|\')?\]#i' => '<div class="bb-quote">'.$quote_user.':<div class="bb-quote-body">',
    '#\[/quote(?::\w+)?\]#si'                                  => '</div></div>',

    // PHP code blocks (syntax highlighted)
    '#\[php(?::\w+)?\](?:[\r\n])*(.*?)\[/php(?::\w+)?\]#sie' => '_bbcode_php_tag("\\1")',
    
    // Different kinds of lists and list items
    '#\[\*(?::\w+)?\](.+)(?=\[\*(?::\w+)?\]|\[/list)#Usi'    => '<li>\\1',
    '#\[list(?::\w+)?\]#si'                                  => '<ol class="bb-list" style="list-style-type:circle;">',
    '#\[list=c(?::\w+)?\]#si'                                => '<ol class="bb-list" style="list-style-type:circle;">',
    '#\[list=d(?::\w+)?\]#si'                                => '<ol class="bb-list" style="list-style-type:disc;">',
    '#\[list=s(?::\w+)?\]#si'                                => '<ol class="bb-list" style="list-style-type:square;">',
    '#\[list=1(?::\w+)?\]#si'                                => '<ol class="bb-list" style="list-style-type:decimal;">',
    '#\[list=i(?::\w+)?\]#si'                                => '<ol class="bb-list" style="list-style-type:lower-roman;">',
    '#\[list=I(?::\w+)?\]#si'                                => '<ol class="bb-list" style="list-style-type:upper-roman;">',
    '#\[list=a(?::\w+)?\]#si'                                => '<ol class="bb-list" style="list-style-type:upper-alpha;">',
    '#\[list=A(?::\w+)?\]#si'                                => '<ol class="bb-list" style="list-style-type:upper-alpha;">',
    '#\[/list(?::\w+)?\]#si'                                 => '</ol>',
    
    // Clean up list output and add closing </li> tags
    '#(?=<li>|</ol>)#si'                                    => '</li>\\1',
    '#<ol(.*?)>(?:.*?)<li(.*?)>#si'                         => '<ol\\1><li\\2>',
  );
  $body = preg_replace(array_keys($preg), array_values($preg), $body);

  $str = array(
    // Horizontal delimiter
    '[hr]'   => '<hr class="bb-hr" />',
    // Force line break
    '[br]'   => '<br class="bb-br" />',
    // Force space
    '[sp]'   => '&nbsp;',
  );
  $body = str_replace(array_keys($str), array_values($str), $body);

  // We cannot evaluate the variable in callback function because there is no way to pass the $format variable
  if (variable_get("bbcode_encode_mailto_$format", 1)) {
    // Replacing email addresses with encoded html
    $body = preg_replace_callback('#\[email(?::\w+)?\](.*?)\[/email(?::\w+)?\]#si', '_bbcode_encode_mailto', $body);
    $body = preg_replace_callback('#\[email=(.*?)(?::\w+)?\](.*?)\[/email(?::\w+)?\]#si', '_bbcode_encode_mailto', $body);
  }
  else {
    $body = preg_replace(
      array('#\[email(?::\w+)?\](.*?)\[/email(?::\w+)?\]#si','#\[email=(.*?)(?::\w+)?\](.*?)\[/email(?::\w+)?\]#si'),
      array('<a href="mailto:\\1" class="bb-email">\\1</a>', '<a href="mailto:\\1" class="bb-email">\\2</a>'),
      $body);
  }

  // Find all [code] tags and check if they contain a newline. In case we find a newline,
  // that [code] should be rendered as a block, otherwise it will still be inline
  if (preg_match_all('#\[code(?::\w+)?\](.*?)\[/code(?::\w+)?\]#si', $body, $code_tags, PREG_SET_ORDER)) {
    foreach ($code_tags as $code_tag) {
      if (strpos($code_tag[1], "\n") !== FALSE) {
          $code_tag[1] = str_replace(array("\n ", "  ", "\n"), array('<br />&nbsp;', ' &nbsp;', '<br />'), trim($code_tag[1]));
          $code_block = '<span class="bb-code-block">%s</span>';
      } 
      else 
          $code_block = '<code class="bb-code">%s</code>';
      $body = str_replace($code_tag[0], sprintf($code_block, $code_tag[1]), $body);
    }
  }
  
  /**
   * - Goes through the given string, and replaces xxxx://yyyy with an HTML <a> tag linking
   *  to that URL
   * - Goes through the given string, and replaces www.xxxx.yyyy[zzzz] with an HTML <a> tag linking
   *  to http://www.xxxx.yyyy[/zzzz]
   * - Goes through the given string, and replaces xxxx@yyyy with an HTML mailto: tag linking
   *    to that email address
   * - Only matches these 2 patterns either after a space, or at the beginning of a line
   *
   * Notes: the email one might get annoying - it's easy to make it more restrictive, though.. maybe
   * have it require something like xxxx@yyyy.zzzz or such. We'll see.
   */

  // pad it with a space so we can match things at the start of the 1st line.
  $ret = ' ' . $body;

  // matches an "xxxx://yyyy" URL at the start of a line, or after a space.
  // xxxx can only be alpha characters.
  // yyyy is anything up to the first space, newline, comma, double quote or <
  $ret = preg_replace("#([\t\r\n ])([a-z0-9]+?){1}://([\w\-]+\.([\w\-]+\.)*[\w]+(:[0-9]+)?(/[^ \"\n\r\t<]*)?)#i", '\1<a href="\2://\3">\2://\3</a>', $ret);

  // matches a "www|ftp.xxxx.yyyy[/zzzz]" kinda lazy URL thing
  // Must contain at least 2 dots. xxxx contains either alphanum, or "-"
  // zzzz is optional.. will contain everything up to the first space, newline,
  // comma, double quote or <.
  $ret = preg_replace("#([\t\r\n ])(www|ftp)\.(([\w\-]+\.)*[\w]+(:[0-9]+)?(/[^ \"\n\r\t<]*)?)#i", '\1<a href="http://\2.\3">\2.\3</a>', $ret);

  // matches an email@domain type address at the start of a line, or after a space.
  // Note: Only the followed chars are valid; alphanums, "-", "_" and or ".".
  if (variable_get("bbcode_encode_mailto_$format", 1))
    $ret = preg_replace_callback("#([\t\r\n ])([a-z0-9\-_.]+?)@([\w\-]+\.([\w\-\.]+\.)*[\w]+)#i", '_bbcode_encode_mailto', $ret);
  else 
    $ret = preg_replace("#([\t\r\n ])([a-z0-9\-_.]+?)@([\w\-]+\.([\w\-\.]+\.)*[\w]+)#i", "\\1<a href=\"mailto:\\2@\\3\">\\2@\\3</a>", $ret);

  // Remove our padding..
  $ret = substr($ret, 1);

  return $ret;
}

function _bbcode_encode_mailto($matches) {
  if (isset($matches[3])) 
    $link = 'document.write(\'<a href="mailto:' . $matches[2].'@'.$matches[3] . '">' . $matches[2].'@'.$matches[3] . '</a>\');';
  else 
    $link = 'document.write(\'<a href="mailto:' . $matches[1] . '" class="bb-email">' . (isset($matches[2]) ? $matches[2] : $matches[1]) . '</a>\');';

  $js_encode = '';
  for ($x = 0; $x < strlen($link); $x++) 
    $js_encode .= '%' . bin2hex($link{$x});

  $link = '<script type="text/javascript" language="javascript">eval(unescape(\''.$js_encode.'\'))</script>';
  if (isset($matches[3]))
    $link = $matches[1] . $link;

  return $link;
}

function _bbcode_size_tag($size = NULL, $text = NULL) {
  if ($size < 6)
    $size = 6;
  if ($size > 48)
    $size = 48;
  return '<span style="font-size:'.$size.'px">'.$text.'</span>';
}

function _bbcode_notag_tag($text = NULL) {
  return str_replace( array('[', ']', '@'), array('&#91;', '&#93;', '&#64;'), $text);
}

function _bbcode_php_tag($text = NULL) {
  return '<pre>'. highlight_string($text, true) .'</pre>';
}
