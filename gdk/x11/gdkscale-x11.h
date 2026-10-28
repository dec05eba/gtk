/* GDK - The GIMP Drawing Kit
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "gdktypes.h"

#include <math.h>

#define GDK_X11_SCALE_DEFAULT_DPI 96

typedef struct _GdkX11Scale GdkX11Scale;

struct _GdkX11Scale
{
  int dpi;
};

#define GDK_X11_SCALE_INIT_DPI(dpi) (GdkX11Scale) { MAX ((dpi), GDK_X11_SCALE_DEFAULT_DPI) }
#define GDK_X11_SCALE_INIT_INT(scale) GDK_X11_SCALE_INIT_DPI ((scale) * GDK_X11_SCALE_DEFAULT_DPI)

static inline gboolean
gdk_x11_scale_equal (const GdkX11Scale *a,
                     const GdkX11Scale *b)
{
  return a->dpi == b->dpi;
}

static inline gboolean
gdk_x11_scale_is_integer (const GdkX11Scale *self)
{
  return self->dpi % GDK_X11_SCALE_DEFAULT_DPI == 0;
}

static inline double
gdk_x11_scale_to_double (const GdkX11Scale *self)
{
  return (double) self->dpi / GDK_X11_SCALE_DEFAULT_DPI;
}

static inline int
gdk_x11_scale_position_to_device (const GdkX11Scale *self,
                                  int                position)
{
  return ceil ((double) position * self->dpi / GDK_X11_SCALE_DEFAULT_DPI);
}

static inline int
gdk_x11_scale_size_to_device (const GdkX11Scale *self,
                              int                size)
{
  return floor ((double) size * self->dpi / GDK_X11_SCALE_DEFAULT_DPI);
}

static inline int
gdk_x11_scale_position_from_device (const GdkX11Scale *self,
                                    int                position)
{
  return floor ((double) position * GDK_X11_SCALE_DEFAULT_DPI / self->dpi);
}

static inline int
gdk_x11_scale_size_from_device (const GdkX11Scale *self,
                                int                size)
{
  return ceil ((double) size * GDK_X11_SCALE_DEFAULT_DPI / self->dpi);
}

static inline void
gdk_x11_scale_rect_to_device (const GdkX11Scale  *self,
                              const GdkRectangle *rect,
                              GdkRectangle       *device_rect)
{
  int x = gdk_x11_scale_position_to_device (self, rect->x);
  int y = gdk_x11_scale_position_to_device (self, rect->y);

  device_rect->width = gdk_x11_scale_position_to_device (self, rect->x + rect->width) - x;
  device_rect->height = gdk_x11_scale_position_to_device (self, rect->y + rect->height) - y;
  device_rect->x = x;
  device_rect->y = y;
}

static inline void
gdk_x11_scale_rect_from_device (const GdkX11Scale  *self,
                                const GdkRectangle *device_rect,
                                GdkRectangle       *rect)
{
  int x = gdk_x11_scale_position_from_device (self, device_rect->x);
  int y = gdk_x11_scale_position_from_device (self, device_rect->y);

  rect->width = ceil ((double) (device_rect->x + device_rect->width) * GDK_X11_SCALE_DEFAULT_DPI / self->dpi) - x;
  rect->height = ceil ((double) (device_rect->y + device_rect->height) * GDK_X11_SCALE_DEFAULT_DPI / self->dpi) - y;
  rect->x = x;
  rect->y = y;
}
