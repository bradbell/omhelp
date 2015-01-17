" Vim syntax file
" Language:   OMhelp input file
" Maintainer: Brad Bell (bradbell@seanet.com)
" Last Change: 2006 Jan 24


" clear syntax every time for testing
:syntax clear

:syntax case match

:syntax match omh_dollardollar    /\$\$/
:highlight link omh_dollardollar  Keyword

:syntax match omh_aindex          /\$aindex/
:highlight link omh_aindex        Keyword

:syntax match omh_align           /\$align/
:highlight link omh_align         Keyword

:syntax match omh_begin           /\$begin/
:highlight link omh_begin         Keyword

:syntax match omh_bgcolor         /\$bgcolor/
:highlight link omh_bgcolor       Keyword

:syntax match omh_big             /\$big/
:highlight link omh_big           Keyword

:syntax match omh_bold            /\$bold/
:highlight link omh_bold          Keyword

:syntax match omh_cend            /\$cend/
:highlight link omh_cend          Special

:syntax match omh_center          /\$center/
:highlight link omh_center        Keyword

:syntax match omh_children        /\$children/
:highlight link omh_children      Keyword

:syntax match omh_childtable      /\$childtable/
:highlight link omh_childtable    Keyword

:syntax match omh_cindex          /\$cindex/
:highlight link omh_cindex        Keyword

:syntax match omh_cmark           /\$cmark/
:highlight link omh_cmark         Keyword

:syntax match omh_cnext           /\$cnext/
:highlight link omh_cnext         Special

:syntax match omh_code            /\$code/
:highlight link omh_code          Keyword

:syntax match omh_codecolor       /\$codecolor/
:highlight link omh_codecolor     Keyword

:syntax match omh_codei           /\$codei/
:highlight link omh_codei         Keyword

:syntax match omh_codep           /\$codep/
:highlight link omh_codep         Keyword

:syntax match omh_comment         /\$comment/
:highlight link omh_comment       Keyword

:syntax match omh_contents        /\$contents/
:highlight link omh_contents      Keyword

:syntax match omh_cref            /\$cref/
:highlight link omh_cref          Keyword

:syntax match omh_date            /\$date/
:highlight link omh_date          Special

:syntax match omh_dollar          /\$dollar/
:highlight link omh_dollar        Keyword

:syntax match omh_end             /\$end/
:highlight link omh_end           Special

:syntax match omh_errorcolor      /\$errorcolor/
:highlight link omh_errorcolor    Keyword

:syntax match omh_escape          /\$escape/
:highlight link omh_escape        Keyword

:syntax match omh_execute         /\$execute/
:highlight link omh_execute       Keyword

:syntax match omh_fend            /\$fend/
:highlight link omh_fend          Keyword

:syntax match omh_fixed           /\$fixed/
:highlight link omh_fixed         Keyword

:syntax match omh_head            /\$head/
:highlight link omh_head          Keyword

:syntax match omh_hilitecmd       /\$hilitecmd/
:highlight link omh_hilitecmd     Keyword

:syntax match omh_hilitecolor      /\$hilitecolor/
:highlight link omh_hilitecolor   Keyword

:syntax match omh_hiliteseq       /\$hiliteseq/
:highlight link omh_hiliteseq     Keyword

:syntax match omh_href            /\$href/
:highlight link omh_href          Keyword

:syntax match omh_icode           /\$icode/
:highlight link omh_icode         Keyword

:syntax match omh_icon            /\$icon/
:highlight link omh_icon          Keyword

:syntax match omh_image           /\$image/
:highlight link omh_image         Keyword

:syntax match omh_include         /\$include/
:highlight link omh_include       Keyword

:syntax match omh_index           /\$index/
:highlight link omh_index         Keyword

:syntax match omh_italic          /\$italic/
:highlight link omh_italic        Keyword

:syntax match omh_latex           /\$latex/
:highlight link omh_latex         Keyword

:syntax match omh_lend            /\$lend/
:highlight link omh_lend          Special

:syntax match omh_linkcolor       /\$linkcolor/
:highlight link omh_linkcolor     Special

:syntax match omh_list            /\$list/
:highlight link omh_list          Special

:syntax match omh_lnext           /\$lnext/
:highlight link omh_lnext         Special

:syntax match omh_math            /\$math/
:highlight link omh_math          Keyword

:syntax match omh_mindex          /\$mindex/
:highlight link omh_mindex        Keyword

:syntax match omh_mref            /\$mref/
:highlight link omh_mref          Keyword

:syntax match omh_navigate        /\$navigate/
:highlight link omh_navigate      Keyword

:syntax match omh_newlinech       /\$newlinech/
:highlight link omh_newlinech     Keyword

:syntax match omh_nobreak         /\$nobreak/
:highlight link omh_nobreak       Keyword

:syntax match omh_nospell         /\$nospell/
:highlight link omh_nospell       Keyword

:syntax match omh_path            /\$path/
:highlight link omh_path          Keyword

:syntax match omh_pre             /\$pre/
:highlight link omh_pre           Keyword

:syntax match omh_rend            /\$rend/
:highlight link omh_rend          Keyword

:syntax match omh_rmark           /\$rmark/
:highlight link omh_rmark         Keyword

:syntax match omh_rnext           /\$rnext/
:highlight link omh_rnext         Special

:syntax match omh_rref            /\$rref/
:highlight link omh_rref          Keyword

:syntax match omh_section         /\$section/
:highlight link omh_section       Keyword

:syntax match omh_skipnl          /\$skipnl/
:highlight link omh_skipnl        Keyword

:syntax match omh_small           /\$small/
:highlight link omh_small         Keyword

:syntax match omh_spell           /\$spell/
:highlight link omh_spell         Keyword

:syntax match omh_subhead         /\$subhead/
:highlight link omh_subhead       Keyword

:syntax match omh_syntax          /\$syntax/
:highlight link omh_syntax        Keyword

:syntax match omh_table           /\$table/
:highlight link omh_table         Special

:syntax match omh_tabsize         /\$tabsize/
:highlight link omh_tabsize       Keyword

:syntax match omh_tend            /\$tend/
:highlight link omh_tend          Special

:syntax match omh_textcolor       /\$textcolor/
:highlight link omh_textcolor     Keyword

:syntax match omh_th              /\$th/
:highlight link omh_th            Keyword

:syntax match omh_title           /\$title/
:highlight link omh_title         Keyword

:syntax match omh_trace           /\$trace/
:highlight link omh_trace         Keyword

:syntax match omh_tref            /\$tref/
:highlight link omh_tref          Keyword

:syntax match omh_verbatim        /\$verbatim/
:highlight link omh_verbatim      Keyword

:syntax match omh_wspace          /\$wspace/
:highlight link omh_wspace        Keyword

:syntax match omh_xref            /\$xref/
:highlight link omh_xref          Keyword

