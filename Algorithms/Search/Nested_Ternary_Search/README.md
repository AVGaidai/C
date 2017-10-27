# Nested ternary search by gold ratio

O(log(X/eps)) <br>
X = Right - left; <br>
eps is accuracy calculations.

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/xhtml;charset=UTF-8"/>
<meta http-equiv="X-UA-Compatible" content="IE=9"/>
<meta name="generator" content="Doxygen 1.8.13"/>
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<link href="tabs.css" rel="stylesheet" type="text/css"/>
<link href="search/search.css" rel="stylesheet" type="text/css"/>
<link href="doxygen.css" rel="stylesheet" type="text/css" />
</head>
<body>

<div id="main-nav"></div>
<!-- window showing the filter options -->
<div id="MSearchSelectWindow"
     onmouseover="return searchBox.OnSearchSelectShow()"
     onmouseout="return searchBox.OnSearchSelectHide()"
     onkeydown="return searchBox.OnSearchSelectKey(event)">
</div>

<!-- iframe showing the search results (closed by default) -->

</div><!-- top -->
<div class="header">
  <div class="summary">
<a href="#define-members">Macros</a> &#124;
<a href="#func-members">Functions</a>  </div>
  <div class="headertitle">
<div class="title">main.c File Reference</div>  </div>
</div><!--header-->
<div class="contents">
<div class="textblock"><code>#include &lt;stdio.h&gt;</code><br />
<code>#include &lt;stdlib.h&gt;</code><br />
<code>#include &lt;math.h&gt;</code><br />
</div><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="define-members"></a>
Macros</h2></td></tr>
<tr class="memitem:a656da95f9680f14093be09a52ab6752f"><td class="memItemLeft" align="right" valign="top"><a id="a656da95f9680f14093be09a52ab6752f"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>GR</b>&#160;&#160;&#160;1.618</td></tr>
<tr class="separator:a656da95f9680f14093be09a52ab6752f"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a587e21dda1f72be700a6206023ad681b"><td class="memItemLeft" align="right" valign="top"><a id="a587e21dda1f72be700a6206023ad681b"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>FUNC</b>&#160;&#160;&#160;x * x + y * y + 6 * y - 4 * x</td></tr>
<tr class="separator:a587e21dda1f72be700a6206023ad681b"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="func-members"></a>
Functions</h2></td></tr>
<tr class="memitem:a5171488338932f60aa0e91441b310bea"><td class="memItemLeft" align="right" valign="top">double&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a5171488338932f60aa0e91441b310bea">f</a> (double x, double y)</td></tr>
<tr class="memdesc:a5171488338932f60aa0e91441b310bea"><td class="mdescLeft">&#160;</td><td class="mdescRight">The function under study.  <a href="#a5171488338932f60aa0e91441b310bea">More...</a><br /></td></tr>
<tr class="separator:a5171488338932f60aa0e91441b310bea"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a59261b05d65b92eb8ec22fb00d3aa04c"><td class="memItemLeft" align="right" valign="top">double&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a59261b05d65b92eb8ec22fb00d3aa04c">Ternary_Search_Min</a> (double(*<a class="el" href="main_8c.html#a5171488338932f60aa0e91441b310bea">f</a>)(double, double), double left, double right, double eps, int var)</td></tr>
<tr class="memdesc:a59261b05d65b92eb8ec22fb00d3aa04c"><td class="mdescLeft">&#160;</td><td class="mdescRight">The ternary search minimum of the function.  <a href="#a59261b05d65b92eb8ec22fb00d3aa04c">More...</a><br /></td></tr>
<tr class="separator:a59261b05d65b92eb8ec22fb00d3aa04c"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a89a8bf7fadd3a1e7014fb68bcbce473a"><td class="memItemLeft" align="right" valign="top">double&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a89a8bf7fadd3a1e7014fb68bcbce473a">Ternary_Search_Max</a> (double(*<a class="el" href="main_8c.html#a5171488338932f60aa0e91441b310bea">f</a>)(double, double), double left, double right, double eps, int var)</td></tr>
<tr class="memdesc:a89a8bf7fadd3a1e7014fb68bcbce473a"><td class="mdescLeft">&#160;</td><td class="mdescRight">The ternary search maximum of the function.  <a href="#a89a8bf7fadd3a1e7014fb68bcbce473a">More...</a><br /></td></tr>
<tr class="separator:a89a8bf7fadd3a1e7014fb68bcbce473a"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a0c686a2d0571106d96c1076fe16e642a"><td class="memItemLeft" align="right" valign="top">void&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a0c686a2d0571106d96c1076fe16e642a">Nested_Ternary_Search_Min</a> (double(*<a class="el" href="main_8c.html#a5171488338932f60aa0e91441b310bea">f</a>)(double, double), double left_x, double right_x, double left_y, double right_y, double eps, double *x, double *y)</td></tr>
<tr class="memdesc:a0c686a2d0571106d96c1076fe16e642a"><td class="mdescLeft">&#160;</td><td class="mdescRight">The nested ternary search minimum of the function.  <a href="#a0c686a2d0571106d96c1076fe16e642a">More...</a><br /></td></tr>
<tr class="separator:a0c686a2d0571106d96c1076fe16e642a"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a894a46d66482d15364343f1b48cf11f7"><td class="memItemLeft" align="right" valign="top">void&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a894a46d66482d15364343f1b48cf11f7">Nested_Ternary_Search_Max</a> (double(*<a class="el" href="main_8c.html#a5171488338932f60aa0e91441b310bea">f</a>)(double, double), double left_x, double right_x, double left_y, double right_y, double eps, double *x, double *y)</td></tr>
<tr class="memdesc:a894a46d66482d15364343f1b48cf11f7"><td class="mdescLeft">&#160;</td><td class="mdescRight">The nested ternary search maximum of the function.  <a href="#a894a46d66482d15364343f1b48cf11f7">More...</a><br /></td></tr>
<tr class="separator:a894a46d66482d15364343f1b48cf11f7"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a0ddf1224851353fc92bfbff6f499fa97"><td class="memItemLeft" align="right" valign="top">int&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a0ddf1224851353fc92bfbff6f499fa97">main</a> (int argc, char *argv[])</td></tr>
<tr class="memdesc:a0ddf1224851353fc92bfbff6f499fa97"><td class="mdescLeft">&#160;</td><td class="mdescRight">Main function.  <a href="#a0ddf1224851353fc92bfbff6f499fa97">More...</a><br /></td></tr>
<tr class="separator:a0ddf1224851353fc92bfbff6f499fa97"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table>
<h2 class="groupheader">Function Documentation</h2>
<a id="a5171488338932f60aa0e91441b310bea"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a5171488338932f60aa0e91441b310bea">&#9670;&nbsp;</a></span>f()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">double f </td>
          <td>(</td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>x</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>y</em>&#160;</td>
        </tr>
        <tr>
          <td></td>
          <td>)</td>
          <td></td><td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>The function under study. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">x</td><td>is value of first variable. </td></tr>
    <tr><td class="paramname">y</td><td>is value of second variable.</td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>value of function in the point (x; y). </dd></dl>

</div>
</div>
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

<p>Main function. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">arg_1</td><td>is left border of the function definition area for first variable. </td></tr>
    <tr><td class="paramname">arg_2</td><td>is right border of the function definition area for first variable. </td></tr>
    <tr><td class="paramname">arg_3</td><td>is left border of the function definition area for second variable. </td></tr>
    <tr><td class="paramname">arg_4</td><td>is right border of the function definition area for second variable. </td></tr>
    <tr><td class="paramname">arg_5</td><td>is accuracy of calculations.</td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>zero if success, else 1. </dd></dl>

</div>
</div>
<a id="a894a46d66482d15364343f1b48cf11f7"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a894a46d66482d15364343f1b48cf11f7">&#9670;&nbsp;</a></span>Nested_Ternary_Search_Max()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">void Nested_Ternary_Search_Max </td>
          <td>(</td>
          <td class="paramtype">double(*)(double, double)&#160;</td>
          <td class="paramname"><em>f</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>left_x</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>right_x</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>left_y</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>right_y</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>eps</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double *&#160;</td>
          <td class="paramname"><em>x</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double *&#160;</td>
          <td class="paramname"><em>y</em>&#160;</td>
        </tr>
        <tr>
          <td></td>
          <td>)</td>
          <td></td><td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>The nested ternary search maximum of the function. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">f</td><td>is function under study. </td></tr>
    <tr><td class="paramname">left_x</td><td>is left border of the function definition area for first variable. </td></tr>
    <tr><td class="paramname">right_x</td><td>is right border of the function definition area for first variable. </td></tr>
    <tr><td class="paramname">left_y</td><td>is left border of the function definition area for second variable. </td></tr>
    <tr><td class="paramname">right_y</td><td>is right border of the function definition area for second variable. </td></tr>
    <tr><td class="paramname">eps</td><td>is accuracy of calculations. </td></tr>
    <tr><td class="paramname">x</td><td>is first variable. </td></tr>
    <tr><td class="paramname">y</td><td>is second variable.</td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>no value. </dd></dl>

</div>
</div>
<a id="a0c686a2d0571106d96c1076fe16e642a"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a0c686a2d0571106d96c1076fe16e642a">&#9670;&nbsp;</a></span>Nested_Ternary_Search_Min()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">void Nested_Ternary_Search_Min </td>
          <td>(</td>
          <td class="paramtype">double(*)(double, double)&#160;</td>
          <td class="paramname"><em>f</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>left_x</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>right_x</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>left_y</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>right_y</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>eps</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double *&#160;</td>
          <td class="paramname"><em>x</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double *&#160;</td>
          <td class="paramname"><em>y</em>&#160;</td>
        </tr>
        <tr>
          <td></td>
          <td>)</td>
          <td></td><td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>The nested ternary search minimum of the function. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">f</td><td>is function under study. </td></tr>
    <tr><td class="paramname">left_x</td><td>is left border of the function definition area for first variable. </td></tr>
    <tr><td class="paramname">right_x</td><td>is right border of the function definition area for first variable. </td></tr>
    <tr><td class="paramname">left_y</td><td>is left border of the function definition area for second variable. </td></tr>
    <tr><td class="paramname">right_y</td><td>is right border of the function definition area for second variable. </td></tr>
    <tr><td class="paramname">eps</td><td>is accuracy of calculations. </td></tr>
    <tr><td class="paramname">x</td><td>is first variable. </td></tr>
    <tr><td class="paramname">y</td><td>is second variable.</td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>no value. </dd></dl>

</div>
</div>
<a id="a89a8bf7fadd3a1e7014fb68bcbce473a"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a89a8bf7fadd3a1e7014fb68bcbce473a">&#9670;&nbsp;</a></span>Ternary_Search_Max()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">double Ternary_Search_Max </td>
          <td>(</td>
          <td class="paramtype">double(*)(double, double)&#160;</td>
          <td class="paramname"><em>f</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>left</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>right</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>eps</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">int&#160;</td>
          <td class="paramname"><em>var</em>&#160;</td>
        </tr>
        <tr>
          <td></td>
          <td>)</td>
          <td></td><td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>The ternary search maximum of the function. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">f</td><td>is function under study. </td></tr>
    <tr><td class="paramname">left</td><td>is left border of the function definition area. </td></tr>
    <tr><td class="paramname">right</td><td>is right border of the function definition area. </td></tr>
    <tr><td class="paramname">eps</td><td>is accuracy of calculations. </td></tr>
    <tr><td class="paramname">var</td><td>is number of variable.</td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>the point at which the function reaches maximum. </dd></dl>

</div>
</div>
<a id="a59261b05d65b92eb8ec22fb00d3aa04c"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a59261b05d65b92eb8ec22fb00d3aa04c">&#9670;&nbsp;</a></span>Ternary_Search_Min()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">double Ternary_Search_Min </td>
          <td>(</td>
          <td class="paramtype">double(*)(double, double)&#160;</td>
          <td class="paramname"><em>f</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>left</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>right</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">double&#160;</td>
          <td class="paramname"><em>eps</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype">int&#160;</td>
          <td class="paramname"><em>var</em>&#160;</td>
        </tr>
        <tr>
          <td></td>
          <td>)</td>
          <td></td><td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>The ternary search minimum of the function. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">f</td><td>is function under study. </td></tr>
    <tr><td class="paramname">left</td><td>is left border of the function definition area. </td></tr>
    <tr><td class="paramname">right</td><td>is right border of the function definition area. </td></tr>
    <tr><td class="paramname">eps</td><td>is accuracy of calculations. </td></tr>
    <tr><td class="paramname">var</td><td>is number of variable.</td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>the point at which the function reaches minimum. </dd></dl>

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
