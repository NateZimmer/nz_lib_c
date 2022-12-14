
#include "ring_buf.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief initialize ring buffer
 * @param[in] buf - Pointer to ring buf struct, see ring_buf_t
 * @param[in] len - Length of buffer in bytes
 */
void ring_buf_init(ring_buf_t *buf, uint16_t len)
{
  if(buf == NULL)
    return;
  if(buf->data != NULL)
    return;
  buf->data = malloc(len);
  if(buf->data == NULL)
    return;
  buf->head = buf->data;
  buf->tail = buf->data;
  buf->total_size = len;
  memset(buf->data, 0, len);
}

/**
 * @brief gets the length of bytes in buffer
 * @param[in] buf - Pointer to ring buf struct, see ring_buf_t
 */
uint16_t ring_buf_len(ring_buf_t *buf) { return buf->head >= buf->tail ? (buf->head - buf->tail) : ((buf->total_size + buf->data) - buf->tail) + (buf->head - buf->data); }

/**
 * @brief add bytes into ring buffer
 * @param[in] buf - Pointer to ring buf struct, see ring_buf_t
 * @param[in] data - Pointer to buffer to be filled into ring buffer
 * @param[in] len - length of data in bytes
 * @return overflow, true if an overflow occurred
 */
bool ring_buf_add(ring_buf_t *buf, uint8_t *data, uint16_t len)
{
  bool overflow = false;
  for(int i = 0; i < len; i++)
  {
    *(buf->head++) = data[i];
    buf->head = buf->head >= (buf->data + buf->total_size) ? buf->data : buf->head; // wrap if needed
    if(buf->head == buf->tail)
    {
      overflow = true;
    }
  }
  return overflow;
}

/**
 * @brief get bytes from ring buffer
 * @param[in] buf - Pointer to ring buf struct, see ring_buf_t
 * @param[out] data - Pointer to buffer to be filled into ring buffer
 * @param[in] len - length of data in bytes
 * @return bytes read, will be less than len if amount in buffer is less than len
 */
uint16_t ring_buf_get(ring_buf_t *buf, uint8_t *data, uint16_t len)
{
  uint16_t bytes_read = 0;
  for(int i = 0; i < len; i++)
  {
    if(buf->head == buf->tail)
    {
      break;
    }
    data[i] = *(buf->tail++);
    bytes_read++;
    buf->tail = buf->tail >= (buf->data + buf->total_size) ? buf->data : buf->tail; // wrap if needed
  }
  return bytes_read;
}

/**
 * @brief clears out data in buffer
 * @param[in] buf - Pointer to ring buf struct, see ring_buf_t
 */
void ring_buf_reset(ring_buf_t *buf)
{
  buf->head = buf->tail;
  int i = 0;
}
