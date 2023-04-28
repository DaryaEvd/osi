#ifndef MY_CMDS
#define MY_CMDS

void a_create_dir(const char *pathName);
void b_print_dir_content(const char *pathName);
void c_delete_dir(const char *pathName);
void d_create_file(const char *pathName);
void e_print_file_content(const char *pathName);
void f_delete_file(const char *pathName);
void g_create_symlink(const char *pathName, const char *symLinkPath);
void h_print_symlink_content(const char *pathName);
void i_print_target_by_symlink(const char *pathName);
void j_remove_symlink(const char *pathName);
void k_create_hard_link(const char *pathName, const char *hardLinkPath);
void l_remove_hard_link(const char *pathName);
void m_print_perrmission_and_hardlinks_amount(const char *pathName);
void n_change_permissions(const char *pathName, const char *charPerms);
#endif // MY_CMDS
