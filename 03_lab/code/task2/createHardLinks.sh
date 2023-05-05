#!/bin/bash

gcc -o main main.c my_commands.c
rm -rf  bin
mkdir bin

ln ./main bin/a_create_dir
ln ./main bin/b_print_dir_content
ln ./main bin/c_delete_dir
ln ./main bin/d_create_file
ln ./main bin/e_print_file_content
ln ./main bin/f_delete_file
ln ./main bin/g_create_symlink
ln ./main bin/h_print_symlink_content
ln ./main bin/i_print_target_by_symlink
ln ./main bin/j_remove_symlink
ln ./main bin/k_create_hard_link
ln ./main bin/l_remove_hard_link
ln ./main bin/m_print_perrmission_and_hardlinks_amount
ln ./main bin/n_change_permissions
