namespace methods
{
namespace screenshot
{
/**
  * Use this function to get the origin and dimensions of the virtual screen.
  * For more information, visit
  * https://msdn.microsoft.com/en-us/library/windows/desktop/dd145136(v=vs.85).aspx
  *
  * @param[out] upper_left_x - where screen.origin.x will be stored.
  * @param[out] upper_left_y - where screen.origin.y will be stored.
  * @param[out] width        - where screen.width will be stored.
  * @param[out] height       - where screen.height will be stored.
  * @return None.
  */
static void GetVirtualScreenRectangle(uint32_t *upper_left_x,
                                      uint32_t *upper_left_y,
                                      uint32_t *width,
                                      uint32_t *height);
}
}

void
methods::screenshot::GetVirtualScreenRectangle(
    uint32_t *upper_left_x,
    uint32_t *upper_left_y,
    uint32_t *width,
    uint32_t *height)
{
    *upper_left_x   = GetSystemMetrics(SM_XVIRTUALSCREEN);
    *upper_left_y   = GetSystemMetrics(SM_YVIRTUALSCREEN);
    *width          = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    *height         = GetSystemMetrics(SM_CYVIRTUALSCREEN);
}
