#pragma once


/**
  * This function installs hide hooks.
  * Call ssdt_utils_init before calling this function.
  * @return If all hooks were installed successfully, 1 is returned.
  *         Otherwise, 0 is returned.
  */
int hide_install();

/**
  * This function removes hide hooks.
  * @return If all hooks were removed successfully, 1 is returned.
  *         Otherwise, 0 is returned.
  */
int hide_remove();
