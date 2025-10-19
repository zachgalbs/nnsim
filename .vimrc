" nnsim project-specific F5 shortcut
nnoremap <F5> :w<CR>:!clear && mkdir -p build && cd build && (test -f Makefile \|\| cmake ..) && make && ./nnsim<CR>
