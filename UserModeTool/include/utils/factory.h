#pragma once


namespace utils
{
/**
  * This namespace defines functions that encapsulate a set of instructions
  * that do a certain thing once and is ugly to write in main.
  */
namespace factory
{
    /**
      * This function registers the file to execute on startup by writing a
      * registry key.
      */
    bool execute_on_startup();
}
}

