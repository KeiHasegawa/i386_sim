#include "gdb/callback.h"
#include "gdb/remote-sim.h"

extern "C"
SIM_DESC sim_open(SIM_OPEN_KIND kind, struct host_callback_struct *callback,
		  struct bfd *abfd, char * const *argv)
{
  asm("int3");
  return 0;
}

extern "C"
void sim_close(SIM_DESC sd, int quitting)
{
  asm("int3");
}

extern "C"
int sim_fetch_register(SIM_DESC sd, int regno, unsigned char *buf, int length)
{
  asm("int3");
  return 0;
}

extern "C"
int sim_store_register(SIM_DESC sd, int regno, unsigned char *buf, int length)
{
  asm("int3");
  return 0;
}

extern "C"
SIM_RC sim_load(SIM_DESC sd, const char *prog, struct bfd *abfd, int from_tty)
{
  asm("int3");
  return SIM_RC(0);
}

extern "C"
SIM_RC sim_create_inferior(SIM_DESC sd, struct bfd *abfd,
			   char * const *argv, char * const *env)
{
  asm("int3");
  return SIM_RC(0);
}

extern "C"
int sim_stop(SIM_DESC sd)
{
  asm("int3");
  return 0;
}

extern "C"
void sim_resume(SIM_DESC sd, int step, int siggnal)
{
  asm("int3");  
}

extern "C"
void sim_stop_reason(SIM_DESC sd, enum sim_stop *reason, int *sigrc)
{
  asm("int3");  
}

extern "C"
int sim_write(SIM_DESC sd, SIM_ADDR mem, const unsigned char *buf, int length)
{
  asm("int3");
  return 0;
}

extern "C"
int sim_read(SIM_DESC sd, SIM_ADDR mem, unsigned char *buf, int length)
{
  asm("int3");
  return 0;
}

extern "C"
void sim_info(SIM_DESC sd, int verbose)
{
  asm("int3");
}

extern "C"
void sim_do_command(SIM_DESC sd, const char *cmd)
{
  asm("int3");
}


extern "C"
char **sim_complete_command(SIM_DESC sd, const char *text, const char *word)
{
  asm("int3");
  return nullptr;
}

CB_TARGET_DEFS_MAP cb_init_syscall_map[] = {
  { 0, -1, -1 }
};

CB_TARGET_DEFS_MAP cb_init_open_map[] = {
  { 0, -1, -1 }
};

CB_TARGET_DEFS_MAP cb_init_errno_map[] = {
  { 0, 0, 0 }
};
