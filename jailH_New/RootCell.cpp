/*
 * Module consists of getters and setters for RootCell specific configuration
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "RootCell.h"

Hypervisor_Memory RootCell::get_Hypervisor_Memory() const
{ 
  return hypervisor_memory; 
}

Debug_Console RootCell::get_Debug_Console() const
{
  return debug_console;
}

Platform_Info RootCell::get_Platform_Info() const
{
  return platform_info;
}

void RootCell::set_Hypervisor_Memory(Hypervisor_Memory & hvm)
{
  hypervisor_memory = hvm; 
}

void RootCell::set_Debug_Console(Debug_Console & dc)
{
  debug_console = dc;
}
void RootCell::set_Platform_Info(Platform_Info & pi)
{
  platform_info = pi;
}

RootCell::~RootCell() {}
