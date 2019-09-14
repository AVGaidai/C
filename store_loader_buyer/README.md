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
<b>Имеется пять магазинов (массив из пяти целых положительных чисел 
инициализированных числами 1000-1200). Имеется погрузчик (отдельный поток) 
задача которого загружать товары в магазин (просто добавлять к тому, 
что там есть число из диапазона 300-500) и засыпать на 1 секунды. 
Пока погрузчик в одном из магазинов, туда больше никто не может заходить. 
Магазин погрузчик выбирает произвольно. Также имеется три потока 
покупателей с потребностью в диапазоне 3000-3500. Их задача заходить в 
магазины и покупать товары пока не удовлетворят свои потребности, также 
пока покупатель в магазине туда никто не может зайти. Если товары кончились, 
то покупатель покидает магазин и засыпает на 3 секунды. Программа 
функционирует пока все покупатели не удовлетворятся.</b>
</div>
<div id="top"><!-- do not remove this div, it is closed by doxygen! -->
<div id="main-nav"></div>
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
<a href="#define-members">Macros</a> &#124;
<a href="#func-members">Functions</a> &#124;
<a href="#var-members">Variables</a>  </div>
  <div class="headertitle">
<div class="title">main.c File Reference</div>  </div>
</div><!--header-->
<div class="contents">
<div class="textblock"><code>#include &lt;stdio.h&gt;</code><br />
<code>#include &lt;stdbool.h&gt;</code><br />
<code>#include &lt;pthread.h&gt;</code><br />
<code>#include &lt;unistd.h&gt;</code><br />
<code>#include &lt;stdlib.h&gt;</code><br />
<code>#include &lt;time.h&gt;</code><br />
</div><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="nested-classes"></a>
Classes</h2></td></tr>
<tr class="memitem:"><td class="memItemLeft" align="right" valign="top">struct &#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="structstore.html">store</a></td></tr>
<tr class="memdesc:"><td class="mdescLeft">&#160;</td><td class="mdescRight">Data structure for describe store.  <a href="structstore.html#details">More...</a><br /></td></tr>
<tr class="separator:"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="define-members"></a>
Macros</h2></td></tr>
<tr class="memitem:a9a8e700d56e7d858108b755ad3edb52e"><td class="memItemLeft" align="right" valign="top"><a id="a9a8e700d56e7d858108b755ad3edb52e"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>FREE</b>&#160;&#160;&#160;0</td></tr>
<tr class="separator:a9a8e700d56e7d858108b755ad3edb52e"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:ab5be0aaddb58ffb9cb20c12530d66316"><td class="memItemLeft" align="right" valign="top"><a id="ab5be0aaddb58ffb9cb20c12530d66316"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>BUSY</b>&#160;&#160;&#160;1</td></tr>
<tr class="separator:ab5be0aaddb58ffb9cb20c12530d66316"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a5b146c246c83364125feb6c92ce028c8"><td class="memItemLeft" align="right" valign="top"><a id="a5b146c246c83364125feb6c92ce028c8"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>NSTORES</b>&#160;&#160;&#160;5</td></tr>
<tr class="separator:a5b146c246c83364125feb6c92ce028c8"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a9610235eb0d5257f15c8ecbf15a7caee"><td class="memItemLeft" align="right" valign="top"><a id="a9610235eb0d5257f15c8ecbf15a7caee"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>NBUYERS</b>&#160;&#160;&#160;3</td></tr>
<tr class="separator:a9610235eb0d5257f15c8ecbf15a7caee"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a21910b18dcd047ecdc84837c1dc801fd"><td class="memItemLeft" align="right" valign="top"><a id="a21910b18dcd047ecdc84837c1dc801fd"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>LB_STORE_START_VAL</b>&#160;&#160;&#160;1000</td></tr>
<tr class="separator:a21910b18dcd047ecdc84837c1dc801fd"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a09c1333ef9e9f690644f2090295dca29"><td class="memItemLeft" align="right" valign="top"><a id="a09c1333ef9e9f690644f2090295dca29"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>RB_STORE_START_VAL</b>&#160;&#160;&#160;1200</td></tr>
<tr class="separator:a09c1333ef9e9f690644f2090295dca29"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a6daed247f3d6193ee8e9fc7277240678"><td class="memItemLeft" align="right" valign="top"><a id="a6daed247f3d6193ee8e9fc7277240678"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>LB_LOADER_CAPACITY</b>&#160;&#160;&#160;300</td></tr>
<tr class="separator:a6daed247f3d6193ee8e9fc7277240678"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:abb693cad492158ea255010b939697a36"><td class="memItemLeft" align="right" valign="top"><a id="abb693cad492158ea255010b939697a36"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>RB_LOADER_CAPACITY</b>&#160;&#160;&#160;500</td></tr>
<tr class="separator:abb693cad492158ea255010b939697a36"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a664c9105cddfdbb4f3101b641f5c5c49"><td class="memItemLeft" align="right" valign="top"><a id="a664c9105cddfdbb4f3101b641f5c5c49"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>LB_NEEDS_BUYER</b>&#160;&#160;&#160;3000</td></tr>
<tr class="separator:a664c9105cddfdbb4f3101b641f5c5c49"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a1d870ee17df0a340d1d41b2389e45fc0"><td class="memItemLeft" align="right" valign="top"><a id="a1d870ee17df0a340d1d41b2389e45fc0"></a>
#define&#160;</td><td class="memItemRight" valign="bottom"><b>RB_NEEDS_BUYER</b>&#160;&#160;&#160;3500</td></tr>
<tr class="separator:a1d870ee17df0a340d1d41b2389e45fc0"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="func-members"></a>
Functions</h2></td></tr>
<tr class="memitem:af5363b9631ef5e5ed967b233ebd8251c"><td class="memItemLeft" align="right" valign="top">void&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#af5363b9631ef5e5ed967b233ebd8251c">init_stores</a> (struct <a class="el" href="structstore.html">store</a> *stores)</td></tr>
<tr class="memdesc:af5363b9631ef5e5ed967b233ebd8251c"><td class="mdescLeft">&#160;</td><td class="mdescRight">This function sets initial values for stores.  <a href="#af5363b9631ef5e5ed967b233ebd8251c">More...</a><br /></td></tr>
<tr class="separator:af5363b9631ef5e5ed967b233ebd8251c"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a1395bab6ed2ea9d6461f0c09762fd9ff"><td class="memItemLeft" align="right" valign="top">void *&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a1395bab6ed2ea9d6461f0c09762fd9ff">loader</a> (void *arg)</td></tr>
<tr class="memdesc:a1395bab6ed2ea9d6461f0c09762fd9ff"><td class="mdescLeft">&#160;</td><td class="mdescRight">This thread function for loader.  <a href="#a1395bab6ed2ea9d6461f0c09762fd9ff">More...</a><br /></td></tr>
<tr class="separator:a1395bab6ed2ea9d6461f0c09762fd9ff"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a84f14923762fd0838dceaa6931c7977b"><td class="memItemLeft" align="right" valign="top">void *&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a84f14923762fd0838dceaa6931c7977b">buyer</a> (void *arg)</td></tr>
<tr class="memdesc:a84f14923762fd0838dceaa6931c7977b"><td class="mdescLeft">&#160;</td><td class="mdescRight">This thread function for buyer.  <a href="#a84f14923762fd0838dceaa6931c7977b">More...</a><br /></td></tr>
<tr class="separator:a84f14923762fd0838dceaa6931c7977b"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a0ddf1224851353fc92bfbff6f499fa97"><td class="memItemLeft" align="right" valign="top"><a id="a0ddf1224851353fc92bfbff6f499fa97"></a>
int&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="main_8c.html#a0ddf1224851353fc92bfbff6f499fa97">main</a> (int argc, char *argv[])</td></tr>
<tr class="memdesc:a0ddf1224851353fc92bfbff6f499fa97"><td class="mdescLeft">&#160;</td><td class="mdescRight">This main task function. <br /></td></tr>
<tr class="separator:a0ddf1224851353fc92bfbff6f499fa97"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="var-members"></a>
Variables</h2></td></tr>
<tr class="memitem:a524048671a65927d5bf8256c0fe67f7d"><td class="memItemLeft" align="right" valign="top"><a id="a524048671a65927d5bf8256c0fe67f7d"></a>
pthread_cond_t&#160;</td><td class="memItemRight" valign="bottom"><b>cv</b></td></tr>
<tr class="separator:a524048671a65927d5bf8256c0fe67f7d"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a5a9933cd4a8dfe11fff0d0e1e7a3e197"><td class="memItemLeft" align="right" valign="top"><a id="a5a9933cd4a8dfe11fff0d0e1e7a3e197"></a>
pthread_mutex_t&#160;</td><td class="memItemRight" valign="bottom"><b>cm</b></td></tr>
<tr class="separator:a5a9933cd4a8dfe11fff0d0e1e7a3e197"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a53a2d16dac430353052f49aaa0cce34a"><td class="memItemLeft" align="right" valign="top"><a id="a53a2d16dac430353052f49aaa0cce34a"></a>
bool&#160;</td><td class="memItemRight" valign="bottom"><b>stop</b></td></tr>
<tr class="separator:a53a2d16dac430353052f49aaa0cce34a"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:af01f12917f253ae4478699e86cb28aad"><td class="memItemLeft" align="right" valign="top"><a id="af01f12917f253ae4478699e86cb28aad"></a>
bool&#160;</td><td class="memItemRight" valign="bottom"><b>cond</b></td></tr>
<tr class="separator:af01f12917f253ae4478699e86cb28aad"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:aa8c9a0c47d4b86fff105edb4ac288c3e"><td class="memItemLeft" align="right" valign="top"><a id="aa8c9a0c47d4b86fff105edb4ac288c3e"></a>
struct <a class="el" href="structstore.html">store</a>&#160;</td><td class="memItemRight" valign="bottom"><b>stores</b> [NSTORES]</td></tr>
<tr class="separator:aa8c9a0c47d4b86fff105edb4ac288c3e"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table>
<h2 class="groupheader">Function Documentation</h2>
<a id="a84f14923762fd0838dceaa6931c7977b"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a84f14923762fd0838dceaa6931c7977b">&#9670;&nbsp;</a></span>buyer()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">void* buyer </td>
          <td>(</td>
          <td class="paramtype">void *&#160;</td>
          <td class="paramname"><em>arg</em></td><td>)</td>
          <td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>This thread function for buyer. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">arg</td><td>is thread info (empty) </td></tr>
  </table>
  </dd>
</dl>

</div>
</div>
<a id="af5363b9631ef5e5ed967b233ebd8251c"></a>
<h2 class="memtitle"><span class="permalink"><a href="#af5363b9631ef5e5ed967b233ebd8251c">&#9670;&nbsp;</a></span>init_stores()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">void init_stores </td>
          <td>(</td>
          <td class="paramtype">struct <a class="el" href="structstore.html">store</a> *&#160;</td>
          <td class="paramname"><em>stores</em></td><td>)</td>
          <td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>This function sets initial values for stores. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">stores</td><td>is pointer to stores array </td></tr>
  </table>
  </dd>
</dl>

</div>
</div>
<a id="a1395bab6ed2ea9d6461f0c09762fd9ff"></a>
<h2 class="memtitle"><span class="permalink"><a href="#a1395bab6ed2ea9d6461f0c09762fd9ff">&#9670;&nbsp;</a></span>loader()</h2>

<div class="memitem">
<div class="memproto">
      <table class="memname">
        <tr>
          <td class="memname">void* loader </td>
          <td>(</td>
          <td class="paramtype">void *&#160;</td>
          <td class="paramname"><em>arg</em></td><td>)</td>
          <td></td>
        </tr>
      </table>
</div><div class="memdoc">

<p>This thread function for loader. </p>
<dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">arg</td><td>is thread info (empty) </td></tr>
  </table>
  </dd>
</dl>

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
