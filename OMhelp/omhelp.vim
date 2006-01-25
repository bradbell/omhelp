" Vim syntax file
" Language:   OMhelp input file
" Maintainer: Brad Bell (bradbell@seanet.com)
" Last Change: 2006 Jan 24


" clear syntax every time for testing
:syntax clear

:syntax case match

:syntax match omhelp_dollardollar    /\$\$/
:highlight link omhelp_dollardollar  Keyword

:syntax match omhelp_aindex          /\$aindex/
:highlight link omhelp_aindex        Keyword

:syntax match omhelp_align           /\$align/
:highlight link omhelp_align         Keyword

:syntax match omhelp_begin           /\$begin/
:highlight link omhelp_begin         Keyword

:syntax match omhelp_bgcolor         /\$bgcolor/
:highlight link omhelp_bgcolor       Keyword

:syntax match omhelp_big             /\$big/
:highlight link omhelp_big           Keyword

:syntax match omhelp_bold            /\$bold/
:highlight link omhelp_bold          Keyword

:syntax match omhelp_cend            /\$cend/
:highlight link omhelp_cend          Special

:syntax match omhelp_center          /\$center/
:highlight link omhelp_center        Keyword

:syntax match omhelp_children        /\$children/
:highlight link omhelp_children      Keyword

:syntax match omhelp_childtable      /\$childtable/
:highlight link omhelp_childtable    Keyword

:syntax match omhelp_cindex          /\$cindex/
:highlight link omhelp_cindex        Keyword

:syntax match omhelp_cmark           /\$cmark/
:highlight link omhelp_cmark         Keyword

:syntax match omhelp_cnext           /\$cnext/
:highlight link omhelp_cnext         Special

:syntax match omhelp_code            /\$code/
:highlight link omhelp_code          Keyword

:syntax match omhelp_codecolor       /\$codecolor/
:highlight link omhelp_codecolor     Keyword

:syntax match omhelp_codep           /\$codep/
:highlight link omhelp_codep         Keyword

:syntax match omhelp_comment         /\$comment/
:highlight link omhelp_comment       Keyword

:syntax match omhelp_contents        /\$contents/
:highlight link omhelp_contents      Keyword

:syntax match omhelp_date            /\$date/
:highlight link omhelp_date          Special

:syntax match omhelp_dollar          /\$dollar/
:highlight link omhelp_dollar        Keyword

:syntax match omhelp_end             /\$end/
:highlight link omhelp_end           Special

:syntax match omhelp_errorcolor      /\$errorcolor/
:highlight link omhelp_errorcolor    Keyword

:syntax match omhelp_escape          /\$escape/
:highlight link omhelp_escape        Keyword

:syntax match omhelp_execute         /\$execute/
:highlight link omhelp_execute       Keyword

:syntax match omhelp_fend            /\$fend/
:highlight link omhelp_fend          Keyword

:syntax match omhelp_fixed           /\$fixed/
:highlight link omhelp_fixed         Keyword

:syntax match omhelp_head            /\$head/
:highlight link omhelp_head          Keyword

:syntax match omhelp_href            /\$href/
:highlight link omhelp_href          Keyword

:syntax match omhelp_icon            /\$icon/
:highlight link omhelp_icon          Keyword

:syntax match omhelp_image           /\$image/
:highlight link omhelp_image         Keyword

:syntax match omhelp_include         /\$include/
:highlight link omhelp_include       Keyword

:syntax match omhelp_index           /\$index/
:highlight link omhelp_index         Keyword

:syntax match omhelp_italic          /\$italic/
:highlight link omhelp_italic        Keyword

:syntax match omhelp_latex           /\$latex/
:highlight link omhelp_latex         Keyword

:syntax match omhelp_lend            /\$lend/
:highlight link omhelp_lend          Special

:syntax match omhelp_list            /\$list/
:highlight link omhelp_list          Special

:syntax match omhelp_lnext           /\$lnext/
:highlight link omhelp_lnext         Special

:syntax match omhelp_math            /\$math/
:highlight link omhelp_math          Keyword

:syntax match omhelp_mindex          /\$mindex/
:highlight link omhelp_mindex        Keyword

:syntax match omhelp_mref            /\$mref/
:highlight link omhelp_mref          Keyword

:syntax match omhelp_newlinech       /\$newlinech/
:highlight link omhelp_newlinech     Keyword

:syntax match omhelp_nobreak         /\$nobreak/
:highlight link omhelp_nobreak       Keyword

:syntax match omhelp_nospell         /\$nospell/
:highlight link omhelp_nospell       Keyword

:syntax match omhelp_path            /\$path/
:highlight link omhelp_path          Keyword

:syntax match omhelp_pre             /\$pre/
:highlight link omhelp_pre           Keyword

:syntax match omhelp_rend            /\$rend/
:highlight link omhelp_rend          Keyword

:syntax match omhelp_rmark           /\$rmark/
:highlight link omhelp_rmark         Keyword

:syntax match omhelp_rnext           /\$rnext/
:highlight link omhelp_rnext         Special

:syntax match omhelp_rref            /\$rref/
:highlight link omhelp_rref          Keyword

:syntax match omhelp_section         /\$section/
:highlight link omhelp_section       Keyword

:syntax match omhelp_skipnl          /\$skipnl/
:highlight link omhelp_skipnl        Keyword

:syntax match omhelp_small           /\$small/
:highlight link omhelp_small         Keyword

:syntax match omhelp_spell           /\$spell/
:highlight link omhelp_spell         Keyword

:syntax match omhelp_subhead         /\$subhead/
:highlight link omhelp_subhead       Keyword

:syntax match omhelp_syntax          /\$syntax/
:highlight link omhelp_syntax        Keyword

:syntax match omhelp_table           /\$table/
:highlight link omhelp_table         Special

:syntax match omhelp_tabsize         /\$tabsize/
:highlight link omhelp_tabsize       Keyword

:syntax match omhelp_tend            /\$tend/
:highlight link omhelp_tend          Special

:syntax match omhelp_textcolor       /\$textcolor/
:highlight link omhelp_textcolor     Keyword

:syntax match omhelp_th              /\$th/
:highlight link omhelp_th            Keyword

:syntax match omhelp_title           /\$title/
:highlight link omhelp_title         Keyword

:syntax match omhelp_trace           /\$trace/
:highlight link omhelp_trace         Keyword

:syntax match omhelp_tref            /\$tref/
:highlight link omhelp_tref          Keyword

:syntax match omhelp_verbatim        /\$verbatim/
:highlight link omhelp_verbatim      Keyword

:syntax match omhelp_wspace          /\$wspace/
:highlight link omhelp_wspace        Keyword

:syntax match omhelp_xref            /\$xref/
:highlight link omhelp_xref          Keyword

