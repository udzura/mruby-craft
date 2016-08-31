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

void mrb_mruby_craft_class_init(mrb_state *mrb,
                                struct RClass *craft,
                                struct RClass *server,
                                struct RClass *entry);

void mrb_mruby_craft_gem_init(mrb_state *mrb)
{
  struct RClass *craft,
    *server,
    *entry;

  craft = mrb_define_module(mrb, "CRaft");
  mrb_mruby_craft_class_init(mrb,
                             craft,
                             server,
                             entry);

  DONE;
}

void mrb_mruby_craft_gem_final(mrb_state *mrb)
{
}
