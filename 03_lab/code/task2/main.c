#include "my_commands.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  // printf("%s\n", argv[0]);
  // argv[0] - command, argv[1] - pathName

  if (strcmp(argv[0], "./bin/a_create_dir") == 0) {
    a_create_dir(argv[0]);
  }

  if (strcmp(argv[0], "./bin/b_print_dir_content") == 0) {
    b_print_dir_content(argv[0]);
  }

  if (strcmp(argv[0], "./bin/c_delete_dir") == 0) {
    c_delete_dir(argv[1]);
  }

  if (strcmp(argv[0], "./bin/d_create_file") == 0) {
    d_create_file(argv[1]);
  }

  if (strcmp(argv[0], "./bin/e_print_file_content") == 0) {
    e_print_file_content(argv[1]);
  }

  if (strcmp(argv[0], "./bin/f_delete_file") == 0) {
    f_delete_file(argv[1]);
  }

  if (strcmp(argv[0], "./bin/g_create_symlink") == 0) {
    g_create_symlink(argv[1]);
  }

  if (strcmp(argv[0], "./bin/h_print_symlink_content") == 0) {
    h_print_symlink_content(argv[1]);
  }

  if (strcmp(argv[0], "./bin/i_print_target_by_symlink") == 0) {
    i_print_target_by_symlink(argv[1]);
  }

  if (strcmp(argv[0], "./bin/j_remove_symlink") == 0) {

    j_remove_symlink(argv[1]);
  }

  // TODO: add target
  if (strcmp(argv[0], "./bin/k_create_hard_link") == 0) {
    k_create_hard_link(argv[1]);
  }

  if (strcmp(argv[0], "./bin/l_remove_hard_link") == 0) {
    l_remove_hard_link(argv[1]);
  }

  if (strcmp(argv[0],
             "./bin/m_print_perrmission_and_hardlinks_amount") == 0) {

    m_print_perrmission_and_hardlinks_amount(argv[1]);
  }

  if (strcmp(argv[0],
             "./bin/n_change_perrmission_and_hardlinks_amount") ==
      0) {

    n_change_perrmissions(argv[1], argv[3]);
  }

  return 0;
}
