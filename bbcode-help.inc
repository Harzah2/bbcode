<?php
// $Id$

function _bbcode_filter_tip() {
  return t("<h1>BBCode Guide</h1>

<h2>Introduction</h2>

<p>
 BBCode allows you to specify formatting rules for your text,
 even if you are not allowed to use HTML in your posts. BBCode
 originated from the forum software named PHPBB, and Drupal has a
 special implementation of it.
</p>
<p>
 In BBCode terms, you use \"tags\" to add formatting to your text. Every
 tag is enclosed in [ and ]. If you want to mark some region in
 your text, you need to use an opening tag and a closing tag. Closing
 tags start with [/, as you will see in the examples below. If you
 mistype a tag or forget to close it, you will not get the desired
 formatting.
</p>

<h2>Simple text formatting</h2>

<p>
 BBCode allows you to make some parts of your texts stand out from the
 context by adding <strong>[b]</strong>old, <strong>[i]</strong>talic
 and <strong>[u]</strong>nderlined formatting to them. The
 <strong>[color]</strong> and <strong>[size]</strong> tags allow you to
 change the color and size of portions of the text you enclose with
 these tags. Both require a parameter (which colour or how big) that is
 suffixed to the name of the tag by an equals sign (example below).
 You should not repeat the parameter in the closing tag!
</p>

<p>
 You can specify any recognized color name (red, blue, green, white, etc.)
 or a hexadecimal color value (#CDCDCD, #FFFFFF, etc.) as the parameter of
 a <strong>[color]</strong> tag. The <strong>[size]</strong> tag allows you
 to set the font size between 10 and 30, 10 being the smallest size.
 Note that using very large text is considered by many to be annoying, and
 it is seldom a good idea to try to drive more attention to your post in
 this way.
</p>

<table>
 <tr>
  <th>usage</th><th>display</th>
 </tr>
 <tr>
  <td>I [b]need to do[/b] this by the weekend</td>
  <td>I <strong>need to do</strong> this by the weekend</td>
 </tr>
 <tr>
  <td>John said, that [i]we should[/i] ask her</td>
  <td>John said, that <em>we should</em> ask her</td>
 </tr>
 <tr>
  <td>I [u]would not like to[/u] offend you</td>
  <td>I <span style=\"text-decoration: underline;\">would not like to</span> offend you</td>
 </tr>
 <tr>
  <td>Jane was at [color=blue]the coast[/color]</td>
  <td>Jane was at <span style=\"color: blue;\">the coast</span></td>
 </tr>
 <tr>
  <td>Joe was in [color=#00FF00]the forest[/color]</td>
  <td>Joe was in <span style=\"color: #00FF00;\">the forest</span></td>
 </tr>
 <tr>
  <td>You said: [size=20]HEY![/size]</td>
  <td>You said: <span style=\"font-size: 20px;\">HEY!</span></td>
 </tr>
</table>

<h2>Creating Links</h2>

<p>
 You have multiple options to specify links to other destinations in
 your posts.
</p>

<p>
 Drupal recognizes URLs (Uniform Resource Locators) used in your posts, and
 automatically replaces them with links. For URLs starting with \"www\" or
 \"ftp\" (eg. www.example.com) there is no need for a protocol specification,
 but you need to specify a protocol for other types of addresses
 (eg. example.com).
</p>
<p>
 Drupal also recognizes email addresses in posts automatically, but for compatibility
 with the common BBCode implementations, also provides the <strong>[email]</strong> tag
 to mark email addresses. There is no spam protection applied to the email addresses!
</p>
<p>
 You can use the <strong>[url]</strong> tag with a parameter to specify a link with
 meaningful text to click on. If you use the url tag without the parameter,
 then the enclosed text is assumed to be an URL, and a link is created to that
 destination.
</p>

<table>
 <tr>
  <th>usage</th><th>display</th>
 </tr>
 <tr>
  <td>For more examples, visit www.example.com</td>
  <td>For more examples, visit <a href=\"http://www.example.com\" target=\"_blank\">www.example.com</a></td>
 </tr>
 <tr>
  <td>For more examples, visit http://example.com</td>
  <td>For more examples, visit <a href=\"http://example.com\" target=\"_blank\">http://example.com</a></td>
 </tr>
 <tr>
  <td>If you have questions ask me at joe@example.com</td>
  <td>If you have questions ask me at <a href=\"mailto:joe@example.com\">joe@example.com</a></td>
 </tr>
 <tr>
  <td>If you have questions ask me at [email]joe@example.com[/email]</td>
  <td>If you have questions ask me at <a href=\"mailto:joe@example.com\">joe@example.com</a></td>
 </tr>
 <tr>
  <td>We use [url=http://example.com/]the example site[/url] in these examples</td>
  <td>We use <a href=\"http://example.com/\" target=\"_blank\">the example site</a> in these examples</td>
 </tr>
 <tr>
  <td>We use [url]http://example.com/[/url] in these examples</td>
  <td>We use <a href=\"http://example.com/\" target=\"_blank\">http://example.com/</a> in these examples</td>
 </tr>
</table>

<h2>Displaying images</h2>

<p>
 The <strong>[img]</strong> tag allows you to display an image in your
 post. You need to specify a URL to the image, so it needs to be
 accessible somewhere on the internet. Beware of adding very large
 images to your text, or otherwise the page will load very slowly!
</p>

<p>
 If you enclose a URL in an <strong>[img]</strong> tag, then it will
 be replaced with code to display the image. For example <code>A good
 screenshot: [img]http://example.com/screenshot.png[/img]</code>
 will show you the screenshot (if it exists). 
</p>
<p>
 You can also specify the desired display dimensions of the image by
 adding a dimension parameter to the <strong>[img]</strong> tag. <code>A
 good screenshot: [img=640x480]http://example.com/screenshot.png[/img]</code>
 will display the image in 640x480 (though the full image will be
 downloaded). Do not use this to show a thumbnail of an image!
</p>

<p>
 You are free to link an image to an external destination by enclosing
 the <strong>[img]</strong> tag with an <strong>[url]</strong> tag: <code>See
 [url=http://example.com][img]http://example.com/screenshot.png[/img][/url]</code>.
</p>

<h2>Ordered and unordered lists</h2>

<p>
 The simplest list type is the unordered list, which means that there is
 no numbering applied to the elements. You can make such a list by enclosing
 the list elements in <strong>[list]</strong> opening and closing tags.
 Specify the start of one element with the <strong>[*]</strong> list element
 marker, which has no closing tag pair.
</p>

<p>
 To create an ordered list, you should add a parameter to the [list]
 list tag specifying what type of ordered list you would like to see.
 The possible parameters are \"i\", \"I\", \"1\", \"a\", and \"A\" which all
 correspond to the display of the first list element.
</p>

<table>
 <tr>
  <th>usage</th><th>display</th>
 </tr>
 <tr>
  <td><pre>
I love
 [list]
  [*]Oranges
  [*]Apples
  [*]Bananas
 [/list]
</pre></td>
  <td>
   I love 
   <ul>
    <li>Oranges</li>
    <li>Apples</li>
    <li>Bananas</li>
   </ul>
  </td>
 </tr>
 <tr>
  <td><pre>
I love
 [list=I]
  [*]Oranges
  [*]Apples
  [*]Bananas
 [/list]
</pre></td>
  <td>
   I love 
   <ol style=\"list-style-type: upper-roman;\">
    <li>Oranges</li>
    <li>Apples</li>
    <li>Bananas</li>
   </ol>
  </td>
 </tr>
 <tr>
  <td><pre>
I love
 [list=1]
  [*]Oranges
  [*]Apples
  [*]Bananas
 [/list]
</pre></td>
  <td>
   I love 
   <ol style=\"list-style-type: decimal;\">
    <li>Oranges</li>
    <li>Apples</li>
    <li>Bananas</li>
   </ol>
  </td>
 </tr>
</table>

<h2>Fixed-width text and block formatting</h2>

<p>
 You can use the <strong>[code]</strong> tag to add an inline fixed-width
 formatted part or to add a block of (usually program) code. If there is
 any newline present between the opening and closing tags, then a block
 will be displayed.
</p>

<table>
 <tr>
  <th>usage</th><th>display</th>
 </tr>
 <tr>
  <td>Edit your [code]robots.txt[/code] file</td>
  <td>Edit your <code>robots.txt</code> file</td>
  </td>
 </tr>
 <tr>
  <td>
An HTML title example:<br />
[code]<br />
&lt;head&gt;<br />
&nbsp;&lt;title&gt;Page Title&lt;/title&gt;<br />
&lt;/head&gt;<br />
[/code]
  </td>
  <td>
An HTML title example:<br />
<div class=\"codeblock\"><code>
&lt;head&gt;<br />
&nbsp;&lt;title&gt;Page Title&lt;/title&gt;<br />
&lt;/head&gt;<br />
</code>
  </td>
 </tr>
</table>

<h2>Using multiple formatting tags</h2>

<p>
 You can apply more than one formatting specification to a portion of some
 text. <code>I was at [b][i]the coast[/i][/b]</code> will be
 rendered as <code>I was at <strong><em>the coast</em></strong></code> for
 example.
</p>

<p>
 Make sure that you take care of the proper order of the opening and closing
 tags. You should close the tags in the opposite order in which you opened
 them. Otherwise you might get very strange rendering results. Also check
 your post with the preview function before submiting it to discover possible
 formatting errors due to improper BBCode usage.
</p>

<p>
 There are some exceptions where you cannot add more BBCode tags. Examples
 of these include the contents of the <strong>[img]</strong> tag, which by
 definition should contain an URL only. BBCode tags are also disallowed
 inside <strong>[code]</strong> tags, and you cannot apply some formatting
 to all list items by wrapping the list with that formatting tag.
</p>");

}
