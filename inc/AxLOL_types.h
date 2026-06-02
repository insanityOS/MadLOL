/*! @file AxLOL_types.h
 *  @brief AxLOL Base type definitions.
 *
 * Definitions for AxLOL basic types, including status returns.
 */

#ifndef AXLOL_TYPES_H
#define AXLOL_TYPES_H

#include <stdint.h>

/*! @brief Status enumeration definition.
 *
 * Enumeration for AxLOL Status returns. For variable declaration, please use
 * @ref AxLOL_Status_t instead; this definition is intended for value
 * definitions.
 *
 *  @var AxLOL_Status_e::LOL_SUCCESS
 * Operation reports successfully. Seee specific functions for further details.
 *
 *  @var AxLOL_Status_e::LOL_NULLPTR
 * Operation failed due to an unexpected null pointer.
 */
typedef enum {
  LOL_SUCCESS = 0,
  LOL_NULLPTR = 1,
} AxLOL_Status_e;

/*! @brief Status type definition.
 *
 * Type for AxLOL Status returns. Would that C23 were more widespread.
 *
 * For actual values of this type, see the enumeration @ref AxLOL_Status_e.
 */
typedef uint16_t AxLOL_Status_t;

#endif
