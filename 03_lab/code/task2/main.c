#include "my_commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extractLastToken(const char *inputPathToBin) {
  int amountSymbolsInLastToken = 0;

  for (int i = strlen(inputPathToBin) - 1; i > 0; i--) {
    if (inputPathToBin[i] == '/') {
      break;
    }
    amountSymbolsInLastToken++;
  }

  char *lastToken =
      calloc(amountSymbolsInLastToken + 1, sizeof(char));

  for (int i = 0; i < amountSymbolsInLastToken; i++) {
    lastToken[i] = inputPathToBin[i + (strlen(inputPathToBin) -
                                       amountSymbolsInLastToken)];
  }

  return lastToken;
}

/*
TODO: 
  - почему нельзя создать симлинку на директорию?
  - можно ли создать симлинку на симлинку?
  - можно ли создать хардлинку на симлинку?
  - можно ли создать хардлинку на директорию?
  и еще какие-нить компибнации... 
*/

int main(int argc, char **argv) {
  // printf("%s\n", argv[0]);
  // argv[0] - command, argv[1] - pathName

  const char *inputPathToBin = argv[0];

  char *lastToken = extractLastToken(inputPathToBin);

  if (strcmp(lastToken, "a_create_dir") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    a_create_dir(argv[1]);
  }

  if (strcmp(lastToken, "b_print_dir_content") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    b_print_dir_content(argv[1]);
  }

  if (strcmp(lastToken, "c_delete_dir") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    c_delete_dir(argv[1]);
  }

  if (strcmp(lastToken, "d_create_file") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    d_create_file(argv[1]);
  }

  if (strcmp(lastToken, "e_print_file_content") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    e_print_file_content(argv[1]);
  }

  if (strcmp(lastToken, "f_delete_file") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    f_delete_file(argv[1]);
  }

  if (strcmp(lastToken, "g_create_symlink") == 0) {
    if (argc != 3) {
      printf("Bad amount of argc\n");
      return 0;
    }
    g_create_symlink(argv[1], argv[2]);
  }

  if (strcmp(lastToken, "h_print_symlink_content") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    h_print_symlink_content(argv[1]);
  }

  if (strcmp(lastToken, "i_print_target_by_symlink") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    i_print_target_by_symlink(argv[1]);
  }

  if (strcmp(lastToken, "j_remove_symlink") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    j_remove_symlink(argv[1]);
  }

  if (strcmp(lastToken, "k_create_hard_link") == 0) {
    if (argc != 3) {
      printf("Bad amount of argc\n");
      return 0;
    }
    k_create_hard_link(argv[1], argv[2]);
  }

  if (strcmp(lastToken, "l_remove_hard_link") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    l_remove_hard_link(argv[1]);
  }

  if (strcmp(lastToken,
             "m_print_perrmission_and_hardlinks_amount") == 0) {
    if (argc != 2) {
      printf("Bad amount of argc\n");
      return 0;
    }
    m_print_perrmission_and_hardlinks_amount(argv[1]);
  }

  if (strcmp(argv[0], "n_change_permissions") == 0) {
    if (argc != 3) {
      printf("Bad amount of argc\n");
      return 0;
    }
    n_change_permissions(argv[1], argv[2]);
  }

  return 0;
}
