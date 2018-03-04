set nu
set mouse=a
set ruler
set tabstop=4
syntax on
set showcmd
set scrolloff=3
set foldenable
set foldmethod=manual
set fencs=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8
set fileencodings=ucs-bom,utf-8,cp936
set fileencoding=utf-8
set foldcolumn=0
set foldmethod=indent
set foldlevel=3
set foldenable
set confirm
set autoindent
set cindent
set softtabstop=4
set shiftwidth=4
set noexpandtab
set nobackup
set noswapfile
filetype on
filetype indent on
set wildmenu
set backspace=2
set selection=exclusive
set selectmode=mouse,key
set smartindent
:inoremap ( ()<ESC>i
:inoremap ) <c-r>=ClosePair(')')<CR>
:inoremap { {<CR>}<ESC>O
:inoremap } <c-r>=ClosePair('}')<CR>
:inoremap [ []<ESC>i
:inoremap ] <c-r>=ClosePair(']')<CR>
:inoremap " ""<ESC>i
:inoremap ' ''<ESC>i
function! ClosePair(char)
    if getline('.')[col('.')-1]==a:char
		return"\<Right>"
	else
	    return a:char
	endif
endfunction
filetype plugin indent on
set completeopt=longest,menu
autocmd BufNewFile *.cpp,*.[ch],*.sh exec":call SetTitle()"
func SetTitle()
	if &filetype == 'sh'
		call setline(1,"\#########################################################################")
		call append(line("."),"\#FileName: ".expand("%"))
		call append(line(".")+1,"\#Author: liaoxingbin")
		call append(line(".")+2,"\#CreatedTime:".strftime("%c"))
		call append(line(".")+3,"\#########################################################################")
		call append(line(".")+4,"\#!/bin/bash")												        
		call append(line(".")+5,"")
	else
		call setline(1,"/*************************************************************************")
		call append(line("."),">FileName: ".expand("%"))
		call append(line(".")+1,">Author: liaoxingbin")
		call append(line(".")+2,">CreatedTime:".strftime("%c"))
		call append(line(".")+3,"************************************************************************/")
        call append(line(".")+4,"")
	endif
    if &filetype=='cpp'
        call append(line(".")+5,"#include <iostream>")
        call append(line(".")+6,"using namespace std;")
        call append(line(".")+7,"")
    endif
    if &filetype=='c'
       call append(line(".")+5,"#include \"common.h\"")
       call append(line(".")+6,"")
    endif
    autocmd BufNewFile * normal G
endfunc
