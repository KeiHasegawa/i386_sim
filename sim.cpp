#include "gdb/callback.h"
#include "gdb/remote-sim.h"
#include <bfd.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

struct sim_state {
  bfd_vma pc;
} obj;

extern "C"
SIM_DESC sim_open(SIM_OPEN_KIND kind, struct host_callback_struct *callback,
		  struct bfd *abfd, char * const *argv)
{
  return &obj;
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

namespace load_impl {
  using namespace std;
  struct info_t {
    string name;
    bfd_vma vma;
    bfd_size_type size;
    bfd_byte* contents;
  };
  ostream* out = &cerr;
  void to_file(const char* fn)
  {
    if (out != &cerr)
      delete out;
    out = new ofstream(fn);
    if (!*out)
      cerr << "Cannot open " << fn << '\n';
  }
  void to_cerr()
  {
    if (out != &cerr)
      delete out;
    out = &cerr;
  }
  inline void debug(const info_t& x)
  {
    auto size = x.size;
    *out << x.name << ' ' << hex << "0x" << x.vma << ' ' << dec << size;
    auto p = x.contents;
    for (int i = 0 ; i != size ; ++i) {
      if (!(i & 15))
	*out << '\n';
      *out << ' ' << setfill('0') << setw(2) << hex << int(p[i]);
    }
    *out << '\n';
  }
  vector<info_t> info;
  void debug(const vector<info_t>& v)
  {
    for (const auto& x : v)
      debug(x);
  }
  inline bool load_if(bfd* bp, bfd_section* sec)
  {
    auto flags = sec->flags;
    if (!(flags & SEC_LOAD))
      return false;

    bfd_byte* buf;
    if (!bfd_malloc_and_get_section(bp, sec, &buf))
      return true;
    
    auto name = sec->name;
    auto vma = sec->vma;
    auto size = sec->size;
    info.push_back(info_t{name, vma, size, buf});
    return false;
  }
} // end of namespace load_impl

extern "C"
SIM_RC sim_load(SIM_DESC sd, const char *prog, struct bfd *abfd, int from_tty)
{
  using namespace load_impl;

  bfd* bp = bfd_openr(prog, nullptr);
  if (!bp)
    return SIM_RC_FAIL;
  struct sweeper {
    bfd* bp;
    sweeper(bfd* p) : bp{p} {}
    ~sweeper(){ bfd_close(bp); }
  } sweeper {bp};

  if (!bfd_check_format(bp, bfd_object))
    return SIM_RC_FAIL;

  for (auto sect = bp->sections; sect ; sect = sect->next) {
    if (load_if(bp, sect))
      return SIM_RC_FAIL;
  }

  return SIM_RC_OK;
}

extern "C"
SIM_RC sim_create_inferior(SIM_DESC sd, struct bfd *abfd,
			   char * const *argv, char * const *env)
{
  sd->pc = abfd->start_address;
  return SIM_RC_OK;
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
