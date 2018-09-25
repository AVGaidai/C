<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/xhtml;charset=UTF-8"/>
<meta http-equiv="X-UA-Compatible" content="IE=9"/>
<meta name="generator" content="Doxygen 1.8.13"/>
<meta name="viewport" content="width=device-width, initial-scale=1"/>
</head>
<body>
<div>
<b>Написать командный интерпретатор на подобии bash. Водиться команда, 
выполняется, ожидается её завершение. Также необходжимо обавить 
возможность применения неименованных каналов, для передачи вывода 
одной программы на ввод другой.</b>
</div>
<div id="top"><!-- do not remove this div, it is closed by doxygen! -->
<div id="titlearea">
<!-- window showing the filter options -->
<div id="MSearchSelectWindow"
     onmouseover="return searchBox.OnSearchSelectShow()"
     onmouseout="return searchBox.OnSearchSelectHide()"
     onkeydown="return searchBox.OnSearchSelectKey(event)">
</div>

<!-- iframe showing the search results (closed by default) -->
<div class="header">
  <div class="summary">
<a href="#nested-classes">Classes</a> &#124;
<a href="#func-members">Functions</a>  </div>
  <div class="headertitle">
<div class="title">main.c File Reference</div>  </div>
</div><!--header-->
<div class="contents">
<div class="textblock"><code>#include &lt;stdio.h&gt;</code><br />
<code>#include &lt;string.h&gt;</code><br />
<code>#include &lt;stdlib.h&gt;</code><br />
<code>#include &lt;sys/wait.h&gt;</code><br />
<code>#include &lt;sys/types.h&gt;</code><br />
<code>#include &lt;unistd.h&gt;</code><br />
</div><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="nested-classes"></a>
Classes</h2></td></tr>
<tr class="memitem:"><td class="memItemLeft" align="right" valign="top">struct &#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="structcommand__t.html">command_t</a></td></tr>
<tr class="memdesc:"><td class="mdescLeft">&#160;</td><td class="mdescRight">Data structure for describe command.  <a href="structcommand__t.html#details">More...</a><br /></td></tr>
<tr class="separator:"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:"><td class="memItemLeft" align="right" valign="top">struct &#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="structcommand__set__t.html">command_set_t</a></td></tr>
<tr class="memdesc:"><td class="mdescLeft">&#160;</td><td class="mdescRight">Data structure for describe command set.  <a href="structcommand__set__t.html#details">More...</a><br /></td></tr>
<tr class="separator:"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="func-members"></a>
Functions</h2></td></tr>
<tr class="memitem:a36b1ee9868ce04049406385504d07f44"><td class="memItemLeft" align="right" valign="top">void&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a36b1ee9868ce04049406385504d07f44">string_command_parser</a> (struct <a class="el" href="structcommand__set__t.html">command_set_t</a> *command_set, char *str)</td></tr>
<tr class="memdesc:a36b1ee9868ce04049406385504d07f44"><td class="mdescLeft">&#160;</td><td class="mdescRight">This function splits the input command string into commands and their arguments.  <a href="#a36b1ee9868ce04049406385504d07f44">More...</a><br /></td></tr>
<tr class="separator:a36b1ee9868ce04049406385504d07f44"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a0ddf1224851353fc92bfbff6f499fa97"><td class="memItemLeft" align="right" valign="top">int&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a0ddf1224851353fc92bfbff6f499fa97">main</a> (int argc, char *argv[])</td></tr>
<tr class="memdesc:a0ddf1224851353fc92bfbff6f499fa97"><td class="mdescLeft">&#160;</td><td class="mdescRight">This main function of task.  <a href="#a0ddf1224851353fc92bfbff6f499fa97">More...</a><br /></td></tr>
<tr class="separator:a0ddf1224851353fc92bfbff6f499fa97"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table>
<h2 class="groupheader">Function Documentation</h2>
<a id="a0ddf1224851353fc92bfbff6f499fa97"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a0ddf1224851353fc92bfbff6f499fa97">&#9670;&nbsp;</a></span>main()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">int main </td>
          <td>(</td>
          <td class="paramtype">int&#160;</td>
          <td class="paramname"><em>argc</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">char *&#160;</td>
          <td class="paramname"><em>argv</em>[]&#160;</td>
        </tr>
        <tr>
          <td></td>
          <td>)</td>
          <td></td><td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>This main function of task. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">argc</td><td>is a counter of the command string parametrs </td></tr>
    <tr><td class="paramname">argv</td><td>is a command string in format "cmd &lt;arg&gt; ... &lt;arg&gt; &lt;|&gt; cmd &lt;arg&gt; ... &lt;arg&gt; ...". The command string must be in double qutes! The quntity a commands and their argument is unlimited, but maximum total length of the one command (with their arguments) is 256 characters</td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>0 on success or 1 on failure </dd></dl>

</div>
</div>
<a id="a36b1ee9868ce04049406385504d07f44"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a36b1ee9868ce04049406385504d07f44">&#9670;&nbsp;</a></span>string_command_parser()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">void string_command_parser </td>
          <td>(</td>
          <td class="paramtype">struct <a class="el" href="structcommand__set__t.html">command_set_t</a> *&#160;</td>
          <td class="paramname"><em>command_set</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">char *&#160;</td>
          <td class="paramname"><em>str</em>&#160;</td>
        </tr>
        <tr>
          <td></td>
          <td>)</td>
          <td></td><td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>This function splits the input command string into commands and their arguments. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">command_set</td><td>is a pointer to <a class="el" href="structcommand__set__t.html" title="Data structure for describe command set. ">command_set_t</a> type variable in which all commands and their arguments will be stored </td></tr>
    <tr><td class="paramname">str</td><td>is at array of char type which is the input command string</td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>no return value </dd></dl>

</div>
</div>
</div><!-- contents -->
<!-- start footer part -->
<hr class="footer"/><address class="footer"><small>
Generated by &#160;<a href="http://www.doxygen.org/index.html">
<img class="footer" src="doxygen.png" alt="doxygen"/>
</a> 1.8.13
</small></address>
</body>
</html>
