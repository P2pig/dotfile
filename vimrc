" Force the cursor onto a new line after 80 characters
set textwidth=80
" However, in Git commit messages, let’s make it 72 characters
autocmd FileType gitcommit set textwidth=72
" Colour the 81st (or 73rd) column so that we don’t type over our limit
set colorcolumn=+1
" In Git commit messages, also colour the 51st column (for titles)
autocmd FileType gitcommit set colorcolumn+=51
autocmd Filetype make setlocal noexpandtab

set hidden
set nu
set relativenumber
highlight ColorColumn ctermbg=8
" highlight Search guibg=peru guifg=wheat
hi Search cterm=NONE guibg=bg ctermfg=black ctermbg=red

syntax enable
set smartindent
set tabstop=4
set shiftwidth=4
set expandtab

" Hot key for switch tabs
map \1 :1tabnext<CR>
map \2 :2tabnext<CR>
map \3 :3tabnext<CR>
map \4 :4tabnext<CR>
map \5 :5tabnext<CR>
map <C-w><C-e> :Explore<CR>
map <C-w><C-t> :tabnew<CR>:Explore<CR>

" netrw
let g:netrw_banner = 0
"let g:netrw_liststyle = 0
