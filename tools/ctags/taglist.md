## vim taglist plugin
```
set nu                                                                                                                                                                                                            
set syntax=on
set cindent
set expandtab
set tabstop=4
set shiftwidth=4
set hlsearch
set nocompatible
set ignorecase
set incsearch
set cursorline
set encoding=utf-8
"set fileencoding=ucs-bom,utf-8,cp936,big5,euc-jp,euc-kr,latin1
filetype on
filetype plugin on
filetype indent on
map <silent> t :TlistToggle<cr>
```
backup:

```
set nu                                                                                                                                          
set syntax=on
set cindent
set expandtab
set tabstop=4
set shiftwidth=4
set hlsearch
set nocompatible
set ignorecase
set incsearch
set cursorline
set encoding=utf-8
set fileencodings=ucs-bom,utf-8,cp936,big5,euc-jp,euc-kr,latin1
filetype on
filetype plugin on
filetype indent on
""""""""""""""""""""""""""""""
" Tag list (ctags)
""""""""""""""""""""""""""""""
"if MySys() == "windows"                "设定windows系统中ctags程序的位置
"let Tlist_Ctags_Cmd = 'ctags'
"elseif MySys() == "linux"              "设定linux系统中ctags程序的位置
"if MySys() == "linux"              "设定linux系统中ctags程序的位置
"let Tlist_Ctags_Cmd = '/usr/bin/ctags'
"endif
let Tlist_Show_One_File = 1            "不同时显示多个文件的tag，只显示当前文件的
let Tlist_Exit_OnlyWindow = 1          "如果taglist窗口是最后一个窗口，则退出vim
"let Tlist_Use_Right_Window = 1         "在右侧窗口中显示taglist窗口 
let Tlist_Use_Left_Window = 1         "在右侧窗口中显示taglist窗口 
map <silent> t :TlistToggle<cr>
set tags+=/home/json-lee/workdir/compile/ElasticActor/tags

```

## Ref
- [advanced vim skills taglist plugin](http://easwy.com/blog/archives/advanced-vim-skills-taglist-plugin/)
- [git link page](https://github.com/ma6174/vim)
