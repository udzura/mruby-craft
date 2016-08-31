#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>

#include <raft.h>

#define DECLARE_RAFT_TYPE(name, data_type_name, raft_type)              \
  typedef struct {                                                      \
    raft_type *data;                                                    \
  } data_type_name;

#define DECLARE_RAFT_CLEANUP(data_type_name, mrb_data_type_varname, free_func_name) \
  static const struct mrb_data_type mrb_data_type_varname = {           \
    #data_type_name, free_func_name,                                    \
  };

#define INITALIZE_RAFT_DATA(data, data_type_name, mrb_data_type_varname) \
    do {                                                                \
      data = (data_type_name *)DATA_PTR(self);                          \
      if (data) {                                                       \
        mrb_free(mrb, data);                                            \
      }                                                                 \
      DATA_TYPE(self) = &mrb_data_type_varname;                         \
      DATA_PTR(self) = NULL;                                            \
      data = (data_type_name *)mrb_malloc(mrb, sizeof(data_type_name)); \
    } while (0)

/* Core class declarations */

DECLARE_RAFT_TYPE(server, mrb_craft_server_data, raft_server_t);
static void mrb_craft_server_free(mrb_state *mrb, void* p)
{
  mrb_craft_server_data *srv = (mrb_craft_server_data *)p;
  raft_free(srv->data);
}
DECLARE_RAFT_CLEANUP(mrb_craft_server_data, mrb_craft_server_data_type, mrb_craft_server_free);

DECLARE_RAFT_TYPE(entry, mrb_craft_entry_data, raft_entry_t);
DECLARE_RAFT_CLEANUP(mrb_craft_entry_data, mrb_craft_entry_data_type, mrb_free);

static mrb_value mrb_craft_server_init(mrb_state *mrb, mrb_value self)
{
  mrb_craft_server_data *data;
  INITALIZE_RAFT_DATA(data, mrb_craft_server_data, mrb_craft_server_data_type);

  data->data = raft_new();
  DATA_PTR(self) = data;
  return self;
}

static mrb_value mrb_craft_entry_init(mrb_state *mrb, mrb_value self)
{
  mrb_craft_entry_data *data;
  raft_entry_t e;
  INITALIZE_RAFT_DATA(data, mrb_craft_entry_data, mrb_craft_entry_data_type);

  data->data = &e;
  DATA_PTR(self) = data;
  return self;
}

void mrb_mruby_craft_class_init(mrb_state *mrb,
                                struct RClass *craft,
                                struct RClass *server,
                                struct RClass *entry)
{
  server = mrb_define_class_under(mrb, craft, "Server", mrb->object_class);
  mrb_define_method(mrb, server, "initialize", mrb_craft_server_init, MRB_ARGS_NONE());

  entry = mrb_define_class_under(mrb, craft, "Entry", mrb->object_class);
  mrb_define_method(mrb, entry, "initialize", mrb_craft_entry_init, MRB_ARGS_NONE());
}
