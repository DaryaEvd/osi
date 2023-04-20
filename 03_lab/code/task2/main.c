#include "my_commands.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  // argv[1] - command, argv[2] - pathName

  if (strcmp(argv[1], "a_create_dir") == 0) {
    // a_create_dir
    // /home/dasha/masec/osi/labs/03_lab/code/number2/dir_for_trash
    a_create_dir(argv[2]);
  }

  if (strcmp(argv[1], "b_print_dir_content") == 0) {
    // b_print_dir_content
    // /home/dasha/masec/osi/labs/03_lab/code/number2
    b_print_dir_content(argv[2]);
  }

  if (strcmp(argv[1], "c_delete_dir") == 0) {
    // c_delete_dir
    // /home/dasha/masec/osi/labs/03_lab/code/number2/dir_for_trash
    c_delete_dir(argv[2]);
  }

  if (strcmp(argv[1], "d_create_file") == 0) {
    // d_create_file
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    d_create_file(argv[2]);
  }

  if (strcmp(argv[1], "e_print_file_content") == 0) {
    // e_print_file_content
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    e_print_file_content(argv[2]);
  }

  if (strcmp(argv[1], "f_delete_file") == 0) {
    // f_delete_file
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    f_delete_file(argv[2]);
  }

  if (strcmp(argv[1], "g_create_symlink") == 0) {
    // g_create_symlink
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    g_create_symlink(argv[2]);
  }

  if (strcmp(argv[1], "h_print_symlink_content") == 0) {
    // h_print_symlink_content
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    h_print_symlink_content(argv[2]);
  }

  if (strcmp(argv[1], "i_print_target_by_symlink") == 0) {
    // i_print_target_by_symlink
    // /home/dasha/masec/osi/labs/03_lab/code/number2/link_to_newfile.txt
    i_print_target_by_symlink(argv[2]);
  }

  if (strcmp(argv[1], "j_remove_symlink") == 0) {
    // j_remove_symlink
    // /home/dasha/masec/osi/labs/03_lab/code/number2/link_to_newfile.txt

    j_remove_symlink(argv[2]);
  }

  if (strcmp(argv[1], "k_create_hard_link") == 0) {
    // k_create_hard_link
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    k_create_hard_link(argv[2]);
  }

  if (strcmp(argv[1], "l_remove_hard_link") == 0) {
    // l_remove_hard_link
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    l_remove_hard_link(argv[2]);
  }

  if (strcmp(argv[1], "m_print_perrmission_and_hardlinks_amount") ==
      0) {

    // m_print_perrmission_and_hardlinks_amount
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    m_print_perrmission_and_hardlinks_amount(argv[2]);
  }

  if (strcmp(argv[1], "n_change_perrmission_and_hardlinks_amount") ==
      0) {

    // n_change_perrmission_and_hardlinks_amount
    // /home/dasha/masec/osi/labs/03_lab/code/number2/newfile.txt
    n_change_perrmissions(argv[2], argv[3]);
  }



  return 0;
}
