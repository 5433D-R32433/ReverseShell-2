#include <ntddk.h>


/**
  * This is a hook structure. It is used to save important information
  * about a specific hook.
  */
typedef struct SSTHook
{
    ULONG func_index;   /// Index of hooked function in SSDT
    PVOID org_func;     /// Pointer to original function
    PVOID new_func;     /// Pointer to new function
} s_SSTHook;

/**
  * Function creates and applies a hook using WCHAR function name.
  * @param[in,out] hook - hook struct to initialize and apply
  * @param[in] new_func_ptr - pointer to overriding function
  * @param[in] org_func_name - name of function to hook
  * @param[in] org_func_name_len - length of originalFuncName in bytes.
  * @return On failure, 0 is returned.
  *         Otherwise, 1 is returned.
  */
int ssdt_hook_w(s_SSTHook *hook,
                PVOID new_func_ptr,
                WCHAR * org_func_name,
                size_t org_func_name_len);

/**
  * Function creates and applies a hook using UNICODE_STRING function name.
  * @param[in,out] hook - hook struct to initialize and apply
  * @param[in] new_func_ptr - pointer to overriding function
  * @param[in] org_func_name - name of function to hook
  * @return On failure, 0 is returned.
  *         Otherwise, 1 is returned.
  */
int ssdt_hook_u(s_SSTHook *hook,
                PVOID new_func_ptr,
                PUNICODE_STRING org_func_name);

/**
  * Function initializes a hook structure.
  * @param[out] hook - hook struct to initialize
  * @param[in] new_func_ptr - pointer to overriding function
  * @param[in] org_func_name - name of function to hook
  * @return On failure, 0 is returned.
  *         Otherwise, 1 is returned.
  */
int create_hook(s_SSTHook *hook,
                PVOID new_func_ptr,
                PUNICODE_STRING org_func_name);

/**
  * This function changes a pointer in SSDT according to
  * hook structure.
  * @param[in] hook - hook structure to apply.
  * @return On failure, 0 is returned.
  *         Otherwise, 1 is returned.
  */
int apply_hook(s_SSTHook *hook);

/**
  * Function removes SSDT hook (opposite of apply_hook).
  * @param[in] hook - hook struct to disclaim
  * @return On failure, 0 is returned.
  *         Otherwise, 1 is returned.
  */
int disclaim_hook(s_SSTHook *hook);

/**
  * Function clears CR0's Write Protection bit
  */
void clear_wp_bit();

/**
  * Function sets CR0's Write Protection bit
  */
void set_wp_bit();
