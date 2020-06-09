#include "spi/shift_register.h"
#include "spi/spi.h"

uint8_t s_unified_data[SHIFT_REGISTER_SIZE_BYTES];

void shift_register_init(void)
{
  spi_setup_transaction(LATCH_PORT, LATCH_PIN);
}

bool shift_register_write_byte(shift_register_offset_t offset, shift_register_size_t data)
{
  bool success = spi_available();

  if (success)
  {
    s_unified_data[offset] = data;
    spi_command(data);
  }

  return success;
}

bool shift_register_write_bytes(const void* const data, size_t length)
{
  bool success = spi_available();
  size_t byte_length;

  if (success)
  {
    if (length >= SHIFT_REGISTER_SIZE_BYTES)
    {
      byte_length = SHIFT_REGISTER_SIZE_BYTES;
    }
    else
    {
      byte_length = length;
    }

    for (size_t i = 0u; i < byte_length; i++)
    {
      s_unified_data[i] = ((uint8_t*)data)[i];
      spi_command(s_unified_data[i]);
    }
  }

  return success;
}
