#ifndef _UNISTD_H_
#define _UNISTD_H_

struct sgttyb;
struct stat;

int fork(void);
int dup(int fd);
int dup2(int from, int to);
int read(int fd, void *buf, size_t count);
int write(int fd, void *buf, size_t count);
int close(int fd);
int wait(int pid);
int link(char *, char *);
int unlink(char *link);
int exec(char *path, char **argv);
int exece(char *path, char **argv, char **envp);
int chdir(char *path);
size_t time(void);
int alarm(int secs);
int mknod(char *path, int mode, int dev);
int chmod(char *path, int mode);
int chown(char *path, int uid, int gid);
int chroot(char *path);
void *sbreak(size_t inc);
int stat(char *path, struct stat *st);
int fstat(int fd, struct stat *st);
int seek(int fd, size_t off, int whence);
int getpid(void);
int gettid(void);
int mount(char *src, char *target);
int umount(char *target);
int getuid(void);
int getgid(void);
int setuid(int uid);
int setgid(int gid);
int stty(int dev, struct sgttyb *args);
int gtty(int dev, struct sgttyb *args);
int access(char *path, int mode);
int nice(int nice);
int kill(int pid, int sig);

#endif /* !_UNISTD_H_ */
