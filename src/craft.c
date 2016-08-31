/*
** mrb_craft.c - CRaft class
**
** Copyright (c) Uchio Kondo 2016
**
** See Copyright Notice in LICENSE
*/

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>

#include <raft.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

void mrb_mruby_craft_class_init(mrb_state *mrb, struct RClass *craft, struct RClass *entry);

typedef struct {
  raft_server_t *srv;
} mrb_craft_server_data;

static void mrb_craft_server_free(mrb_state *mrb, void* p)
{
  mrb_craft_server_data *srv = (mrb_craft_server_data *)p;
  raft_free(srv->srv);
}

static const struct mrb_data_type mrb_craft_server_data_type = {
  "mrb_craft_server_data", mrb_craft_server_free,
};

static mrb_value mrb_craft_server_init(mrb_state *mrb, mrb_value self)
{
  mrb_craft_server_data *data;

  data = (mrb_craft_server_data *)DATA_PTR(self);
  if (data) {
    raft_free(data->srv);
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_craft_server_data_type;
  DATA_PTR(self) = NULL;

  data = (mrb_craft_server_data *)mrb_malloc(mrb, sizeof(mrb_craft_server_data));
  data->srv = raft_new();
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_craft_hello(mrb_state *mrb, mrb_value self)
{
  mrb_craft_server_data *srv = DATA_PTR(self);

  return mrb_str_new_lit(mrb, "Hello");
}

void mrb_mruby_craft_gem_init(mrb_state *mrb)
{
  struct RClass *craft, *server, *entry;
  craft = mrb_define_module(mrb, "CRaft");
  server = mrb_define_class_under(mrb, craft, "Server", mrb->object_class);

  mrb_define_method(mrb, server, "initialize", mrb_craft_server_init, MRB_ARGS_NONE());

  mrb_mruby_craft_class_init(mrb, craft, entry);

  DONE;
}

void mrb_mruby_craft_gem_final(mrb_state *mrb)
{
}
